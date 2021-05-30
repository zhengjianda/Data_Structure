#include<iostream>
#include<stack>
#include<queue>
enum tag1
{
	L, R
};
template<class T>
struct BinTreeNode {  //�����������
	T data;
	BinTreeNode<T> * leftChild, *rightChild;
	BinTreeNode() :leftChild(nullptr), rightChild(nullptr) {

	}
	BinTreeNode(T x, BinTreeNode<T> * l = nullptr, BinTreeNode<T> *r = nullptr) :data(x), leftChild(l), rightChild(r) {

	}
};
template<class T>
struct strNode {
	BinTreeNode<T> *ptr;    //���ڵ�ָ��
	tag1 tag;
	strNode(BinTreeNode<T>* N = nullptr) :ptr(N), tag(L) {

	};
};
template<class T>
class BinaryTree {
public:
	BinaryTree() :root(nullptr) {
		RefValue = -1;   //����ֹ�ı�־
	}
	BinaryTree(BinTreeNode<T>* root1) {
		root = root1;
		RefValue = -1;
	}
	BinaryTree(const BinaryTree<T>& s);
	~BinaryTree()
	{
		destroy(root);
	}
	bool IsEmpty() {
		return ((root == nullptr) ? true : false);
	}
	BinTreeNode<T> * Parent(BinTreeNode<T> *current) {   //���ظ��ڵ�
		return (root == nullptr || root == current) ? nullptr : Parent(root, current);
	}
	BinTreeNode<T> * LeftChild(BinTreeNode<T>* current) {    //��������Ů
		return (current != nullptr) ? current->leftChild : nullptr;
	}
	BinTreeNode<T> * RightChild(BinaryTree<T>* current) {     //��������Ů
		return (current != nullptr) ? current->RightChild : nullptr;
	}
	int Height() {
		return Height(root); //�������߶�
	}
	int Size() {         //���ؽ����
		return Size(root);
	}
	BinTreeNode<T> * getRoot() const {
		return root;           //ȡ��
	}
	void preOrder(BinTreeNode<T>* & subTree);
	void preOrder2(BinTreeNode<T>* & subTree);  //ǰ��ǵݹ��㷨
	void inOrder(BinTreeNode<T>* &p);
	void inOrder2(BinTreeNode<T>* &p);
	void postOrder(BinTreeNode<T>* &subTree);
	void postOrder2(BinTreeNode<T>* &subTree);
	void levelOrder(BinTreeNode<T>* p);
	int Insert(const T& item) {
		Insert(this->root, item);
	}
	BinTreeNode<T>* Find(T& item) const;
public:
	BinTreeNode<T> * root;
	T RefValue;
	void visitRoot(BinTreeNode<T>* p) {
		if (p != nullptr) {
			std::cout << p->data << " ";
		}
		else {
			std::cout << "���Ϊ��" << std::endl;
		}
	}
	void CreateBinTree(BinTreeNode<T>* &subtree);
	bool Insert(BinTreeNode<T>* &subTree, const T &x);
	void destroy(BinTreeNode<T>* &subTree);
	bool Find(BinTreeNode<T> * subTree, const T &x) const;
	BinTreeNode<T> * Copy(BinTreeNode<T> * orignode);
	int Height(BinTreeNode<T> * subTree) const;
	int Size(BinTreeNode<T> *subTree) const;
	BinTreeNode<T> * Parent(BinTreeNode<T> * subTree, BinTreeNode<T> * current);
	//	BinTreeNode<T> * Find(BinTreeNode<T> *subTree, const T& x) const;
	void Traverse(BinTreeNode<T> * subTree, std::ostream& out);
	friend std::istream& operator >>(std::istream&in, BinaryTree<T>& Tree);
	friend std::ostream& operator <<(std::ostream& out, BinaryTree<T>& Tree);
};
template<class T>
void BinaryTree<T>::destroy(BinTreeNode<T>* &subTree) {
	if (subTree != nullptr) {
		destroy(subTree->leftChild); //�ݻ�������
		destroy(subTree->rightChild); //�ݻ�������
		delete subTree;  //�ݻٸ�
	}
}
template<class T>
BinTreeNode<T> * BinaryTree<T>::Parent(BinTreeNode<T>* subTree, BinTreeNode<T>* current) {
	if (subTree == nullptr) {
		return nullptr;       //���� ����
	}
	if (subTree->leftChild == current || subTree->rightChild == current)
		return subTree;         //�ҵ������ظ��ڵ�
	BinTreeNode<T> *p;
	if ((p = Parent(subTree->leftChild, current)) != nullptr) {
		return p;   //��������������
	}
	else               //�������������� 
		return Parent(subTree->rightChild, current);
}
template<class T>
void BinaryTree<T>::Traverse(BinTreeNode<T>* subTree, std::ostream& out) {  //˽�к����������������ΪsubTree�Ķ�����
	if (subTree != nullptr) {
		out << subTree->data << " ";   //�����������
		Traverse(subTree->leftChild, out); //���������
		Traverse(subTree->rightChild, out); //���������
	}
};
template<class T>
void BinaryTree<T>::levelOrder(BinTreeNode<T>* subtree) {   //��α���
	std::queue<BinTreeNode<T>*> MyQue;
	BinTreeNode<T> *p = subtree;
	MyQue.push(p);
	while (!MyQue.empty()) {
		p = MyQue.front();
		MyQue.pop();
		std::cout << p->data << " ";
		if (p->leftChild != nullptr)
			MyQue.push(p->leftChild);
		if (p->rightChild != nullptr)
			MyQue.push(p->rightChild);
	}
}
template<class T>
std::istream& operator >>(std::istream& in, BinaryTree<T>& Tree) {
	CreateBinTree(Tree.root);
	return in;
}
template<class T>
std::ostream& operator <<(std::ostream& out, BinaryTree<T>& Tree) {
	out << "��������ǰ�����\n";
	Tree.Traverse(Tree.root, out);
	out << std::endl;
	return out;
}
template<class T>
void BinaryTree<T>::inOrder(BinTreeNode<T> * &subTree) {
	if (subTree != nullptr) {
		inOrder(subTree->leftChild); //����������������� : �����
		//visit(subTree);  //���ʸ��ڵ�
		std::cout << subTree->data << " ";
		inOrder(subTree->rightChild); //�����������������
	}
}
template<class T>
void BinaryTree<T>::inOrder2(BinTreeNode<T>* &subTree) {  //����������ǵݹ��㷨
	std::stack<BinTreeNode<T>*> mystack;
	BinTreeNode<T> *p = this->root;
	do {
		while (p != nullptr) {
			mystack.push(p);
			p = p->leftChild;
		}
		if (!mystack.empty) {
			p = mystack.top();
			mystack.pop();
			std::cout << p->data << " ";
			p = p->rightChild;
		}
	} while (p != nullptr || !mystack.empty());
}
template<class T>
void BinaryTree<T>::preOrder(BinTreeNode<T>* &subTree) {
	if (subTree != nullptr) {
		std::cout << subTree->data << " ";  //��  ����
		preOrder(subTree->leftChild); //ǰ���������������
		preOrder(subTree->rightChild); //ǰ���������������
	}
}
template<class T>
void BinaryTree<T>::preOrder2(BinTreeNode<T>* &subTree) {
	std::stack <BinTreeNode<T> *> mystack;
	BinTreeNode<T> *p = root;  //����˳�򣺸�����
	while (p != nullptr) {
		std::cout << p->data << " ";  //�ȴ����
		if (p->leftChild&&p->rightChild) {  //ͬʱӵ����������
			mystack.push(p);  //����������ֻ���ȴ���һ��������Ҫ�Ȱѽ�㱣����ջ���Ա����������
			p = p->leftChild;
		}
		else if (p->leftChild) {
			p = p->leftChild;
		}
		else if (p->rightChild) {
			p = p->rightChild;
		}
		else {
			if (!mystack.empty()) {
				p = mystack.top();
				mystack.pop();
				p = p->rightChild;
			}
			else {
				break;
			}
		}
	}
}
template<class T>
void BinaryTree<T>::postOrder(BinTreeNode<T>* &subTree) {
	if (subTree != nullptr) {
		postOrder(subTree->leftChild); //������������������
		postOrder(subTree->rightChild); //������������������
		std::cout << subTree->data << " "; //���ڵ�
	}
}

template<class T>
void BinaryTree<T>::postOrder2(BinTreeNode<T>* &subTree) {
	std::stack<strNode<T>> mystack2;
	strNode<T> w;
	BinTreeNode<T> *p = this->root;
	do {
		while (p != nullptr) {
			w.ptr = p;
			w.tag = L;
			mystack2.push(w);
			p = p->leftChild;
		}
		int continue1 = 1;
		while (continue1 && !mystack2.empty()) {
			w = mystack2.top();
			mystack2.pop();
			p = w.ptr;
			switch (w.tag)
			{
			case 'L':
				w.tag = R;
				mystack2.push(w);
				continue1 = 0;
				p = p->rightChild;
			case 'R':
				std::cout << p->data << " ";
				break;
			default:
				std::cout << "�������" << std::endl;
				break;
			}
		}
	} while (!mystack2.empty());
	std::cout << std::endl;
}
template<class T>
int BinaryTree<T>::Size(BinTreeNode<T>* subTree) const {  //Ѱ�ҽ��ĸ���
	if (subTree == nullptr)
		return 0;  //����Ϊ0
	else
		return 1 + Size(subTree->leftChild) + Size(subTree->rightChild); //���������+���������+1
}
template<class T>
int BinaryTree<T>::Height(BinTreeNode<T>* subtree) const {
	if (subtree == nullptr)
		return 0;
	else {
		int i = Height(subtree->leftChild);
		int j = Height(subtree->rightChild);
		return ((i < j) ? j + 1 : i + 1);  //���������+1

	}
}
template<class T>
BinaryTree<T>::BinaryTree(const BinaryTree<T>& s) {
	root = Copy(s.root);  //���ƹ��캯��
}
template<class T>
BinTreeNode<T>* BinaryTree<T>::Copy(BinTreeNode<T>* orignode) {
	if (orignode == nullptr)  //��Ϊ�գ����ؿ�ָ��
		return nullptr;
	BinTreeNode<T> *temp = new BinTreeNode<T>;
	temp->data = orignode->data; //���͸�����
	temp->leftChild = Copy(orignode->leftChild); //����������
	temp->rightChild = Copy(orignode->rightChild);  //����������
	return temp;
}
template<class T>
int operator ==(const BinaryTree<T>& s, const BinaryTree<T>& t) {
	return (equal(s.root, t.root)) ? true : false;     //�ж����ö������ĵȼ��ԣ��ٵ�����BinaryTree�����Ԫ����
}
template<class T>
bool equal(BinTreeNode<T>* a, BinTreeNode<T> *b) {  //�ж�������������ǲ���ͬһ����
	if (a == nullptr&&b == nullptr)
		return true;
	if (a != nullptr&&b != nullptr&&a->data == b->data && equal(a->leftChild, b->leftChild) && equal(a->rightChild, b->rightChild))
		return true;
	else
		return false;
}
template<class T>
void BinaryTree<T>::CreateBinTree(BinTreeNode<T>* &subtree) {
	T item;
	if (!(std::cin.eof())) {   //δ���꣬���벢����
		std::cin >> item;  //���������ֵ
		if (item != RefValue) {
			subtree = new BinTreeNode<T>(item); //���������
			if (subtree == nullptr) {
				std::cerr << "�洢�������" << std::endl;
				exit(1);
			}
			CreateBinTree(subtree->leftChild);  //�ݹ齨��������dAD 
			CreateBinTree(subtree->rightChild); //�ݹ齨��������
		}
		else {
			subtree = nullptr;   //���ָ���������ָ��
			return;
		}
	}
}
template<class T>
void PrintBTree(BinTreeNode<T>* BT) {
	if (BT != nullptr) {
		std::cout << BT->data;
		if (BT->leftChild != nullptr || BT->rightChild != nullptr) {
			std::cout << "(";
			PrintBTree(BT->leftChild);
			std::cout << ",";
			if (BT->rightChild != nullptr)
				PrintBTree(BT->rightChild);
			std::cout << ")";
		}
	}
	else
	{
		std::cout << "���������ϻ���Ϊ��" << std::endl;
	}
}
template<class T>
bool BinaryTree<T>::Insert(BinTreeNode<T>* &subTree, const T &x) {
	if (subTree == nullptr) {
		subTree = new BinTreeNode<T>(x);
		return true;
	}
	else if (x < subTree->data)
		Insert(subTree->leftChild, x);
	else if (x > subTree->data)
		Insert(subTree->rightChild, x);
	else
		return false;
}
template<class T>
bool BinaryTree<T>::Find(BinTreeNode<T> * subTree, const T &x) const {
	if (subTree == nullptr)
		return nullptr;
	else if (subTree->data == x) {
		return subTree;
	}
	else {
		Find(subTree->leftChild, x);
		Find(subTree->rightChild, x);
	}
	return false; //����ʧ��
}
void print_menu7()
{
	std::cout << "1------���ɶ���������-1Ϊ��ֹ��\n"
		<< "2------�����\n"
		<< "3------���ĸ߶�\n"
		<< "4------���Ľ��ĸ���\n"
		<< "5------�ж����Ƿ�Ϊ��\n"
		<< "6------ǰ�������\n"
		<< "7------���������\n"
		<< "8------���������\n"
		<< "9------��α�����\n"
		<< " 10-----�˳�\n"
		<< "��������Ҫ���еĲ�����1-10��: ";
}
void CreateBinTree(BinTreeNode<char>* &BT) {
	std::stack<BinTreeNode<char>*> s;
	BT = nullptr;
	BinTreeNode<char> *p, *t;
	int k;
	char ch;
	std::cin >> ch;
	while (ch != '#') {
		switch (ch)
		{
		case '(':
			s.push(p);
			k = 1;
			break;
		case ')':
			t = s.top();
			s.pop();
			break;
		case ',':
			k = 2;
			break;
		default:
			p = new BinTreeNode<char>(ch);
			if (BT == nullptr)
				BT = p;
			else if (k == 1) {
				t = s.top();
				t->leftChild = p;
			}
			else {
				t = s.top();
				t->rightChild = p;
			}
		}
		std::cin >> ch;
	}

}
template<class T>
void Menu7(BinaryTree<T>& mytree) {
	while (true) {
		print_menu7();
		int n;
		std::cin >> n;
		switch (n)
		{
		case 1:
			mytree.CreateBinTree(mytree.root);
			std::cout << "�����ɳɹ�" << std::endl;
			break;
		case 2:
			std::cout << "�����" << std::endl;
			PrintBTree(mytree.root);
			std::cout << std::endl;
			break;
		case 3:
			std::cout << "���ĸ߶�Ϊ" << mytree.Height();
			std::cout << std::endl;
			break;
		case 4:
			std::cout << "���Ľ�����Ϊ" << mytree.Size();
			std::cout << std::endl;
			break;
		case 5:
			if (mytree.IsEmpty()) {
				std::cout << "��ǰ��Ϊ��" << std::endl;
			}
			else
				std::cout << "��ǰ����Ϊ��" << std::endl;
			break;
		case 6:
			std::cout << "ǰ�������(������)" << std::endl;
			mytree.preOrder(mytree.root);
			std::cout << std::endl;
			break;
		case 7:
			std::cout << "���������(�����)" << std::endl;
			mytree.inOrder(mytree.root);
			std::cout << std::endl;
			mytree.inOrder(mytree.root);
			std::cout << std::endl;
			break;
		case 8:
			std::cout << "���������(���Ҹ�)" << std::endl;
			mytree.postOrder(mytree.root);
			std::cout << std::endl;
			break;
		case 9:
			std::cout << "��α�����" << std::endl;
			mytree.levelOrder(mytree.root);
			std::cout << std::endl;
			break;
		default:
			break;
		}
	}
}
/*int main()
{
	//BinTreeNode<int>* root=new BinTreeNode<int>(8);
	BinaryTree<int> mytree;
	//std::cin >> mytree;
	Menu<int>(mytree);

}*/



