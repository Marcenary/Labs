#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <random>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <cctype>

// Шаблонный класс DataManager
template <typename T>
class DataManager {
private:
    static constexpr size_t MAX_CAPACITY = 64;
    std::vector<T> data;
    std::string dumpFile = "dump.dat";

    void dumpToFile() {
        std::ofstream outFile(dumpFile, std::ios::app | std::ios::binary);
        if (!outFile) {
            throw std::runtime_error("Ошибка открытия файла для записи!");
        }
        outFile.write(reinterpret_cast<const char*>(data.data()), data.size() * sizeof(T));
        outFile.close();
        data.clear();
    }

    void loadFromFile() {
        std::ifstream inFile(dumpFile, std::ios::in | std::ios::binary);
        if (!inFile || inFile.peek() == std::ifstream::traits_type::eof()) {
            return; // Файл пуст или отсутствует
        }
        std::vector<T> temp((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
        inFile.close();
        data.insert(data.end(), temp.begin(), temp.end());
        std::ofstream clearFile(dumpFile, std::ios::trunc);
        clearFile.close();
    }

public:
    void push(T elem) {
        if (data.size() == MAX_CAPACITY) {
            dumpToFile();
        }
        data.push_back(elem);
    }

    void push(T elems[], size_t n) {
        for (size_t i = 0; i < n; ++i) {
            push(elems[i]);
        }
    }

    T peek() const {
        if (data.empty()) {
            throw std::runtime_error("Контейнер пуст!");
        }
        return data.back();
    }

    T pop() {
        if (data.empty()) {
            loadFromFile();
            if (data.empty()) {
                throw std::runtime_error("Контейнер пуст и файл не содержит данных!");
            }
        }
        T elem = data.back();
        data.pop_back();
        return elem;
    }

    void display() const {
        std::copy(data.begin(), data.end(), std::ostream_iterator<T>(std::cout, " "));
        std::cout << std::endl;
    }
};

// Явная специализация для char
template <>
class DataManager<char> {
private:
    static constexpr size_t MAX_CAPACITY = 64;
    std::vector<char> data;
    std::string dumpFile = "dump.dat";

    void dumpToFile() {
        std::ofstream outFile(dumpFile, std::ios::app | std::ios::binary);
        if (!outFile) {
            throw std::runtime_error("Ошибка открытия файла для записи!");
        }
        outFile.write(data.data(), data.size());
        outFile.close();
        data.clear();
    }

    void loadFromFile() {
        std::ifstream inFile(dumpFile, std::ios::in | std::ios::binary);
        if (!inFile || inFile.peek() == std::ifstream::traits_type::eof()) {
            return; // Файл пуст или отсутствует
        }
        std::vector<char> temp((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
        inFile.close();
        data.insert(data.end(), temp.begin(), temp.end());
        std::ofstream clearFile(dumpFile, std::ios::trunc);
        clearFile.close();
    }

public:
    void push(char elem) {
        if (std::ispunct(elem)) {
            elem = '_';
        }
        if (data.size() == MAX_CAPACITY) {
            dumpToFile();
        }
        data.push_back(elem);
    }

    void push(char elems[], size_t n) {
        for (size_t i = 0; i < n; ++i) {
            push(elems[i]);
        }
    }

    char peek() const {
        if (data.empty()) {
            throw std::runtime_error("Контейнер пуст!");
        }
        return data.back();
    }

    char pop() {
        if (data.empty()) {
            loadFromFile();
            if (data.empty()) {
                throw std::runtime_error("Контейнер пуст и файл не содержит данных!");
            }
        }
        char elem = data.back();
        data.pop_back();
        return elem;
    }

    char popUpper() {
        return std::toupper(pop());
    }

    char popLower() {
        return std::tolower(pop());
    }

    void display() const {
        std::copy(data.begin(), data.end(), std::ostream_iterator<char>(std::cout, " "));
        std::cout << std::endl;
    }
};

int main() {
    try {
        // Пример с int
        DataManager<int> intManager;
        intManager.push(10);
        intManager.push(20);
        int arr[] = {30, 40, 50};
        intManager.push(arr, 3);
        intManager.display();
        std::cout << "Peek: " << intManager.peek() << std::endl;
        std::cout << "Pop: " << intManager.pop() << std::endl;
        intManager.display();

        // Пример с double
        DataManager<double> doubleManager;
        doubleManager.push(1.1);
        doubleManager.push(2.2);
        double arrD[] = {3.3, 4.4, 5.5};
        doubleManager.push(arrD, 3);
        doubleManager.display();

        // Пример с char
        DataManager<char> charManager;
        charManager.push('a');
        charManager.push('!');
        char arrC[] = {'b', 'c', '?'};
        charManager.push(arrC, 3);
        charManager.display();
        std::cout << "PopUpper: " << charManager.popUpper() << std::endl;
        std::cout << "PopLower: " << charManager.popLower() << std::endl;
        charManager.display();

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

