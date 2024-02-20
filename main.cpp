#include "matrix_oop.h"
#include <iostream>

int main() {
    try {
        // Создаем матрицы
        Matrix mat1(2, 3);
        Matrix mat2(2, 3);
        Matrix mat3(3, 2);

        // Заполняем матрицы
        for (int i = 0; i < mat1.GetRows(); ++i) {
            for (int j = 0; j < mat1.GetCols(); ++j) {
                mat1[i][j] = i * mat1.GetCols() + j + 1;
            }
        }

        for (int i = 0; i < mat2.GetRows(); ++i) {
            for (int j = 0; j < mat2.GetCols(); ++j) {
                mat2[i][j] = i * mat2.GetCols() + j + 1;
            }
        }
        
        for (int i = 0; i < mat3.GetRows(); ++i) {
            for (int j = 0; j < mat3.GetCols(); ++j) {
                mat3[i][j] = i * mat3.GetCols() + j + 1;
            }
        }

        // Выводим исходные матрицы
        std::cout << "Matrix 1:" << std::endl;
        mat1.Display();

        std::cout << "\nMatrix 2:" << std::endl;
        mat2.Display();

        // Тестируем операторы и операции
        Matrix sumMatrix = mat1 + mat2;
        std::cout << "\nMatrix 1 + Matrix 2:" << std::endl;
        sumMatrix.Display();

        Matrix subMatrix = mat1 - mat2;
        std::cout << "\nMatrix 1 - Matrix 2:" << std::endl;
        subMatrix.Display();

        Matrix mulMatrix = mat2 * mat3;
        std::cout << "\nMatrix 2 * Matrix 3:" << std::endl;
        mulMatrix.Display();

        Matrix scalarMulMatrix = mat1 * 2;
        std::cout << "\nMatrix 1 * 2:" << std::endl;
        scalarMulMatrix.Display();

        if (mat1 == mat1) {
            std::cout << "\nMatrix 1 is equal to itself." << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
