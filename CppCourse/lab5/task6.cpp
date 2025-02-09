#include <iostream>
#include <list>
#include <algorithm>
#include <random>
#include <ctime>
#include <numeric>
#include <map>

class Card {
public:
    enum Rank { TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE };
    enum Suit { HEARTS, DIAMONDS, CLUBS, SPADES };

    Card(Rank r, Suit s) : rank(r), suit(s) {}

    int getValue() const {
        if (rank >= TWO && rank <= TEN) return rank;
        if (rank == JACK || rank == QUEEN || rank == KING) return 10;
        return 11; // ACE
    }

    void display() const {
        static std::map<Rank, std::string> rankNames = {
            {TWO, "2"}, {THREE, "3"}, {FOUR, "4"}, {FIVE, "5"}, {SIX, "6"},
            {SEVEN, "7"}, {EIGHT, "8"}, {NINE, "9"}, {TEN, "10"},
            {JACK, "J"}, {QUEEN, "Q"}, {KING, "K"}, {ACE, "A"}
        };
        static const char* suitNames[] = {"♥", "♦", "♣", "♠"};
        std::cout << rankNames[rank] << suitNames[suit] << " ";
    }

private:
    Rank rank;
    Suit suit;
};

class Deck {
public:
    Deck() {
        for (int s = 0; s < 4; ++s)
            for (int r = 2; r <= 14; ++r)
                cards.push_back(Card(static_cast<Card::Rank>(r), static_cast<Card::Suit>(s)));
    }

    void shuffle() {
        std::random_device rd;
        std::mt19937 g(rd());
        cards.sort([&](const Card&, const Card&) { return g() % 2 == 0; });
    }

    Card dealCard() {
        if (cards.empty()) throw std::out_of_range("Deck is empty!");
        Card card = cards.front();
        cards.pop_front();
        return card;
    }

private:
    std::list<Card> cards;
};

int calculateHandValue(std::list<Card>& hand) {
    int totalValue = std::accumulate(hand.begin(), hand.end(), 0, [](int sum, const Card& c) {
        return sum + c.getValue();
    });

    if (std::find_if(hand.begin(), hand.end(), [](const Card& c) { return c.getValue() == 11; }) != hand.end() && totalValue > 21) {
        totalValue -= 10; // Adjust for Ace
    }
    return totalValue;
}

int main() {
	system("chcp 65001");
    std::srand(std::time(0));
    Deck deck;
    char choice;
    int balance = 1000; // Начальный баланс

    do {
        if (balance <= 0) {
            std::cout << "Вы банкрот! Игра окончена.\n";
            break;
        }

        int bet;
        std::cout << "Ваш баланс: " << balance << "\nВведите ставку: ";
        std::cin >> bet;
        if (bet > balance || bet <= 0) {
            std::cout << "Неверная ставка. Попробуйте снова.\n";
            continue;
        }

        deck.shuffle();
        std::list<Card> playerHand = { deck.dealCard(), deck.dealCard() };
        std::list<Card> dealerHand = { deck.dealCard(), deck.dealCard() };

        std::cout << "Ваши карты: ";
        for (const auto& card : playerHand) card.display();
        std::cout << "\n";

        int playerValue = calculateHandValue(playerHand);
        std::cout << "Сумма ваших очков: " << playerValue << "\n";

        while (playerValue < 21) {
            std::cout << "Взять еще карту? (y/n): ";
            std::cin >> choice;
            if (choice == 'y' || choice == 'Y') {
                playerHand.push_back(deck.dealCard());
                playerValue = calculateHandValue(playerHand);
                std::cout << "Ваши карты: ";
                for (const auto& card : playerHand) card.display();
                std::cout << "\nСумма ваших очков: " << playerValue << "\n";
            } else break;
        }

        if (playerValue > 21) {
            std::cout << "Вы проиграли! Перебор.\n";
            balance -= bet;
        } else {
            int dealerValue = calculateHandValue(dealerHand);
            std::cout << "Карты дилера: ";
            for (const auto& card : dealerHand) card.display();
            std::cout << "\nСумма очков дилера: " << dealerValue << "\n";

            while (dealerValue < 17) {
                dealerHand.push_back(deck.dealCard());
                dealerValue = calculateHandValue(dealerHand);
                std::cout << "Дилер берет карту. Новые карты дилера: ";
                for (const auto& card : dealerHand) card.display();
                std::cout << "\nСумма очков дилера: " << dealerValue << "\n";
            }

            if (dealerValue > 21 || playerValue > dealerValue) {
                std::cout << "Вы победили!\n";
                balance += 2*bet;
            } else if (dealerValue == playerValue) {
                std::cout << "Ничья!\n";
            } else {
                std::cout << "Дилер победил!\n";
                balance -= bet;
            }
        }

        std::cout << "Хотите сыграть снова? (y/n): ";
        std::cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    return 0;
}

/*
1. **Что такое шаблонная функция? Шаблонный класс?**  
   - **Шаблонная функция** — это функция, которая определяется с использованием шаблона (ключевое слово `template`), позволяя работать с различными типами данных без дублирования кода. Например:
     ```cpp
     template <typename T>
     T max(T a, T b) {
         return a > b ? a : b;
     }
     ```
   - **Шаблонный класс** — это класс, который может быть параметризован типами данных, позволяя создавать объекты с различными типами. Например:
     ```cpp
     template <typename T>
     class Box {
         T value;
     public:
         Box(T val) : value(val) {}
         T getValue() { return value; }
     };
     ```

2. **Как компилятор работает с шаблонами? Статические члены шаблонных классов.**  
   - При компиляции шаблонов создаются их *инстанциации* (конкретные реализации) только тогда, когда шаблон используется с определённым типом. Например, при вызове `max<int>(1, 2)` создаётся инстанциация для `T = int`.
   - **Статические члены шаблонных классов** общие для всех объектов, инстанциированных с одним и тем же типом, но уникальны для каждого типа. Например:
     ```cpp
     template <typename T>
     class MyClass {
         static int count;
     public:
         static void increment() { count++; }
     };
     template <typename T>
     int MyClass<T>::count = 0;
     ```

3. **Что означает явная специализация шаблона? Частичная специализация шаблона?**  
   - **Явная специализация** — это предоставление конкретной реализации шаблона для определённого типа. Например:
     ```cpp
     template <>
     class Box<int> {
         int value;
     public:
         Box(int val) : value(val) {}
         int getValue() { return value; }
     };
     ```
   - **Частичная специализация** применяется только к шаблонным классам и позволяет определить частично специализированную версию для некоторых типов. Например:
     ```cpp
     template <typename T>
     class Box<T*> {
         T* value;
     public:
         Box(T* val) : value(val) {}
         T* getValue() { return value; }
     };
     ```

4. **Что означает идиома SFINAE?**  
   SFINAE (Substitution Failure Is Not An Error) — механизм, при котором неудачная подстановка типов в шаблон не приводит к ошибке компиляции, а просто делает шаблон недоступным. Например:
   ```cpp
   template <typename T>
   typename std::enable_if<std::is_integral<T>::value, T>::type
   func(T value) {
       return value;
   }
   ```

5. **Кратко опишите типы контейнеров STL.**  
   - **Последовательные контейнеры**: `vector`, `deque`, `list`, `array`, `forward_list`. Хранят элементы в линейной последовательности.
   - **Ассоциативные контейнеры**: `map`, `multimap`, `set`, `multiset`. Элементы организованы как дерево, что позволяет быстро искать и сортировать.
   - **Нестандартные контейнеры**: `unordered_map`, `unordered_set`, и их вариации. Используют хеш-таблицы для быстрого доступа.
   - **Адаптеры контейнеров**: `stack`, `queue`, `priority_queue`. Обеспечивают специфические интерфейсы на базе других контейнеров.

6. **Чем отличаются контейнеры vector, deque и list? Как они реализованы в STL?**  
   - **`vector`**: динамический массив с произвольным доступом, хранит элементы в смежной области памяти.
   - **`deque`**: двухсторонняя очередь, поддерживающая быструю вставку и удаление элементов в начале и в конце.
   - **`list`**: двусвязный список, элементы не смежны в памяти, доступ осуществляется через указатели.

7. **Кратко опишите типы итераторов STL и методологию работы с ними.**  
   - **Типы итераторов**:  
     - Input (ввод).
     - Output (вывод).
     - Forward (однопроходный).
     - Bidirectional (двунаправленный).
     - Random Access (произвольный доступ).
   - Итераторы используются для последовательного доступа к элементам контейнера с помощью стандартных алгоритмов, например:  
     ```cpp
     std::vector<int> v = {1, 2, 3};
     for (auto it = v.begin(); it != v.end(); ++it) {
         std::cout << *it << " ";
     }
     ```

8. **Что такое ассоциативный массив? Кратко опишите контейнеры map, multimap, set.**  
   - Ассоциативный массив — структура данных, где ключи ассоциируются с соответствующими значениями.
     - **`map`**: ключи уникальны, организованы в отсортированном порядке.
     - **`multimap`**: ключи могут повторяться, организованы в отсортированном порядке.
     - **`set`**: множество уникальных элементов, хранящихся в отсортированном порядке.

9. **Кратко опишите адаптеры контейнеров stack, queue, priority_queue.**  
   - **`stack`**: реализация стека (последний пришёл — первый ушёл, LIFO).  
   - **`queue`**: очередь (первый пришёл — первый ушёл, FIFO).  
   - **`priority_queue`**: очередь с приоритетом, где элементы извлекаются в порядке убывания (или возрастания) приоритета.

10. **Что такое функтор? Где и как функторы используются в библиотеке STL?**  
    Функтор — это объект, который можно вызывать как функцию (через перегрузку оператора `operator()`):
    ```cpp
    struct Functor {
        void operator()(int x) { std::cout << x << " "; }
    };
    ```
    Они используются в алгоритмах STL, таких как `std::for_each`.

11. **Что означает аббревиатура RAII? Что такое умный указатель?**  
    - **RAII (Resource Acquisition Is Initialization)** — идиома C++, в которой управление ресурсами (память, файлы) завязано на их жизненный цикл. Ресурсы выделяются в конструкторе и освобождаются в деструкторе.
    - **Умный указатель** — это объект, управляющий динамически выделенной памятью. Примеры: `std::unique_ptr`, `std::shared_ptr`, `std::weak_ptr`.
*/