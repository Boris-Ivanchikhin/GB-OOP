// *** Урок 08. Механизм исключительных ситуаций / The mechanism of exceptional situations

#include <locale.h>  // Для setlocale (LC_ALL, "")
#include <iostream>
#include <conio.h>
#include <cstdlib> // Для rand()
#include <sstream>
#include <limits>

using namespace std;

double askNumber(string prompt) {
    double value;
    cout << prompt << ": ";
    cin >> value;
    while (cin.fail() || cin.get() != '\n') {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.sync();
        cout << "error!\n\n" << prompt << ": ";
        cin >> value;
    }
    return value;
}

/*
 * 1. Написать шаблонную функцию div, которая должна вычислять результат деления двух параметров 
 *    и запускать исключение DivisionByZero, если второй параметр равен 0. 
 *    В функции main выводить результат вызова функции div в консоль, а также ловить исключения.
 */

class DivisionByZero {};

template<typename T1, typename T2>
auto div (T1 x, T2 y) -> decltype (x/y) {
    if (!y)
        throw DivisionByZero();
    return x / y;
}

/*
 * 2. Написать класс Ex, хранящий вещественное число x и имеющий конструктор по вещественному числу, 
 *    инициализирующий x значением параметра. Написать класс Bar, хранящий вещественное число y 
 *    (конструктор по умолчанию инициализирует его нулем) и имеющий метод set с единственным вещественным параметром a. 
 *    Если y + a > 100, возбуждается исключение типа Ex с данными a*y, иначе в y заносится значение a. 
 *    В функции main завести переменную класса Bar и в цикле в блоке try вводить с клавиатуры целое n. 
 *    Использовать его в качестве параметра метода set до тех пор, пока не будет введено 0. 
 *    В обработчике исключения выводить сообщение об ошибке, содержащее данные объекта исключения.
 */

class Ex {
private:
    double x;
public:
    Ex(const double &_x) : x(_x) {};
    ~Ex()= default;
    double get() const {return x;};
};

class Bar {
private:
    double y;
public:
    Bar() {y = 0;};
    ~Bar() = default;
    void set(const double &a) {
        if (y + a <= 100)
            y = a;
        else
            throw Ex (y * a);
    };
    double get() const {return y;};
};

/*
 * 3. Написать класс «робот», моделирующий перемещения робота по сетке 10x10, у которого есть метод,
 *    означающий задание переместиться на соседнюю позицию.
 *    Эти методы должны запускать классы-исключения OffTheField, если робот должен уйти с сетки, и IllegalCommand,
 *    если подана неверная команда (направление не находится в нужном диапазоне).
 *    Объект исключения должен содержать всю необходимую информацию — текущую позицию и направление движения.
 *    Написать функцию main, пользующуюся этим классом и перехватывающую все исключения от его методов,
 *    а также выводящую подробную информацию о всех возникающих ошибках.
 */

#define MAX_SIZE 10
using uint = unsigned int; // С++11

// * class OffTheField
class OffTheField
{
private:
    const uint xR;
    const uint yR;
    const string command;

public:
    OffTheField (uint _x, uint _y, string _command) :
        xR (_x), yR (_y), command (_command) {};
    ~OffTheField() = default;
    string what();
}; // class OffTheField

string OffTheField::what() {
    stringstream out;
    out << "An «OffTheField» exception was handled! " <<
            "Coordinates [" << xR << "][" << yR << "]. " <<
            "The last command: «" << command << "»." << endl;
    return out.str();
}

// * class IllegalCommand
class IllegalCommand
{
private:
    const char command;

public:
    IllegalCommand (char _command) :
        command (_command) {};
    ~IllegalCommand() = default;
    string what();
}; // class IllegalCommand

string IllegalCommand::what() {
    stringstream out;
    out << "An «IllegalCommand» exception was handled! " <<
            "Unknown command: «" << command << "»." << endl;
    return out.str();
}

// * class Robot
class Robot
{
private:
    uint xR, yR;
    uint RandInt();

    void Info();
    void Display ();
    void Up();
    void Down();
    void Left();
    void Right();

public:
    Robot (uint _x = 0, uint _y = 0);
    ~Robot () = default;

    void Run();
};

uint Robot::RandInt() {
    return rand() % 10;
}

Robot::Robot(uint _x, uint _y) {
    srand((uint) time(0));
    xR = !_x ? RandInt() : _x % MAX_SIZE;
    yR = !_y ? RandInt() : _y % MAX_SIZE;
}

void Robot::Display() {
    // шапка
    for (int i = 0; i < MAX_SIZE; ++ i)
        cout << (!i ? "\n   | " : "") << i <<  " | ";
    for (int i = 0; i < MAX_SIZE; ++ i)
        cout << (!i ? "\n----" : "") << "----";
    // поле
    for (int y = 0; y < MAX_SIZE; ++y) {
        cout << "\n " << y <<  " | ";
        for (int x = 0; x < MAX_SIZE; ++x) {
            cout << ((y == yR && x == xR) ? "R" : " ") << " | ";
        }
    }
    // подвал
    for (int i = 0; i < MAX_SIZE; ++ i)
        cout << (!i ? "\n----" : "") << "----";
}

void Robot::Info() {
    cout << endl;
    cout << "W -> one cell up.\n";
    cout << "S -> one cell down.\n";
    cout << "A -> one cell left.\n";
    cout << "D -> one cell right.\n";
    cout << "0 -> exit the program.\n";
}

void Robot::Up() {
    if (!yR)
        throw OffTheField(xR, yR, __FUNCTION__);
    else
        --yR;
}

void Robot::Down() {
    if (yR == MAX_SIZE - 1)
        throw OffTheField(xR, yR, __FUNCTION__);
    else
        ++yR;
}

void Robot::Left() {
    if (!xR)
        throw OffTheField(xR, yR, __FUNCTION__);
    else
        --xR;
}

void Robot::Right()  {
    if (xR == MAX_SIZE - 1)
        throw OffTheField(xR, yR, __FUNCTION__);
    else
        ++xR;
}

void Robot::Run() {
    cout << "Welcome to the Robot control program.\n";
    for (;;) {
        Display();
        Info();
        cout << "command?: ";
        char input = getch();
        switch (input) {
        case ('W','w'):
            Up();
            break;
        case ('S','s'):
            Down();
            break;
        case ('A','a'):
            Left();
            break;
        case ('D','d'):
            Right();
            break;
        case 0:
            cout << "exit..." << endl;
            return;
        default:
            throw IllegalCommand(input);
        }
    }
}

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

    cout << "Lesson 08. The mechanism of exceptional situations.\n\n";

    // * Exercise #1
    cout << "Exercise #1.\n";
    double x = askNumber("input X");
    double y = askNumber("input Y");
    try {
        cout << x << " / " << y << " = " << div (x , y) << endl;
    }
    catch (DivisionByZero) {
        cerr << endl << "division by zero!" << endl;
        //return EXIT_FAILURE;
    }

    // * Exercise #2
    cout << "\nExercise #2.\n";
    Bar b;
    for (;;) {
        double N = askNumber("input N");
        if (!N)
            break;
        try {
            b.set(N);
            cout << "B.y = " << b.get() << endl;
        }
        catch(Ex &err) {
            cerr << "exception: a * y = " << err.get() << endl;
            //return EXIT_FAILURE;
            break;
        };
    };

    // * Exercises #3
    cout << "\nExercise #3.\n";
    Robot robot;
    try {
        robot.Run();
    }
    catch (OffTheField &ex) {
        cerr << endl << ex.what() << endl;
        //return EXIT_FAILURE;
    }
    catch (IllegalCommand &ex) {
        cerr << endl << ex.what() << endl;
        //return EXIT_FAILURE;
    }

    // return o.k.
    return EXIT_SUCCESS;
} // main
