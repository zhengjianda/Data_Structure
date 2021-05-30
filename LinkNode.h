#pragma once
#pragma once
#include<iostream>
using namespace std;
template<class T>
struct LinkNode1 {
	T data;
	LinkNode1<T>* link;
	LinkNode1(LinkNode1<T> * ptr = nullptr) {
		link = ptr;
	}
	LinkNode1(const T& item, LinkNode1<T> * ptr = nullptr) {
		data = item;
		link = ptr;
	}
};
