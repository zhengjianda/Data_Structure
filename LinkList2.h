#include "LinkList.h"

// �����ʵ��
template<class T>
MyList<T>::MyList(MyList<T>& L) {
	T value;                       //���ƹ��캯��
	LinkNode<T> *srcptr = L.getHead();
	LinkNode<T> *destptr = first = new LinkNode<T>;  //�����µ�����
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
	// ��������Ϊ�ձ�
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
	//��λ���������ر��е�i��Ԫ�صĵ�ַ����i<0��i�������нڵ�������򷵻�NULL
	if (i < 0)
		return nullptr;   //0���ص��Ǳ�ͷ���
	LinkNode<T> * current = first;
	int k = 0;
	while (current != nullptr&&k < i) {  //����i���ҵ��ˣ�����ѭ��
		current = current->link;
		k++;
	}
	return current;
}
template<class T>
bool MyList<T>::getData(int i, T& x)
{
	//ȡ�������е�i��Ԫ��
	if (i <= 0)
		return nullptr;
	LinkNode<T> * current = Locate(i);   //��λȡ�õ�i��Ԫ�صĵ�ַ
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
	LinkNode<T> * current = Locate(i);  //��λ��ַ Locateȫ�ܺ������ҵ���ַ
	if (current == nullptr)
		return;
	else
		current->data = x;   //�Ϸ���ֵ
}
template<class T>
void MyList<T>::delRepeat() {   //�����ȥ��
	bool judge[50000] = { 0 };
	LinkNode<T> * pre = first;
	LinkNode<T> * current = first->link;
	while (current != nullptr) {
		if (judge[current->data] == false) {
			judge[current->data] = true;
			pre = pre->link;
			current = current->link;
			//std::cout << "�����ظ�" << std::endl;
		}
		else {
			pre->link = current->link;  //ȥ���ظ�Ԫ��
			current = current->link;
			//std::cout << "�ظ���" << std::endl;
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
	while (first->link != end) {   //����ѭ��
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
		end = p;  //���Ч��
	}
}
template<class T>
bool MyList<T>::Insert(int i, T& x) {
	//����Ԫ��x�����������е�i�����֮��
	LinkNode<T> * current = Locate(i);
	if (current == nullptr) {
		std::cout << "Ҫ����ĵ�ַΪ�գ�����ʧ��" << std::endl;
		return false;
	}
	LinkNode<T> * newNode = new LinkNode<T>(x);
	if (newNode == nullptr) {
		std::cerr << "�洢�������!" << std::endl;
		exit(1);
	}
	newNode->link = current->link;
	current->link = newNode;
	return true;
}
template<class T>
bool MyList<T>::Remove(int i, T& x) {
	//�������еĵ�i��Ԫ��ɾ����ͨ�����ò���x���ظ�Ԫ�ص�ֵ
	LinkNode<T> * current = Locate(i - 1);
	if (current == nullptr || current->link == nullptr) {
		std::cout << "��λ����Ϊ�գ�ɾ��ʧ��" << std::endl;
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
	//���������������������������������ݰ��߼�˳���������Ļ��
	LinkNode<T> * current = first->link;
	while (current != nullptr) {
		cout << current->data << " ";
		current = current->link;
	}
	std::cout << std::endl;
}
template<class T>
MyList<T>& MyList<T>::operator=(MyList<T>& L) {
	//���غ�������ֵ������������A=B������A�ǵ��ôκ�����MyList����B����������е�
	// �����Ͳ���L��ϵ�ʵ��
	T value;
	LinkNode<T> * srcptr = L.getHead();   //�����Ʊ�ĸ���ͷ����ַ
	LinkNode<T>* destptr = first = new LinkNode<T>;
	while (srcptr->link != nullptr) {   //�����㸴��
		value = srcptr->link->data;
		destptr->link = new LinkNode<T>(value);
		destptr = destptr->link;
		srcptr = srcptr->link;
	}
	destptr->link = nullptr;
	return *this;     //���ز��������ַ
}
template<class T>
void MyList<T>::InputFront(T end) {
	//end��Լ�����������н����ı�־�����������������������end������0����
	//��������������ַ���end�������ַ����в�����ֵ��ַ����硰\0��
	LinkNode<T> * newNode;
	T val;
	makeEmpty();
	std::cin >> val;
	while (val != end) {
		newNode = new LinkNode<T>(val);  //�����½ڵ�
		newNode->link = first->link;
		first->link = newNode;
		std::cin >> val;
	}
}
template<class T>
void MyList<T>::InputRear(T end) {
	//end��Լ�����������н����ı�־����ֵ������ͷ�����㷨ͬ
	LinkNode<T> * newNode, *last;
	T val;
	makeEmpty();
	std::cin >> val;
	last = first;  //lastָ���β
	while (val != end) {
		newNode = new LinkNode<T>(val);
		last->link = newNode;
		last = newNode;
		std::cin >> val; //���뵽ĩ��
	}
	last->link = nullptr;   //����β
}
void print_menu2()
{
	std::cout << "1------ͷ���뽨������\n"
		<< "2------β���뽨������\n"
		<< "3------�������Ԫ��\n"
		<< "4------����һ��Ԫ��\n"
		<< "5------ɾ��һ��Ԫ��\n"
		<< "6------��ȡ˳����о���λ�õ�Ԫ��ֵ\n"
		<< "7------����˳����о���λ�õ�Ԫ��ֵ\n"
		<< "8------��ȡ��ǰ˳����Ԫ�ظ���\n"
		<< "9------����ĳ��Ԫ���������еĵ�ַ�������ڽ�����nullptr\n"
		<< "10------�ж�˳����Ƿ�Ϊ��\n"
		<< "11------��λ���������������е�i��Ԫ�ص�ָ��\n"
		<< "12------���������\n"
		<< "13------�˳�\n"
		<< "14------����ȥ��\n"
		<< "15------�������������\n"
		<< "16------��������\n"
		<< "17------��ĩ���Բ���\n"
		<< "��������Ҫ���еĲ�����1-12��: ";
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
			std::cout << "������������ı�־" << std::endl;
			T tem;
			std::cin >> tem;
			mylist.InputFront(tem);
			std::cout << "�������ɹ�����ʽΪͷ����" << std::endl;
			break;
		case 2:
			std::cout << "������������ı�־" << std::endl;
			T tem1;
			std::cin >> tem1;
			mylist.InputRear(tem);
			std::cout << "�������ɹ�����ʽΪβ����" << std::endl;
			break;
		case 3:
			mylist.output();
			break;
		case 4:
			std::cout << "�������Ԫ�ص�λ�ú�Ҫ�����Ԫ��" << std::endl;
			std::cin >> i >> x;
			mylist.Insert(i, x);
			break;
		case 5:
			std::cout << "����Ҫɾ��Ԫ�ص�λ��" << std::endl;
			std::cin >> i;
			mylist.Remove(i, x);
			std::cout << "ɾ���ɹ�,ɾ����Ԫ��Ϊ: " << x << std::endl;
			break;
		case 6:
			std::cout << "����Ҫ��ȡԪ�ص�λ��" << std::endl;
			std::cin >> i;
			if (mylist.getData(i, x))
				std::cout << "��" << i << "��λ�õ�Ԫ��Ϊ: " << x << std::endl;
			break;
		case 7:
			std::cout << "����Ҫ���õ�Ԫ��λ�ú�ֵ" << std::endl;
			std::cin >> i >> x;
			mylist.setData(i, x);
			std::cout << "���óɹ�" << std::endl;
			break;
		case 8:
			std::cout << "��ǰ˳����Ԫ�ظ��� " << mylist.Length() << std::endl;
			break;
		case 9:
			std::cout << "����Ҫ���ҵ�Ԫ��" << std::endl;
			std::cin >> x;
			std::cout << mylist.Search(x) << std::endl;
			break;
		case 10:
			if (mylist.IsEmpty())
				std::cout << "˳���Ϊ��" << std::endl;
			else
				std::cout << "˳���Ϊ��" << std::endl;
			break;
		case 11: {
			std::cout << "�����붨λ��λ��" << std::endl;
			std::cin >> i;
			LinkNode<T> * temp = mylist.Locate(i);
			std::cout << "��ַΪ " << temp << std::endl;
			std::cout << temp->data << " " << temp->link << std::endl;
			break;
		}
		case 12:
			mylist.makeEmpty();
			std::cout << "���������" << std::endl;
			break;
		case 14:
			mylist.delRepeat();
			std::cout << "������ȥ��" << std::endl;
			break;
		case 15:
			mylist.Sort();
			std::cout << "����������" << std::endl;
			break;
		case 16:
			mylist.reverse();
			std::cout << "�����Ѿ�����" << std::endl;
			break;
		case 17:
			/*std::cout << "������������" << std::endl;
			std::cin >> x;*/
			mylist.reverse1();
			std::cout << "���óɹ�" << std::endl;
			break;
		default:
			std::cout << "�壺ϼ��������" << std::endl;
			return;
		}
	}
}


