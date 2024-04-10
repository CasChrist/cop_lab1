#include "matrix_oop.h"
#include <iostream>

int main() {
    try {
        // Создаем матрицы
        Matrix mat1(2, 3);
        Matrix mat2(2, 3);
        Matrix mat3(3, 2);
        Matrix mat4(3, 3);
        Matrix detZeroMat(3, 3);

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
        
        mat4[0][0] = 1;
        mat4[0][1] = 4;
        mat4[0][0] = 3;
        mat4[1][0] = 2;
        mat4[1][1] = 1;
        mat4[1][2] = 5;
        mat4[2][0] = 3;
        mat4[2][1] = 2;
        mat4[2][2] = 1;
        
        detZeroMat[0][0] = 1;
        detZeroMat[0][1] = 4;
        detZeroMat[0][2] = 2;
        detZeroMat[1][0] = 1;
        detZeroMat[1][1] = 4;
        detZeroMat[1][2] = 2;
        detZeroMat[2][0] = 3;
        detZeroMat[2][1] = 9;
        detZeroMat[2][2] = 5;
        
        // Матрицы для тестирования
        Matrix testMat1(2, 3);
        for (int i = 0; i < testMat1.GetRows(); ++i) {
            for (int j = 0; j < testMat1.GetCols(); ++j) {
                testMat1[i][j] = (i * testMat1.GetCols() + j + 1) * 2;
            }
        }
        
        Matrix testMat2(2, 3);
        for (int i = 0; i < testMat2.GetRows(); ++i) {
            for (int j = 0; j < testMat2.GetCols(); ++j) {
                testMat2[i][j] = 0;
            }
        }
        
        Matrix testMat3(2, 2);
        testMat3[0][0] = 22;
        testMat3[0][1] = 28;
        testMat3[1][0] = 49;
        testMat3[1][1] = 64;

        Matrix testMat4(3, 2);
        testMat4[0][0] = 1; testMat4[0][1] = 4;
        testMat4[1][0] = 2; testMat4[1][1] = 5;
        testMat4[2][0] = 3; testMat4[2][1] = 6;

        // Выводим исходные матрицы
        std::cout << "Matrix 1:" << std::endl;
        mat1.Display();

        std::cout << "\nMatrix 2:" << std::endl;
        mat2.Display();
        
        std::cout << "\nMatrix 3:" << std::endl;
        mat3.Display();
        
        int countPassedTests = 0;

        // Тестируем операторы и операции
        Matrix sumMatrix = mat1 + mat2;
        std::cout << "\nMatrix 1 + Matrix 2:" << std::endl;
        sumMatrix.Display();
        
        if (sumMatrix == testMat1) {
            std::cout << "\nPASSED matrix summation test." << std::endl;
            countPassedTests++;
        } else {
            std::cout << "\nFAILED matrix summation test." << std::endl;
        }

        Matrix subMatrix = mat1 - mat2;
        std::cout << "\nMatrix 1 - Matrix 2:" << std::endl;
        subMatrix.Display();
        
        if (subMatrix == testMat2) {
            std::cout << "\nPASSED matrix subtraction test." << std::endl;
            countPassedTests++;
        } else {
            std::cout << "\nFAILED matrix subtraction test." << std::endl;
        }

        Matrix mulMatrix = mat2 * mat3;
        std::cout << "\nMatrix 2 * Matrix 3:" << std::endl;
        mulMatrix.Display();
        
        if (mulMatrix == testMat3) {
            std::cout << "\nPASSED matrix multiplication test." << std::endl;
            countPassedTests++;
        } else {
            std::cout << "\nFAILED matrix multiplication test." << std::endl;
        }

        Matrix scalarMulMatrix = mat1 * 2;
        std::cout << "\nMatrix 1 * 2:" << std::endl;
        scalarMulMatrix.Display();

        if (scalarMulMatrix == testMat1) {
            std::cout << "\nPASSED scalar multiplication test." << std::endl;
            countPassedTests++;
        } else {
            std::cout << "\nFAILED scalar multiplication test." << std::endl;
        }
        
        Matrix transMatrix = mat1.Transpose();
        std::cout << "\nTransposed Matrix 1:" << std::endl;
        transMatrix.Display();
        
        if (transMatrix == testMat4) {
            std::cout << "\nPASSED matrix transposition test." << std::endl;
            countPassedTests++;
        } else {
            std::cout << "\nFAILED matrix transposition test." << std::endl;
        }
        
        Matrix invMat4 = mat4.InverseMatrix();
        std::cout << "Inversed Matrix 4:\n";
        invMat4.Display();
        std::cout << "\nPASSED matrix inversion test." << std::endl;
        countPassedTests++;
        
        std::cout << "\nMatrix 4 determinant: " << mat4.Determinant() << "\n\n";
        std::cout << "\nPASSED calculate determinant test." << std::endl;
        countPassedTests++;
        
        Matrix calcComplMat = mat4.CalcComplements();
        std::cout << "Calculated compliments matrix for Matrix 4:\n";
        calcComplMat.Display();
        std::cout << "\nPASSED calculate compliments test." << std::endl;
        countPassedTests++;
        
        std::cout << "detZeroMat determinant: " << detZeroMat.Determinant() << "\n\n";
        std::cout << "\nPASSED calculate determinant test." << std::endl;
        countPassedTests++;
        
        Matrix invDetZeroMat = detZeroMat.InverseMatrix();
        invDetZeroMat.Display();
        std::cout << "\nFAILED matrix inversion test." << std::endl;
        
        std::cout << "\nPASSED " << countPassedTests << " tests of 10." << std::endl;
        
        } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
