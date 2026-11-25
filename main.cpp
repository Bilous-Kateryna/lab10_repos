// main.cpp — головна функція
// Лабораторна робота № 10.1, варіант 2, рівень А
#include <iostream>
#include "student.h"
using namespace std;

int main()
{
    int N;
    do {
        cout << "Введіть кількість студентів N: ";
        cin >> N;
    } while (N <= 0);

    Student* p = new Student[N];

    Create(p, N);
    Print(p, N);

    int k = CountNoThrees(p, N);
    cout << "Кількість студентів без трійок: " << k << endl;

    double proc = PercentLowAverage(p, N);
    cout << "Процент студентів із середнім балом менше 4: "
         << proc << "%" << endl;

    delete[] p;
    return 0;
}
