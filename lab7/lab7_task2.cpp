//
// Created by Ксения on 17.11.2025.
//
#include <iostream>
#include <stdexcept>
#include <vector>
struct Matrix {
    int** data_ = nullptr;
    size_t n_ = 0u;  // столбцы
    size_t m_ = 0u;  // строки
};
// заполнение нулями матрицы
void Construct(Matrix& out, size_t n, size_t m) {
    // освобождение памяти
    out.n_ = n;
    out.m_ = m;
    out.data_ = new int*[m];
    for (size_t i = 0; i < m; ++i) {
        out.data_[i] = new int[n];
        for (size_t j = 0; j < n; ++j) {
            out.data_[i][j] = 0;
        }
    }
}
// освобождение выделенной памяти
void Destruct(Matrix& in) {
    if (in.data_ != nullptr) {
        for (size_t i = 0; i < in.m_; ++i) {
            delete[] in.data_[i];
        }
        delete[] in.data_;
        in.data_ = nullptr;
    }
    in.n_ = 0;
    in.m_ = 0;
}
// копия матрицы |matrix|
Matrix Copy(const Matrix& matrix) {
    Matrix result;
    Construct(result, matrix.n_, matrix.m_);
    for (size_t i = 0; i < matrix.m_; ++i) {
        for (size_t j = 0; j < matrix.n_; ++j) {
            result.data_[i][j] = matrix.data_[i][j];
        }
    }
    return result;
}
// сумма матриц
Matrix Add(const Matrix& a, const Matrix& b) {
    if (a.n_ != b.n_ || a.m_ != b.m_) {
        return Matrix{};  // пустая матрица
    }
    Matrix result;
    Construct(result, a.n_, a.m_);
    for (size_t i = 0; i < a.m_; ++i) {
        for (size_t j = 0; j < a.n_; ++j) {
            result.data_[i][j] = a.data_[i][j] + b.data_[i][j];
        }
    }
    return result;
}
// разница матриц
Matrix Sub(const Matrix& a, const Matrix& b) {
    if (a.n_ != b.n_ || a.m_ != b.m_) {
        return Matrix{};
    }
    Matrix result;
    Construct(result, a.n_, a.m_);
    for (size_t i = 0; i < a.m_; ++i) {
        for (size_t j = 0; j < a.n_; ++j) {
            result.data_[i][j] = a.data_[i][j] - b.data_[i][j];
        }
    }
    return result;
}
// произведение матриц
Matrix Mult(const Matrix& a, const Matrix& b) {
    if (a.n_ != b.m_) {
        return Matrix{};
    }
    Matrix result;
    Construct(result, b.n_, a.m_);
    for (size_t i = 0; i < a.m_; ++i) {
        for (size_t j = 0; j < b.n_; ++j) {
            result.data_[i][j] = 0;
            for (size_t k = 0; k < a.n_; ++k) {
                result.data_[i][j] += a.data_[i][k] * b.data_[k][j];
            }
        }
    }
    return result;
}
// транспонирование матрицы
void Transposition(Matrix& matrix) {
    Matrix temp;
    Construct(temp, matrix.m_, matrix.n_);
    for (size_t i = 0; i < matrix.m_; ++i) {
        for (size_t j = 0; j < matrix.n_; ++j) {
            temp.data_[j][i] = matrix.data_[i][j];
        }
    }
    Destruct(matrix);
    matrix = temp;
}
// сравнение 2х матриц
bool operator==(const Matrix& a, const Matrix& b) {
    if (a.n_ != b.n_ || a.m_ != b.m_) {
        return false;
    }
    for (size_t i = 0; i < a.m_; ++i) {
        for (size_t j = 0; j < a.n_; ++j) {
            if (a.data_[i][j] != b.data_[i][j]) {
                return false;
            }
        }
    }
    return true;
}
// вспомогательная функция для вывода матрицы
void PrintMatrix(const Matrix& matrix, const std::string& name = "") {
    if (!name.empty()) {
        std::cout << name << " (" << matrix.m_ << "x" << matrix.n_ << "):" << std::endl;
    }

    if (matrix.data_ == nullptr) {
        std::cout << "Empty matrix" << std::endl;
        return;
    }

    for (size_t i = 0; i < matrix.m_; ++i) {
        for (size_t j = 0; j < matrix.n_; ++j) {
            std::cout << matrix.data_[i][j] << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
// функция для заполнения матрицы значениями
void FillMatrix(Matrix& matrix, const std::vector<std::vector<int>>& values) {
    if (matrix.m_ != values.size() || matrix.n_ != values[0].size()) {
        throw std::invalid_argument("Matrix dimensions don't match fill values");
    }
    for (size_t i = 0; i < matrix.m_; ++i) {
        for (size_t j = 0; j < matrix.n_; ++j) {
            matrix.data_[i][j] = values[i][j];
        }
    }
}
int main() {
    Matrix A, B; //копирование матриц
    Construct(A, 3, 2);  // матрица 2x3
    Construct(B, 3, 2);
    FillMatrix(A, {{1, 2, 3}, {4, 5, 6}});
    FillMatrix(B, {{7, 8, 9}, {10, 11, 12}});
    PrintMatrix(A, "A");
    PrintMatrix(B, "B");

    Matrix C = Copy(A);
    PrintMatrix(C, "Copy A (C)");

    //Сложение и вычитание
    Matrix sum = Add(A, B);
    Matrix diff = Sub(B, A);
    PrintMatrix(sum, "A + B");
    PrintMatrix(diff, "B - A");

    //умножение матриц
    Matrix D, E;
    Construct(D, 2, 3);  // 3x2
    Construct(E, 3, 2);  // 2x3
    FillMatrix(D, {{1, 2}, {3, 4}, {5, 6}});
    FillMatrix(E, {{7, 8, 9}, {10, 11, 12}});
    PrintMatrix(D, "D");
    PrintMatrix(E, "E(2x3)");

    Matrix product = Mult(D, E);  // Результат: 3x3
    PrintMatrix(product, "D * E");

    //Транспонирование
    Matrix F;
    Construct(F, 3, 2);
    FillMatrix(F, {{1, 2, 3}, {4, 5, 6}});

    PrintMatrix(F, "F");
    Transposition(F);
    PrintMatrix(F, "Transport F");

    //сравнение матриц
    Matrix G = Copy(A);
    std::cout << "A == G: " << (A == G) << std::endl;
    std::cout << "A == B: " << (A == B) << std::endl;
    std::cout << std::endl;
    // освобождаем память
    Destruct(A);
    Destruct(B);
    Destruct(C);
    Destruct(D);
    Destruct(E);
    Destruct(F);
    Destruct(G);
    return 0;
}
