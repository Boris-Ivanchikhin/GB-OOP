// *** Урок 02. Наследование / Inheritance

#include <locale.h>  // Для setlocale (LC_ALL, "")
#include <iostream>
//#include <cstdlib> // Для rand()

using namespace std;

/*
 * 1. Создать класс Person (человек) с полями: имя, возраст, пол и вес. 
 *    Определить методы переназначения имени, изменения возраста и веса. 
 *    Создать производный класс Student (студент), имеющий поле года обучения. 
 *    Определить методы переназначения и увеличения этого значения. 
 *    Создать счетчик количества созданных студентов. 
 *    В функции main() создать несколько (не больше трёх) студентов. Вывести информацию о них.
 */

using uint = unsigned int; // С++11
enum  Gender {Man = 1, Woman};

class Person
{
private:
    string Name;
    uint Age, Weight;
    Gender Who;
public:
    // constructor
    Person(string pName = "", uint pAge = 0, uint pWeight = 0, Gender pWho = Man) :
            Name (pName), Age (pAge), Weight (pWeight), Who (pWho) {};
    // copy constructor
    Person (const Person &obj);
    // default destructor
    ~Person(){};
    // other methods
    void setName (string pName) {Name = pName;};
    void setAge (uint pAge) {Age = pAge;};
    void setWeight (uint pWeight) {Weight = pWeight;};
    void setWho (Gender pWho) {cout << "this option is not applicable in Russia!" << endl;}

    string getName () {return Name;};
    uint getAge () {return Age;};
    uint getWeight () {return Weight;};
    Gender getWho () {return Who;};
};

Person::Person (const Person &obj) {
    Name = obj.Name, Age = obj.Age, Weight = obj.Weight, Who = obj.Who;
}

class Student : public Person // закрытое наследование
{
private:
    uint Study;
    static uint Count;
public:
    // constructor
    Student(string pName = "", uint pAge = 0, uint pWeight = 0, Gender pWho = Man, uint pStudy = 0) :
            Person(pName, pAge, pWeight, pWho), Study (pStudy) {Count++;};
    // copy constructor
    Student (const Student &obj);
    // default destructor
    ~Student(){Count--;};
    // other methods
    void setStudy (uint pStudy) {Study = pStudy;};
    uint getStudy () {return Study;};
    void print (void);
    static uint getCount() {return Count;};
};

Student::Student (const Student &obj) : Person ((const Person) obj) {
    Study = obj.Study;
    Count++;
}

void Student::print () {
    printf ("student: %s, %s, age->%u, weight->%u, study->%u.\n", 
            getName().c_str(), (getWho()==Man ? "man" : "woman!"), getAge(), getWeight(), getStudy());
}

uint Student::Count = 0;

/*
 * 2. Создать классы Apple (яблоко) и Banana (банан), которые наследуют класс Fruit (фрукт). 
 *    У Fruit есть две переменные-члена: name (имя) и color (цвет). 
 *    Добавить новый класс GrannySmith, который наследует класс Apple. 
 */

class Fruit
{
private:
    const string Name;
    const string Color;
public:
    // constructor
    Fruit(string pName, string pColor) :
            Name (pName), Color (pColor) {};
    // copy constructor
    Fruit (const Fruit &obj) : Name (obj.Name), Color (obj.Color) {};
    // default destructor
    ~Fruit(){};
    // other methods
    const string getName () const {return Name;};
    const string getColor () const {return Color;};

    friend class GrannySmith;
    friend class Apple;
};

class Apple : public Fruit
{
public:
    // constructor
    Apple(string pColor) : Fruit((string)"apple", pColor) {};
    // default destructor
    ~Apple(){};
    // other methods
    const string getName () const {return (string)"apple";};
};

class Banana : public Fruit
{
public:
    // constructor
    Banana() : Fruit((string)"banana", (string)"yellow") {};
    // default destructor
    ~Banana(){};
    // other methods
    const string getName () const {return (string)"banana";};
};

class GrannySmith : public Apple
{
public:
    // constructor
    GrannySmith() : Apple((string)"green") {};
    // default destructor
    ~GrannySmith(){};
    // other methods
    const string getName () const {return (string)"Granny Smith" + " " + Apple::getName();};
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

    // Lesson 01. Named states
    cout << "Lesson 02. Inheritance.\n\n";

    // Exercise #1
    cout << "Exercise #1.\n";
    Student std1((string)"Ivan", 20, 60, Man, 2);
    Student std2("Hippolyte ", 21, 65, Man, 3);
    Student std3("Masha (nice tits)", 19, 52, Woman, 1);
    std1.print();
    std2.print();
    std3.print();
    cout << "amount of students: " << Student::getCount() << "." << endl;

    // Exercise #2
    cout << "\nExercise #2.\n";
    Apple a("red");
    Banana b;
    GrannySmith c;

    cout << "My " << a.getName() << " is " << a.getColor() << ".\n";
    cout << "My " << b.getName() << " is " << b.getColor() << ".\n";
    cout << "My " << c.getName() << " is " << c.getColor() << ".\n";

    // return o.k.
    return EXIT_SUCCESS;
} // main