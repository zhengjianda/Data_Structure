#pragma once
#include<iostream>
template<class T>
class Stack {
public:
	virtual void Push(const T& x) = 0;
	virtual bool Pop(T& x) = 0;
	virtual bool getTop(T& x) = 0;
	virtual bool IsEmpty() const = 0;
	virtual bool IsFull() const = 0;
	virtual int getSize() const = 0;
};