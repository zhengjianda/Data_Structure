#pragma
#include "LinearList.h"
// ˳���
const int defaultSize = 1000;
template<class T>
class SeqList :public Linearlist<T> {
protected:
	T* data;   //�洢����
	int maxsize;  // ����
	int last = 0;
public:
	SeqList(int sz = defaultSize);
	SeqList(SeqList<T>& L);
	void resize(int newsize);
	int Size() const {    //����˳���ɴ洢�����ֵ
		return maxsize;
	}
	int Length() const {  //����˳���ǰ�洢��Ԫ�ظ���
		return last;
	}
	int Search(T &x) const;
	int Locate(int i) const;
	bool Getdata(int i, T& x) {    //��ȡIλ�õ�Ԫ�أ�ʵ�ʴ洢�������е�λ��Ҫ��1
		if (i > 0 && i <= last) {
			x = data[i - 1];
			return true;
		}
		else {
			std::cout << "���뷶Χ���󣬲���ʧ��" << std::endl;
			return false;
		}
	}
	bool Setdata(int i, T& x) {     //����iλ��Ԫ�ص�ֵ
		if (i > 0 && i <= last) {
			data[i - 1] = x;
		}
		return true;
	}
	bool Insert(int i, T& x);
	bool InsertX(T x) {   //��ĩ���ԡ�
		if (last == maxsize - 1) {
			std::cout << "���Ѿ�����,����ʧ��" << std::endl;
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
		std::cout << "���óɹ�" << std::endl;
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
SeqList<T>::SeqList(int sz) {   //���캯��
	if (sz > 0) {
		maxsize = sz;
		this->last = 0;
		data = new T[maxsize];
		if (data == nullptr) {
			std::cout << "�洢�������!" << std::endl;
			exit(1);
		}
	}
}
template<class T>
SeqList<T>::SeqList(SeqList<T>& L) {  //���ƹ��캯��
	this->maxsize = L.Size();
	last = L.Length() - 1;
	T value;
	data = new T[maxsize];
	if (data == nullptr) {
		std::cerr << "�洢�������!" << endl;
		exit(1);
	}
	for (int i = 1; i < last + 1; ++i) {
		L.Getdata(i, value);  //��ȡL�е�����
		data[i - 1] = value;
	}
}
template<class T>
void SeqList<T>::resize(int newsize) {   //����˳�������洢ֵ
	if (newsize <= 0) {   //�Ϸ��Լ��
		std::cerr << "��Ч�������С" << endl;
		return;
	}
	if (newsize != maxsize) {
		T * newarray = new T[newsize];
		if (newarray == nullptr) {
			std::cerr << "�洢�������" << endl;
			exit(1);
		}  //���ô�С
		int n = last;
		T* srcptr = data;
		T* destprt = newarray;
		while (n--)
			*destprt++ = *srcptr++;      //����ԭ����
		delete[] data;
		data = new T[newsize + 1];
		data = newarray;
		maxsize = newsize;    //���ֵ�ı�
	}
}
template<class T>
int SeqList<T>::Search(T& x) const {   //����ĳ��Ԫ�ص�λ��
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
bool SeqList<T>::Insert(int i, T& x) {   //��i+1��λ�ã�����һ��x
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
	std::cout << "��ʼ����˳������������Ԫ�صĸ���: ";
	while (true)
	{
		std::cin >> last;
		if (last <= maxsize - 1)
			break;
		std::cout << "��Ԫ�ظ����������󣬷�Χ���ܳ���" << maxsize - 1 << ";" << std::endl;
		std::cout << "��ʼ����˳�������ȷ�������Ԫ�صĸ���:" << std::endl;
	}
	std::cout << "��һ������" << last << "��Ԫ��" << endl;
	for (int i = 0; i < last; ++i) {
		std::cin >> data[i];
	}
	std::cout << "�������ɹ�!" << std::endl;
}
template<class T>
void SeqList<T>::output() {
	std::cout << "˳���ǰԪ�ص����λ��: " << last << std::endl;
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
		//std::cout << "����" << x << endl;
		j++;
		k++;
	}
	newList.output();
	return true;
}
void print_menu1()
{
	std::cout << "1------����˳���Ԫ��\n"
		<< "2------���˳���Ԫ��\n"
		<< "3------����һ��Ԫ��\n"
		<< "4------ɾ��һ��Ԫ��\n"
		<< "5------��ȡ˳����о���λ�õ�Ԫ��ֵ\n"
		<< "6------����˳����о���λ�õ�Ԫ��ֵ\n"
		<< "7------��ȡ��ǰ˳����Ԫ�ظ���\n"
		<< "8------��ȡ��ǰ˳�����������Ԫ�ظ���\n"
		<< "9------����ĳ��Ԫ����˳����е�λ�ã������ڽ�����-1\n"
		<< "10-----����˳���洢�����ֵ\n"
		<< "11------�ж�˳����Ƿ�Ϊ��\n"
		<< "12------��ĩ����\n"
		<< "13------�˳�\n"
		<< "��������Ҫ���еĲ�����1-12��: ";
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
			std::cout << "�������Ԫ�ص�λ�ú�Ҫ�����Ԫ��" << std::endl;
			std::cin >> i >> x;
			mylist.Insert(i, x);
			break;
		case 4:
			std::cout << "����Ҫɾ��Ԫ�ص�λ��" << std::endl;
			std::cin >> i;
			mylist.Remove(i, x);
			std::cout << "ɾ���ɹ�,ɾ����Ԫ��Ϊ: " << x << std::endl;
			break;
		case 5:
			std::cout << "����Ҫ��ȡԪ�ص�λ��" << std::endl;
			std::cin >> i;
			if (mylist.Getdata(i, x))
				std::cout << "��" << i << "��λ�õ�Ԫ��Ϊ: " << x << std::endl;
			break;
		case 6:
			std::cout << "����Ҫ���õ�Ԫ��λ�ú�ֵ" << std::endl;
			std::cin >> i >> x;
			mylist.Setdata(i, x);
			std::cout << "���óɹ�" << std::endl;
			break;
		case 7:
			std::cout << "��ǰ˳����Ԫ�ظ��� " << mylist.Length() << std::endl;
			break;
		case 8:
			std::cout << "˳�����������Ԫ�ظ��� " << mylist.Size() << std::endl;
			break;
		case 9:
			std::cout << "����Ҫ���ҵ�Ԫ��" << std::endl;
			std::cin >> x;
			std::cout << mylist.Search(x) << std::endl;
			break;
		case 10:
			std::cout << "����˳����µ����ֵ" << std::endl;
			std::cin >> i;
			mylist.resize(i);
			std::cout << "���óɹ�!" << std::endl;
			break;
		case 11:
			if (mylist.IsEmpty())
				std::cout << "˳���Ϊ��" << std::endl;
			else
				std::cout << "˳���Ϊ��" << std::endl;
			break;
		case 12:
			/*std::cout << "������Ҫ�����Ԫ��" << std::endl;
			std::cin >> x;*/
			mylist.reverse();
			break;
		default:
			std::cout << "�壺ϼ��������" << std::endl;
			return;
		}
	}
}