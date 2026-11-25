// student.h — структура Student та оголошення функцій
// Лабораторна робота № 10.2, варіант 2, рівень А
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
    int    inform;  // оцінка з інформатики
};

int    InputInt(const string prompt, const int min, const int max);
Spec   InputSpec();
void   Create(Student* p, const int N);
void   PrintHeader();
void   PrintRow(const Student s, const int number);
void   PrintFooter();
void   Print(Student* p, const int N);
void   PrintIndexSorted(Student* p, int* I, const int N);
string SpecName(const Spec spec);
string Pad(const string s, const int width);
bool   IsGreater(const Student a, const Student b);
bool   MustSwap(const Student a, const Student b);
void   Sort(Student* p, const int N);
int*   IndexSort(Student* p, const int N);
int    BinSearch(Student* p, int* I, const int N,
                 const string prizv, const int kurs, const Spec spec);

#endif
