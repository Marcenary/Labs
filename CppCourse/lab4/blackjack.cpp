#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <random>
#include <algorithm>

using namespace std;

// Класс Карта
class Card {
private:
    string suit; // Масть
    string rank; // Достоинство
public:
    Card(const string& rank, const string& suit) : rank(rank), suit(suit) {}

    int getValue() const {
        if (rank == "J" || rank == "Q" || rank == "K") return 10;
        if (rank == "A") return 11; // Ас может быть 1, это будет учтено в логике игры
        return stoi(rank);
    }

    friend ostream& operator<<(ostream& os, const Card& card) {
        os << card.rank << card.suit;
        return os;
    }
};

// Класс Колода
class Deck {
private:
    vector<Card> cards;
    void shuffleDeck() {
        random_device rd;
        mt19937 g(rd());
        shuffle(cards.begin(), cards.end(), g);
    }

public:
    Deck(int deckSize = 52) {
        const vector<string> suits = {"\u2660", "\u2665", "\u2666", "\u2663"}; // Пики, Черви, Бубны, Трефы
        const vector<string> ranks = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};

        for (int i = 0; i < deckSize / 52; ++i)
            for (const auto& suit : suits)
                for (const auto& rank : ranks)
                    cards.emplace_back(rank, suit);
        shuffleDeck();
    }

    Card drawCard() {
        if (cards.empty())
            throw runtime_error("Колода пуста!");
        Card card = cards.back();
        cards.pop_back();
        return card;
    }

    int size() const { return cards.size(); }
};

// Класс Игрок
class Player {
private:
    vector<Card> hand;
    int balance;
public:
    Player(int initialBalance) : balance(initialBalance) {}

    void addCard(const Card& card) { hand.push_back(card); }

    int getHandValue() const {
        int totalValue = 0;
        int aceCount = 0;
        for (const auto& card : hand) {
            totalValue += card.getValue();
            if (card.getValue() == 11)
                ++aceCount;
        }
        while (totalValue > 21 && aceCount > 0) {
            totalValue -= 10;
            --aceCount;
        }
        return totalValue;
    }

    void resetHand() { hand.clear(); }

    void adjustBalance(int amount) { balance += amount; }

    int getBalance() const { return balance; }

    void showHand() const {
        for (const auto& card : hand)
            cout << card << " ";
        cout << "(Сумма: " << getHandValue() << ")" << endl;
    }

    bool isBusted() const { return getHandValue() > 21; }
};

// Класс Дилер
class Dealer {
private:
    vector<Card> hand;
public:
    void addCard(const Card& card) { hand.push_back(card); }

    int getHandValue() const {
        int totalValue = 0;
        int aceCount = 0;
        for (const auto& card : hand) {
            totalValue += card.getValue();
            if (card.getValue() == 11)
                ++aceCount;
        }
        while (totalValue > 21 && aceCount > 0) {
            totalValue -= 10;
            --aceCount;
        }
        return totalValue;
    }

    void showInitialHand() const {
        if (!hand.empty())
            cout << hand[0] << " ??" << endl;
    }

    void showHand() const {
        for (const auto& card : hand)
            cout << card << " ";
        cout << "(Сумма: " << getHandValue() << ")" << endl;
    }

    bool isBusted() const { return getHandValue() > 21; }

    void resetHand() { hand.clear(); }
};

// Основной класс Игра
class BlackJackGame {
private:
    Deck deck;
    Player player;
    Dealer dealer;

public:
    BlackJackGame(int initialBalance, int deckSize = 52) : deck(deckSize), player(initialBalance), dealer() {}

    void startGame() {
        cout << "Добро пожаловать в игру BlackJack!" << endl;
        bool keepPlaying = true;
        while (keepPlaying && player.getBalance() > 0) {
            playRound();
            char choice;
            cout << "Хотите сыграть еще раз? (y/n): ";
            cin >> choice;
            keepPlaying = (choice == 'y' || choice == 'Y');
        }
        cout << "Игра окончена. Ваш баланс: " << player.getBalance() << endl;
    }

    void playRound() {
        player.resetHand();
        dealer.resetHand();

        int bet;
        cout << "Ваш баланс: " << player.getBalance() << endl;
        cout << "Введите вашу ставку: ";
        cin >> bet;

        if (bet > player.getBalance()) {
            cout << "Недостаточно средств! Попробуйте снова." << endl;
            return;
        }

        player.addCard(deck.drawCard());
        player.addCard(deck.drawCard());
        dealer.addCard(deck.drawCard());
        dealer.addCard(deck.drawCard());

        cout << "Дилер: ";
        dealer.showInitialHand();
        cout << "Вы: ";
        player.showHand();

        bool playerTurn = true;
        while (playerTurn) {
            int choice;
            cout << "1. Хватит  2. Еще" << endl;
            cin >> choice;

            if (choice == 2) {
                player.addCard(deck.drawCard());
                cout << "Вы: ";
                player.showHand();
                if (player.isBusted()) {
                    cout << "Перебор! Вы проиграли!" << endl;
                    player.adjustBalance(-bet);
                    return;
                }
            } else
                playerTurn = false;
        }

        cout << "Дилер открывает карты..." << endl;
        dealer.showHand();
        while (dealer.getHandValue() < 17) {
            dealer.addCard(deck.drawCard());
            cout << "Дилер берет карту." << endl;
            dealer.showHand();
        }

        if (dealer.isBusted() || player.getHandValue() > dealer.getHandValue()) {
            cout << "Поздравляем! Вы выиграли!" << endl;
            player.adjustBalance(bet);
        } else if (player.getHandValue() < dealer.getHandValue()) {
            cout << "Вы проиграли!" << endl;
            player.adjustBalance(-bet);
        } else
            cout << "Ничья!" << endl;
    }
};

int main() {
    BlackJackGame game(10000);
    game.startGame();
    return 0;
}