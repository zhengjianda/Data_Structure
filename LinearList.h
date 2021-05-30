#pragma once
//  线性表的抽象函数
#include<iostream>
using namespace std;
template<class T>
class Linearlist
{
public:
	Linearlist() {

	}
	virtual int Size() const = 0;
	virtual int Length() const = 0;
	virtual int Search(T &x) const = 0;
	virtual int Locate(int i) const = 0;
	virtual bool Getdata(int i, T& x) = 0;
	virtual bool Setdata(int i, T& x) = 0;
	virtual bool Insert(int i, T&x) = 0;
	virtual bool Remove(int i, T&x) = 0;
	virtual bool IsEmpty() = 0;
	virtual bool IsFull() const = 0;
	//virtual void Sort() = 0;
	virtual void input() = 0;
	virtual void output() = 0;
	//virtual Linearlist<T> operator = (Linearlist<T>& L) = 0;
};
