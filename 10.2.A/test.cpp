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

// заповнює масив з 4 студентів
void FillArray(Student* p)
{
    p[0] = MakeStudent("Мельник", 2, IN, 4, 4, 4);
    p[1] = MakeStudent("Шевчук", 1, TN, 5, 5, 5);
    p[2] = MakeStudent("Коваль", 1, KN, 4, 5, 4);
    p[3] = MakeStudent("Бондаренко", 2, IN, 3, 4, 5);
}

TEST_CASE("Sort")
{
    Student p[4];
    FillArray(p);
    Sort(p, 4);

    // курс і спеціальність - за зростанням, прізвище - за спаданням
    CHECK(p[0].prizv == "Коваль");
    CHECK(p[1].prizv == "Шевчук");
    CHECK(p[2].prizv == "Мельник");
    CHECK(p[3].prizv == "Бондаренко");
}

TEST_CASE("IndexSort")
{
    Student p[4];
    FillArray(p);
    int* I = IndexSort(p, 4);

    // курс, спеціальність і прізвище - за зростанням
    CHECK(I[0] == 2);
    CHECK(I[1] == 1);
    CHECK(I[2] == 3);
    CHECK(I[3] == 0);
    CHECK(p[0].prizv == "Мельник");   // сам масив не змінився
    delete[] I;
}

TEST_CASE("BinSearch")
{
    Student p[4];
    FillArray(p);
    int* I = IndexSort(p, 4);

    CHECK(BinSearch(p, I, 4, "Шевчук", 1, TN) == 1);
    CHECK(BinSearch(p, I, 4, "Мельник", 2, IN) == 0);
    CHECK(BinSearch(p, I, 4, "Мельник", 1, IN) == -1);   // інший курс
    CHECK(BinSearch(p, I, 4, "Яковенко", 2, IN) == -1);  // немає прізвища
    delete[] I;
}
