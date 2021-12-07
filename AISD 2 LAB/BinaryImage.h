#ifndef BinaryImage_h
#define BinaryImage_h
template<typename T, T falseValue, T trueValue>//1
class BinaryImage {
private:
    class TT {//Вспомогательный класс для работы с шаблонным типом данных
    public:
        T data;
        TT& operator=(bool value) {
            if (value)
                data = trueValue;
            else
                data = falseValue;
            return *this;
        }
        TT& operator=(T value) {
            if (value != trueValue && value != falseValue)
                throw "invalid value assignment";
            if (value == trueValue)
                data = trueValue;
            else
                data = falseValue;
            return *this;
        }
        bool operator==(T value) {
            if (value == data)
                return true;
            else
                return false;
        }//проверка есть ли значение(Вывод ячеейчный через прегруженный оператор вывода)(!)
    };
    TT** data;//эта переменная связывает класс BinaryImage с классом TT, для взаимодействия с ячейками(с методами записи(2))
    int cols;
    int rows;
public:
    BinaryImage() : data(nullptr), cols(0), rows(0) {}
    BinaryImage(int cols, int rows) : cols(cols), rows(rows), data(new TT* [rows]) {//выделяя память для матрицы, тип данных TT=> работа в классе TT
        for (int i = 0; i < rows; ++i)
            data[i] = new TT[cols];
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                data[i][j] = falseValue;
    }
    BinaryImage(const BinaryImage& rhs) : BinaryImage(rhs.cols, rhs.rows) {
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                data[i][j] = rhs.data[i][j];

    }
    ~BinaryImage() {
        if (data) {
            for (int i = 0; i < rows; ++i)
                if (data[i])
                    delete[] data[i];
            delete[] data;
        }
    }

    double Ratio()
    {
        int count = 0;
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                if (data[i][j] == trueValue)
                    count++;
        return (double)count / (rows * cols);
    }
    BinaryImage& operator=(const BinaryImage& other) {
        if (this == &other)
            return *this;
        if (cols != other.cols || rows != other.rows) {
            if (data) {
                for (int i = 0; i < rows; ++i)
                    if (data[i])
                        delete[] data[i];
                delete[] data;
            }
            cols = other.cols;
            rows = other.rows;
            data = new bool* [rows];
            for (int i = 0; i < rows; ++i)
                data[i] = new bool[cols];
            for (int i = 0; i < rows; ++i)
                for (int j = 0; j < cols; ++j)
                    data[i][j] = other.data[i][j];
        }
        return *this;
    }
    bool operator==(const BinaryImage& rhs) {
        if (cols != rhs.cols || rows != rhs.rows)
            return false;
        bool res = true;
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                if (data[i][j] != rhs.data[i][j]) {
                    res = false;
                    break;
                }
        return res;
    }
    bool operator!=(const BinaryImage& rhs)
    {
        return !(*this == rhs);

    }
    TT operator()(int i, int j) const {
        if (!(i >= 0 && i < rows && j >= 0 && j < cols)) {
            throw "Error";
        }
        return data[i][j] == trueValue;
    }

    TT& operator()(int i, int j) {
        if (!(i >= 0 && i < rows && j >= 0 && j < cols)) {
            throw "Error";
        }
        return data[i][j];
    }

    void operator!() {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (data[i][j] == trueValue)
                    data[i][j] = falseValue;
                else
                    data[i][j] = trueValue;
            }
        }
    }

    BinaryImage& operator*(const BinaryImage& rhs) {
        if (rows != rhs.rows || cols != rhs.cols) {
            throw "Error";
        }
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (data[i][j] == trueValue && rhs.data[i][j] == trueValue)
                    data[i][j] = trueValue;
                else
                    data[i][j] = falseValue;
            }
        }
        return *this;
    }

    BinaryImage& operator*(bool value) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (data[i][j] == trueValue && value == trueValue)
                    data[i][j] = trueValue;
                else
                    data[i][j] = falseValue;
            }
        }
        return *this;
    }


    BinaryImage& operator+(const BinaryImage& rhs) {
        if (rows != rhs.rows || cols != rhs.cols) {
            throw"Error";
        }
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (data[i][j] == falseValue && rhs.data[i][j] == falseValue)
                    data[i][j] = falseValue;
                else
                    data[i][j] = trueValue;
            }
        }
        return *this;
    }

    BinaryImage& operator+(bool value) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (data[i][j] == falseValue && value == falseValue)
                    data[i][j] = falseValue;
                else
                    data[i][j] = trueValue;
            }
        }
        return *this;
    }

    void Print() {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (data[i][j] == falseValue)
                    std::cout << '.';
                else
                    std::cout << '1';
            }
            std::cout << '\n';
        }
    }


    friend std::ostream& operator<<(std::ostream& out, const BinaryImage<T, falseValue, trueValue>& img)
    {
        for (int i = 0; i < img.rows; ++i) {
            for (int j = 0; j < img.cols; ++j) {
                if (img.data[i][j] == falseValue)
                    out << '.';
                else
                    out << '1';
            }
            out << '\n';
        }

        return out;
    }
};
#endif
#pragma once
