// *** Урок 06. Потоки ввода-вывода / I/O Streams

//#pragma once

#include <locale.h>  // Для setlocale (LC_ALL, "")
#include <iostream>
#include <limits>
#include <string>
#include <iosfwd>

using namespace std;

/*
 * 1. Создать программу, которая считывает целое число типа int. И поставить «защиту от дурака»: 
 *    если пользователь вводит что-то кроме одного целочисленного значения, нужно вывести сообщение об ошибке
 *    и предложить ввести число еще раз. Пример неправильных введенных строк:
 *      • rbtrb
 *      • nj34njkn
 *      • 1n
 */

class mCheck
{
public:
    string prompt;
    mCheck& operator >> (string& str) //------------------------std::string:
    {
        getline(cin, str);
        prompt = "";
        return *this;
    };
    mCheck& operator >> (unsigned char& ch) //------------------unsigned char:
    {
        bool     is_error;
        unsigned n;
        do {
            cin  >> n;
            is_error = cin.fail() || cin.get() != '\n';
            if (is_error) {
                cout << "Error!\n\n" << prompt;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.sync();
            }
            else if(n > 255) {
                is_error  = true;
                cout << "Error bound!\n\n" << prompt;
            }
        } while (is_error);

        ch = n;
        prompt = "";
        return *this;
    };
    mCheck& operator >>(const char* _prompt) //-----------------promt
    {
        cout << _prompt;
        prompt = _prompt;
        return *this;
    };
    template<class T>
    mCheck& operator >> (T& value) //---------------------------template:
    {
        cin >> value;
        while (cin.fail() || cin.get() != '\n') {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.sync();
            cout << "Error!\n\n" << prompt;
            cin >> value;
        }
        prompt = "";
        return *this;
    };
} cin_check;

/*
 * 2. Создать собственный манипулятор endll для стандартного потока вывода, который выводит два перевода строки и сбрасывает буфер.
 */

template <class _Elem, class _Traits>
basic_ostream<_Elem, _Traits>& endll(
    basic_ostream<_Elem, _Traits>& _Ostr) { // insert two newlines and flush stream
    _Ostr.put(_Ostr.widen('\n'));
    _Ostr.put(_Ostr.widen('\n'));
    _Ostr.flush();
    return _Ostr;
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

    cout << "Lesson 06. I/O Streams.\n\n";

    // * Exercise #1
    cout << "Exercise #1.\n";

    int number;
    cout << "int------------------------:\n";
    cin_check >> "n = " >> number;
    cout << "validator: " << number << endll;

    // cout << "char-----------------------:\n";
    // char c;  cin_check >> "c = " >> c;
    // cout << "validator: " << c << endll;

    // cout << "unsigned char-----0,...,255:\n";
    // unsigned char u; cin_check >> "u = " >> u;
    // cout << "validator: '" << u << endll;

    // cout << "float----------------------:\n";
    // float f; cin_check >> "f = " >> f;
    // cout << "validator: " << f << endll;

    // * Exercise #2
    cout << "Exercise #2.";
	cout << endll << "after endll" << endl;

    // Exercises #3, #4 & #5
    cout << "\nExercises #3, #4 & #5.\n";
    cout << "see files «blackjack.*»" << endl;

    // return o.k.
    return EXIT_SUCCESS;
} // main