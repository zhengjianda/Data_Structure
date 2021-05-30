#pragma
#include "LinearList.h"
// 顺序表
const int defaultSize = 1000;
template<class T>
class SeqList :public Linearlist<T> {
protected:
	T* data;   //存储数组
	int maxsize;  // 容量
	int last = 0;
public:
	SeqList(int sz = defaultSize);
	SeqList(SeqList<T>& L);
	void resize(int newsize);
	int Size() const {    //返回顺序表可存储的最大值
		return maxsize;
	}
	int Length() const {  //返回顺序表当前存储的元素个数
		return last;
	}
	int Search(T &x) const;
	int Locate(int i) const;
	bool Getdata(int i, T& x) {    //获取I位置的元素，实际存储在数组中的位置要减1
		if (i > 0 && i <= last) {
			x = data[i - 1];
			return true;
		}
		else {
			std::cout << "输入范围有误，查找失败" << std::endl;
			return false;
		}
	}
	bool Setdata(int i, T& x) {     //设置i位置元素的值
		if (i > 0 && i <= last) {
			data[i - 1] = x;
		}
		return true;
	}
	bool Insert(int i, T& x);
	bool InsertX(T x) {   //期末测试、
		if (last == maxsize - 1) {
			std::cout << "表已经满了,插入失败" << std::endl;
			return false;
		}
		else {
			int j = last;
			while (data[j - 1] >= x && j >= 1) {
				data[j] = data[j - 1];
				j--;
			}
			data[j] = x;
		}
		last++;
		return true;
	}
	void reverse() {
		int i = 0;
		int j = last - 1;
		while (i < j) {
			int temp = data[i];
			data[i] = data[j];
			data[j] = temp;
			++i;
			--j;
		}
		std::cout << "逆置成功" << std::endl;
	}
	bool Remove(int i, T& x);
	virtual bool IsEmpty() {
		return (last == 0 ? true : false);
	}
	virtual bool IsFull() const {
		return (last == this->maxsize - 1 ? true : false);
	}
	void Sort() {

	}
	void input();
	void output();
};
template<class T>
SeqList<T>::SeqList(int sz) {   //构造函数
	if (sz > 0) {
		maxsize = sz;
		this->last = 0;
		data = new T[maxsize];
		if (data == nullptr) {
			std::cout << "存储分配错误!" << std::endl;
			exit(1);
		}
	}
}
template<class T>
SeqList<T>::SeqList(SeqList<T>& L) {  //复制构造函数
	this->maxsize = L.Size();
	last = L.Length() - 1;
	T value;
	data = new T[maxsize];
	if (data == nullptr) {
		std::cerr << "存储分配错误!" << endl;
		exit(1);
	}
	for (int i = 1; i < last + 1; ++i) {
		L.Getdata(i, value);  //获取L中的数据
		data[i - 1] = value;
	}
}
template<class T>
void SeqList<T>::resize(int newsize) {   //重置顺序表的最大存储值
	if (newsize <= 0) {   //合法性检查
		std::cerr << "无效的数组大小" << endl;
		return;
	}
	if (newsize != maxsize) {
		T * newarray = new T[newsize];
		if (newarray == nullptr) {
			std::cerr << "存储分配错误" << endl;
			exit(1);
		}  //重置大小
		int n = last;
		T* srcptr = data;
		T* destprt = newarray;
		while (n--)
			*destprt++ = *srcptr++;      //保持原数组
		delete[] data;
		data = new T[newsize + 1];
		data = newarray;
		maxsize = newsize;    //最大值改变
	}
}
template<class T>
int SeqList<T>::Search(T& x) const {   //搜索某个元素的位置
	for (int i = 0; i < last; ++i) {
		if (data[i] == x) {
			return i + 1;
		}
	}
	return -1;
}
template<class T>
int SeqList<T>::Locate(int i) const {
	if (i >= 1 && i <= last + 1) {
		return i;
	}
	else
		return 0;
}
template<class T>
bool SeqList<T>::Insert(int i, T& x) {   //在i+1个位置，插入一个x
	if (last == maxsize - 1)
		return false;
	if (i == last) {
		data[last] = x;
		last++;
		return true;
	}
	if (i<0 || i>last)
		return false;
	for (int j = last - 1; j >= i; j--) {
		data[j + 1] = data[j];
	}
	data[i] = x;
	last++;
	return true;
}
template<class T>
bool SeqList<T>::Remove(int i, T& x) {
	if (last == 0)
		return false;
	if (i < 1 || i >= last + 1)
		return false;
	x = data[i - 1];
	for (int j = i; j < last; j++)
		data[j - 1] = data[j];
	last--;
	return true;
}
template<class T>
void SeqList<T>::input()
{
	std::cout << "开始建立顺序表，请输入表中元素的个数: ";
	while (true)
	{
		std::cin >> last;
		if (last <= maxsize - 1)
			break;
		std::cout << "表元素个数输入有误，范围不能超过" << maxsize - 1 << ";" << std::endl;
		std::cout << "开始建立顺序表，请正确输入表中元素的个数:" << std::endl;
	}
	std::cout << "请一次输入" << last << "个元素" << endl;
	for (int i = 0; i < last; ++i) {
		std::cin >> data[i];
	}
	std::cout << "链表建立成功!" << std::endl;
}
template<class T>
void SeqList<T>::output() {
	std::cout << "顺序表当前元素的最后位置: " << last << std::endl;
	for (int i = 0; i < last; i++) {
		std::cout << '#' << i + 1 << ": " << data[i] << endl;
	}
}
template<class T>
bool Union(SeqList<T> & mylist1, SeqList<T>& mylist2, SeqList<T>& newList) {
	T x;
	T y;
	int i = 1, j = 1, k = 0;
	while (i <= mylist1.Length() && j <= mylist2.Length()) {
		mylist1.Getdata(i, x);
		mylist2.Getdata(j, y);
		if (x < y) {
			//newList.Setdata(k, x);
			newList.Insert(k, x);
			i++;
		}
		else {
			//newList.Setdata(k, y);
			newList.Insert(k, y);
			j++;
		}
		k++;
	}
	while (i <= mylist1.Length()) {
		mylist1.Getdata(i, x);
		//newList.Setdata(k, x);
		newList.Insert(k, x);
		i++;
		k++;
	}
	while (j <= mylist2.Length()) {
		std::cout << " " << mylist2.Getdata(j, x) << std::endl;
		//newList.Setdata(k, x);
		newList.Insert(k, x);
		//std::cout << "这里" << x << endl;
		j++;
		k++;
	}
	newList.output();
	return true;
}
void print_menu1()
{
	std::cout << "1------输入顺序表元素\n"
		<< "2------输出顺序表元素\n"
		<< "3------插入一个元素\n"
		<< "4------删除一个元素\n"
		<< "5------获取顺序表中具体位置的元素值\n"
		<< "6------设置顺序表中具体位置的元素值\n"
		<< "7------获取当前顺序表的元素个数\n"
		<< "8------获取当前顺序表允许的最大元素个数\n"
		<< "9------查找某个元素在顺序表中的位置，不存在将返回-1\n"
		<< "10-----重置顺序表存储的最大值\n"
		<< "11------判断顺序表是否为空\n"
		<< "12------期末测试\n"
		<< "13------退出\n"
		<< "请输入您要进行的操作（1-12）: ";
}
template<class T>
void Menu1(SeqList<T> & mylist)
{
	while (true) {
		print_menu1();
		int n;
		std::cin >> n;
		switch (n) {
			int i;
			T x;
		case 1:
			mylist.input();
			break;
		case 2:
			mylist.output();
			break;
		case 3:
			std::cout << "输入插入元素的位置和要插入的元素" << std::endl;
			std::cin >> i >> x;
			mylist.Insert(i, x);
			break;
		case 4:
			std::cout << "输入要删除元素的位置" << std::endl;
			std::cin >> i;
			mylist.Remove(i, x);
			std::cout << "删除成功,删除的元素为: " << x << std::endl;
			break;
		case 5:
			std::cout << "输入要获取元素的位置" << std::endl;
			std::cin >> i;
			if (mylist.Getdata(i, x))
				std::cout << "第" << i << "个位置的元素为: " << x << std::endl;
			break;
		case 6:
			std::cout << "输入要设置的元素位置和值" << std::endl;
			std::cin >> i >> x;
			mylist.Setdata(i, x);
			std::cout << "设置成功" << std::endl;
			break;
		case 7:
			std::cout << "当前顺序表的元素个数 " << mylist.Length() << std::endl;
			break;
		case 8:
			std::cout << "顺序表允许的最大元素个数 " << mylist.Size() << std::endl;
			break;
		case 9:
			std::cout << "输入要查找的元素" << std::endl;
			std::cin >> x;
			std::cout << mylist.Search(x) << std::endl;
			break;
		case 10:
			std::cout << "输入顺序表新的最大值" << std::endl;
			std::cin >> i;
			mylist.resize(i);
			std::cout << "重置成功!" << std::endl;
			break;
		case 11:
			if (mylist.IsEmpty())
				std::cout << "顺序表为空" << std::endl;
			else
				std::cout << "顺序表不为空" << std::endl;
			break;
		case 12:
			/*std::cout << "请输入要插入的元素" << std::endl;
			std::cin >> x;*/
			mylist.reverse();
			break;
		default:
			std::cout << "洛：霞，结束了" << std::endl;
			return;
		}
	}
}