#pragma once
#include<iostream>
#include<assert.h>
#include<stdlib.h>
const int DefaultPQSize = 50;
template<class T>
class PQueue {
public:
	PQueue(int sz = DefaultPQSize);
	~PQueue()
	{
		delete[] pqelements;
	}
	bool Insert(const T& x);
	bool RemoveMin(T& x);
	bool getFront(T& x) const;
	void makeEmpty() {
		this->count = 0;
	}
	bool IsEmpty() const {
		return (count == 0) ? true : false;
	}
	bool IsFull() const {
		return (count == maxSize) ? true : false;
	}
	int getSize() const {
		return count;
	}
protected:
	T* pqelements;
	int maxSize;
	int count;
	void Adjust();
};
template<class T>
PQueue<T>::PQueue(int sz) :maxSize(sz) {
	pqelements = new T[maxSize];
	count = 0;
}
template<class T>
bool PQueue<T>::Insert(const T& x) {
	if (count == maxSize)
		return false;
	pqelements[count++] = x;
	Adjust;
}
template<class T>
void PQueue<T>::Adjust() {
	T temp = pqelements[count - 1];
	int j;
	for (j = count - 2; j >= 0; j--) {
		if (pqelements[j] < temp)
			break;
		else
			pqelements[j + 1] = pqelements[j];
	}
	pqelements[j + 1] = temp;
}
template<class T>
bool PQueue<T>::RemoveMin(T& x) {
	if (count == 0)
		return false;
	x = pqelements[0];
	for (int i = 1; i < count; ++i)
		pqelements[i - 1] = pqelements[i];
	count--;
	return true;
}
template<class T>
bool PQueue<T>::getFront(T& x) const {
	if (count == 0)
		return false;
	x = pqelements[0];
	return true;
}
