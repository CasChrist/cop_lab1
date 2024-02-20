#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

class Matrix {
    private:
    int rows_, cols_;
    double **matrix_;
    
    public:
    Matrix();
    Matrix(int rows, int cols);
    Matrix(const Matrix& other);
    Matrix(Matrix&& other);
    ~Matrix();
    void Display() const;
    
    bool EqMatrix(const Matrix& other);
    void SumMatrix(const Matrix& other);
    void SubMatrix(const Matrix& other);
    void MulNumber(const int num);
    void MulMatrix(const Matrix& other);
    
    Matrix Transpose() const;
    Matrix CalcComplements() const;
    double Determinant() const;
    Matrix InverseMatrix() const;
    
    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    Matrix operator*(int scalar) const;
    bool operator==(const Matrix& other);
    Matrix &operator=(const Matrix& other);
    Matrix operator+=(const Matrix& other) const;
    Matrix operator-=(const Matrix& other) const;
    Matrix operator*=(const Matrix& other) const;
    double *operator[](int index) const;
    
    int GetRows() const;
    int GetCols() const;
    void SetRows(int rows);
    void SetCols(int cols);

    
};

#endif