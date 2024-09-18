#include <iostream>
#include <string>
#include <ctime>
#include <math.h>

enum Type
{
    Square,
    Hexagon,
    Triangle,
    Circle
};

struct Figure
{
    Type type;
    size_t side;
};

/*
 * Генерация фигун
 *
 * @param figures массив фигур для заполнения.
 * @param N размер массива.
 * @return void
 */
void GenerateFigures(Figure *figure, int N) {
    for (int i = 0; i < N; i++) {
        figure[i].type = static_cast<Type>(rand() % 4);
        figure[i].side = rand() % (100 - 1) + 1;
    }
}

/*
 * Вывод фигур
 *
 * @param figures массив фигур для вывода.
 * @param N размер массива.
 * @return void
 */
void PrintFigures(Figure *figure, int N)
{
    for (int i = 0; i < N; i++) {
        std::cout << "Type: " << figure[i].type << " Side: " << figure[i].side << std::endl;
    }
}

/*
 * Вычисление площади шестиугольника
 *
 * param figure фигура
 * 
 * @return площадь
*/
float GetHexagonSquere(Figure figure)
{
    return (3 * figure.side * figure.side) / 2;
}

/*
 * Вычисление площади треугольника
 *
 * param figure фигура
 * 
 * @return площадь
*/
float GetTriangleSquere(Figure figure) {
    return figure.side * figure.side / 2;
}

/*
 * Вычисление площади круга
 *
 * param figure фигура
 * 
 * @return площадь
*/
float GetCircleSquere(Figure figure) {
    return M_PI * figure.side * figure.side;
}

/*
 * Вычисление площади фигуры любого типа
 * 
 * @param figure фигура
 * 
 * @return площадь
 */
float GetSquare(Figure figure)
{
    if(figure.type == 1) {
        return GetHexagonSquere(figure);
    } else if(figure.type == 2) {
        return GetTriangleSquere(figure);
    } else if(figure.type == 3) {
        return GetCircleSquere(figure);
    } else if(figure.type == 0) {
        return figure.side * figure.side;
    }
    return 0;
}

/*
 * Сумма площадей всех фигур
 *
 * @param figures массив фигур
 * 
 * @return сумма площадей
*/
float SumSquare(Figure *figures, int N) {
    float sum = 0;
    for (int i = 0; i < N; i++) {
        sum += GetSquare(figures[i]);
    }
    return sum;
}

/*
 * Количество фигур по типу
 *
 * @param figures массив фигур
 * @param N размер массива
 * @param counts массив счетчиков
 * 
 * @return сумма площадей
*/
void CountFiguresByType(Figure *figures, int N, int *counts) {
    for (int i = 0; i < N; i++) {
        counts[figures[i].type]++;
    }
}

/*
 * Вывод большей площади фигуры от заданной пользователем
 *
 * @param figures массив фигур
 * @param N размер массива
 * @param userSquare площадь пользователя
 * 
 * @return void
*/
void PrintBiggerSquareFigures(Figure *figures, int N, float userSquare) {
    std::cout << "With bigger square: " << std::endl;
    for (int i = 0; i < N; i++) {
        if(GetSquare(figures[i]) > userSquare) {
            PrintFigures(&figures[i], 1);
        }
    }
}

/*
 * Вычисление радиуса описанной окружности в зависимости от типа фигуры
 *
 * @param figure фигура
 * @param N размер массива
 * 
 * @return радиус
*/
float FindRadius(Figure figure) {
    if(figure.type == 3) {
      return figure.side;
    } else if(figure.type == 1) {
      return figure.side;
    } else if(figure.type == 2) {
        return figure.side / sqrt(3);
    } else if(figure.type == 0) {
        return figure.side / sqrt(2);
    }
    return 0;
}

/*
 * Нахождение минимального радиуса который опишет все фигуры
 *
 * @param figures массив фигур
 * @param N размер массива
 * 
 * @return минимальный радиус
*/
float findMinRadius(Figure *figures, int N) {
    float minRadius = FindRadius(figures[0]);
    for(int i = 1; i < N; i++) {
        float radius = FindRadius(figures[i]);
        if(radius > minRadius) {
          minRadius = radius;
        }
    }

    return minRadius;
}


int main() {
    srand(time(0));

    int N;
    std::cout << "Type N: ";
    std::cin >> N;

    Figure *figures = new Figure[N];
    GenerateFigures(figures, N);

    PrintFigures(figures, N);

    int counts[4] = {0};
    CountFiguresByType(figures, N, counts);
    for (int i = 0; i < 4; i++) {
        std::cout << "Count " << i << ": " << counts[i] << std::endl;
    }

    float userSquare;
    std::cout << "Type square: ";
    std::cin >> userSquare;

    PrintBiggerSquareFigures(figures, N, userSquare);

    float minRadius = findMinRadius(figures, N);
    std::cout << "Min radius: " << minRadius << std::endl;

    std::cout << "Sum square: " << SumSquare(figures, N) << std::endl;
}