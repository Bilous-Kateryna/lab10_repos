// student.h — структура Student та оголошення функцій
// Лабораторна робота № 10.1, варіант 2, рівень Б
#ifndef STUDENT_H
#define STUDENT_H

#include <string>
using namespace std;

// перелік спеціальностей
enum Spec { KN, IN, ME, FI, TN };

// структура з даними про студента
struct Student
{
    string prizv;   // прізвище
    int    kurs;    // курс
    Spec   spec;    // спеціальність
    int    fizyka;  // оцінка з фізики
    int    matem;   // оцінка з математики
    union           // третя оцінка залежить від спеціальності
    {
        int prog;   // програмування (Комп'ютерні науки)
        int chys;   // чисельні методи (Інформатика)
        int ped;    // педагогіка (всі інші спеціальності)
    };
};

void   Create(Student* p, const int N);
void   Print(Student* p, const int N);
string SpecName(const Spec spec);
string Pad(const string s, const int width);
int    ThirdMark(const Student s);
double Average(const Student s);
int    CountNoThrees(Student* p, const int N);
double PercentLowAverage(Student* p, const int N);

#endif
