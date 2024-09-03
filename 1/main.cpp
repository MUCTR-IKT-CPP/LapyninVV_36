#include <iostream>
#include <string>
#include <ctime>

#define COUNT_LETTERS 26

/*
 * Функция генерации случайной буквы
 *
 * @return возвращает случайную букву
 */
char GetRandomChar() {
    return 'a' + rand() % COUNT_LETTERS;
}

/*
 * Функция заполнения строки случайными буквами
 *
 * @param str - строка для заполнения
 * @param length - длина строки
 */
void FillStringRandomly(std::string& str, int length) {
    for (int i = 0; i < length; ++i) {
        str += GetRandomChar();
    }
}

/*
 * Функция для подсчета количества букв в строке
 *
 * @param str - строка для подсчета
 * @param letters_map - массив для хранения количества букв
 */
void CountLetters(const std::string& str, int* letters_map) {
    for (int i = 0; i < str.length(); ++i) {
        letters_map[str[i] - 'a']++;
    }
}

/*
 * Функция для вывода результата в консоль
 *
 * @param letters_map - массив для хранения количества букв
 */
void PrintResult(int* letters_map) {
    for (char letter = 'a'; letter <= 'z'; ++letter) {
        std::cout << letter << ": " << letters_map[letter - 'a'] << std::endl;
    }
}

int main() {
    srand(time(0));

    const int STRING_LENGTH = 10000;

    std::string rand_str;
    int letters_map[COUNT_LETTERS] = {0};

    FillStringRandomly(rand_str, STRING_LENGTH);

    CountLetters(rand_str, letters_map);

    PrintResult(letters_map);
    return 0;
}