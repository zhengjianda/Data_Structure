#include<iostream>
#include<stack>
#include<queue>
enum tag1
{
	L, R
};
template<class T>
struct BinTreeNode {  //结点数据类型
	T data;
	BinTreeNode<T> * leftChild, *rightChild;
	BinTreeNode() :leftChild(nullptr), rightChild(nullptr) {

	}
	BinTreeNode(T x, BinTreeNode<T> * l = nullptr, BinTreeNode<T> *r = nullptr) :data(x), leftChild(l), rightChild(r) {

	}
};
template<class T>
struct strNode {
	BinTreeNode<T> *ptr;    //树节点指针
	tag1 tag;
	strNode(BinTreeNode<T>* N = nullptr) :ptr(N), tag(L) {

	};
};
template<class T>
class BinaryTree {
public:
	BinaryTree() :root(nullptr) {
		RefValue = -1;   //树终止的标志
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
	BinTreeNode<T> * Parent(BinTreeNode<T> *current) {   //返回父节点
		return (root == nullptr || root == current) ? nullptr : Parent(root, current);
	}
	BinTreeNode<T> * LeftChild(BinTreeNode<T>* current) {    //返回左子女
		return (current != nullptr) ? current->leftChild : nullptr;
	}
	BinTreeNode<T> * RightChild(BinaryTree<T>* current) {     //返回右子女
		return (current != nullptr) ? current->RightChild : nullptr;
	}
	int Height() {
		return Height(root); //返回树高度
	}
	int Size() {         //返回结点数
		return Size(root);
	}
	BinTreeNode<T> * getRoot() const {
		return root;           //取根
	}
	void preOrder(BinTreeNode<T>* & subTree);
	void preOrder2(BinTreeNode<T>* & subTree);  //前序非递归算法
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
			std::cout << "结点为空" << std::endl;
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
		destroy(subTree->leftChild); //摧毁左子树
		destroy(subTree->rightChild); //摧毁右子树
		delete subTree;  //摧毁根
	}
}
template<class T>
BinTreeNode<T> * BinaryTree<T>::Parent(BinTreeNode<T>* subTree, BinTreeNode<T>* current) {
	if (subTree == nullptr) {
		return nullptr;       //空树 报错
	}
	if (subTree->leftChild == current || subTree->rightChild == current)
		return subTree;         //找到，返回父节点
	BinTreeNode<T> *p;
	if ((p = Parent(subTree->leftChild, current)) != nullptr) {
		return p;   //从左子树继续找
	}
	else               //从右子树继续找 
		return Parent(subTree->rightChild, current);
}
template<class T>
void BinaryTree<T>::Traverse(BinTreeNode<T>* subTree, std::ostream& out) {  //私有函数，搜索并输出根为subTree的二叉树
	if (subTree != nullptr) {
		out << subTree->data << " ";   //输出根的数据
		Traverse(subTree->leftChild, out); //左子树输出
		Traverse(subTree->rightChild, out); //右子树输出
	}
};
template<class T>
void BinaryTree<T>::levelOrder(BinTreeNode<T>* subtree) {   //层次遍历
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
	out << "二叉树的前序遍历\n";
	Tree.Traverse(Tree.root, out);
	out << std::endl;
	return out;
}
template<class T>
void BinaryTree<T>::inOrder(BinTreeNode<T> * &subTree) {
	if (subTree != nullptr) {
		inOrder(subTree->leftChild); //中序遍历根的左子树 : 左根右
		//visit(subTree);  //访问根节点
		std::cout << subTree->data << " ";
		inOrder(subTree->rightChild); //中序遍历根的右子树
	}
}
template<class T>
void BinaryTree<T>::inOrder2(BinTreeNode<T>* &subTree) {  //中序遍历树非递归算法
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
		std::cout << subTree->data << " ";  //根  左右
		preOrder(subTree->leftChild); //前序遍历根的左子树
		preOrder(subTree->rightChild); //前序遍历根的右子树
	}
}
template<class T>
void BinaryTree<T>::preOrder2(BinTreeNode<T>* &subTree) {
	std::stack <BinTreeNode<T> *> mystack;
	BinTreeNode<T> *p = root;  //遍历顺序：根左右
	while (p != nullptr) {
		std::cout << p->data << " ";  //先处理根
		if (p->leftChild&&p->rightChild) {  //同时拥有左右子树
			mystack.push(p);  //有两个根，只能先处理一个根，需要先把结点保存在栈，以便遍历右子树
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
		postOrder(subTree->leftChild); //后续遍历根的左子树
		postOrder(subTree->rightChild); //后续遍历根的右子树
		std::cout << subTree->data << " "; //根节点
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
				std::cout << "输入错误" << std::endl;
				break;
			}
		}
	} while (!mystack2.empty());
	std::cout << std::endl;
}
template<class T>
int BinaryTree<T>::Size(BinTreeNode<T>* subTree) const {  //寻找结点的个数
	if (subTree == nullptr)
		return 0;  //空树为0
	else
		return 1 + Size(subTree->leftChild) + Size(subTree->rightChild); //左子树结点+右子树结点+1
}
template<class T>
int BinaryTree<T>::Height(BinTreeNode<T>* subtree) const {
	if (subtree == nullptr)
		return 0;
	else {
		int i = Height(subtree->leftChild);
		int j = Height(subtree->rightChild);
		return ((i < j) ? j + 1 : i + 1);  //找最高子树+1

	}
}
template<class T>
BinaryTree<T>::BinaryTree(const BinaryTree<T>& s) {
	root = Copy(s.root);  //复制构造函数
}
template<class T>
BinTreeNode<T>* BinaryTree<T>::Copy(BinTreeNode<T>* orignode) {
	if (orignode == nullptr)  //根为空，返回空指针
		return nullptr;
	BinTreeNode<T> *temp = new BinTreeNode<T>;
	temp->data = orignode->data; //传送根数据
	temp->leftChild = Copy(orignode->leftChild); //复制左子树
	temp->rightChild = Copy(orignode->rightChild);  //复制右子树
	return temp;
}
template<class T>
int operator ==(const BinaryTree<T>& s, const BinaryTree<T>& t) {
	return (equal(s.root, t.root)) ? true : false;     //判断两棵二叉树的等价性，假的它是BinaryTree类的友元函数
}
template<class T>
bool equal(BinTreeNode<T>* a, BinTreeNode<T> *b) {  //判断两个结点代表的是不是同一根树
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
	if (!(std::cin.eof())) {   //未读完，读入并建树
		std::cin >> item;  //读入根结点的值
		if (item != RefValue) {
			subtree = new BinTreeNode<T>(item); //建立根结点
			if (subtree == nullptr) {
				std::cerr << "存储分配错误" << std::endl;
				exit(1);
			}
			CreateBinTree(subtree->leftChild);  //递归建立左子树dAD 
			CreateBinTree(subtree->rightChild); //递归建立右子树
		}
		else {
			subtree = nullptr;   //封闭指向空子树的指针
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
		std::cout << "树已输出完毕或树为空" << std::endl;
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
	return false; //搜索失败
}
void print_menu7()
{
	std::cout << "1------生成二叉树，以-1为终止点\n"
		<< "2------输出树\n"
		<< "3------树的高度\n"
		<< "4------树的结点的个数\n"
		<< "5------判断树是否为空\n"
		<< "6------前序遍历树\n"
		<< "7------中序遍历树\n"
		<< "8------后序遍历树\n"
		<< "9------层次遍历树\n"
		<< " 10-----退出\n"
		<< "请输入您要进行的操作（1-10）: ";
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
			std::cout << "树生成成功" << std::endl;
			break;
		case 2:
			std::cout << "输出树" << std::endl;
			PrintBTree(mytree.root);
			std::cout << std::endl;
			break;
		case 3:
			std::cout << "树的高度为" << mytree.Height();
			std::cout << std::endl;
			break;
		case 4:
			std::cout << "树的结点个数为" << mytree.Size();
			std::cout << std::endl;
			break;
		case 5:
			if (mytree.IsEmpty()) {
				std::cout << "当前树为空" << std::endl;
			}
			else
				std::cout << "当前树不为空" << std::endl;
			break;
		case 6:
			std::cout << "前序遍历树(根左右)" << std::endl;
			mytree.preOrder(mytree.root);
			std::cout << std::endl;
			break;
		case 7:
			std::cout << "中序遍历树(左根右)" << std::endl;
			mytree.inOrder(mytree.root);
			std::cout << std::endl;
			mytree.inOrder(mytree.root);
			std::cout << std::endl;
			break;
		case 8:
			std::cout << "后序遍历树(左右根)" << std::endl;
			mytree.postOrder(mytree.root);
			std::cout << std::endl;
			break;
		case 9:
			std::cout << "层次遍历树" << std::endl;
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



