#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <random>
#include <algorithm>

// Интерфейс IFormattable
class IFormattable {
public:
    virtual ~IFormattable() = default;
    virtual std::string format() const = 0;
};

// Функция prettyPrint
void prettyPrint(const IFormattable& object) {
    std::cout << object.format() << std::endl;
}

// Класс Карта
class Card {
private:
    std::string suit; // Масть
    std::string rank; // Достоинство
public:
    Card(const std::string& rank, const std::string& suit) : rank(rank), suit(suit) {}

    int getValue() const {
        if (rank == "J" || rank == "Q" || rank == "K") return 10;
        if (rank == "A") return 11; // Ас может быть 1, это будет учтено в логике игры
        return std::stoi(rank);
    }

    friend std::ostream& operator<<(std::ostream& os, const Card& card) {
        os << card.rank << card.suit;
        return os;
    }

    std::string toString() const {
        return rank + suit;
    }
};

// Класс DeckAdapter (адаптер объекта)
class Deck;
class DeckAdapter : public IFormattable {
private:
    const Deck& deck;

public:
    DeckAdapter(const Deck& deck) : deck(deck) {}

    std::string format() const override;
};

// Класс Колода
class Deck {
private:
    std::vector<Card> cards;
    void shuffleDeck() {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(cards.begin(), cards.end(), g);
    }

public:
    Deck(int deckSize = 52) {
        const std::vector<std::string> suits = {"\u2660", "\u2665", "\u2666", "\u2663"}; // Пики, Черви, Бубны, Трефы
        const std::vector<std::string> ranks = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};

        for (int i = 0; i < deckSize / 52; ++i) {
            for (const auto& suit : suits) {
                for (const auto& rank : ranks) {
                    cards.emplace_back(rank, suit);
                }
            }
        }
        shuffleDeck();
    }

    Card drawCard() {
        if (cards.empty()) {
            throw std::runtime_error("Колода пуста!");
        }
        Card card = cards.back();
        cards.pop_back();
        return card;
    }

    int size() const {
        return cards.size();
    }

    const std::vector<Card>& getCards() const {
        return cards;
    }
};

// Реализация метода format для DeckAdapter
std::string DeckAdapter::format() const {
    std::string result = "Колода: \n";
    for (const auto& card : deck.getCards()) {
        result += card.toString() + " ";
    }
    return result;
}

// Класс DeckClassAdapter (адаптер класса)
class DeckClassAdapter : public Deck, public IFormattable {
public:
    DeckClassAdapter(int deckSize = 52) : Deck(deckSize) {}

    std::string format() const override {
        std::string result = "Колода: \n";
        for (const auto& card : getCards()) {
            result += card.toString() + " ";
        }
        return result;
    }
};

int main() {
    Deck deck;
    DeckAdapter deckAdapter(deck);
    prettyPrint(deckAdapter);

    DeckClassAdapter classAdapter;
    prettyPrint(classAdapter);

    return 0;
}

/*
Контрольные вопросы
[ОТЧЕТ]
1. Приведите три примера пар классов, находящихся в отношении «has-a»?
Машина, Двигатель, Колесо
2. Укажите сходства и различия композиции и агрегации?
Композиция - это связь между объектами, агрегация - это связь между объектами, которые являются частью другого объекта
3. Опишите суть паттерна делегирования и приведите пример с композицией.
Это паттерн, в котором один класс делегирует работу другому классу.
4. Какими способами можно реализовать композицию в С++?
Композицию можно реализовать, используя указатели на объекты других классов.
5. Что такое исключение? Как генерируются и обрабатываются исключения в С++?
Исключение - это объект, который представляет собою ошибку или неправильное поведение программы.
6. Какие есть стандартные типы исключений в С++?
std::exception, std::logic_error, std::runtime_error
7. Что такое дружественный класс и дружественная функция?
Дружественный класс - это класс, который является частью другого класса.
Дружественная функция - это функция, которая является частью другого класса.
*/