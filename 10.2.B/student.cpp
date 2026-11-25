// student.cpp — реалізація функцій
#include <iostream>
#include "student.h"
using namespace std;

// вводить ціле число від min до max (з перевіркою)
int InputInt(const string prompt, const int min, const int max)
{
    int x;
    cout << prompt;
    cin >> x;
    while (cin.fail() || x < min || x > max)
    {
        cin.clear();               // знімаємо помилку введення
        cin.ignore(1000, '\n');    // видаляємо неправильні символи
        cout << "Помилка! Введіть число від " << min
             << " до " << max << ": ";
        cin >> x;
    }
    cin.ignore(1000, '\n');        // видаляємо решту рядка
    return x;
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

        // третя оцінка залежить від спеціальності
        switch (p[i].spec)
        {
        case KN:
            p[i].prog = InputInt("   оцінка з програмування (1-5): ", 1, 5);
            break;
        case IN:
            p[i].chys = InputInt("   оцінка з чисельних методів (1-5): ", 1, 5);
            break;
        case ME:
        case FI:
        case TN:
            p[i].ped = InputInt("   оцінка з педагогіки (1-5): ", 1, 5);
            break;
        }
        cout << endl;
    }
}

// вивід шапки таблиці
void PrintHeader()
{
    cout << "Список студентів групи" << endl;
    cout << string(105, '=') << endl;
    cout << "| " << Pad("№", 3)
         << " | " << Pad("Прізвище", 11)
         << " | " << Pad("Курс", 4)
         << " | " << Pad("Спеціальність", 23)
         << " | " << Pad("Фізика", 6)
         << " | " << Pad("Матем.", 6)
         << " | " << Pad("Програм.", 8)
         << " | " << Pad("Чис.мет.", 8)
         << " | " << Pad("Педагог.", 8) << " |" << endl;
    cout << string(105, '-') << endl;
}

// вивід одного рядка таблиці
void PrintRow(const Student s, const int number)
{
    // заповнена тільки одна з трьох останніх клітинок
    string prog = "", chys = "", ped = "";
    switch (s.spec)
    {
    case KN:
        prog = to_string(s.prog);
        break;
    case IN:
        chys = to_string(s.chys);
        break;
    case ME:
    case FI:
    case TN:
        ped = to_string(s.ped);
        break;
    }

    cout << "| " << Pad(to_string(number), 3)
         << " | " << Pad(s.prizv, 11)
         << " | " << Pad(to_string(s.kurs), 4)
         << " | " << Pad(SpecName(s.spec), 23)
         << " | " << Pad(to_string(s.fizyka), 6)
         << " | " << Pad(to_string(s.matem), 6)
         << " | " << Pad(prog, 8)
         << " | " << Pad(chys, 8)
         << " | " << Pad(ped, 8) << " |" << endl;
}

// вивід масиву студентів у вигляді таблиці
void Print(Student* p, const int N)
{
    PrintHeader();
    for (int i = 0; i < N; i++)
        PrintRow(p[i], i + 1);
    cout << string(105, '=') << endl << endl;
}

// вивід масиву в порядку, який задає індексний масив I
void PrintIndexSorted(Student* p, int* I, const int N)
{
    PrintHeader();
    for (int i = 0; i < N; i++)
        PrintRow(p[I[i]], i + 1);
    cout << string(105, '=') << endl << endl;
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

// фізичне впорядкування масиву (метод "бульбашки"):
// курс (зростання), спеціальність (зростання), прізвище (спадання)
void Sort(Student* p, const int N)
{
    Student tmp;
    for (int i0 = 0; i0 < N - 1; i0++)
        for (int i1 = 0; i1 < N - i0 - 1; i1++)
            if ((p[i1].kurs > p[i1 + 1].kurs)
                ||
                (p[i1].kurs == p[i1 + 1].kurs &&
                 p[i1].spec > p[i1 + 1].spec)
                ||
                (p[i1].kurs == p[i1 + 1].kurs &&
                 p[i1].spec == p[i1 + 1].spec &&
                 p[i1].prizv < p[i1 + 1].prizv))
            {
                tmp = p[i1];
                p[i1] = p[i1 + 1];
                p[i1 + 1] = tmp;
            }
}

// індексне впорядкування (метод вставки): повертає індексний масив,
// сам масив p не змінюється;
// курс, спеціальність, прізвище - за зростанням
int* IndexSort(Student* p, const int N)
{
    int* I = new int[N];       // створюємо індексний масив
    for (int i = 0; i < N; i++)
        I[i] = i;              // заповнюємо його числами 0, 1, 2, ...

    int i, j, value;
    for (i = 1; i < N; i++)
    {
        value = I[i];
        for (j = i - 1;
             j >= 0 && ((p[I[j]].kurs > p[value].kurs)
                        ||
                        (p[I[j]].kurs == p[value].kurs &&
                         p[I[j]].spec > p[value].spec)
                        ||
                        (p[I[j]].kurs == p[value].kurs &&
                         p[I[j]].spec == p[value].spec &&
                         p[I[j]].prizv > p[value].prizv));
             j--)
        {
            I[j + 1] = I[j];
        }
        I[j + 1] = value;
    }
    return I;
}

// бінарний пошук за індексним масивом I (курс, спеціальність, прізвище)
// повертає номер студента в масиві p або -1, якщо його немає
int BinSearch(Student* p, int* I, const int N,
              const string prizv, const int kurs, const Spec spec)
{
    int L = 0, R = N - 1, m;
    while (L <= R)
    {
        m = (L + R) / 2;
        if (p[I[m]].kurs == kurs && p[I[m]].spec == spec
            && p[I[m]].prizv == prizv)
            return I[m];
        if ((p[I[m]].kurs < kurs)
            ||
            (p[I[m]].kurs == kurs && p[I[m]].spec < spec)
            ||
            (p[I[m]].kurs == kurs && p[I[m]].spec == spec
             && p[I[m]].prizv < prizv))
            L = m + 1;
        else
            R = m - 1;
    }
    return -1;
}
