#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

// Метод Борда
string borda_method(const vector<vector<string>>& votes, const vector<string>& candidates) {
    unordered_map<string, int> score;
    int n = candidates.size();

    for (const auto& vote : votes) {
        for (int i = 0; i < n; ++i) {
            score[vote[i]] += n - i - 1;
        }
    }

    return max_element(score.begin(), score.end(),
        [](const auto& a, const auto& b) { return a.second < b.second; })->first;
}

// Метод Кондорсе
string condorcet_method(const vector<vector<string>>& votes, const vector<string>& candidates) {
    int n = candidates.size();
    unordered_map<string, unordered_map<string, int>> wins;

    for (const auto& vote : votes) {
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                wins[vote[i]][vote[j]]++;
            }
        }
    }

    for (const auto& cand1 : candidates) {
        bool winner = true;
        for (const auto& cand2 : candidates) {
            if (cand1 == cand2) continue;
            if (wins[cand1][cand2] <= wins[cand2][cand1]) {
                winner = false;
                break;
            }
        }
        if (winner) return cand1;
    }
    return "Нет победителя по Кондорсе";
}

int main() {
    int n, k;
    cout << "Введите количество кандидатов и избирателей: ";
    cin >> n >> k;

    vector<string> candidates(n);
    cout << "Введите имена кандидатов:\n";
    for (int i = 0; i < n; ++i) {
        cin >> candidates[i];
    }

    vector<vector<string>> votes(k, vector<string>(n));
    cout << "Введите предпочтения избирателей (по " << n << " кандидатов в строке):\n";
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> votes[i][j];
        }
    }

    string borda_winner = borda_method(votes, candidates);
    string condorcet_winner = condorcet_method(votes, candidates);

    cout << "\nПобедитель по методу Борда: " << borda_winner << "\n";
    cout << "Победитель по методу Кондорсе: " << condorcet_winner << "\n";

    if (borda_winner != condorcet_winner && condorcet_winner != "Нет победителя по Кондорсе") {
        cout << "Разные алгоритмы дали разные результаты.\n";
    }

    return 0;
}
