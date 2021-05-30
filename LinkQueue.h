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
		std::cout << "嘿嘿嘿" << std::endl;
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
		front = rear = new LinkNode1<T>(x); //空队列进第一个元素
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
	std::cout << "1------输入元素入队列\n"
		<< "2------输出队列元素\n"
		<< "3------队头元素出队列，并返回出队列的元素值\n"
		<< "4------获得队头元素\n"
		<< "5------判断队列是否为空\n"
		<< "6------获取当前队列的元素个数\n"
		<< "7------退出\n"
		<< "请输入您要进行的操作（1-8s）: ";
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
	LinkedQueue<int> myQueue;
	Menu<int>(myQueue);
	std::cout << "Hello world" << std::endl;
	return 0;
}*/



