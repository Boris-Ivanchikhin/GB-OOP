// *** Урок 04. Отношения между объектами в С++ / Relationships between objects in C++

#include <locale.h>  // Для setlocale (LC_ALL, "")
#include <iostream>
#include <cassert> // для assert()
#include <cstdlib> // Для rand()

#include <algorithm>
#include <vector>
#include <set>
#include <iterator>

using namespace std;

/*
 * 1. Добавить в контейнерный класс, который был написан в этом уроке, методы:
 *      • для удаления последнего элемента массива (аналог функции pop_back() в векторах);
 *      • для удаления первого элемента массива (аналог pop_front() в векторах);
 *      • для сортировки массива;
 *      • для вывода на экран элементов.
 */

using uint = unsigned int; // С++11

// Разделение по схеме Lomuto
int partition (int a[], int start, int end) {
    // Выбираем крайний правый элемент в качестве опорного элемента массива
    int pivot = a[end];
    // элементы, меньшие точки поворота, будут перемещены влево от `pIndex`
    // элементы больше, чем точка поворота, будут сдвинуты вправо от `pIndex`
    // равные элементы могут идти в любом направлении
    int pIndex = start;
    // каждый раз, когда мы находим элемент, меньший или равный опорному, `pIndex`
    // увеличивается, и этот элемент будет помещен перед опорной точкой.
    for (uint i = start; i < end; i++) {
        if (a[i] <= pivot) {
            swap(a[i], a[pIndex]);
            pIndex++;
        }
    }
    // поменять местами `pIndex` с пивотом
    swap (a[pIndex], a[end]);
    // вернуть `pIndex` (индекс опорного элемента)
    return pIndex;
}

// Процедура быстрой сортировки
void quickSort (int a[], int start, int end) {
    if (start >= end) return;
    // переставить элементы по оси
    int pivot = partition(a, start, end);
    // повторяем подмассив, содержащий элементы, меньшие опорной точки
    quickSort(a, start, pivot - 1);
    // повторяем подмассив, содержащий элементы, превышающие точку опоры
    quickSort(a, pivot + 1, end);
}

class ArrayInt
{
private:

    uint m_length;
    int *m_data;

public:

    ArrayInt() : m_length(0), m_data(nullptr) {};
    ArrayInt(int length) : m_length(length)
    {
        assert(length >= 0);
        if (length > 0)
            m_data = new int[length];
        else
            m_data = nullptr;
    };
    ~ArrayInt()
    {
        delete[] m_data;
    };

    void erase();
    uint getLength();
    void resize(uint newLength);
    void insertBefore(int value, uint index);
    void push_back(int value) {insertBefore (value, m_length);};

    void pop_back();
    void pop_front();
    void sort();
    
    int& operator[] (const uint index);
    const int& operator[] (const uint index) const;
    friend ostream& operator <<(ostream& output, const ArrayInt& value);
    
};

void ArrayInt::erase() {
    delete[] m_data;
    m_data = nullptr;
    m_length = 0;
} 

uint ArrayInt::getLength() {
    return m_length;
}

void ArrayInt::resize(uint newLength) {
    if (newLength == m_length)
        return;

    if (newLength <= 0) {
        erase();
        return;
    }

    int *data = new int[newLength];
    if (m_length > 0) {
        int elementsToCopy = (newLength > m_length) ? m_length : newLength;
        for (int index=0; index < elementsToCopy ; ++index)
            data[index] = m_data[index];
    }

    delete[] m_data;
    m_data = data;
    m_length = newLength;
}

void ArrayInt::insertBefore(int value, uint index) {
    assert(index >= 0 && index <= m_length);

    int *data = new int[m_length+1];
    for (int before=0; before < index; ++before)
        data[before] = m_data[before];

    data [index] = value;
    for (int after=index; after < m_length; ++after)
        data[after+1] = m_data[after];

    delete[] m_data;
    m_data = data;
    ++m_length;
}

void ArrayInt::pop_back() {
    if (m_length <= 0) return;
    else if (m_length == 1) {
        erase ();
        return;
    }
    int *data = new int [--m_length];
    for (int index = 0; index < m_length; ++index)
        data [index] = m_data [index];

    delete[] m_data;
    m_data = data;
}

void ArrayInt::pop_front() {
    if (m_length <= 0) return;
    else if (m_length == 1) {
        erase ();
        return;
    }
    int *data = new int [--m_length];
    for (int index = 1; index < m_length + 1; ++index)
        data [index - 1] = m_data [index];

    delete[] m_data;
    m_data = data;
}

void ArrayInt::sort() {
    if (!m_length || m_length == 1)
        return;
    quickSort (m_data, 0, m_length - 1);
}

// * для неконстантных объектов: может использоваться как для присваивания значений элементам, так и для их просмотра
int& ArrayInt::operator[] (const uint index) {
    assert(index >= 0 && index < m_length);
    return m_data [index];
}

// * для константных объектов: используется только для просмотра (вывода) элементов массива
const int& ArrayInt::operator[] (const uint index) const {
    assert(index >= 0 && index < m_length);
    return m_data [index];
}

ostream& operator <<(ostream& output, const ArrayInt& value) {
    output << "{";
    for (uint index = 0; index < value.m_length; ++index)
        output << (index ? " " : "") << value [index];
    output << "}" << endl;
    return output;
}

int rData()
{
    return rand()%10+1;
}

// Функция, вызываемая при завершении работы
void endFunction (void)
{
    // Вывод сообщения о завершении работы
    puts ("\nthe work is completed!");
}

#define MAX_COUNT 5

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
    
    ArrayInt AI;
    srand((unsigned int)time(0));
    for (int i = 0; i < MAX_COUNT; ++i)
        AI.push_back (rData());
    cout << AI;
    AI.sort();
    cout << "after sorting: " << AI;
    AI.pop_back();
    cout << "after pop_back(): " << AI;
    AI.pop_front();
    cout << "after pop_front(): " << AI;

    // Exercise #2
    cout << "\nExercise #2.\n";
    vector<int> vct (MAX_COUNT);
    generate (vct.begin(), vct.end(), rData);
    cout << "source vector: ";
    copy (vct.begin(), vct.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    set<int> st (vct.begin(), vct.end());
    cout << "total different numbers = " << st.size() << endl << "they are: ";
    copy (st.begin(), st.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    // Exercise #3
    cout << "\nExercise #3.\n";
    cout << "see files «blackjack.*»" << endl;

    // return o.k.
    return EXIT_SUCCESS;
} // main