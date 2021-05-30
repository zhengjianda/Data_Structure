#include"LinearList2.h"
template<class T>
struct DblNode {
	T data;
	DblNode<T> *lLink, *rLink;   //ǰ�����ͺ������
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
		return first->rLink == first;   //ֻ�б�ͷ��㣬���ؿ�
	}
	DblNode<T>* getHead() const {
		return first;  //��ȡ��ͷ���
	}
	void setHead(DblNode<T>* ptr) {
		first = ptr;  //���ñ�ͷ���
	}
	DblNode<T>* Search(T& x);
	DblNode<T>* Locate(int i, int d);
	bool Insert(int i, T& x, int d);
	bool Remove(int i, T& x, int d);
	void Output1() {
		//���������������������������������ݰ��߼�˳���������Ļ�� //�������
		DblNode<T> * current = first->lLink;
		std::cout << "��ͷ���Ϊ��" << first->data << std::endl;
		while (current != first) {
			cout << current->data << " ";
			current = current->lLink;
		}
		std::cout << std::endl;
	}
	void Output2() {
		//���������������������������������ݰ��߼�˳���������Ļ�� //�������
		DblNode<T> * current = this->Locate(1, 1);
		while (current != first) {
			cout << current->data << " ";
			current = current->rLink;
		}
		std::cout << std::endl;
	}
	void Sort() {
		if (first == 0) { ///������ֱ�ӷ���
			return;
		}
		DblNode<T>* end = first;  //������־
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
				std::cout << "�ڲ�ѭ��" << std::endl;
			}
			end = begin;
			std::cout << "���ѭ��" << std::endl;
		}
	}
private:
	DblNode<T>* first;
};
template<class T>
DblList<T>::DblList(T uniqueVal) {
	first = new DblNode<T>(uniqueVal);
	first->rLink = first->lLink = first;  //ǰ����������ָ���Լ�
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
		current = first->lLink; //��������
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
		std::cout << "���������ȷ��������0��" << this->Length() << std::endl;
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
	std::cout << "1------���������һ��Ԫ��\n"
		<< "2------�������˫������Ԫ��\n"
		<< "3------ɾ�������е�һ��Ԫ��\n"
		<< "4------��������ĳ���\n"
		<< "5------�ж������Ƿ�Ϊ��\n"
		<< "6------�������˫������Ԫ��\n"
		<< "7------����\n"
		<< "8~-----�˳�\n"
		<< "��������Ҫ���еĲ�����1-7��: ";
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
			std::cout << "�밴˳������Ҫ�����λ�ã���0��ʼ)�������Ԫ��ֵ���Ͳ���ķ���ֵ(d=0��ǰ������d!=0�ں�������" << std::endl;
			std::cin >> i >> x >> d;
			mylist.Insert(i, x, d);
			break;
		case 2:
			std::cout << "�������" << std::endl;
			mylist.Output1();
			break;
		case 3:
			std::cout << "�밴˳������Ҫɾ����λ�ã���1��ʼ������ɾ���ķ���ֵ(d=0��ǰ������d!=0�ں�������" << std::endl;
			std::cin >> i >> d;
			mylist.Remove(i, x, d);
			break;
		case 4:
			std::cout << "����ĳ���Ϊ" << mylist.Length() << std::endl;
			break;
		case 5:
			if (mylist.IsEmpty()) {
				std::cout << "��ǰ����Ϊ��" << std::endl;
			}
			else {
				std::cout << "��ǰ����Ϊ��" << std::endl;
			}
			break;
		case 6:
			std::cout << "�����������" << std::endl;
			mylist.Output2();
			break;
		case 7:
			std::cout << "����" << std::endl;
			mylist.Sort();
			break;
		default:
			std::cout << "�壬ϼ������" << std::endl;
			return;
		}
	}
}