// student.cpp — реалізація функцій
#include <iostream>
#include "student.h"
using namespace std;

// введення даних про студентів з клавіатури
void Create(Student* p, const int N)
{
    int spec;
    for (int i = 0; i < N; i++)
    {
        cout << "Студент № " << i + 1 << ":" << endl;
        cout << "   прізвище: ";
        cin >> p[i].prizv;
        cout << "   курс: ";
        cin >> p[i].kurs;
        do {
            cout << "   спеціальність (0 - Комп'ютерні науки, "
                 << "1 - Інформатика," << endl
                 << "      2 - Математика та економіка, "
                 << "3 - Фізика та інформатика," << endl
                 << "      4 - Трудове навчання): ";
            cin >> spec;
        } while (spec < 0 || spec > 4);
        p[i].spec = (Spec)spec;
        cout << "   оцінка з фізики: ";
        cin >> p[i].fizyka;
        cout << "   оцінка з математики: ";
        cin >> p[i].matem;

        // третя оцінка залежить від спеціальності
        switch (p[i].spec)
        {
        case KN:
            cout << "   оцінка з програмування: ";
            cin >> p[i].prog;
            break;
        case IN:
            cout << "   оцінка з чисельних методів: ";
            cin >> p[i].chys;
            break;
        case ME:
        case FI:
        case TN:
            cout << "   оцінка з педагогіки: ";
            cin >> p[i].ped;
            break;
        }
        cout << endl;
    }
}

// вивід масиву студентів у вигляді таблиці
void Print(Student* p, const int N)
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

    for (int i = 0; i < N; i++)
    {
        // у таблиці заповнена тільки одна з трьох останніх клітинок
        string prog = "", chys = "", ped = "";
        switch (p[i].spec)
        {
        case KN:
            prog = to_string(p[i].prog);
            break;
        case IN:
            chys = to_string(p[i].chys);
            break;
        case ME:
        case FI:
        case TN:
            ped = to_string(p[i].ped);
            break;
        }

        cout << "| " << Pad(to_string(i + 1), 3)
             << " | " << Pad(p[i].prizv, 11)
             << " | " << Pad(to_string(p[i].kurs), 4)
             << " | " << Pad(SpecName(p[i].spec), 23)
             << " | " << Pad(to_string(p[i].fizyka), 6)
             << " | " << Pad(to_string(p[i].matem), 6)
             << " | " << Pad(prog, 8)
             << " | " << Pad(chys, 8)
             << " | " << Pad(ped, 8) << " |" << endl;
    }
    cout << string(105, '=') << endl;
    cout << endl;
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

// повертає третю оцінку студента (залежить від спеціальності)
int ThirdMark(const Student s)
{
    switch (s.spec)
    {
    case KN: return s.prog;
    case IN: return s.chys;
    default: return s.ped;
    }
}

// повертає середній бал студента
double Average(const Student s)
{
    return (s.fizyka + s.matem + ThirdMark(s)) / 3.0;
}

// повертає кількість студентів без трійок (всі оцінки 4 або 5)
int CountNoThrees(Student* p, const int N)
{
    int k = 0;
    for (int i = 0; i < N; i++)
        if (p[i].fizyka >= 4 && p[i].matem >= 4 && ThirdMark(p[i]) >= 4)
            k++;
    return k;
}

// повертає процент студентів, у яких середній бал менший за 4
double PercentLowAverage(Student* p, const int N)
{
    int k = 0;
    for (int i = 0; i < N; i++)
        if (Average(p[i]) < 4)
            k++;
    return 100.0 * k / N;
}
