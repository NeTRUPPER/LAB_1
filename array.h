#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

template <typename T>
class Array {
private:
    T* data;
    size_t capacity;
    size_t length;

public:
    Array(size_t cap = 100) : capacity(cap), length(0) {
        data = new T[capacity];
    }

    ~Array() {
        delete[] data;
    }

    // Добавление элемента в конец массива
    void push_back(const T& value) {
        if (length >= capacity) {
            throw overflow_error("Array is full");
        }
        data[length++] = value;
    }

    // Добавление элемента по индексу
    void insert_at(size_t index, const T& value) {
        if (index > length || length >= capacity) {
            throw out_of_range("Index out of range or array is full");
        }
        for (size_t i = length; i > index ; --i) {
            data[i] = data[i - 1];
        }
        data[index] = value;
        ++length;
    }

    // Удаление элемента по индексу
    void remove_at(size_t index) {
        if (index >= length) {
            throw out_of_range("Index out of range");
        }
        for (size_t i = index; i < length - 1; ++i) {
            data[i] = data[i + 1];
        }
        --length;
    }

    // Замена элемента по индексу
    void replace_at(size_t index, const T& value) {
        if (index >= length) {
            throw out_of_range("Index out of range");
        }
        data[index] = value;
    }

    // Получение элемента по индексу
    T get_at(size_t index) const {
        if (index >= length) {
            throw out_of_range("Index out of range");
        }
        return data[index];
    }

    // Получение длины массива
    size_t size() const {
        return length;
    }

    // Загрузка данных из файла
    void load_from_file(const std::string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            length = 0;
            T value;
            while (file >> value) {
                if (length >= capacity) break;
                data[length++] = value;
            }
            file.close();
        }
    }

    // Сохранение данных в файл
    void save_to_file(const std::string& filename) const {
        ofstream file(filename);
        if (file.is_open()) {
            for (size_t i = 0; i < length; ++i) {
                file << data[i] << " ";
            }
            file.close();
        }
    }
};

#endif // ARRAY_H
