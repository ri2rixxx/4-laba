#include <iostream>
#include <vector>

int main() {
    unsigned int X0, A, B, C;
    std::cout << "Введите X0, A, B, C (через пробел): ";
    std::cin >> X0 >> A >> B >> C;

    std::vector<unsigned int> sequence;
    sequence.push_back(X0);

    // Генерируем первые 10 элементов
    for (int i = 1; i < 10; ++i) {
        unsigned int next = (A * sequence.back() + B) % C;
        sequence.push_back(next);
    }

    std::cout << "\nСгенерированная последовательность:\n";
    for (auto x : sequence) std::cout << x << " ";
    std::cout << "\n";

    // Поиск начала периода (где начинается повторяющаяся часть)
    for (int i = 1; i < sequence.size(); ++i) {
        bool match = true;
        for (int j = 0; j + i < sequence.size(); ++j) {
            if (sequence[j] != sequence[j + i]) {
                match = false;
                break;
            }
        }
        if (match) {
            std::cout << i << std::endl;
            return 0;
        }
    }

    std::cout << "Нет повтора в первых 10 элементах.\n";
    return 0;
}
