#include"Stack.h"
const int stackIncreament = 20;  //自增量
template<class T>
class SeqStack :public Stack<T> {
public:
	SeqStack(int sz = 50);
	~SeqStack()     //析构函数
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
		return (top == maxSize - 1) ? true : false;  //栈顶等于容量-1，栈满
	}
	virtual int getSize() const {   // 获取栈容量
		return top + 1;
	}
	virtual void MakeEmpty() {   //清空栈
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
	T* elements;    //栈数组指针
	int top;     //栈顶指针，顺序栈用数组下标，伪指针
	int maxSize;    //栈可容纳的最大元素
	void overflowProcess();  //栈的溢出处理
};
template<class T>
SeqStack<T>::SeqStack(int sz) :top(-1), maxSize(sz) {
	elements = new T[maxSize];
	assert(elements != nullptr);//断言检查
}
template<class T>
void SeqStack<T>::overflowProcess() {
	//私有函数，扩展栈的存储空间
	T* newArray = new T[maxSize + stackIncreament];
	if (newArray == nullptr) {
		std::cerr << "存储分配失败!" << std::endl;
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
	elements[++top] = x;  //栈顶先加1，再入栈
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
	std::cout << "1------元素入栈\n"
		<< "2------获取栈顶元素的值\n"
		<< "3------将栈顶元素顶出\n"
		<< "4------判断栈是否为空\n"
		<< "5------返回栈中元素的个数\n"
		<< "6------清空栈\n"
		<< "7------输出栈中的全部元素\n"
		<< "8------退出\n"
		<< "请输入您要进行的操作（1-12）: ";
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
			std::cout << "请输入要入栈的元素" << std::endl;
			std::cin >> x;
			mystack.Push(x);
			break;
		case 2:
			if (mystack.getTop(x))
				std::cout << "栈顶的元素为" << x << std::endl;
			else
				std::cout << "栈已为空，返回失败" << std::endl;
			break;
		case 3:
			mystack.Pop(x);
			std::cout << "出栈的栈顶元素为" << x << std::endl;
			break;
		case 4:
			if (mystack.IsEmpty()) {
				std::cout << "栈为空" << std::endl;
			}
			else
				std::cout << "当前栈不为空" << std::endl;
			break;
		case 5:
			i = mystack.getSize();
			std::cout << "当前栈中元素的个数为" << i << std::endl;
			break;
		case 6:
			mystack.MakeEmpty();
			std::cout << "栈已经清空" << std::endl;
			break;
		case 7:
			mystack.Output();
			break;
		default:
			std::cout << "洛:霞结束了" << std::endl;
			return;
		}
	}
}
