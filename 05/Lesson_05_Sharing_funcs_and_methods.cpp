// *** Урок 05. Совместное использование функций и методов / Sharing functions and methods

#include <locale.h>  // Для setlocale (LC_ALL, "")
#include <iostream>
#include <cstring>
// #include <cassert> // для assert()
// #include <cstdlib> // Для rand()

// #include <algorithm>
// #include <vector>
// #include <set>
// #include <iterator>

using namespace std;

/*
 * 1. Реализовать шаблон класса Pair1, который позволяет пользователю передавать данные одного типа парами.
 *    Следующий код:
 *    int main()
 *    {
 *      Pair1<int> p1(6, 9);
 *      cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';
 *      
 *      const Pair1<double> p2(3.4, 7.8);
 *      cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';
 *      
 *      return 0;
 *    }
 *    … должен производить результат:
 *    Pair: 6 9
 *    Pair: 3.4 7.8
 */

template <class T = int>
class Pair1
{
private:
    T m_first, m_second;
public:
    Pair1(T _first, T _second) : m_first (_first), m_second (_second) {};
    Pair1(const Pair1 &obj) {
        m_first = obj.first(); 
        m_second = obj.second();
    };
    ~Pair1() {};
    T first() const {return m_first;};
    T second() const {return m_second;};
};

/*
 * 2. Реализовать класс Pair, который позволяет использовать разные типы данных в передаваемых парах.
 *    Следующий код:
 *    int main()
 *    {
 *      Pair<int, double> p3(6, 7.8);
 *      cout << "Pair: " << p3.first() << ' ' << p3.second() << '\n';
 *    
 *      const Pair<double, int> p4(3.4, 5);
 *      cout << "Pair: " << p4.first() << ' ' << p4.second() << '\n';
 *    
 *      return 0;
 *    }
 *    … должен производить следующий результат:
 *    Pair: 6 7.8
 *    Pair: 3.4 5
 */

template <class T1, class T2>
class Pair
{
private:
    T1 m_first;
    T2 m_second;
public:
    Pair(T1 _first, T2 _second) : m_first (_first), m_second (_second) {};
    Pair(const Pair &obj) {
        m_first = obj.first(); 
        m_second = obj.second();
    };
    ~Pair() {};
    T1 first() const {return m_first;};
    T2 second() const {return m_second;};
};

/*
 * 3. Написать шаблон класса StringValuePair, в котором первое значение всегда типа string, а второе — любого типа. 
 *    Этот шаблон класса должен наследовать частично специализированный класс Pair, в котором первый параметр — string, 
 *    а второй — любого типа данных.
 *    Следующий код:
 *    int main()
 *    {
 *      StringValuePair<int> svp("Amazing", 7);
 *      std::cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';
 *      return 0;
 *    }
 *    … должен производить следующий результат:
 *    Pair: Amazing 7
 */

// частичная специализация Pair
template <class U>
class Pair <string, U>
{
private:
    string m_first;
    U m_second;
public:
    Pair(string _first, U _second) : m_first (_first), m_second (_second) {};
    Pair(const Pair &obj) {
        m_first  = obj.first();
        m_second = obj.second();
    };
    ~Pair() {};
    string first() const {return m_first;};
    U second() const {return m_second;};
};

// шаблон производного класса
template <class U>
class StringValuePair : public Pair <string, U>
{
public:
    StringValuePair(string _first, U _second) : Pair<string, U> (_first, _second) {};
    StringValuePair(const StringValuePair &obj) : Pair<string, U> (obj) {};
    ~StringValuePair(){};
};


// Функция, вызываемая при завершении работы
void endFunction (void)
{
    // Вывод сообщения о завершении работы
    puts ("\nthe work is completed!");
}

// main
int main (void) {

    // Русский язык в консоли
    setlocale (LC_ALL, "");

     // Регистрация функции, которая будет вызвана, при нормальном завершении работы.
    if (atexit (endFunction)) {
        // Проверка регистрации функции endFunction
        puts ("post- function registration error!");
    }

    cout << "Lesson 05. Sharing functions and methods.\n\n";

    // Exercise #1
    cout << "Exercise #1.\n";
    Pair1<int> p1(6, 9);
    cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';
    const Pair1<double> p2(3.4, 7.8);
    cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';

    // Exercise #2
    cout << "\nExercise #2.\n";
    Pair<int, double> p3(6, 7.8);
    cout << "Pair: " << p3.first() << ' ' << p3.second() << '\n';
    const Pair<double, int> p4(3.4, 5);
    cout << "Pair: " << p4.first() << ' ' << p4.second() << '\n';

    // Exercise #3
    cout << "\nExercise #3.\n";
    StringValuePair<int> svp("Amazing", 7);
    cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';

    // Exercise #4
    cout << "\nExercise #4.\n";
    cout << "see files «blackjack.*»" << endl;

    // return o.k.
    return EXIT_SUCCESS;
} // main