#pragma once
#include<iostream>
#include<stack>
using namespace std;
template<class T>
struct LinkNode {
	T data;  //����
	LinkNode<T> *link;  //��һ�ڵ�
	LinkNode(LinkNode<T> * ptr = nullptr) {
		link = ptr;
	}
	LinkNode(const T& item, LinkNode<T> * ptr = nullptr) {
		data = item;
		link = ptr;
	}
};
template<class T>
class MyList {
public:
	MyList() {
		first = new LinkNode<T>;  //ͷָ��
	}
	MyList(const T& x) {
		first = new LinkNode<T>(x);
	}
	MyList(MyList<T>& L);
	~MyList()
	{
		makeEmpty();  //��Ϊ��
	}
	void makeEmpty();
	void reverse() {
		stack<LinkNode<T>*> myStack;
		LinkNode<T>* p = new LinkNode<T>;
		p = this->first->link;  //��ͷ��㲻Ҫ   Ԫ����ջ
		while (p != nullptr) {
			myStack.push(p);
			if (p->link != nullptr) {
				p = p->link;
			}
			else {
				break;
			}
		}
		LinkNode<T>* Newhead;  //���ν�ջ��Ԫ��ȡ�������������β�������
		LinkNode<T>* NewTail;
		Newhead = NewTail = new LinkNode<T>;
		if (!myStack.empty()) {
			NewTail = Newhead = myStack.top();
			myStack.pop();
		}
		else {
			std::cout << "ջΪ��" << std::endl;
			return;
		}
		while (!myStack.empty()) {
			LinkNode<T>* temp = new LinkNode<T>;
			temp = myStack.top();
			myStack.pop();
			NewTail->link = temp;
			NewTail = temp;
			NewTail->link = nullptr;
		}
		first->link = Newhead;   //ת��
	}
	void reverse1() {
		LinkNode<T>* newhead = new LinkNode<T>;
		newhead = nullptr;
		LinkNode<T>* p = first->link;
		while (p != nullptr) {
			LinkNode<T>* temNode = new LinkNode<T>;
			temNode->data = p->data;
			LinkNode<T>* del = p;
			p = p->link;
			temNode->link = newhead;
			newhead = temNode;
			delete del;
		}
		first->link = newhead;
	}
	int Length() const;
	LinkNode<T>* getHead() const {
		return first;
	}
	LinkNode<T> *Search(T x);
	LinkNode<T> * Locate(int i);
	bool getData(int i, T& x);
	void setData(int i, T& x);
	bool Insert(int i, T& x);
	bool Remove(int i, T& x);
	bool IsEmpty() const {
		return first->link == nullptr ? true : false;
	}
	bool IsFull() const {
		return false;
	}
	bool RemoveX(T x) {
		LinkNode<T> *pre = first;
		LinkNode<T> *p = first->link;
		if (pre == nullptr || p == nullptr) {
			std::cout << "ɾ��ʧ��" << std::endl;
			return false;
		}
		while (p != nullptr&&p->data != x) {
			pre = pre->link;
			p = p->link;
		}
		if (p == nullptr) {
			std::cout << "δ�ҵ�ɾ��Ԫ�أ�ɾ��ʧ��" << std::endl;
			return false;
		}
		else {
			LinkNode<T>* del = p;
			pre->link = p->link;
			delete del;
			return true;
		}
	}
	bool InsertX(T x) {
		LinkNode<T>* pre = first;
		LinkNode<T>* p = first->link;
		while (p != nullptr&&p->data < x) {
			pre = pre->link;
			p = p->link;
		}
		if (p == nullptr) {
			LinkNode<T>* newNode = new LinkNode<T>;
			newNode->data = x;
			pre->link = newNode;
			newNode->link = nullptr;
		}
		else {
			LinkNode<T>* newNode = new LinkNode<T>;
			newNode->data = x;
			pre->link = newNode;
			newNode->link = p;
		}
		return true;
	}
	void delRepeat();
	void Sort();
	void InputFront(T endTag);
	void InputRear(T endTag);
	void output();
	MyList<T>& operator=(MyList<T>& L);
protected:
	LinkNode<T> * first;
};
