#### ООП на примере C++ / OOP on the example of C++  
#### Урок 07. Поддержка модульности. Написание игры Blackjack / Modularity support. Writing a Blackjack Game

***

1. Создайте класс Date с полями день, месяц, год и методами доступа к этим полям. Перегрузите оператор вывода для данного класса. Создайте два "умных" указателя today и date. Первому присвойте значение сегодняшней даты. Для него вызовите по отдельности методы доступа к полям класса Date, а также выведите на экран данные всего объекта с помощью перегруженного оператора вывода. Затем переместите ресурс, которым владеет указатель today в указатель date. Проверьте, являются ли нулевыми указатели today и date и выведите соответствующую информацию об этом в консоль.  
2. По условию предыдущей задачи создайте два умных указателя date1 и date2.  
    * Создайте функцию, которая принимает в качестве параметра два умных указателя типа Date и сравнивает их между собой (сравнение происходит по датам). Функция должна вернуть более позднюю дату;  
    * Создайте функцию, которая обменивает ресурсами (датами) два умных указателя, переданных в функцию в качестве параметров.  
    > Примечание:  
    > обратите внимание, что первая функция не должна уничтожать объекты, переданные ей в качестве параметров.  
3. Создать класс Deck, который наследует от класса Hand и представляет собой колоду карт. Класс Deck имеет 4 метода:  
    * vold Populate() - Создает стандартную колоду из 52 карт, вызывается из конструктора;  
    * void Shuffle() - Метод, который тасует карты, можно использовать функцию из алгоритмов STL random_shuffle;  
    * vold Deal (Hand& aHand) - метод, который раздает в руку одну карту;  
    * void AddltionalCards (GenericPlayer& aGenerlcPlayer) - раздает игроку дополнительные карты до тех пор, пока он может и хочет их получать.  
    > Обратите внимание на применение полиморфизма.  
4. Реализовать класс Game, который представляет собой основной процесс игры. У этого класса будет 3 поля:  
    * колода карт;  
    * рука дилера;  
    * вектор игроков.  
Конструктор класса принимает в качестве параметра вектор имен игроков и создает объекты самих игроков. В конструкторе создается колода карт и затем перемешивается.  
Также класс имеет один метод play(). В этом методе раздаются каждому игроку по две стартовые карты, а первая карта дилера прячется. Далее выводится на экран информация о картах каждого игра, в т.ч. и для дилера. Затем раздаются игрокам дополнительные карты. Потом показывается первая карта дилера и дилер набирает карты, если ему надо. После этого выводится сообщение, кто победил, а кто проиграл. В конце руки всех игроков очищаются.  
5. Написать функцию main() к игре Blackjack. В этой функции вводятся имена игроков. Создается объект класса Game и запускается игровой процесс. Предусмотреть возможность повторной игры.