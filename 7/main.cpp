#include <iostream>
#include <stdexcept>

template<typename T>
class Vector {
private:
    T* data;
    size_t length;
    size_t capacity;

    /*
     * Перераспределение памяти вектора
     *
     * @param new_capacity новая вместимость вектора.
     */
    void _recopy(size_t new_capacity) {
        T* new_data = new T[new_capacity];
        for (size_t i = 0; i < length; ++i) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }

public:
    /*
     * Конструктор вектора
     *
     * @param n начальная вместимость вектора.
     */
    Vector(size_t n = 0) : data(nullptr), length(0), capacity(n) {
        if (n > 0) {
            data = new T[n];
        }
    }

    /*
     * Деструктор вектора
     */
    ~Vector() {
        delete[] data;
    }

    /*
     * Проверка, пуст ли вектор
     *
     * @return возвращает true, если вектор пуст, иначе false.
     */
    bool IsEmpty() const {
        return length == 0;
    }

    /*
     * Получение длины вектора
     *
     * @return возвращает текущую длину вектора.
     */
    size_t GetLength() const {
        return length;
    }

    /*
     * Получение вместимости вектора
     *
     * @return возвращает текущую вместимость вектора.
     */
    size_t GetCapacity() const {
        return capacity;
    }

    /*
     * Оператор доступа к элементу вектора по индексу
     *
     * @param index индекс элемента.
     * @return возвращает константную ссылку на элемент вектора.
     * @throw std::out_of_range если индекс выходит за границы вектора.
     */
    const T& operator[](size_t index) const {
        if (index >= length) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    /*
     * Изменение вместимости вектора
     *
     * @param new_capacity новая вместимость вектора.
     */
    void Resize(size_t new_capacity) {
        if(new_capacity < length) {
          return;
        }
        _recopy(new_capacity);
        capacity = new_capacity;
    }

    /*
     * Добавление элемента в конец вектора
     *
     * @param value значение добавляемого элемента.
     */
    void PushBack(const T& value) {
        if (length == capacity) {
            size_t new_capacity = (capacity == 0) ? 1 : 2 * capacity;
            _recopy(new_capacity);
        }
        data[length++] = value;
    }

    /*
     * Удаление последнего элемента вектора
     *
     * @throw std::out_of_range если вектор пуст.
     */
    void PopBack() {
        if (IsEmpty()) {
            throw std::out_of_range("Vector is empty");
        }
        --length;
    }

    /*
     * Получение итератора на начало вектора
     *
     * @return возвращает указатель на первый элемент вектора.
     */
    T* begin() {
        return data;
    }

    /*
     * Получение итератора на конец вектора
     *
     * @return возвращает указатель на элемент, следующий за последним в векторе.
     */
    T* end() {
        return data + length;
    }

    /*
     * Получение константного итератора на начало вектора
     *
     * @return возвращает константный указатель на первый элемент вектора.
     */
    const T* begin() const {
        return data;
    }

    /*
     * Получение константного итератора на конец вектора
     *
     * @return возвращает константный указатель на элемент, следующий за последним в векторе.
     */
    const T* end() const {
        return data + length;
    }
};

/*
 * Демонстрация работы вектора
 */
void DemonstrateVector() {
    Vector<std::string> vec;

    std::cout << "Is empty: " << (vec.IsEmpty() ? "yes" : "no") << std::endl;

    vec.PushBack("1");
    vec.PushBack("2");
    vec.PushBack("3");

    std::cout << "Length: " << vec.GetLength() << std::endl;
    std::cout << "Capacity: " << vec.GetCapacity() << std::endl;
    std::cout << "Elements: ";
    for (const auto& element : vec) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    vec.PopBack();
    std::cout << "After PopBack, length: " << vec.GetLength() << std::endl;

    vec.Resize(5);
    std::cout << "After Resize(5), capacity: " << vec.GetCapacity() << std::endl;

    std::cout << "Element on 0 index: " << vec[0] << std::endl;
}

int main() {
    DemonstrateVector();
    return 0;
}
