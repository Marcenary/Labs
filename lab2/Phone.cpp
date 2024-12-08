#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Telephone {
    string model;
    string phoneNumber;
    string lastCalledNumber;
    double balance;

public:
    // Конструктор без параметров
    Telephone() : model("Unknown"), phoneNumber("0000000000"), lastCalledNumber(""), balance(0.0) {}

    // Конструктор с параметрами
    Telephone(const string& model, const string& phoneNumber, double balance)
        : model(model), phoneNumber(phoneNumber), lastCalledNumber(""), balance(balance) {}

    // Сеттеры
    void setModel(const string& model) { this->model = model; }
    void setPhoneNumber(const string& phoneNumber) { this->phoneNumber = phoneNumber; }
    void setBalance(double balance) { this->balance = balance; }

    // Геттеры
    string getModel() const { return model; }
    string getPhoneNumber() const { return phoneNumber; }
    string getlastCalledNumber() const { return lastCalledNumber; }
    double getBalance() const { return balance; }

    // Метод для звонка
    void call(const string& number, int minutes) {
        lastCalledNumber = number;
        balance -= minutes * 0.5;
    }

    // Метод для сериализации данных в файл
    void serialize(const string& filename = "telephone.dat") const {
        ofstream outFile(filename, ios::binary);
        if (outFile.is_open()) {
            outFile << model << "\n";
            outFile << phoneNumber << "\n";
            outFile << lastCalledNumber << "\n";
            outFile << balance << "\n";
            outFile.close();
        } else
            cerr << "Unable to open file for writing: " << filename << endl;
    }

    // Метод для десериализации данных из файла
    void deserialize(const string& filename = "telephone.dat") {
        ifstream inFile(filename, ios::binary);
        if (inFile.is_open()) {
            getline(inFile, model);
            getline(inFile, phoneNumber);
            getline(inFile, lastCalledNumber);
            inFile >> balance;
            inFile.close();
        } else
            cerr << "Unable to open file for reading: " << filename << endl;
    }

    // Метод для вывода информации о телефоне
    void printInfo() const {
        cout << "Модель: " << model << endl;
        cout << "Номер телефона: " << phoneNumber << endl;
        cout << "Последний набранный номер: " << lastCalledNumber << endl;
        cout << "Баланс: " << balance << " рублей" << endl;
    }
};

int main() {
    // Создание двух телефонов в куче
    Telephone* phone1 = new Telephone();
    Telephone* phone2 = new Telephone("iPhone 12", "1234567890", 100.0);

    // Установка данных первого телефона с помощью сеттеров
    phone1->setModel("Samsung Galaxy S21");
    phone1->setPhoneNumber("0987654321");
    phone1->setBalance(200.0);

    // Имитация десяти звонков
    phone1->call("1111111111", 2);
    phone1->call("2222222222", 3);
    phone1->call(phone2->getPhoneNumber(), 1);
    phone1->call("1111111111", 1);
    phone1->call("2222222222", 2);
    phone1->call(phone2->getPhoneNumber(), 1);
    phone2->call("3333333333", 2);
    phone2->call("4444444444", 3);
    phone2->call(phone1->getPhoneNumber(), 1);
    phone2->call("3333333333", 1);

    // Вывод информации о телефонах после звонков
    cout << "Телефон 1 - Информация:" << endl;
    phone1->printInfo();
    cout << "Телефон 2 - Информация:" << endl;
    phone2->printInfo();

    // Сериализация данных в файл
    phone1->serialize("phone1.dat");
    phone2->serialize("phone2.dat");

    // Десериализация данных из файла
    Telephone phone3;
    phone3.deserialize("phone1.dat");
    cout << "Прочитанные данные об телефоне 1:" << endl;
    phone3.printInfo();

    // Освобождение памяти
    delete phone1;
    delete phone2;

    return 0;
}
