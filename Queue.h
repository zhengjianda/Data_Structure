#pragma once
#include<iostream>
// ���еĳ�����������
const int massize = 50;
template<class T>
class Queue {
public:
	Queue() {

	};
	~Queue()
	{

	};
	virtual bool EnQueue(const T& x) = 0;
	virtual bool DeQueue(T& x) = 0;
	virtual bool getFront(T& x) = 0;
	virtual bool IsEmpty() const = 0;
	virtual bool IsFull() const = 0;
	virtual int getSize() const = 0;
};