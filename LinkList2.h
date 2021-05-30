#include "LinkList.h"

// 链表的实现
template<class T>
MyList<T>::MyList(MyList<T>& L) {
	T value;                       //复制构造函数
	LinkNode<T> *srcptr = L.getHead();
	LinkNode<T> *destptr = first = new LinkNode<T>;  //借助新的链表
	while (srcptr->link != nullptr)
	{
		value = srcptr->link->data;
		destptr->link = new LinkNode<T>(value);
		destptr = destptr->link;
		srcptr = srcptr->link;
	}
	destptr->link = nullptr;
}
template<class T>
void MyList<T>::makeEmpty() {
	// 将链表置为空表
	LinkNode<T> *q;
	while (first->link != nullptr) {
		q = first->link;
		first->link = q->link;
		delete q;
	}
}
template<class T>
int MyList<T>::Length() const {
	LinkNode<T> *p = first->link;
	int count = 0;
	while (p != nullptr) {
		p = p->link;
		count++;
	}
	return count;
}
template<class T>
LinkNode<T> * MyList<T>::Search(T x) {
	LinkNode<T> * current = first->link;
	while (current != nullptr) {
		if (current->data == x) {
			break;
		}
		else
			current = current->link;
	}
	return current;
}
template<class T>
LinkNode<T> * MyList<T>::Locate(int i) {
	//定位函数。返回表中第i个元素的地址，若i<0或i超出表中节点个数，则返回NULL
	if (i < 0)
		return nullptr;   //0返回的是表头结点
	LinkNode<T> * current = first;
	int k = 0;
	while (current != nullptr&&k < i) {  //等于i即找到了，跳出循环
		current = current->link;
		k++;
	}
	return current;
}
template<class T>
bool MyList<T>::getData(int i, T& x)
{
	//取出链表中第i个元素
	if (i <= 0)
		return nullptr;
	LinkNode<T> * current = Locate(i);   //定位取得第i个元素的地址
	if (current == nullptr)
		return false;
	else {
		x = current->data;
		return true;
	}
}
template<class T>
void MyList<T>::setData(int i, T& x) {
	if (i <= 0)
		return;
	LinkNode<T> * current = Locate(i);  //定位地址 Locate全能函数，找到地址
	if (current == nullptr)
		return;
	else
		current->data = x;   //合法则赋值
}
template<class T>
void MyList<T>::delRepeat() {   //链表的去重
	bool judge[50000] = { 0 };
	LinkNode<T> * pre = first;
	LinkNode<T> * current = first->link;
	while (current != nullptr) {
		if (judge[current->data] == false) {
			judge[current->data] = true;
			pre = pre->link;
			current = current->link;
			//std::cout << "不会重复" << std::endl;
		}
		else {
			pre->link = current->link;  //去掉重复元素
			current = current->link;
			//std::cout << "重复了" << std::endl;
		}
	}
}
template<class T>
void MyList<T>::Sort() {
	LinkNode<T>* p, *q, *end = nullptr;
	int x;
	if (first == nullptr) {
		return;
	}
	while (first->link != end) {   //两层循环
		p = first;
		while (p->link != end) {
			q = p->link;
			if (p->data > q->data) {
				x = p->data;
				p->data = q->data;
				q->data = x;
			}
			p = p->link;
		}
		end = p;  //提高效率
	}
}
template<class T>
bool MyList<T>::Insert(int i, T& x) {
	//将新元素x插入在链表中第i个结点之后
	LinkNode<T> * current = Locate(i);
	if (current == nullptr) {
		std::cout << "要插入的地址为空，插入失败" << std::endl;
		return false;
	}
	LinkNode<T> * newNode = new LinkNode<T>(x);
	if (newNode == nullptr) {
		std::cerr << "存储分配错误!" << std::endl;
		exit(1);
	}
	newNode->link = current->link;
	current->link = newNode;
	return true;
}
template<class T>
bool MyList<T>::Remove(int i, T& x) {
	//将链表中的第i个元素删除，通过引用参数x返回该元素的值
	LinkNode<T> * current = Locate(i - 1);
	if (current == nullptr || current->link == nullptr) {
		std::cout << "该位置已为空，删除失败" << std::endl;
		return false;
	}
	LinkNode<T> * del = current->link;
	current->link = del->link;
	x = del->data;
	delete del;
	return true;
}
template<class T>
void MyList<T>::output() {
	//单链表的输出函数，将单链表中所以数据按逻辑顺序输出到屏幕上
	LinkNode<T> * current = first->link;
	while (current != nullptr) {
		cout << current->data << " ";
		current = current->link;
	}
	std::cout << std::endl;
}
template<class T>
MyList<T>& MyList<T>::operator=(MyList<T>& L) {
	//重载函数，赋值操作，形势如A=B，其中A是调用次函数的MyList对象，B是与参数表中的
	// 引用型参数L结合的实参
	T value;
	LinkNode<T> * srcptr = L.getHead();   //被复制表的附加头结点地址
	LinkNode<T>* destptr = first = new LinkNode<T>;
	while (srcptr->link != nullptr) {   //逐个结点复制
		value = srcptr->link->data;
		destptr->link = new LinkNode<T>(value);
		destptr = destptr->link;
		srcptr = srcptr->link;
	}
	destptr->link = nullptr;
	return *this;     //返回操作对象地址
}
template<class T>
void MyList<T>::InputFront(T end) {
	//end是约定的输入序列结束的标志。如果输入序列是正整数，end可以是0或负数
	//如果输入序列是字符，end可以是字符集中不会出现的字符，如“\0”
	LinkNode<T> * newNode;
	T val;
	makeEmpty();
	std::cin >> val;
	while (val != end) {
		newNode = new LinkNode<T>(val);  //创建新节点
		newNode->link = first->link;
		first->link = newNode;
		std::cin >> val;
	}
}
template<class T>
void MyList<T>::InputRear(T end) {
	//end是约定的输入序列结束的标志，定值方法与头插入算法同
	LinkNode<T> * newNode, *last;
	T val;
	makeEmpty();
	std::cin >> val;
	last = first;  //last指向表尾
	while (val != end) {
		newNode = new LinkNode<T>(val);
		last->link = newNode;
		last = newNode;
		std::cin >> val; //插入到末端
	}
	last->link = nullptr;   //表收尾
}
void print_menu2()
{
	std::cout << "1------头插入建立链表\n"
		<< "2------尾插入建立链表\n"
		<< "3------输出链表元素\n"
		<< "4------插入一个元素\n"
		<< "5------删除一个元素\n"
		<< "6------获取顺序表中具体位置的元素值\n"
		<< "7------设置顺序表中具体位置的元素值\n"
		<< "8------获取当前顺序表的元素个数\n"
		<< "9------查找某个元素在链表中的地址，不存在将返回nullptr\n"
		<< "10------判断顺序表是否为空\n"
		<< "11------定位函数，返回链表中第i个元素的指针\n"
		<< "12------清空链表函数\n"
		<< "13------退出\n"
		<< "14------链表去重\n"
		<< "15------对链表进行排序\n"
		<< "16------链表逆置\n"
		<< "17------期末考试测试\n"
		<< "请输入您要进行的操作（1-12）: ";
}
template<class T>
void Menu2(MyList<T> & mylist)
{
	while (true) {
		print_menu2();
		int n;
		std::cin >> n;
		switch (n) {
			int i;
			T x;
		case 1:
			std::cout << "输入链表结束的标志" << std::endl;
			T tem;
			std::cin >> tem;
			mylist.InputFront(tem);
			std::cout << "链表建立成功，方式为头插入" << std::endl;
			break;
		case 2:
			std::cout << "输入链表结束的标志" << std::endl;
			T tem1;
			std::cin >> tem1;
			mylist.InputRear(tem);
			std::cout << "链表建立成功，方式为尾插入" << std::endl;
			break;
		case 3:
			mylist.output();
			break;
		case 4:
			std::cout << "输入插入元素的位置和要插入的元素" << std::endl;
			std::cin >> i >> x;
			mylist.Insert(i, x);
			break;
		case 5:
			std::cout << "输入要删除元素的位置" << std::endl;
			std::cin >> i;
			mylist.Remove(i, x);
			std::cout << "删除成功,删除的元素为: " << x << std::endl;
			break;
		case 6:
			std::cout << "输入要获取元素的位置" << std::endl;
			std::cin >> i;
			if (mylist.getData(i, x))
				std::cout << "第" << i << "个位置的元素为: " << x << std::endl;
			break;
		case 7:
			std::cout << "输入要设置的元素位置和值" << std::endl;
			std::cin >> i >> x;
			mylist.setData(i, x);
			std::cout << "设置成功" << std::endl;
			break;
		case 8:
			std::cout << "当前顺序表的元素个数 " << mylist.Length() << std::endl;
			break;
		case 9:
			std::cout << "输入要查找的元素" << std::endl;
			std::cin >> x;
			std::cout << mylist.Search(x) << std::endl;
			break;
		case 10:
			if (mylist.IsEmpty())
				std::cout << "顺序表为空" << std::endl;
			else
				std::cout << "顺序表不为空" << std::endl;
			break;
		case 11: {
			std::cout << "请输入定位的位置" << std::endl;
			std::cin >> i;
			LinkNode<T> * temp = mylist.Locate(i);
			std::cout << "地址为 " << temp << std::endl;
			std::cout << temp->data << " " << temp->link << std::endl;
			break;
		}
		case 12:
			mylist.makeEmpty();
			std::cout << "链表已清空" << std::endl;
			break;
		case 14:
			mylist.delRepeat();
			std::cout << "链表已去重" << std::endl;
			break;
		case 15:
			mylist.Sort();
			std::cout << "链表已排序" << std::endl;
			break;
		case 16:
			mylist.reverse();
			std::cout << "链表已经逆置" << std::endl;
			break;
		case 17:
			/*std::cout << "请输入插入的数" << std::endl;
			std::cin >> x;*/
			mylist.reverse1();
			std::cout << "逆置成功" << std::endl;
			break;
		default:
			std::cout << "洛：霞，结束了" << std::endl;
			return;
		}
	}
}


