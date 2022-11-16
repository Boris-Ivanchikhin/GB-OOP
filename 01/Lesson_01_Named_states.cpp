// *** Урок 01. Именованные состояния / Named states

#include <locale.h>  // Для setlocale (LC_ALL, "")
#include <iostream>
#include <cstdlib> // Для rand()
#include <cmath>

using namespace std;

/*
 * 1. Создать класс Power, который содержит два вещественных числа. 
 * Этот класс должен иметь две переменные-члена для хранения этих вещественных чисел. 
 * Еще создать два метода: один с именем set, который позволит присваивать значения объявленным в классе переменным, 
 * второй — calculate, который будет выводить результат возведения первого числа в степень второго числа. 
 * Задать значения этих двух чисел по умолчанию.
 */

class Power
{
private:
    double Base = 1.0; 
    double Degree = 1.0;
public:
    // default constructor
    Power(){};
    Power(double,double);
    // default destructor
    ~Power(){};
    void setBase (double pBase) {Base = pBase;};
    void setDegree (double pDegree) {Degree = pDegree;};
    double getBase (void) {return Base;};
    double getDegree (void) {return Degree;};
    void calculate (void);
};

Power::Power(double pBase, double pDegree) : Base(pBase), Degree(pDegree)
{}

void Power::calculate (void) {
    printf ("current calc result: %f (Base) ^ %f (Degree) = %f.\n", 
        getBase(), getDegree(), pow (getBase(), getDegree()));
}

/*
 * 2. Написать класс с именем RGBA, который содержит 4 переменные-члена 
 *    типа std::uint8_t: m_red, m_green, m_blue и m_alpha (#include cstdint для доступа к этому типу). 
 *    Задать 0 в качестве значения по умолчанию для m_red, m_green, m_blue и 255 для m_alpha. 
 *    Создать конструктор со списком инициализации членов, который позволит пользователю передавать 
 *    значения для m_red, m_blue, m_green и m_alpha. 
 *    Написать функцию print(), которая будет выводить значения переменных-членов.
 */

class RGBA
{
private:
    uint8_t m_red = 0, m_green = 0, m_blue = 0, m_alpha = 255;
public:
    // default constructor
    RGBA(){};
    RGBA(uint8_t, uint8_t, uint8_t, uint8_t);
    // default destructor
    ~RGBA(){};
    void print (void);
};

RGBA::RGBA(uint8_t p_red, uint8_t p_green, uint8_t p_blue, uint8_t p_alpha) : 
    m_red(p_red), m_green(p_green), m_blue(p_blue), m_alpha(p_alpha)
{}

void RGBA::print() {
    printf ("class RGBA values.: m_red=%u, m_green=%u, m_blue=%u, m_alpha=%u.\n", 
        m_red, m_green, m_blue, m_alpha);
}

/*
 * 3. Написать класс, который реализует функциональность стека. Класс Stack должен иметь:
 *    - private-массив целых чисел длиной 10;
 *    - private целочисленное значение для отслеживания длины стека;
 *    - public-метод с именем reset(), который будет сбрасывать длину и все значения элементов на 0;
 *    - public-метод с именем push(), который будет добавлять значение в стек. push() должен возвращать значение false, 
 *      если массив уже заполнен, и true в противном случае;
 *    - public-метод с именем pop() для вытягивания и возврата значения из стека. 
 *      Если в стеке нет значений, то должно выводиться предупреждение;
 *    - public-метод с именем print(), который будет выводить все значения стека.
 */

#define STACK_SIZE 10
using uint = unsigned int; // С++11

class Stack
{
private:
    int iValues[STACK_SIZE];
    uint count = 0;
public:
    // default constructor
    Stack(){};
    // default destructor
    ~Stack(){};
    // other methods
    void reset (void);
    bool push (int);
    int pop (void);
    void print (void);
};

void Stack::reset (void) {
    count = 0;
    for (int i=0; i<sizeof(iValues)/sizeof(iValues[0]); i++)
        iValues[i]=0;
}

void Stack::print (void) {
    cout << endl << "(";
    for (int i=0; i<count; i++)
        cout << (i ? " " : "") << iValues[i];
    cout << ")";
}

bool Stack::push (int value) {
    if (count >= sizeof(iValues)/sizeof(iValues[0])) {
        cout << "stack overflow" << endl;
        return false;
    }
    iValues[count++] = value;
}

int Stack::pop (void) {
    if (count <= 0) {
        cout << "stack is empty!" << endl;
        return NULL;
    }
    return iValues[--count];
}

// Функция, вызываемая при завершении работы
void endFunction (void)
{
    // Вывод сообщения о завершении работы
    puts ("\nthe work is completed!");
}

#define MAX_VALUE 5.0f

// main
int main (void) {

    // Русский язык в консоли
    setlocale (LC_ALL, "");

    // Lesson 01. Named states
    cout << "Lesson 01. Named states.\n\n";

    // Exercise #1
    cout << "Exercise #1.\n";
    Power myP;
    printf ("default values: Base = %f; Degree = %f.\n", myP.getBase(), myP.getDegree());
    srand((unsigned int)time(0));

    myP.setBase (abs ((2 * MAX_VALUE) * rand() / (double)RAND_MAX - MAX_VALUE));
    myP.setDegree ((2 * MAX_VALUE) * rand() / (double)RAND_MAX - MAX_VALUE);
    myP.calculate ();

    // Exercise #2
    cout << "\nExercise #2.\n";
    RGBA myRGBA1, myRGBA2 (1, 2, 3, 4);
    myRGBA1.print();
    myRGBA2.print();

    // Exercise #3
    cout << "\nExercise #3.";
    Stack stack;
    stack.reset();
    stack.print();

    stack.push(3);
    stack.push(7);
    stack.push(5);
    stack.print();

    stack.pop();
    stack.print();

    stack.pop();
    stack.pop();
    stack.print();

    // Регистрация функции, которая будет вызвана, при нормальном завершении работы.
    if (atexit (endFunction)) {
        // Проверка регистрации функции endFunction
        puts ("post- function registration error!");
    }

    // return o.k.
    return EXIT_SUCCESS;
} // main