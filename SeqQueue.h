#include<assert.h>
#include<iostream>
#include"Queue.h"
template<class T>
class SeqQueue :public Queue<T> {
public:
	SeqQueue(int sz = 10);
	~SeqQueue()
	{
		delete[] elements;
	}
	bool EnQueue(const T& x); // ���в����������У����򱨳�����
	virtual bool DeQueue(T& x); //�˳���ͷԪ��
	virtual bool getFront(T& x);
	void makeEmpty() {
		front = rear = 0;
	}
	virtual bool IsEmpty() const {
		return (front == rear ? true : false);
	}
	virtual bool IsFull() const {
		return ((rear + 1) % maxSize == front ? true : false);
	}
	virtual int getSize() const {
		return (rear - front + maxSize) % maxSize;
	}
	void Output() {
		if (IsEmpty() == true) {   //�����Զ��еĲ�����Ҫ�ȼ��������Ƿ�Ϊ��
			std::cout << "��ǰ����Ϊ��" << std::endl;
			return;
		}
		for (int i = front, j = 1; i != rear; (i++) % maxSize, j++) {
			std::cout << j << ":" << elements[i] << std::endl;
		}
	}
protected:
	int rear, front;   //��β �Ͷ�ͷָ��(��Ϊ��������ʾ�����±�index��Ϊָ��)
	T* elements;   //������Ϊ�������ݽṹ
	int maxSize;
};
template<class T>
SeqQueue<T>::SeqQueue(int sz) {
	this->front = 0;
	this->rear = 0;
	this->maxSize = sz;
	this->elements = new T[maxSize];
	assert(elements != nullptr);
}
template<class T>
bool SeqQueue<T>::EnQueue(const T& x) {
	if (IsFull() == true)
		return false;
	elements[rear] = x;
	rear = (rear + 1) % maxSize;
	return true;
}
template<class T>
bool SeqQueue<T>::DeQueue(T &x) {
	if (front == rear)
		return false;
	x = elements[front];
	front = (front + 1) % maxSize;
	return true;
}
template<class T>
bool SeqQueue<T>::getFront(T& x) {
	if (IsEmpty() == true)
		return false;
	x = elements[front];
	return true;
}
void print_menu5()
{
	std::cout << "1------����Ԫ��������\n"
		<< "2------��������Ԫ��\n"
		<< "3------��ͷԪ�س����У������س����е�Ԫ��ֵ\n"
		<< "4------���ö�ͷԪ��\n"
		<< "5------�ж϶����Ƿ�Ϊ��\n"
		<< "6------�ж϶����Ƿ�����\n"
		<< "7------��ȡ��ǰ���е�Ԫ�ظ���\n"
		<< "8------�˳�\n"
		<< "��������Ҫ���еĲ�����1-8s��: ";
}
template<class T>
void Menu5(SeqQueue<T> & myQueue)
{
	while (true) {
		print_menu5();
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
			if (myQueue.IsFull()) {
				std::cout << "��ǰ��������" << std::endl;
			}
			else {
				std::cout << "��ǰ����δ��" << std::endl;
			}
			break;
		case 7:
			std::cout << "��ǰ���е�Ԫ�ظ��� " << myQueue.getSize() << std::endl;
			break;
		default:
			std::cout << "�壺ϼ��������" << std::endl;
			return;
		}
	}
}
