// test.cpp — unit-тест (doctest)
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "student.h"

// допоміжна функція: створює студента із заданими даними
Student MakeStudent(string prizv, int kurs, Spec spec, int f, int m, int third)
{
    Student s;
    s.prizv = prizv;
    s.kurs = kurs;
    s.spec = spec;
    s.fizyka = f;
    s.matem = m;
    s.inform = third;
    return s;
}

// заповнює масив з 6 студентів
void FillArray(Student* p)
{
    p[0] = MakeStudent("Мельник", 2, IN, 4, 4, 4);
    p[1] = MakeStudent("Шевчук", 1, TN, 5, 5, 5);
    p[2] = MakeStudent("Бондаренко", 2, IN, 3, 4, 5);
    p[3] = MakeStudent("Коваль", 1, KN, 4, 5, 4);
    p[4] = MakeStudent("Сидоренко", 2, KN, 5, 5, 4);
    p[5] = MakeStudent("Петренко", 1, TN, 3, 3, 4);
}

TEST_CASE("Sort")
{
    Student p[6];
    FillArray(p);
    Sort(p, 6);

    // курс і спеціальність - за зростанням, прізвище - за спаданням
    CHECK(p[0].prizv == "Коваль");
    CHECK(p[1].prizv == "Шевчук");
    CHECK(p[2].prizv == "Петренко");
    CHECK(p[3].prizv == "Сидоренко");
    CHECK(p[4].prizv == "Мельник");
    CHECK(p[5].prizv == "Бондаренко");
}

TEST_CASE("IndexSort")
{
    Student p[6];
    FillArray(p);
    int* I = IndexSort(p, 6);

    // курс, спеціальність і прізвище - за зростанням
    CHECK(I[0] == 3);
    CHECK(I[1] == 5);
    CHECK(I[2] == 1);
    CHECK(I[3] == 4);
    CHECK(I[4] == 2);
    CHECK(I[5] == 0);
    // сам масив не змінився
    CHECK(p[0].prizv == "Мельник");
    delete[] I;
}

TEST_CASE("BinSearch")
{
    Student p[6];
    FillArray(p);
    int* I = IndexSort(p, 6);

    CHECK(BinSearch(p, I, 6, "Петренко", 1, TN) == 5);
    CHECK(BinSearch(p, I, 6, "Мельник", 2, IN) == 0);
    CHECK(BinSearch(p, I, 6, "Коваль", 1, KN) == 3);
    CHECK(BinSearch(p, I, 6, "Мельник", 1, IN) == -1);   // інший курс
    CHECK(BinSearch(p, I, 6, "Мельник", 2, TN) == -1);   // інша спеціальність
    CHECK(BinSearch(p, I, 6, "Яковенко", 2, IN) == -1);  // немає прізвища
    delete[] I;
}
