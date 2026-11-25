// main.cpp — головна функція з меню
// Лабораторна робота № 10.2, варіант 2, рівень А
#include <iostream>
#include "student.h"
using namespace std;

int main()
{
    int N = InputInt("Введіть кількість студентів N (від 1 до 100): ", 1, 100);

    Student* p = new Student[N];

    int*   I;          // індексний масив
    int    found;      // результат бінарного пошуку
    string prizv;      // шукане прізвище
    int    kurs;       // шуканий курс
    Spec   spec;       // шукана спеціальність

    int menuItem;
    do {
        cout << endl << endl;
        cout << "Виберіть дію:" << endl << endl;
        cout << " [1] - введення даних з клавіатури (виберіть першим)" << endl;
        cout << " [2] - вивід даних на екран" << endl;
        cout << " [3] - фізичне впорядкування даних" << endl;
        cout << " [4] - індексне впорядкування та вивід даних" << endl;
        cout << " [5] - бінарний пошук студента" << endl << endl;
        cout << " [0] - вихід та завершення роботи програми" << endl << endl;
        menuItem = InputInt("Введіть значення: ", 0, 5);
        cout << endl;

        switch (menuItem)
        {
        case 1:
            Create(p, N);
            break;
        case 2:
            Print(p, N);
            break;
        case 3:
            Sort(p, N);
            cout << "Масив фізично впорядковано." << endl;
            break;
        case 4:
            I = IndexSort(p, N);
            PrintIndexSorted(p, I, N);
            delete[] I;
            break;
        case 5:
            cout << "Введіть прізвище: ";
            cin >> prizv;
            cin.ignore(1000, '\n');
            kurs = InputInt("Введіть курс (від 1 до 6): ", 1, 6);
            spec = InputSpec();

            I = IndexSort(p, N);
            found = BinSearch(p, I, N, prizv, kurs, spec);
            delete[] I;

            if (found != -1)
                cout << "Студента знайдено, номер у таблиці: "
                     << found + 1 << endl;
            else
                cout << "Такого студента немає." << endl;
            break;
        case 0:
            break;
        }
    } while (menuItem != 0);

    delete[] p;
    return 0;
}
