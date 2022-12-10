// *** Урок 07. Поддержка модульности. Написание игры Blackjack / Modularity support. Writing a Blackjack Game

//#pragma once

#include <locale.h>  // Для setlocale (LC_ALL, "")
#include <iostream>
#include <iomanip>
#include <ctime>
#include <memory>

using namespace std;

/*
 * 1. Создайте класс Date с полями день, месяц, год и методами доступа к этим полям.
 *    Перегрузите оператор вывода для данного класса. Создайте два "умных" указателя today и date.
 *    Первому присвойте значение сегодняшней даты. Для него вызовите по отдельности методы доступа к полям класса Date,
 *    а также выведите на экран данные всего объекта с помощью перегруженного оператора вывода.
 *    Затем переместите ресурс, которым владеет указатель today в указатель date.
 *    Проверьте, являются ли нулевыми указатели today и date и выведите соответствующую информацию об этом в консоль.
 */

using uint = unsigned int; // С++11

class Date
{
private:
    uint m_day;
    uint m_month;
    uint m_year;

public:
    enum Month {jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec};

    Date (uint _dd = 14, uint _mm = 12, uint _yyyy = 1972);
    Date (const Date&);
    ~Date () = default;

    uint day () const; // Getter signature
    uint day (uint);   // Setter signature (returns the old value)

    uint month () const;
    uint month (uint);

    uint year () const;
    uint year (uint);

    // friends
    friend ostream& operator <<(ostream&, const Date&);
}; // class Date

Date::Date (uint _dd, uint _mm, uint _yyyy) {
    year (_yyyy);
    month (_mm);
    day (_dd);
}

Date::Date(const Date &obj) {
    year (obj.year());
    month (obj.month());
    day (obj.day());
}

ostream& operator <<(ostream& output, const Date& value) {
    output << setfill('0') << setw(2) << value.day() << "-"
            << value.month() << "-" << setw(4) << value.year();
    return output;
}

uint Date::day () const {
    return m_day;
}

uint Date::day(uint _day) {

    auto leapYear = [=]() {
        /*
        1.If the year is evenly divisible by 4, go to step 2. Otherwise, go to step 5.
        2.If the year is evenly divisible by 100, go to step 3. Otherwise, go to step 4.
        3.If the year is evenly divisible by 400, go to step 4. Otherwise, go to step 5.
        4.The year is a leap year (it has 366 days).
        5.The year is not a leap year (it has 365 days).
        */
        if(m_year % 4)
            return false;
        if(m_year % 100)
            return true;
        if(m_year % 400)
            return false;
        // return
        return true;
    };

    // max day
    int maxDay ((7 < m_month) ? 31 - m_month % 2 : 30 + m_month % 2);
    if (m_month == 2) {
        if(leapYear()) {
            maxDay = 29;
        } else {
            maxDay = 28;
        }
    }
    uint prev_day = m_day;
    // check day
    if (!_day)
        m_day = 1;
    else if (_day % maxDay)
        m_day = _day % maxDay;
    else
        m_day = maxDay;
    // return
    return prev_day;
}

uint Date::month () const {
    return m_month;
}

uint Date::month (uint _month) {
    uint prev_month = m_month;

    // check month
    if (!_month)
        m_month = jan;
    else if (_month % dec)
        m_month = _month % dec;
    else
        m_month = dec;
    // return
    return prev_month;
}

uint Date::year () const {
    return m_year;
}

uint Date::year (uint _year) {
    uint prev_year = m_year;
    m_year = _year;
    // return
    return prev_year;
}

/*
 * 2. По условию предыдущей задачи создайте два умных указателя date1 и date2.
 *    • Создайте функцию, которая принимает в качестве параметра два умных указателя типа Date
 *      и сравнивает их между собой (сравнение происходит по датам). Функция должна вернуть более позднюю дату.
 *    • Создайте функцию, которая обменивает ресурсами (датами) два умных указателя, переданных в функцию в качестве параметров.
 *    Примечание: обратите внимание, что первая функция не должна уничтожать объекты, переданные ей в качестве параметров.
 */

Date latestDate (const shared_ptr<Date> value1, const shared_ptr<Date> value2) {

    if (value1->year() > value2->year())
        return *value1.get();
    else if (value1->year() < value2->year())
        return *value2.get();
    // value1->year() == value2->year()
    if (value1->month() > value2->month())
        return *value1.get();
    else if (value1->month() < value2->month())
        return *value2.get();
    // value1->year() == value2->year()
    // value1->month() == value2->month()
    if (value1->day() > value2->day())
        return *value1.get();
    else if (value1->day() < value2->day())
        return *value2.get();

    // value1->year() == value2->year()
    // value1->month() == value2->month()
    // value1->day() == value2->day()

    // return
    return *value1.get();
} // latestDate

void swapDates (shared_ptr<Date>& value1, shared_ptr<Date>& value2) {
    shared_ptr<Date> temp = value1;
    value1 = value2;
    value2 = temp;
} // swapDates

// Функция, вызываемая при завершении работы
void endFunction (void)
{
    // Вывод сообщения о завершении работы
    puts ("\nthe work is completed!");
} // endFunction

// main
int main (void) {

    // Русский язык в консоли
    setlocale (LC_ALL, "");

     // Регистрация функции, которая будет вызвана, при нормальном завершении работы.
    if (atexit (endFunction)) {
        // Проверка регистрации функции endFunction
        puts ("post- function registration error!");
    }

    cout << "Lesson 07. Modularity support. Writing a Blackjack Game.\n\n";

    // * Exercise #1
    cout << "Exercise #1.\n";

    time_t t = time(0); // get time now
    tm* now = localtime(&t);

    auto today = make_unique<Date>(now->tm_mday, now->tm_mon + 1, now->tm_year + 1900);
    cout << "«*today» is " << *today << "." << endl;
    cout << "day -> " << today->day() << ", month -> " << today->month()
            << ", year -> " << today->year() << "." << endl;

    auto date = move(today);
    cout << "ownership of the smart pointer has been transferred from «*today» to «*date»." << endl;
    cout << "now «*date» is " << *date << "." << endl;

    if (today == nullptr) {
        cout << "now «today» is nullptr!" << endl;
    }

    // * Exercise #2
    cout << "\nExercise #2.\n";
    auto date1 = make_shared<Date> ();
    auto date2 = make_shared<Date> (now->tm_mday, now->tm_mon + 1, now->tm_year + 1900);
    cout << "«*date1» is " << *date1 << "." << endl;
    cout << "«*date2» is " << *date2 << "." << endl;
    cout << "latest date is " << latestDate (date1, date2) << "." << endl;
    cout << "date1 use count: " << date1.use_count() << "." << endl;
    cout << "date2 use count: " << date2.use_count() << "." << endl;
    swapDates (date1, date2);
    cout << "data exchange between «*data1» and «*data2»..." << endl;
    cout << "now «*date1» is " << *date1 << "." << endl;
    cout << "now «*date2» is " << *date2 << "." << endl;
    cout << "date1 use count: " << date1.use_count() << "." << endl;
    cout << "date2 use count: " << date2.use_count() << "." << endl;

    // * Exercises #3, #4 & #5
    cout << "\nExercises #3, #4 & #5.\n";
    cout << "see files «blackjack.*» ..." << endl;

    // return o.k.
    return EXIT_SUCCESS;
} // main
