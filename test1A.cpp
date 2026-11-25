// test.cpp — unit-тест (doctest)
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "student.h"

// допоміжна функція: створює студента із заданими даними
Student MakeStudent(string prizv, Spec spec, int f, int m, int inf)
{
    Student s;
    s.prizv = prizv;
    s.kurs = 1;
    s.spec = spec;
    s.fizyka = f;
    s.matem = m;
    s.inform = inf;
    return s;
}

TEST_CASE("Average")
{
    Student s = MakeStudent("Іваненко", KN, 5, 4, 3);
    CHECK(Average(s) == doctest::Approx(4.0));
}

TEST_CASE("CountNoThrees")
{
    Student p[5];
    p[0] = MakeStudent("Іваненко", KN, 5, 5, 5);
    p[1] = MakeStudent("Петренко", IN, 4, 4, 5);
    p[2] = MakeStudent("Сидоренко", ME, 3, 4, 5);
    p[3] = MakeStudent("Коваль", FI, 3, 3, 4);
    p[4] = MakeStudent("Шевчук", TN, 2, 3, 3);

    CHECK(CountNoThrees(p, 5) == 2);
    CHECK(CountNoThrees(p, 2) == 2);
    CHECK(CountNoThrees(p + 2, 3) == 0);
}

TEST_CASE("PercentLowAverage")
{
    Student p[5];
    p[0] = MakeStudent("Іваненко", KN, 5, 5, 5);
    p[1] = MakeStudent("Петренко", IN, 4, 4, 5);
    p[2] = MakeStudent("Сидоренко", ME, 3, 4, 5);
    p[3] = MakeStudent("Коваль", FI, 3, 3, 4);
    p[4] = MakeStudent("Шевчук", TN, 2, 3, 3);

    CHECK(PercentLowAverage(p, 5) == doctest::Approx(40.0));
    CHECK(PercentLowAverage(p, 2) == doctest::Approx(0.0));
    CHECK(PercentLowAverage(p + 3, 2) == doctest::Approx(100.0));
}
