#pragma once
#include<iostream>
using namespace std;
template<class T>
class Linearlist2
{
public:
	Linearlist2() {

	}
	virtual int Length() const = 0;
	virtual bool IsEmpty() = 0;
};
