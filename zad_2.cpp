#include <iostream>
#include <random>
#include <iomanip>
#include <cmath>
#include <string>
using namespace std;

// Меняет первый и последний разряд в числе (если больше 1 цифры)
int swapDigits(int number) {
    if (number < 10) return number;
    string s = to_string(number);
    swap(s[0], s[s.length() - 1]);
    return stoi(s);
}

int main() {
    int n1, n2;
    cout << "Введите размер первого массива (n1 >= 10): ";
    cin >> n1;
    if (n1 < 10) {
        cerr << "Ошибка: n1 должно быть >= 10\n";
        return 1;
    }

    cout << "Введите размер второго массива (n2 >= 50): ";
    cin >> n2;
    if (n2 < 50) {
        cerr << "Ошибка: n2 должно быть >= 50\n";
        return 1;
    }

    double arr1[1000];
    int arr2[1000];

    // Инициализация генератора ranlux24
    random_device rd;
    ranlux24 gen(rd());
    uniform_real_distribution<> real_dist(0.0, 100.0);
    uniform_int_distribution<> int_dist(-10, 10);

    // 1. Заполнение первого массива
    for (int i = 0; i < n1; ++i)
        arr1[i] = real_dist(gen);

    cout << "\nПервый массив (вещественные числа):\n";
    for (int i = 0; i < n1; ++i)
        cout << fixed << setprecision(2) << arr1[i] << " ";
    cout << "\n";

    // 2. Среднее и сумма квадратов отклонений
    double sum = 0;
    for (int i = 0; i < n1; ++i)
        sum += arr1[i];
    double avg = sum / n1;

    double sq_sum = 0;
    for (int i = 0; i < n1; ++i)
        sq_sum += pow(arr1[i] - avg, 2);

    cout << "\nСреднее значение: " << avg << "\n";
    cout << "Сумма квадратов разностей: " << sq_sum << "\n";

    // 3. Замена разрядов в четных элементах с четным индексом
    for (int i = 0; i < n1; ++i) {
        int val = (int)arr1[i];
        if (i % 2 == 0 && val % 2 == 0)
            arr1[i] = swapDigits(val);
    }

    cout << "\nПосле замены разрядов:\n";
    for (int i = 0; i < n1; ++i)
        cout << arr1[i] << " ";
    cout << "\n";

    // 4. Перемещение первого элемента в конец
    double first = arr1[0];
    for (int i = 0; i < n1 - 1; ++i)
        arr1[i] = arr1[i + 1];
    arr1[n1 - 1] = first;

    cout << "\nПосле модификации (первый в конец):\n";
    for (int i = 0; i < n1; ++i)
        cout << arr1[i] << " ";
    cout << "\n";

    // 5. Заполнение второго массива
    for (int i = 0; i < n2; ++i)
        arr2[i] = int_dist(gen);

    cout << "\nВторой массив (целые числа):\n";
    for (int i = 0; i < n2; ++i)
        cout << arr2[i] << " ";
    cout << "\n";

    // Подсчёт повторов
    int counts[21] = {0}; // Индексы 0..20 для чисел -10..10
    for (int i = 0; i < n2; ++i)
        counts[arr2[i] + 10]++;

    cout << "\nЧастоты элементов:\n";
    for (int i = 0; i <= 20; ++i)
        if (counts[i] > 0)
            cout << (i - 10) << ": " << counts[i] << "\n";

    // Удаление повторов
    int uniqueArr[21];
    int uniqueCount = 0;
    bool seen[21] = {false};

    for (int i = 0; i < n2; ++i) {
        int idx = arr2[i] + 10;
        if (!seen[idx]) {
            seen[idx] = true;
            uniqueArr[uniqueCount++] = arr2[i];
        }
    }

    cout << "\nМассив без повторов:\n";
    for (int i = 0; i < uniqueCount; ++i)
        cout << uniqueArr[i] << " ";
    cout << "\n";

    return 0;
}
