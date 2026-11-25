// student.cpp — реалізація функцій
#include <iostream>
#include "student.h"
using namespace std;

// вводить ціле число від min до max, поки користувач не введе правильно
int InputInt(const string prompt, const int min, const int max)
{
    int x;
    while (true)
    {
        cout << prompt;
        if (cin >> x && x >= min && x <= max)
        {
            cin.ignore(1000, '\n');   // видаляємо решту рядка
            return x;
        }
        cin.clear();                  // скидаємо помилку введення
        cin.ignore(1000, '\n');       // видаляємо неправильні символи
        cout << "Помилка! Введіть ціле число від "
             << min << " до " << max << "." << endl;
    }
}

// вводить спеціальність (з перевіркою)
Spec InputSpec()
{
    cout << "   0 - Комп'ютерні науки, 1 - Інформатика," << endl
         << "   2 - Математика та економіка, 3 - Фізика та інформатика," << endl
         << "   4 - Трудове навчання" << endl;
    return (Spec)InputInt("   спеціальність: ", 0, 4);
}

// введення даних про студентів з клавіатури
void Create(Student* p, const int N)
{
    for (int i = 0; i < N; i++)
    {
        cout << "Студент № " << i + 1 << ":" << endl;
        cout << "   прізвище: ";
        cin >> p[i].prizv;
        cin.ignore(1000, '\n');
        p[i].kurs = InputInt("   курс (від 1 до 6): ", 1, 6);
        p[i].spec = InputSpec();
        p[i].fizyka = InputInt("   оцінка з фізики (1-5): ", 1, 5);
        p[i].matem = InputInt("   оцінка з математики (1-5): ", 1, 5);
        p[i].inform = InputInt("   оцінка з інформатики (1-5): ", 1, 5);
        cout << endl;
    }
}

// вивід шапки таблиці
void PrintHeader()
{
    cout << "Список студентів групи" << endl;
    cout << string(97, '=') << endl;
    cout << "| " << Pad("№", 3)
         << " | " << Pad("Прізвище", 15)
         << " | " << Pad("Курс", 4)
         << " | " << Pad("Спеціальність", 24)
         << " | " << Pad("Фізика", 7)
         << " | " << Pad("Математика", 10)
         << " | " << Pad("Інформатика", 12) << " |" << endl;
    cout << string(97, '-') << endl;
}

// вивід одного рядка таблиці
void PrintRow(const Student s, const int number)
{
    cout << "| " << Pad(to_string(number), 3)
         << " | " << Pad(s.prizv, 15)
         << " | " << Pad(to_string(s.kurs), 4)
         << " | " << Pad(SpecName(s.spec), 24)
         << " | " << Pad(to_string(s.fizyka), 7)
         << " | " << Pad(to_string(s.matem), 10)
         << " | " << Pad(to_string(s.inform), 12) << " |" << endl;
}

// вивід нижньої лінії таблиці
void PrintFooter()
{
    cout << string(97, '=') << endl << endl;
}

// вивід масиву студентів у вигляді таблиці
void Print(Student* p, const int N)
{
    PrintHeader();
    for (int i = 0; i < N; i++)
        PrintRow(p[i], i + 1);
    PrintFooter();
}

// вивід масиву в порядку, який задає індексний масив I
void PrintIndexSorted(Student* p, int* I, const int N)
{
    PrintHeader();
    for (int i = 0; i < N; i++)
        PrintRow(p[I[i]], i + 1);
    PrintFooter();
}

// повертає назву спеціальності
string SpecName(const Spec spec)
{
    switch (spec)
    {
    case KN: return "Комп'ютерні науки";
    case IN: return "Інформатика";
    case ME: return "Математика та економіка";
    case FI: return "Фізика та інформатика";
    case TN: return "Трудове навчання";
    }
    return "";
}

// доповнює рядок пробілами до ширини width символів
// (на Mac кирилична літера займає 2 байти, тому setw не підходить,
//  а тут ми рахуємо саме символи, а не байти)
string Pad(const string s, const int width)
{
    int len = 0;
    for (unsigned i = 0; i < s.length(); i++)
        if ((s[i] & 0xC0) != 0x80)   // рахуємо тільки перші байти символів
            len++;

    string result = s;
    for (int i = len; i < width; i++)
        result += " ";
    return result;
}

// чи студент a має стояти після студента b при порядку:
// курс (зростання), спеціальність (зростання), прізвище (зростання)
bool IsGreater(const Student a, const Student b)
{
    return (a.kurs > b.kurs)
        || (a.kurs == b.kurs && a.spec > b.spec)
        || (a.kurs == b.kurs && a.spec == b.spec && a.prizv > b.prizv);
}

// чи треба поміняти місцями сусідніх студентів a і b при фізичному
// впорядкуванні: курс (зростання), спеціальність (зростання),
// прізвище (спадання)
bool MustSwap(const Student a, const Student b)
{
    return (a.kurs > b.kurs)
        || (a.kurs == b.kurs && a.spec > b.spec)
        || (a.kurs == b.kurs && a.spec == b.spec && a.prizv < b.prizv);
}

// фізичне впорядкування масиву (метод "бульбашки")
void Sort(Student* p, const int N)
{
    Student tmp;
    for (int i0 = 0; i0 < N - 1; i0++)
        for (int i1 = 0; i1 < N - i0 - 1; i1++)
            if (MustSwap(p[i1], p[i1 + 1]))
            {
                tmp = p[i1];
                p[i1] = p[i1 + 1];
                p[i1 + 1] = tmp;
            }
}

// повертає індексний масив (метод вставки): сам масив p не змінюється
int* IndexSort(Student* p, const int N)
{
    int* I = new int[N];       // створили індексний масив
    for (int i = 0; i < N; i++)
        I[i] = i;              // заповнили початковими даними

    int i, j, value;
    for (i = 1; i < N; i++)
    {
        value = I[i];
        for (j = i - 1; j >= 0 && IsGreater(p[I[j]], p[value]); j--)
            I[j + 1] = I[j];
        I[j + 1] = value;
    }
    return I;
}

// бінарний пошук за індексним масивом I (курс, спеціальність, прізвище)
// повертає номер елемента в масиві p або -1, якщо студента немає
int BinSearch(Student* p, int* I, const int N,
              const string prizv, const int kurs, const Spec spec)
{
    Student key = {};          // студент із шуканими даними
    key.prizv = prizv;
    key.kurs = kurs;
    key.spec = spec;

    int L = 0, R = N - 1, m;
    while (L <= R)
    {
        m = (L + R) / 2;
        if (IsGreater(p[I[m]], key))
            R = m - 1;
        else if (IsGreater(key, p[I[m]]))
            L = m + 1;
        else
            return I[m];
    }
    return -1;
}
