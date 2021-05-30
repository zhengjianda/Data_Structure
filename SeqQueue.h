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
	bool EnQueue(const T& x); // 队列不满，进队列，否则报出溢出
	virtual bool DeQueue(T& x); //退出表头元素
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
		if (IsEmpty() == true) {   //任意对队列的操作都要先检查队列是否为空
			std::cout << "当前队列为空" << std::endl;
			return;
		}
		for (int i = front, j = 1; i != rear; (i++) % maxSize, j++) {
			std::cout << j << ":" << elements[i] << std::endl;
		}
	}
protected:
	int rear, front;   //队尾 和队头指针(因为是数组表示，用下标index作为指针)
	T* elements;   //以数组为储存数据结构
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
	std::cout << "1------输入元素入队列\n"
		<< "2------输出队列元素\n"
		<< "3------队头元素出队列，并返回出队列的元素值\n"
		<< "4------获得队头元素\n"
		<< "5------判断队列是否为空\n"
		<< "6------判断队列是否已满\n"
		<< "7------获取当前队列的元素个数\n"
		<< "8------退出\n"
		<< "请输入您要进行的操作（1-8s）: ";
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
			std::cout << "请输入要进入队列的元素" << std::endl;
			std::cin >> x;
			myQueue.EnQueue(x);
			break;
		case 2:
			myQueue.Output();
			break;
		case 3:
			myQueue.DeQueue(x);
			std::cout << "队头元素" << x << "已经出队列" << std::endl;
			break;
		case 4:
			myQueue.getFront(x);
			std::cout << "当前队列队头元素为" << x << std::endl;
			break;
		case 5:
			if (myQueue.IsEmpty())
				std::cout << "当前队列为空" << std::endl;
			else
				std::cout << "当前队列不为空" << std::endl;
			break;
		case 6:
			if (myQueue.IsFull()) {
				std::cout << "当前队列已满" << std::endl;
			}
			else {
				std::cout << "当前队列未满" << std::endl;
			}
			break;
		case 7:
			std::cout << "当前队列的元素个数 " << myQueue.getSize() << std::endl;
			break;
		default:
			std::cout << "洛：霞，结束了" << std::endl;
			return;
		}
	}
}
/*int main()
{
	SeqQueue<int> myQueue(50);
	Menu<int>(myQueue);
	std::cout << "Hello world" << std::endl;
	return 0;
}*/

