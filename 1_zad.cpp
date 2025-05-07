#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double f(double x) {
    return x * log(x + 2) - 2;
}

double df(double x) {
    return log(x + 2) + x / (x + 2);
}

double phi(double x) {
    return 2.0 / log(x + 2);
}

void bisection(double a, double b, double eps) {
    cout << "\nМетод половинного деления\n";
    cout << left << setw(4) << "N" << setw(12) << "a" << setw(12) << "b" << setw(12) << "b - a" << endl;
    int n = 0;
    while ((b - a) >= eps) {
        double c = (a + b) / 2;
        cout << setw(4) << n << setw(12) << a << setw(12) << b << setw(12) << b - a << endl;
        if (f(a) * f(c) < 0)
            b = c;
        else
            a = c;
        n++;
    }
    cout << "Корень ≈ " << (a + b) / 2 << endl;
}

void newton(double x0, double eps) {
    cout << "\nМетод Ньютона\n";
    cout << left << setw(4) << "N" << setw(14) << "x_n" << setw(14) << "x_n+1" << setw(14) << "|x_n+1 - x_n|" << endl;
    int n = 0;
    while (true) {
        double x1 = x0 - f(x0) / df(x0);
        cout << setw(4) << n << setw(14) << x0 << setw(14) << x1 << setw(14) << fabs(x1 - x0) << endl;
        if (fabs(x1 - x0) < eps) {
            cout << "Корень ≈ " << x1 << endl;
            break;
        }
        x0 = x1;
        n++;
    }
}

void iteration(double x0, double eps) {
    cout << "\nМетод простых итераций\n";
    cout << left << setw(4) << "N" << setw(14) << "x_n" << setw(14) << "x_n+1" << setw(14) << "|x_n+1 - x_n|" << endl;
    int n = 0;
    while (true) {
        double x1 = phi(x0);
        cout << setw(4) << n << setw(14) << x0 << setw(14) << x1 << setw(14) << fabs(x1 - x0) << endl;
        if (fabs(x1 - x0) < eps) {
            cout << "Корень ≈ " << x1 << endl;
            break;
        }
        x0 = x1;
        n++;
    }
}

int main() {
    double a, b, x0, eps;
    cout << "Введите a, b, x0, eps: ";
    cin >> a >> b >> x0 >> eps;

    bisection(a, b, eps);
    newton(x0, eps);
    iteration(x0, eps);

    return 0;
}
