#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>

template<typename T>
class SortedVector : public std::vector<T> {
public:
    /*
     * Конструктор по умолчанию
     */
    SortedVector() : std::vector<T>() {}
    
    /*
     * Конструктор из списка инициализации
     * 
     * @param init список начальных значений
     */
    SortedVector(std::initializer_list<T> init) : std::vector<T>(init) {
        std::sort(this->begin(), this->end());
    }

    /*
     * Подсчет количества элементов, делящихся на заданное число
     *
     * @param n делитель для проверки
     * @return количество элементов, делящихся на n без остатка
     */
    size_t countDivisibleBy(const T& n) const {
        return std::count_if(this->begin(), this->end(), 
            [n](const T& elem) { return elem % n == 0; });
    }

    /*
     * Вставка элемента с сохранением сортировки
     *
     * @param value значение для вставки
     * @return итератор на вставленный элемент
     */
    typename std::vector<T>::iterator insert(const T& value) {
        auto pos = std::lower_bound(this->begin(), this->end(), value);
        return std::vector<T>::insert(pos, value);
    }

    /*
     * Вывод всех возможных перестановок элементов вектора
     */
    void printPermutations() {
        std::sort(this->begin(), this->end());
        
        do {
            std::copy(this->begin(), this->end(), 
                     std::ostream_iterator<T>(std::cout, " "));
            std::cout << std::endl;
        } 
        while(std::next_permutation(this->begin(), this->end()));
    }

    /*
     * Оператор вывода в поток
     *
     * @param os поток вывода
     * @param sv вектор для вывода
     * @return ссылка на поток вывода
     */
    friend std::ostream& operator<<(std::ostream& os, const SortedVector<T>& sv) {
        std::copy(sv.begin(), sv.end(), 
                 std::ostream_iterator<T>(os, " "));
        return os;
    }
};

// Пример использования
int main() {
    SortedVector<int> sv = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    
    std::cout << "Sorted vector: " << sv << std::endl;
    
    std::cout << "Elements divisible by 3: " << sv.countDivisibleBy(3) << std::endl;
    
    sv.insert(7);
    std::cout << "After inserting 7: " << sv << std::endl;
    
    SortedVector<int> perm = {1, 2, 3};
    std::cout << "Permutations of {1, 2, 3}:" << std::endl;
    perm.printPermutations();
    
    return 0;
}
