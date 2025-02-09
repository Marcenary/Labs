#include <iostream>
#include <string>
#include <algorithm>

// Interface for callable devices
class ICallable {
public:
    virtual void call(const std::string& recepient) = 0;
};

// Base class for all devices
class Device {
protected:
    std::string firm;
    std::string model;
    double weight;
    std::string color;
    double price;

public:
    Device(const std::string& firm, const std::string& model, double weight, const std::string& color, double price)
        : firm(firm), model(model), weight(weight), color(color), price(price) {}

    virtual void printInfo() const {
        std::cout << "Фирма: " << firm << std::endl;
        std::cout << "Млдель: " << model << std::endl;
        std::cout << "Вес: " << weight << " кг" << std::endl;
        std::cout << "Цвет: " << color << std::endl;
        std::cout << "Цена: " << price << " руб" << std::endl;
    }
};

// Class for telephones
class Telephone : public Device, public ICallable {
protected:
    std::string phoneNumber;
    std::string lastCalledNumber;
    double balance;
    double chargeLevel;

public:
    Telephone(const std::string& firm, const std::string& model, double weight, const std::string& color, double price,
              const std::string& phoneNumber, double balance, double chargeLevel)
        : Device(firm, model, weight, color, price), phoneNumber(phoneNumber), balance(balance), chargeLevel(chargeLevel) {}

    void call(const std::string& recepient) override {
        if (!all_of(recepient.begin(), recepient.end(), ::isdigit)) {
            std::cerr << "Не верный номер!" << std::endl;
            return;
        }

        balance -= 0.5;
        chargeLevel -= 0.03;
        lastCalledNumber = recepient;
        std::cout << "Вызов " << recepient << "..." << std::endl;
    }

    void printInfo() const override {
        Device::printInfo();
        std::cout << "Номер телефона: " << phoneNumber << std::endl;
        std::cout << "Последний вызванный номер: " << lastCalledNumber << std::endl;
        std::cout << "Баланс: " << balance << " $" << std::endl;
        std::cout << "Уровень заряда: " << chargeLevel * 100 << "%" << std::endl;
    }
};

// Class for mobile devices
class MobileDevice : public Telephone {
protected:
    double screenSize;

public:
    MobileDevice(const std::string& firm, const std::string& model, double weight, const std::string& color, double price,
                 const std::string& phoneNumber, double balance, double chargeLevel, double screenSize)
        : Telephone(firm, model, weight, color, price, phoneNumber, balance, chargeLevel), screenSize(screenSize) {}

    void printInfo() const override {
        Telephone::printInfo();
        std::cout << "Размер экрана: " << screenSize << " inches" << std::endl;
    }
};

// Class for tablets
class Tablet : public Device, public ICallable {
protected:
    double chargeLevel;

public:
    Tablet(const std::string& firm, const std::string& model, double weight, const std::string& color, double price,
           double chargeLevel)
        : Device(firm, model, weight, color, price), chargeLevel(chargeLevel) {}

    void call(const std::string& recepient) override {
        chargeLevel -= 0.1;
        std::cout << "Вызов " << recepient << " в Skype..." << std::endl;
    }

    void printInfo() const override {
        Device::printInfo();
        std::cout << "Уровень заряда: " << chargeLevel * 100 << "%" << std::endl;
    }
};

int main() {
    Telephone telephone1("Apple", "iPhone 12", 0.2, "Space Gray", 999, "1234567890", 100, 0.8);
    Telephone telephone2("Samsung", "Galaxy S21", 0.2, "Black", 899, "9876543210", 50, 0.9);

    MobileDevice mobileDevice1("Apple", "iPhone 12 Pro", 0.2, "Gold", 1099, "1234567890", 100, 0.8, 5.8);
    MobileDevice mobileDevice2("Samsung", "Galaxy S21 Ultra", 0.2, "Silver", 1299, "9876543210", 50, 0.9, 6.8);

    Tablet tablet1("Apple", "iPad Air", 0.5, "Silver", 699, 0.7);
    Tablet tablet2("Samsung", "Galaxy Tab S7", 0.5, "Black", 799, 0.6);

    telephone1.printInfo();
    telephone1.call("9876543210");

    telephone2.printInfo();
    telephone2.call("1234567890");

    mobileDevice1.printInfo();
    mobileDevice1.call("9876543210");

    mobileDevice2.printInfo();
    mobileDevice2.call("1234567890");

    tablet1.printInfo();
    tablet1.call("1234567890");

    tablet2.printInfo();
    tablet2.call("9876543210");

    return 0;
}