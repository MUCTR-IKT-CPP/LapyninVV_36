#include <iostream>
#include <string>
#include <ctime>

#define STRING_LENGTH 10000
#define COUNT_LETTERS 26

int main() {
    srand(time(0));
    std::string rand_str;
    int letters_map[COUNT_LETTERS] = {0};

    for (int i = 0; i < STRING_LENGTH; ++i) {
        char rand_letter = 'a' + std::rand() % 26;
        rand_str += rand_letter;
        letters_map[rand_letter - 'a']++;
    }

    for (char letter = 'a'; letter <= 'z'; ++letter) {
        std::cout << letter << ": " << letters_map[letter - 'a'] << std::endl;
    }

    return 0;
}