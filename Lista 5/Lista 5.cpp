// Lista 5.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include "CMySmartPointer.h"
#include "UserInterface.h"
#include "MyUniquePointer.h"
#include "NodeTree.h"

int main()
{
    MyUniquePointer<int> ptr = MyUniquePointer<int>(new int(10));
    MyUniquePointer<std::string> obiekt = MyUniquePointer<std::string>(new std::string("abc"));
    MyUniquePointer<int> ptr2 = std::move(ptr);
    MyUniquePointer<int> ptr3 = MyUniquePointer<int>(std::move(ptr));
    MyUniquePointer<int[]> ptr4 = MyUniquePointer<int[]>(new int[10]);
    MyUniquePointer<int[]> ptr5 = MyUniquePointer<int[]>(new int[10]);
    CMySmartPointer<int> testSmart = CMySmartPointer<int>(new int(10));
}