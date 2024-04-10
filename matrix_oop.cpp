#include "matrix_oop.h"
#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

Matrix::Matrix(): rows_(0), cols_(0), matrix_(nullptr) {}

Matrix::Matrix(int rows, int cols): rows_(rows), cols_(cols) {
    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Rows and cols must be greater than zero.");
    }
    
    matrix_ = new double*[rows];
    
    for (int i = 0; i < rows; ++i) {
        matrix_[i] = new double[cols];
    }
}

Matrix::Matrix(const Matrix& other): rows_(other.rows_), cols_(other.cols_) {
    matrix_ = new double*[rows_];
    for (int i = 0; i < rows_; ++i) {
        matrix_[i] = new double[cols_];
        for (int j = 0; j < cols_; j++) {
            matrix_[i][j] = other.matrix_[i][j];
        }
    }
}

Matrix::Matrix(Matrix&& other): rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix_ = nullptr;
}

Matrix::~Matrix() {
    for (int i = 0; i < rows_; i++) {
        delete matrix_[i];
    }
    delete matrix_;
}

void Matrix::Display() const {
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                std::cout << matrix_[i][j] << ' ';
            }
            std::cout << '\n';
        }
        std::cout << std::endl;
    }

bool Matrix::EqMatrix(const Matrix& other) {
    if (rows_ != other.rows_ || cols_ != other.cols_) return false;
    
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            if (matrix_[i][j] != other.matrix_[i][j]) return false;
        }
    }
    return true;
}

void Matrix::SumMatrix(const Matrix& other) {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw std::invalid_argument("Matrix dimensions do not match.");
    }
    
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            matrix_[i][j] += other.matrix_[i][j];
        }
    }
}

void Matrix::SubMatrix(const Matrix& other) {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw std::invalid_argument("Matrix dimensions do not match.");
    }
    
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            matrix_[i][j] -= other.matrix_[i][j];
        }
    }
}

void Matrix::MulNumber(const int num) {
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            matrix_[i][j] *= num;
        }
    }
}

void Matrix::MulMatrix(const Matrix& other) {
    if (cols_ != other.rows_) {
        throw std::invalid_argument("Matrix dimensions do not match.");
    }

    Matrix result(rows_, other.cols_);

    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < other.cols_; ++j) {
            for (int k = 0; k < cols_; ++k) {
                result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
            }
        }
    }

    *this = result;
}

// Оператор сложения
Matrix Matrix::operator+(const Matrix& other) const {
    Matrix result = *this;
    result.SumMatrix(other);
    return result;
}

// Оператор вычитания
Matrix Matrix::operator-(const Matrix& other) const {
    Matrix result = *this;
    result.SubMatrix(other);
    return result;
}

// Оператор умножения на матрицу
Matrix Matrix::operator*(const Matrix& other) const {
    Matrix result = *this;
    result.MulMatrix(other);
    return result;
}

// Оператор умножения на число
Matrix Matrix::operator*(int scalar) const {
    Matrix result = *this;
    result.MulNumber(scalar);
    return result;
}

// Оператор сравнения на равенство
bool Matrix::operator==(const Matrix& other) {
    return EqMatrix(other);
}

// Оператор присваивания
Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        // Очищаем текущие ресурсы
        for (int i = 0; i < rows_; ++i) {
            delete[] matrix_[i];
        }
        delete[] matrix_;

        // Копируем размеры
        rows_ = other.rows_;
        cols_ = other.cols_;

        // Выделяем новые ресурсы
        matrix_ = new double*[rows_];
        for (int i = 0; i < rows_; ++i) {
            matrix_[i] = new double[cols_];
            for (int j = 0; j < cols_; ++j) {
                matrix_[i][j] = other.matrix_[i][j];
            }
        }
    }

    return *this;
}

// Оператор сложения с обновлением
Matrix Matrix::operator+=(const Matrix& other) const {
    Matrix result = *this;
    result.SumMatrix(other);
    return result;
}

// Оператор вычитания с обновлением
Matrix Matrix::operator-=(const Matrix& other) const {
    Matrix result = *this;
    result.SubMatrix(other);
    return result;
}

// Оператор умножения на матрицу с обновлением
Matrix Matrix::operator*=(const Matrix& other) const {
    Matrix result = *this;
    result.MulMatrix(other);
    return result;
}

// Оператор индексации
double* Matrix::operator[](int index) const {
    if (index < 0 || index >= rows_) {
        throw std::out_of_range("Index out of bounds.");
    }

    return matrix_[index];
}

// Оператор транспонирования
Matrix Matrix::Transpose() const {
    Matrix result(cols_, rows_);

    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            result.matrix_[j][i] = matrix_[i][j];
        }
    }

    return result;
}

// Оператор вычисления дополнений
Matrix Matrix::CalcComplements() const {
    Matrix result(rows_ -1, cols_ -1);

    if (rows_ != cols_) cerr << "Matrix is not square.";

    Matrix calc(rows_, cols_);
    int current_rows_result, current_cols_result;
    for (int current_rows = 0; current_rows < rows_; ++current_rows)
        for (int current_cols = 0; current_cols < cols_; ++current_cols) {
            current_rows_result = 0;
            current_cols_result = 0;
            for (int i = 0; i < rows_; ++i)
                for (int j = 0; j < cols_; ++j) {
                    if (j == current_cols || i == current_rows) {
                        continue;
                    } else {
                        result.matrix_[current_rows_result][current_cols_result] = matrix_[i][j];
                        if (current_cols_result == result.GetCols() - 1) {
                            current_rows_result++;
                            current_cols_result = 0;
                        } else {
                            current_cols_result++;
                        }
                    }
                }
            calc.matrix_[current_rows][current_cols] = result.Determinant();
        }
    for (int i = 0; i < rows_; i++)
        for (int j = 0; j < cols_; j++) {
            if (j % 2 == 1 && i % 2 == 0) {
                calc.matrix_[i][j] *= -1;
            } else if (j % 2 == 0 && i % 2 == 1) {
                calc.matrix_[i][j] *= -1;
            }
        }
    return calc;
}

// Оператор вычисления определителя
double Matrix::Determinant() const {
    if (rows_ != cols_) { cerr << "Matrix is not square.\n"; }

    vector<vector<int>> matrixData(rows_, vector<int>(cols_));
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            matrixData[i][j] = matrix_[i][j];
        }
    }

    int n = matrixData.size();

    vector<int> permutation(n);
    for (int i = 0; i < n; ++i) {
        permutation[i] = i;
    }

    double det = 0;
    do {
        int term = 1;
        for (int i = 0; i < n; ++i) {
            term *= matrixData[i][permutation[i]];
        }

        int sign = 1;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (permutation[i] > permutation[j]) {
                    sign *= -1;
                }
            }
        }
        det += sign * term;
    } while (std::next_permutation(permutation.begin(), permutation.end()));

    return det;
}

// Оператор вычисления обратной матрицы
Matrix Matrix::InverseMatrix() const {
    bool flag = true;
    if (rows_ != cols_) {
        cerr << "Matrix is not square.";
        flag = false;
    }
    if (flag) return CalcComplements().Transpose() * (1.0 / Determinant());
    else return Matrix();
}

int Matrix::GetRows() const {
    return rows_;
}

int Matrix::GetCols() const {
    return cols_;
}

void Matrix::SetRows(int rows) {
    if (rows <= 0) {
        throw std::invalid_argument("Number of rows must be greater than zero.");
    }

    // Создаем новую матрицу с указанным числом строк
    double** newMatrix = new double*[rows];
    for (int i = 0; i < rows; ++i) {
        newMatrix[i] = new double[cols_];
        for (int j = 0; j < cols_; ++j) {
            newMatrix[i][j] = 0.0;  // Заполняем нулями
        }
    }

    // Копируем данные из старой матрицы
    int minRows = std::min(rows, rows_);
    for (int i = 0; i < minRows; ++i) {
        for (int j = 0; j < cols_; ++j) {
            newMatrix[i][j] = matrix_[i][j];
        }
    }

    // Освобождаем ресурсы старой матрицы
    for (int i = 0; i < rows_; ++i) {
        delete[] matrix_[i];
    }
    delete[] matrix_;

    // Устанавливаем новое количество строк
    rows_ = rows;

    // Устанавливаем новую матрицу
    matrix_ = newMatrix;
}

void Matrix::SetCols(int cols) {
    if (cols <= 0) {
        throw std::invalid_argument("Number of columns must be greater than zero.");
    }

    // Создаем новую матрицу с указанным числом столбцов
    double** newMatrix = new double*[rows_];
    for (int i = 0; i < rows_; ++i) {
        newMatrix[i] = new double[cols];
        for (int j = 0; j < cols; ++j) {
            newMatrix[i][j] = 0.0;  // Заполняем нулями
        }
    }

    // Копируем данные из старой матрицы
    int minCols = std::min(cols, cols_);
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < minCols; ++j) {
            newMatrix[i][j] = matrix_[i][j];
        }
    }

    // Освобождаем ресурсы старой матрицы
    for (int i = 0; i < rows_; ++i) {
        delete[] matrix_[i];
    }
    delete[] matrix_;

    // Устанавливаем новое количество столбцов
    cols_ = cols;

    // Устанавливаем новую матрицу
    matrix_ = newMatrix;
}
