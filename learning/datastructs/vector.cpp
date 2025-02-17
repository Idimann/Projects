#include <iostream>
#include <initializer_list>
#include <cstring>

template<size_t num, typename T>
class Vector {
    private:
        T array[num] = { 0 };

    public:
        Vector() { }

        Vector(const std::initializer_list<T> array) {
            for(size_t i = 0; i < std::min(num, array.size()); i++)
                this->array[i] = *(array.begin() + i);
        }

        Vector(const T array[num]) {
            for(size_t i = 0; i < num; i++)
                this->array[i] = array[i];
        }

        const T* arr() const {
            return array;
        }

        constexpr T operator[](const size_t& index) const {
            return array[index];
        }

        constexpr Vector<num, T> operator+(const Vector<num, T>& array) const {
            T nArray[num] = {0};

            for(size_t i = 0; i < num; i++)
                nArray[i] = (*this)[i] + array[i];

            return Vector<num, T>(nArray);
        }

        constexpr Vector<num, T> operator-(const Vector<num, T>& array) const {
            T nArray[num] = {0};

            for(size_t i = 0; i < num; i++)
                nArray[i] = (*this)[i] - array[i];

            return Vector<num, T>(nArray);
        }

        constexpr T operator*(const Vector<num, T>& array) const {
            T returning = 0;

            for(size_t i = 0; i < num; i++)
                returning += (*this)[i] * array[i];

            return returning;
        }

        friend std::ostream& operator<<(std::ostream& os, const Vector<num, T>& ar) {
            os << "Vec" << num << '(';

            for(size_t i = 0; i < num; i++) {
                os << ar[i];

                if(i != num - 1)
                    os << ", ";
            }
            os << ')';

            return os;
        }
};

template<size_t n, size_t m, typename T>
class Matrix {
    private:
        T array[n][m];

    public:
        Matrix() { }

        Matrix(const std::initializer_list<std::initializer_list<T>> array) {
            for(size_t i = 0; i < std::min(n, array.size()); i++)
                for(size_t j = 0; j < std::min(n, (*(array.begin() + i)).size()); j++)
                    this->array[i][j] = *((*(array.begin() + i)).begin() + j);
        }

        Matrix(const T array[n][m]) {
            for(size_t i = 0; i < n; i++)
                for(size_t j = 0; j < m; j++)
                    this->array[i][j] = array[i][j];
        }

        constexpr Matrix<m, n, T> transpose() const {
            T array[m][n] = {0};

            for(size_t i = 0; i < m; i++)
                for(size_t j = 0; j < n; j++)
                    array[i][j] = this->array[j][i];

            return Matrix<m, n, T>(array);
        }

        constexpr Vector<n, T> operator*(const Vector<m, T>& array) const {
            T nArray[n] = {0};

            for(size_t i = 0; i < n; i++)
                nArray[i] = Vector<m, T>(this->array[i]) * array;

            return Vector<n, T>(nArray);
        }

        template<size_t x>
        constexpr Matrix<n, x, T> operator*(Matrix<m, x, T> array) const {
            T nArray[n][x] = {0};

            array = array.transpose();

            for(size_t i = 0; i < n; i++) {
                const auto arr = ((*this) * Vector<m, T>(array.array[i])).arr();

                for(size_t j = 0; j < x; j++)
                    nArray[i][j] = arr[j];
            }

            return Matrix<n, x, T>(nArray);
        }

        friend std::ostream& operator<<(std::ostream& os, const Matrix<n, m, T>& mat) {
            os << "Mat" << n << 'x' << m << "(\n";

            for(size_t i = 0; i < n; i++)
                for(size_t j = 0; j < m; j++)
                    os << mat.array[i][j] << ((j == m - 1) ? '\n' : '\t');

            os << ')';
            return os;
        }
};

int main(int argc, char** argv) {
    const auto vec = Vector<3, float>({1, 2, 3});
    const auto mat = Matrix<3, 3, float>({{1, 0, 0},
                                          {0, 1, 0},
                                          {0, 0, 1}});

    std::cout << mat * vec << ' ' << mat * mat << '\n';

    return 0;
}
