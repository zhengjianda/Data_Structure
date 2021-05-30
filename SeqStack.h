#include"Stack.h"
const int stackIncreament = 20;  //������
template<class T>
class SeqStack :public Stack<T> {
public:
	SeqStack(int sz = 50);
	~SeqStack()     //��������
	{
		delete[]elements;
	}
	virtual void Push(const T& x);
	virtual bool Pop(T& x);
	virtual bool getTop(T& x);
	virtual bool IsEmpty() const {
		return (top == -1) ? true : false;
	}
	virtual bool IsFull() const {
		return (top == maxSize - 1) ? true : false;  //ջ����������-1��ջ��
	}
	virtual int getSize() const {   // ��ȡջ����
		return top + 1;
	}
	virtual void MakeEmpty() {   //���ջ
		this->top = -1;
	}
	virtual void Output() {
		while (this->IsEmpty() == false)
		{
			T x;
			this->getTop(x);
			std::cout << x << " ";
			this->Pop(x);
		}
		std::cout << std::endl;
	}
	friend std::ostream& operator << (std::ostream& os, SeqStack<T>& s);
private:
	T* elements;    //ջ����ָ��
	int top;     //ջ��ָ�룬˳��ջ�������±꣬αָ��
	int maxSize;    //ջ�����ɵ����Ԫ��
	void overflowProcess();  //ջ���������
};
template<class T>
SeqStack<T>::SeqStack(int sz) :top(-1), maxSize(sz) {
	elements = new T[maxSize];
	assert(elements != nullptr);//���Լ��
}
template<class T>
void SeqStack<T>::overflowProcess() {
	//˽�к�������չջ�Ĵ洢�ռ�
	T* newArray = new T[maxSize + stackIncreament];
	if (newArray == nullptr) {
		std::cerr << "�洢����ʧ��!" << std::endl;
		exit(1);
	}
	for (int i = 0; i <= top; i++)
		newArray[i] = elements[i];
	maxSize = maxSize + stackIncreament;
	delete[]elements;
	elements = newArray;
}
template<class T>
void SeqStack<T>::Push(const T& x) {
	if (IsFull() == true)
		overflowProcess();
	elements[++top] = x;  //ջ���ȼ�1������ջ
}
template<class T>
bool SeqStack<T>::Pop(T& x) {
	if (IsEmpty() == true)
		return false;
	x = elements[top--];
	return true;
}
template<class T>
bool SeqStack<T>::getTop(T& x) {
	if (IsEmpty() == true) {
		return false;
	}
	x = elements[top];
	return true;
}
/*template<class T>
std::ostream& operator<<(std::ostream& os, SeqStack<T>& s) {
	for (int i = 0; i <= s.top; i++)
		os << i << ":" << s.elements[i] << std::endl;
	return os;
}*/
void print_menu4()
{
	std::cout << "1------Ԫ����ջ\n"
		<< "2------��ȡջ��Ԫ�ص�ֵ\n"
		<< "3------��ջ��Ԫ�ض���\n"
		<< "4------�ж�ջ�Ƿ�Ϊ��\n"
		<< "5------����ջ��Ԫ�صĸ���\n"
		<< "6------���ջ\n"
		<< "7------���ջ�е�ȫ��Ԫ��\n"
		<< "8------�˳�\n"
		<< "��������Ҫ���еĲ�����1-12��: ";
}
template<class T>
void Menu4(SeqStack<T> & mystack)
{
	while (true) {
		print_menu4();
		int n;
		std::cin >> n;
		switch (n) {
			int i;
			T x;
		case 1:
			std::cout << "������Ҫ��ջ��Ԫ��" << std::endl;
			std::cin >> x;
			mystack.Push(x);
			break;
		case 2:
			if (mystack.getTop(x))
				std::cout << "ջ����Ԫ��Ϊ" << x << std::endl;
			else
				std::cout << "ջ��Ϊ�գ�����ʧ��" << std::endl;
			break;
		case 3:
			mystack.Pop(x);
			std::cout << "��ջ��ջ��Ԫ��Ϊ" << x << std::endl;
			break;
		case 4:
			if (mystack.IsEmpty()) {
				std::cout << "ջΪ��" << std::endl;
			}
			else
				std::cout << "��ǰջ��Ϊ��" << std::endl;
			break;
		case 5:
			i = mystack.getSize();
			std::cout << "��ǰջ��Ԫ�صĸ���Ϊ" << i << std::endl;
			break;
		case 6:
			mystack.MakeEmpty();
			std::cout << "ջ�Ѿ����" << std::endl;
			break;
		case 7:
			mystack.Output();
			break;
		default:
			std::cout << "��:ϼ������" << std::endl;
			return;
		}
	}
}
