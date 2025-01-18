// task2.cpp
#include <iostream>
#include <vector>
#include <cstring>
#include <stdexcept>
#include <random>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <cctype>
#include <sstream>
#include <map>

using namespace std;

// Функция для чтения файла и анализа слов
void analyzeFile(const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        throw runtime_error("Ошибка открытия файла!");
    }

    map<string, size_t> wordFrequency;
    string word;
    char delimiters[] = " .,-:!;";

    // Чтение файла и подсчет частоты слов
    while (inFile >> word) {
        for (char& ch : word) {
            if (strchr(delimiters, ch)) {
                ch = ' ';
            }
        }

        istringstream iss(word);
        while (iss >> word) {
            if (word.size() > 3) {
                ++wordFrequency[word];
            }
        }
    }

    // Фильтрация слов с частотой >= 7
    vector<pair<string, size_t>> filteredWords;
    for (const auto& [key, value] : wordFrequency) {
        if (value >= 7) {
            filteredWords.emplace_back(key, value);
        }
    }

    // Сортировка по убыванию частоты
    sort(filteredWords.begin(), filteredWords.end(), [](const auto& a, const auto& b) {
        return b.second < a.second;
    });

    // Вывод результатов
    cout << "Слова размером более 3 букв, встречающиеся не менее 7 раз, в порядке убывания частоты:" << endl;
    for (const auto& [key, value] : filteredWords) {
        cout << key << ": " << value << endl;
    }
}

int main() {
    try {
        string filename;
        cout << "Введите имя файла: ";
        cin >> filename;
        analyzeFile(filename);
    } catch (const exception& e) {
        cerr << e.what() << endl;
    }

    return 0;
}