#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <map>
#include <vector>
#include <algorithm>
#include <cctype>
#include <sstream>

// Функция для разделения строки на слова с учетом заданных разделителей
std::vector<std::string> splitIntoWords(const std::string& line) {
    std::vector<std::string> words;
    const char* delimiters = " ,.-:;!"; // Заданные разделители
    char* cstr = new char[line.length() + 1];
    strcpy(cstr, line.c_str());

    char* token = strtok(cstr, delimiters);
    while (token != nullptr) {
        std::string word(token);
        // Преобразование в нижний регистр
        for (char& ch : word) {
            ch = std::tolower(ch);
        }
        words.push_back(word);
        token = strtok(nullptr, delimiters);
    }

    delete[] cstr;
    return words;
}

int main() {
    std::string filename;
    std::cout << "Введите имя файла: ";
    std::cin >> filename;

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл " << filename << std::endl;
        return 1;
    }

    std::map<std::string, int> wordCount;
    std::string line;

    // Чтение файла построчно
    while (std::getline(file, line)) {
        std::vector<std::string> words = splitIntoWords(line);
        for (size_t i = 0; i < words.size(); ++i) {
            const std::string& word = words[i];
            if (word.length() > 3) {
                wordCount[word]++;
            }
        }
    }

    file.close();

    // Перенос данных из std::map в std::vector для сортировки
    std::vector<std::pair<std::string, int>> wordVector;
    for (std::map<std::string, int>::iterator it = wordCount.begin(); it != wordCount.end(); ++it) {
        wordVector.push_back(*it);
    }

    // Сортировка по убыванию частоты встречаемости
    std::sort(wordVector.begin(), wordVector.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
        return a.second > b.second;
    });

    // Вывод слов длиной более 3 букв, встречающихся не менее 7 раз
    std::cout << "\nСлова длиной более 3 букв, встречающиеся не менее 7 раз:\n";
    for (size_t i = 0; i < wordVector.size(); ++i) {
        if (wordVector[i].second >= 7) {
            std::cout << wordVector[i].first << ": " << wordVector[i].second << std::endl;
        }
    }

    return 0;
}