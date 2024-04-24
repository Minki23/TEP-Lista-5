#pragma once
#include <iostream>

template <typename T>
class MyUniquePointer {
public:
    MyUniquePointer(T* ptr = nullptr) : ptr(ptr) {
        std::cout << "wywolano konstruktor zwykly\n";
    }

    MyUniquePointer(const MyUniquePointer& other) = delete;

    ~MyUniquePointer() {
        std::cout << "usunieto zwykly wskaznik\n";
        delete ptr;
    }

    MyUniquePointer (MyUniquePointer&& other) : ptr(other.ptr) {
        std::cout << "wywolano konstruktor przenoszacy zwykly\n";
        other.ptr = nullptr;
    }
    MyUniquePointer& operator=(const MyUniquePointer& other) = delete;

    MyUniquePointer& operator=(MyUniquePointer&& other) {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    T& operator*() const {
        return *ptr;
    }

    T* operator->() const {
        return ptr;
    }

private:
    T* ptr;
};

template <typename T>
class MyUniquePointer<T[]> {
public:
    MyUniquePointer(T* ptr = nullptr) : ptr(ptr){
        std::cout << "wywolano konstruktor tablicy\n";
    }

    MyUniquePointer(const MyUniquePointer& other) = delete;

    ~MyUniquePointer() {
        std::cout << "usunieto tablice\n";
        delete[] ptr;
    }

    MyUniquePointer(MyUniquePointer&& other) : ptr(other.ptr){
        std::cout << "wywolano konstruktor przenoszacy tablicy\n";
        other.ptr = nullptr;
    }
    MyUniquePointer& operator=(const MyUniquePointer& other) = delete;

    MyUniquePointer& operator=(MyUniquePointer&& other) {
        if (this != &other) {
            delete[] ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }
    T& operator*() const {
        return *ptr;
    }

    T* operator->() const {
        return ptr;
    }

private:
    T* ptr;
};

