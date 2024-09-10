
#include <iostream>

/*
 * Заполнение матрицы нулями.
 *
 * @return void
 */
void FillMatrixZeros(int **matrix, int N) {
    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < N; j++) {
            matrix[i][j] = 0;
        }
    }
}
/*
 * Очистка матрицы.
 *
 * @return void
 */
void ClearMatrix(int **matrix, int N) {
    return FillMatrixZeros(matrix, N);
}

/*
 * Вывод матрицы.
 *
 * @param matrix - матрица
 * @param N - размер матрицы
 * @return void
 */
void PrintMatrix(int **matrix, int N) {
    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < N; j++) {
            std::cout << " " << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

/*
 * Заполнение матрицы случайными числами относительно главной диагонали.
 *
 * @param matrix - матрица
 * @param N - размер матрицы
 * @return void
 */
void FillSymmetricMainDiagonal(int** matrix, int N) {
    ClearMatrix(matrix, N);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j <= i; ++j) {
            if(j == i) continue;
            int randomInt = rand() % 10;
            matrix[i][j] = randomInt;
            matrix[j][i] = randomInt;
        }
    }
}

/*
 * Заполнение матрицы случайными числами относительно побочной диагонали.
 *
 * @param matrix - матрица
 * @param N - размер матрицы
 * @return void
 */
void FillSymmetricSecondaryDiagonal(int** matrix, int N) {
    ClearMatrix(matrix, N);
    for (int i = 0; i< N; ++i) {
        for(int j = 0; j < N; ++j) {
            if(N-1-j == i) {
                matrix[i][N-1-j] = 0;
                continue;
            }
            if (j <= N - 1 - i) {
                int randInt = rand() % 10;
                matrix[i][j] = randInt;
                matrix[N-1-j][N-1-i] = randInt;
            }
        }
    }
}

/*
 * Заполнение матрицы с помощью треугольника Паскаля.
 *
 * @param matrix - матрица
 * @param N - размер матрицы
 * @return void
 */
void FillPascalTriangle(int** matrix, int N) {
    ClearMatrix(matrix, N);
    for (int i = N - 1; i >= 0; i++) {
        for (int j = 0; j <= N; j++) {
            if (j == i) {
                matrix[i][j] = 1;
            } else {
                int randInt = rand() % 10;
                matrix[i][j] = randInt;
                matrix[N-1-i][N-1-j] = randInt;
            }
        }
    }
}

/*
 * Найти минимальное значение.
 *
 * @param a - первое значение
 * @param b - второе значение
 * @return минимальное значение
 */
int Min(int a, int b) {
    return a < b ? a : b;
}

/*
 * Найти максимальное значение.
 *
 * @param a - первое значение
 * @param b - второе значение
 * @return максимальное значение
 */
int Max(int a, int b) {
    return a > b ? a : b;
}

/*
 * Заполнение матрицы для игры Сапёр.
 *
 * @param matrix - матрица
 * @param N - размер матрицы
 * @return void
 */
void FillSaper(int** matrix, int N) {
    ClearMatrix(matrix, N);

    int filled = 0;
    int countMines = rand() % (N*N - 2) + 2;

    while (filled < countMines) {
        int x = rand() % N;
        int y = rand() % N;
        if(matrix[x][y] != -1) {
            matrix[x][y] = -1;
            filled++;
        } else {
            continue;
        }

        for(int i = Max(x - 1, 0); i <= Min(x + 1, N - 1); i++) {
            for(int j = Max(y - 1, 0); j <= Min(y + 1, N - 1); j++) {
                if(matrix[i][j] != -1) {
                    matrix[i][j]++;
                }
            }
        }
    }

}

void ClearMemory(int** matrix, int N) {
    for (int i = 0; i < N; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

/*
 * Функция запрашивающая у пользователя выбор для действий с матрицей.
 *
 * @param matrix - матрица
 * @param N - размер матрицы
 * @return void
 */
void MatrixActions(int **matrix, int N) {
    int choice;

    do {
        std::cout << "\nSelect an action:\n";
        std::cout << "1. Clear Matrix\n";
        std::cout << "2. Main Diagonal\n";
        std::cout << "3. Secondary Diagonal\n";
        std::cout << "4. Pascal Triangle\n";
        std::cout << "5. Fill Saper\n";
        std::cout << "6. Print Matrix\n";
        std::cout << "0. Exit\n";
        std::cin >> choice;

        switch (choice) {
            case 1:
                ClearMatrix(matrix, N);
                std::cout << "All is cleared.\n";
                break;
            case 2:
                FillSymmetricMainDiagonal(matrix, N);
                std::cout << "All is filled.\n";
                break;
            case 3:
                FillSymmetricSecondaryDiagonal(matrix, N);
                std::cout << "All is filled.\n";
                break;
            case 4:
                FillPascalTriangle(matrix, N);
                std::cout << "All is filled.\n";
                break;
            case 5:
                FillSaper(matrix, N);
                std::cout << "All is filled.\n";
                break;
            case 6:
                PrintMatrix(matrix, N);
                break;
            
            case 0:
                ClearMemory(matrix, N);
                break;
            default:
                std::cout << "Wrong choice.\n";
                break;
        }
    } while (choice != 0);
}

int main() {

    int N;
    std::cout << "Type N: ";
    std::cin >> N;
    
    int** matrix = new int*[N];
    for (int i = 0; i < N; ++i) {
        matrix[i] = new int[N];
    }
    FillMatrixZeros(matrix, N);

    MatrixActions(matrix, N);

    return 0;
}