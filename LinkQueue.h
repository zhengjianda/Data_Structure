#include<iostream>
#include"Queue.h"
#include"LinkNode.h"
template<class T>
class LinkedQueue :public Queue<T> {
public:
	LinkedQueue() :rear(nullptr), front(nullptr) {

	};
	~LinkedQueue()
	{
		makeEmpty();
	}
	virtual bool IsFull() const {
		std::cout << "�ٺٺ�" << std::endl;
		return true;
	};
	bool EnQueue(const T& x);
	bool DeQueue(T& x);
	bool getFront(T& x) ;
	void makeEmpty();
	void Output() {
		LinkNode1<T>* p;
		p = front;
		while (p != rear->link) {
			std::cout << p->data << " ";
			p = p->link;
		}
		std::cout << std::endl;
	}
	bool IsEmpty() const {
		return (front == nullptr) ? true : false;
	}
	int getSize() const;
protected:
	LinkNode1<T> *front, *rear;
};
template<class T>
void LinkedQueue<T>::makeEmpty() {
	LinkNode1<T>* p;
	while (front != nullptr) {
		p = front;
		front = front->link;
		delete p;
	}
}
template<class T>
bool LinkedQueue<T>::EnQueue(const T& x) {
	if (front == nullptr) {
		front = rear = new LinkNode1<T>(x); //�ն��н���һ��Ԫ��
	}
	else {
		rear->link = new LinkNode1<T>(x);
		rear = rear->link;
	}
	return true;
}
template<class T>
bool LinkedQueue<T>::DeQueue(T &x) {
	if (IsEmpty() == true)
		return false;
	LinkNode1<T> *p = front;
	x = front->data;
	front = front->link;
	delete p;
	return true;
}
template<class T>
bool LinkedQueue<T>::getFront(T& x) {
	if (IsEmpty() == true)
		return false;
	x = front->data;
	return true;
}
template<class T>
int LinkedQueue<T>::getSize()const {
	LinkNode1<T>* p = front;
	int k = 0;
	while (p != nullptr) {
		p = p->link;
		k++;
	}
	return k;
}
void print_menu6()
{
	std::cout << "1------����Ԫ��������\n"
		<< "2------��������Ԫ��\n"
		<< "3------��ͷԪ�س����У������س����е�Ԫ��ֵ\n"
		<< "4------���ö�ͷԪ��\n"
		<< "5------�ж϶����Ƿ�Ϊ��\n"
		<< "6------��ȡ��ǰ���е�Ԫ�ظ���\n"
		<< "7------�˳�\n"
		<< "��������Ҫ���еĲ�����1-8s��: ";
}
template<class T>
void Menu6(LinkedQueue<T> & myQueue)
{
	while (true) {
		print_menu6();
		int n;
		std::cin >> n;
		switch (n) {
			int i;
			T x;
		case 1:
			std::cout << "������Ҫ�������е�Ԫ��" << std::endl;
			std::cin >> x;
			myQueue.EnQueue(x);
			break;
		case 2:
			myQueue.Output();
			break;
		case 3:
			myQueue.DeQueue(x);
			std::cout << "��ͷԪ��" << x << "�Ѿ�������" << std::endl;
			break;
		case 4:
			myQueue.getFront(x);
			std::cout << "��ǰ���ж�ͷԪ��Ϊ" << x << std::endl;
			break;
		case 5:
			if (myQueue.IsEmpty())
				std::cout << "��ǰ����Ϊ��" << std::endl;
			else
				std::cout << "��ǰ���в�Ϊ��" << std::endl;
			break;
		case 6:
			std::cout << "��ǰ���е�Ԫ�ظ��� " << myQueue.getSize() << std::endl;
			break;
		default:
			std::cout << "�壺ϼ��������" << std::endl;
			return;
		}
	}
}
