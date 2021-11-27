#ifndef BinaryImage_h
#define BinaryImage_h
template<typename T, T falseValue, T trueValue>//1
class BinaryImage {
private:
    class TT {
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
        }//Заполнение ячеек
        bool operator==(T value) {
            if (value == data)
                return true;
            else
                return false;
        }//проверка есть ли значение
    };
    TT** data;
    int cols;
    int rows;
public:
};
#endif
#pragma once
