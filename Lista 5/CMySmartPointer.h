#pragma once
#include "CRefCounter.h"

template <typename T> class CMySmartPointer
{
public:
	CMySmartPointer(T* pcPointer);
	CMySmartPointer(const CMySmartPointer& pcOther);
	~CMySmartPointer();
	T& operator*();
	T* operator->();
	CMySmartPointer<T>& operator=(const CMySmartPointer& pcOther);
private:
	CRefCounter* pc_counter;
	T* pc_pointer;
};

template <typename T> 
CMySmartPointer<T>::CMySmartPointer<T>(T* pcPointer) {
	pc_pointer = pcPointer;
	pc_counter = new CRefCounter();
	pc_counter->iAdd();
};
template <typename T>
CMySmartPointer<T>::CMySmartPointer<T>(const CMySmartPointer& pcOther)
{
	pc_pointer = pcOther.pc_pointer;
	pc_counter = pcOther.pc_counter;
	pc_counter->iAdd();
}
template<typename T>
CMySmartPointer<T>::~CMySmartPointer<T>()
{
	if (pc_counter->iDec() <= 0)
	{
		delete pc_pointer;
		delete pc_counter;
	}
}
template<typename T>
T& CMySmartPointer<T>::operator*(){ return(*pc_pointer); }

template<typename T>
T* CMySmartPointer<T>::operator->() { return(pc_pointer); }

template <typename T>
CMySmartPointer<T>& CMySmartPointer<T>::operator=(const CMySmartPointer& pcOther) {
	if (this != &pcOther) {
		if (pc_counter->iDec() == 0) {
			delete pc_pointer;
			delete pc_counter;
		}
		pc_pointer = pcOther.pc_pointer;
		pc_counter = pcOther.pc_counter;
		pc_counter->iAdd();
	}

return *this;
}