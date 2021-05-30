#include"LinearList2.h"
template<class T>
struct DblNode {
	T data;
	DblNode<T> *lLink, *rLink;   //前驱结点和后驱结点
	DblNode(DblNode<T> * left = nullptr, DblNode<T> * right = nullptr) :lLink(left), rLink(right) {

	}
	DblNode(T value, DblNode<T> *left = nullptr, DblNode<T> * right = nullptr) :data(value), lLink(left), rLink(right) {

	}
};
template<class T>
class DblList :public Linearlist2<T> {
public:
	DblList(T uniqueVAL);
	~DblList()
	{

	}
	int Length() const;
	bool IsEmpty() {
		return first->rLink == first;   //只有表头结点，返回空
	}
	DblNode<T>* getHead() const {
		return first;  //获取表头结点
	}
	void setHead(DblNode<T>* ptr) {
		first = ptr;  //设置表头结点
	}
	DblNode<T>* Search(T& x);
	DblNode<T>* Locate(int i, int d);
	bool Insert(int i, T& x, int d);
	bool Remove(int i, T& x, int d);
	void Output1() {
		//单链表的输出函数，将单链表中所以数据按逻辑顺序输出到屏幕上 //正向输出
		DblNode<T> * current = first->lLink;
		std::cout << "表头结点为空" << first->data << std::endl;
		while (current != first) {
			cout << current->data << " ";
			current = current->lLink;
		}
		std::cout << std::endl;
	}
	void Output2() {
		//单链表的输出函数，将单链表中所有数据按逻辑顺序输出到屏幕上 //反向输出
		DblNode<T> * current = this->Locate(1, 1);
		while (current != first) {
			cout << current->data << " ";
			current = current->rLink;
		}
		std::cout << std::endl;
	}
	void Sort() {
		if (first == 0) { ///空链表直接返回
			return;
		}
		DblNode<T>* end = first;  //结束标志
		DblNode<T>* begin;
		DblNode<T>* beginLeft;
		while (first->lLink != end) {
			begin = first->lLink;
			while (begin->lLink != end) {
				beginLeft = begin->lLink;
				if (begin->data > begin->lLink->data) {
					int x = begin->data;
					begin->data = begin->lLink->data;
					begin->lLink->data = x;
				}
				begin = begin->lLink;
				std::cout << "内层循环" << std::endl;
			}
			end = begin;
			std::cout << "外层循环" << std::endl;
		}
	}
private:
	DblNode<T>* first;
};
template<class T>
DblList<T>::DblList(T uniqueVal) {
	first = new DblNode<T>(uniqueVal);
	first->rLink = first->lLink = first;  //前驱后驱结点均指向自己
}
template<class T>
int DblList<T>::Length() const {
	DblNode<T>* current = first->rLink;
	int count = 0;
	while (current != first) {
		current = current->rLink;
		count++;
	}
	return count;
}
template<class T>
DblNode<T>* DblList<T>::Search(T& x) {
	DblNode<T>* current = first->rLink;
	while (current != first && current->data != x) {
		current = current->rLink;
	}
	if (current != first)
		return current;
	else
		return nullptr;
}
template<class T>
DblNode<T>* DblList<T>::Locate(int i, int d) {
	if (first->rLink == first || i == 0) {
		return first;
	}
	DblNode<T>* current;
	if (d == 0)
		current = first->lLink; //搜索方向
	else
		current = first->rLink;
	for (int j = 1; j < i; j++) {
		if (current == first)
			break;
		else if (d == 0)
			current = current->lLink;
		else
			current = current->rLink;
	}
	if (current != first)
		return current;
	else {
		return nullptr;
	}
}
template<class T>
bool DblList<T>::Insert(int i, T& x, int d) {
	if (i > this->Length()) {
		std::cout << "输入错误，请确保输入在0到" << this->Length() << std::endl;
		return false;
	}
	DblNode<T>* current = Locate(i, d);
	if (current == nullptr)
		return false;
	DblNode<T>* newNode = new DblNode<T>(x);
	if (d == 0) {
		newNode->lLink = current->lLink;
		current->lLink = newNode;
		newNode->lLink->rLink = newNode;
		newNode->rLink = current;
	}
	else {
		newNode->rLink = current->rLink;
		current->rLink = newNode;
		newNode->rLink->lLink = newNode;
		newNode->lLink = current;
	}
	return true;
}
template<class T>
bool DblList<T>::Remove(int i, T& x, int d) {
	DblNode<T>* current = Locate(i, d);
	if (current == first)
		return false;
	current->rLink->lLink = current->lLink;
	current->lLink->rLink = current->rLink;
	x = current->data;
	delete current;
	return true;
}
void print_menu3()
{
	std::cout << "1------向链表插入一个元素\n"
		<< "2------正向输出双向链表元素\n"
		<< "3------删除链表中的一个元素\n"
		<< "4------返回链表的长度\n"
		<< "5------判断链表是否为空\n"
		<< "6------反向输出双向链表元素\n"
		<< "7------排序\n"
		<< "8~-----退出\n"
		<< "请输入您要进行的操作（1-7）: ";
}
template<class T>
void Menu3(DblList<T> & mylist)
{
	while (true) {
		print_menu3();
		int n;
		T x;
		int d;
		int i;
		std::cin >> n;
		switch (n) {
			int i;
			T x;
		case 1:
			std::cout << "请按顺序输入要插入的位置（从0开始)，插入的元素值，和插入的方向值(d=0在前驱方向，d!=0在后驱方向" << std::endl;
			std::cin >> i >> x >> d;
			mylist.Insert(i, x, d);
			break;
		case 2:
			std::cout << "输出链表" << std::endl;
			mylist.Output1();
			break;
		case 3:
			std::cout << "请按顺序输入要删除的位置（从1开始），和删除的方向值(d=0在前驱方向，d!=0在后驱方向" << std::endl;
			std::cin >> i >> d;
			mylist.Remove(i, x, d);
			break;
		case 4:
			std::cout << "链表的长度为" << mylist.Length() << std::endl;
			break;
		case 5:
			if (mylist.IsEmpty()) {
				std::cout << "当前链表为空" << std::endl;
			}
			else {
				std::cout << "当前链表不为空" << std::endl;
			}
			break;
		case 6:
			std::cout << "反向输出链表" << std::endl;
			mylist.Output2();
			break;
		case 7:
			std::cout << "排序" << std::endl;
			mylist.Sort();
			break;
		default:
			std::cout << "洛，霞结束了" << std::endl;
			return;
		}
	}
}