// *** Урок 03. Виртуальные функции и полиморфизм / Virtual functions and polymorphism

#include <locale.h>  // Для setlocale (LC_ALL, "")
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

/*
 * 1. Создать абстрактный класс Figure (фигура). Его наследниками являются классы Parallelogram (параллелограмм) и Circle (круг). 
 *    Класс Parallelogram — базовый для классов Rectangle (прямоугольник), Square (квадрат), Rhombus (ромб). 
 *    Для всех классов создать конструкторы. Для класса Figure добавить чисто виртуальную функцию area() (площадь). 
 *    Во всех остальных классах переопределить эту функцию, исходя из геометрических формул нахождения площади.
 */

#define _180 ((double)180)

// * class Figure
class Figure
{
public:
    virtual double area(void) = 0;
    virtual double perimeter(void) = 0;
    virtual void   type(void) = 0;
};

class Rectangle;
class Square;
class Rhombus;

// * class Parallelogram
class Parallelogram : public Figure
{
private:
    double sideOne, sideTwo, angle;
public:
    Parallelogram (double _s1, double _s2, double _angle);
    virtual double area (void) override;
    virtual double perimeter (void) override;
    virtual void type (void) override
    {
        cout << "parallelogram." << endl;
    };
    // friends
    friend class Rectangle;
    friend class Square;
    friend class Rhombus;
};

Parallelogram::Parallelogram (double _s1, double _s2, double _angle) : 
    sideOne (abs (_s1)), sideTwo (abs (_s2))
{

    angle = abs (_angle);
    angle = (angle > _180 ? _180 - fmod (angle, _180) : angle);
}

double Parallelogram::area ()
{
    if (angle == _180) return NULL;
    return sideOne * sideTwo * sin(angle * M_PI / _180);
}

double Parallelogram::perimeter()
{
    if (angle == _180) return NULL;
    return (sideOne + sideTwo) * 2;
}

// * class Circle
class Circle : public Figure
{
private:
    double radius;
public:
    Circle (double _r) : radius (abs (_r))
    {};
    virtual double area (void) override
    {
        return radius * radius * M_PI;
    };
    virtual double perimeter (void) override
    {
        return M_PI * radius * 2;
    };
    virtual void type (void) override
    {
        cout << "circle." << endl;
    };
};

// * class Rectangle
class Rectangle : public Parallelogram
{
public:
    Rectangle (double _s1, double _s2) : Parallelogram (_s1, _s2, (double)90)
    {};
    virtual double area (void) override final
    {
        return sideOne * sideTwo;
    };
    virtual double perimeter (void) override final
    {
        return Parallelogram::perimeter();
    };
    virtual void type (void) override final
    {
        cout << "rectangle." << endl;
    };
};

// * class Square
class Square : public Parallelogram
{
public:
    Square (double _s) : Parallelogram (_s, _s, (double)90)
    {};
    virtual double area (void) override final
    {
        return sideOne * sideOne;
    };
    virtual double perimeter (void) override final
    {
        return Parallelogram::perimeter();
    };
    virtual void type (void) override final
    {
        cout << "square." << endl;
    };
};

// * class Rhombus
class Rhombus : public Parallelogram
{
public:
    Rhombus (double _s, double _angle) : Parallelogram (_s, _s, _angle)
    {};
    virtual double area (void) override final
    {
        return Parallelogram::area();
    };
    virtual double perimeter (void) override final
    {
        return Parallelogram::perimeter();
    };
    virtual void type (void) override final
    {
        cout << "rhombus." << endl;
    };
};

/*
 * 2. Создать класс Car (автомобиль) с полями company (компания) и model (модель). 
 *    Классы-наследники: PassengerCar (легковой автомобиль) и Bus (автобус). 
 *    От этих классов наследует класс Minivan (минивэн). Создать конструкторы для каждого из классов, 
 *    чтобы они выводили данные о классах. Создать объекты для каждого из классов и посмотреть, 
 *    в какой последовательности выполняются конструкторы. Обратить внимание на проблему «алмаз смерти».
 */

class PassengerCar;
class Bus;
class Minivan;

class Car
{
private:
    string company, model;
public:
    Car (string _company="", string _model="") : company (_company), model (_model)
    {
        cout << " car -> " << (company.length () ? company : "") 
                << (model.length () ? ", " + model + ".": "") << endl;
    };
    // friends
    friend class PassengerCar;
    friend class Bus;
    friend class Minivan;
};

class PassengerCar : virtual public Car
{
public:
    PassengerCar (string _company="", string _model="") : Car (_company, _model)
    {
        cout << " passenger car -> " << (company.length () ? company : "") 
                << (model.length () ? ", " + model + ".": "") << endl;
    };

};

class Bus : virtual public Car
{
public:
    Bus (string _company="", string _model="") : Car (_company, _model)
    {
        cout << " bus -> " << (company.length () ? company : "") 
                << (model.length () ? ", " + model + ".": "") << endl;
    };

};

class Minivan : public PassengerCar, public Bus
{
public:
    Minivan (string _company="", string _model="") : 
        PassengerCar (_company, _model), Bus (_company, _model), Car (_company, _model)
    {
        cout << " minivan -> " << (company.length () ? company : "") 
                << (model.length () ? ", " + model + ".": "") << endl;
    };

};

/*
 * 3. Создать класс: Fraction (дробь). Дробь имеет числитель и знаменатель (например, 3/7 или 9/2). 
 *    Предусмотреть, чтобы знаменатель не был равен 0. Перегрузить:
 *    a. математические бинарные операторы (+, -, *, /) для выполнения действий с дробями;
 *    б. унарный оператор (-);
 *    в. логические операторы сравнения двух дробей (==, !=, <, >, <=, >=).
 *    Примечание: Поскольку операторы < и >=, > и <= — это логические противоположности, попробуйте перегрузить один через другой.
 *    Продемонстрировать использование перегруженных операторов.
 */

// Function to return GCD of a and b
// Возвращаетнаибольший общий делитель (НОД) для [a] и [b]
int GCD (int a, int b) {
    if (a == 0)
        return b;
    return GCD (b%a, a);
}

// Function to convert the obtained fraction into it's simplest form
// Функция сокращения числителя и знаменателя дроби
void lowest (int &den, int &num)
{
    // Finding GCD of both terms
    int common_factor = GCD (num, den);
    // Converting both terms into simpler terms by dividing them by common factor
    den = den / common_factor;
    num = num / common_factor;
}

class Fraction
{
private:
    int num; // numerator
    int den; // denominator
public:
    Fraction (int numerator,int denominator)
    {
        if (!denominator) {
            cout << "invalid fraction denominator value" << endl;
            den = 1;
        } else {
            den = denominator;
        };
        num = numerator;
        if (den < 0 && num < 0) {
            den = -den;
            num = -num;
        };
    };

    // * mathematical binary operators (+, -, *, /)
    Fraction operator+ (const Fraction value) const
    {
        // Finding GCD of den1 and den2
        int den3 = GCD (den, value.den);
        // Denominator of final fraction obtained finding LCM of den1 and den2
        // LCM * GCD = a * b
        den3 = (den * value.den) / den3;
        // Changing the fractions to have same denominator
        // Numerator of the final fraction obtained
        int num3 = num * (den3 / den) + (value.num) * (den3 / value.den);
        // Calling function to convert final fraction into it's simplest form
        lowest (den3, num3);
        // return
        return Fraction (num3, den3);
    };
    Fraction operator- (const Fraction value) const
    {
        // Finding GCD of den1 and den2
        int den3 = GCD (den, value.den);
        // Denominator of final fraction obtained finding LCM of den1 and den2
        // LCM * GCD = a * b
        den3 = (den * value.den) / den3;
        // Changing the fractions to have same denominator
        // Numerator of the final fraction obtained
        int num3 = num * (den3 / den) - (value.num) * (den3 / value.den);
        // Calling function to convert final fraction into it's simplest form
        lowest (den3, num3);
        // return
        return Fraction (num3, den3);
    };
    Fraction operator/ (const Fraction value)
    {
        if (!value.num) {
            cout << "dividing by zero!" << endl;
            return Fraction (0, 1);
        }
        int den3 =  den * value.num;
        int num3 =  num * value.den;
        // Calling function to convert final fraction into it's simplest form
        lowest (den3, num3);
        // return
        return Fraction (num3, den3);
    };
    Fraction operator* (const Fraction value) const
    {
        int den3 =  den * value.den;
        int num3 =  num * value.num;
        // Calling function to convert final fraction into it's simplest form
        lowest (den3, num3);
        // return
        return Fraction (num3, den3);
    };
    // * unary operator (-)
    Fraction operator- () const
    {
        return Fraction (-num, den);
    };
    // * logical operators for comparing fractions (==, !=, <, >, <=, >=)
    bool operator! () const
    {
        return (!num);
    };
    friend bool operator== (const Fraction &value1, const Fraction &value2);
    friend bool operator!= (const Fraction &value1, const Fraction &value2);
    friend bool operator>  (const Fraction &value1, const Fraction &value2);
    friend bool operator<= (const Fraction &value1, const Fraction &value2);
    friend bool operator<  (const Fraction &value1, const Fraction &value2);
    friend bool operator>= (const Fraction &value1, const Fraction &value2);

    // friends
    friend ostream& operator <<(ostream& output, const Fraction& value)
    {
        output << (value.num * value.den > 0 ? "" : "-") << abs(value.num) << "/" << abs(value.den);
        return output;
    };

};

bool operator== (const Fraction &value1, const Fraction &value2) {
    int num1 = value1.num, den1 = value1.den;
    lowest (den1, num1);
    int num2 = value2.num, den2 = value2.den;
    lowest (den2, num2);
    // return
    return (num1 == num2 && den1 == den2);
}

bool operator!= (const Fraction &value1, const Fraction &value2) {
    return !(value1 == value2);
}

bool operator> (const Fraction &value1, const Fraction &value2) {
    bool positive1 = (value1.num >= 0 && value1.den >= 0);
    bool positive2 = (value2.num >= 0 && value2.den >= 0);
    bool retValue  = NULL;
    if ((positive1 && positive2) || (!positive1 && !positive2)) {
        Fraction res = value1 - value2;
        retValue = (res.num > 0 && res.den > 0);
    } else if (positive1 && !positive2) {
        retValue = true;
    } else if (!positive1 && positive2) {
        retValue = false;
    };
    // return
    return retValue;
}

bool operator<= (const Fraction &value1, const Fraction &value2) {
    return !(value1 > value2);
}

bool operator< (const Fraction &value1, const Fraction &value2) {
    bool positive1 = (value1.num >= 0 && value1.den >= 0);
    bool positive2 = (value2.num >= 0 && value2.den >= 0);
    bool retValue  = NULL;
    if ((positive1 && positive2) || (!positive1 && !positive2)) {
        Fraction res = value2 - value1;
        retValue = (res.num > 0 && res.den > 0);
    } else if (positive1 && !positive2) {
        retValue = false;
    } else if (!positive1 && positive2) {
        retValue = true;
    };
    // return
    return retValue;
}

bool operator>= (const Fraction &value1, const Fraction &value2) {
    return !(value1 < value2);
}

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

    cout << "Lesson 03. Virtual functions and polymorphism.\n\n";

    // Exercise #1
    cout << "Exercise #1.\n";
    double side1 = 10.0, side2 = 5.0, angle = 30.0;
    Parallelogram p(side1, side2, angle);
    Rectangle r1(side1, side2);
    Square s(side1);
    Rhombus r2(side1, angle);
    Circle c(side1);
    p.type();
    printf(" side1-> %.3f; side2-> %.3f; angle->%.3fº; area->%.3f; perimeter->%.3f.\n", 
            side1, side2, angle, p.area(), p.perimeter());
    r1.type();
    printf(" side1-> %.3f; side2-> %.3f; area->%.3f; perimeter->%.3f.\n", 
            side1, side2, r1.area(), r1.perimeter());
    s.type();
    printf(" side-> %.3f; area->%.3f; perimeter->%.3f.\n", 
            side1, s.area(), s.perimeter());
    r2.type();
    printf(" side-> %.3f; angle->%.3fº; area->%.3f; perimeter->%.3f.\n", 
            side1, angle, r2.area(), r2.perimeter());
    c.type();
    printf(" radius-> %.3f; area->%.3f; perimeter->%.3f.\n", 
            side1, c.area(), c.perimeter());

    // Exercise #2
    cout << "\nExercise #2.\n";

    cout << "object Car.\n";
    Car car("company1", "model1");
    
    cout << "object PassengerCar.\n";
    PassengerCar pasCar("company2", "model2");

    cout << "object Bus.\n";
    Bus bus("company3", "model3");

    cout << "object Minivan.\n";
    Minivan mini("company4", "model4");

    // Exercise #3
    cout << "\nExercise #3.\n";
    Fraction f1(1,2), f2(3,4);
    // "+" "-"
    Fraction f3 = f1 + f2, f4 = f1 - f2;
    cout << f1 << " + " << f2 << " = " << f3 << endl;
    cout << f1 << " - " << f2 << " = " << f4 << endl;
    // "*" "/"
    Fraction f5 = f1 * f2, f6 = f1 / f2;
    cout << f1 << " * " << f2 << " = " << f5 << endl;
    cout << f1 << " / " << f2 << " = " << f6 << endl;
    // "!"
    cout << f1 << (!f1 ? " is null" : " isn't null") << endl;
    cout << f2 << (!f2 ? " is null" : " isn't null") << endl;
    // "-"
    Fraction f7 = -f1, f8 = -f2;
    cout << f1 << ", opposite value " << f7 << endl;
    cout << f2 << ", opposite value " << f8 << endl;
    // "==" "!="
    Fraction f10 (2,4);
    cout << f1 << (f1 == f10 ? " is equal " : " isn't equal ") << f10 << endl;
    cout << f1 << (f1 != f2  ? " isn't equal " : " is equal ") << f2 << endl;
    // ">" "<="
    cout << f1 << " >  " << f2 << " : " << boolalpha << (f1 >  f2) << endl;
    cout << f1 << " <= " << f2 << " : " << boolalpha << (f1 <= f2) << endl;
    // "<" ">="
    cout << f1 << " <  " << f2 << " : " << boolalpha << (f1 <  f2) << endl;
    cout << f1 << " >= " << f2 << " : " << boolalpha << (f1 >= f2) << endl;

    // return o.k.
    return EXIT_SUCCESS;
} // main