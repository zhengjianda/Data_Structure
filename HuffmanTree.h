#include<iostream>
#include"heap.h"
const int DefaultSize11 = 20;
template<class T>
struct HuffmanNode    //Huffman树结点的类定义
{
	T data;    //结点数据                                           //左子树右子树和父结点
	HuffmanNode* leftChild = new HuffmanNode();
	HuffmanNode* rightChild = new HuffmanNode();
	HuffmanNode* parent = new HuffmanNode();

	HuffmanNode() :leftChild(nullptr), rightChild(nullptr), parent(nullptr) {

	}
	HuffmanNode(T elem, HuffmanNode* left = nullptr, HuffmanNode* right = nullptr, HuffmanNode* pr = nullptr) :data(elem), leftChild(left), rightChild(right), parent(pr) {

	}
	bool operator <=(HuffmanNode& R) {
		return data <= R.data;
	}
	bool operator >(HuffmanNode& R) {
		return data > R.data;
	}
};
template<class T>
class HuffmanTree {
public:
	HuffmanTree(T w[], int n);  //构造函数
	~HuffmanTree()
	{
		//deleteTree(root);
	}
	void PrintBTree(HuffmanNode<T>* BT) {
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
	HuffmanNode<T>* root;
protected:
	void deleteTree(HuffmanNode<T> *t);
	void mergeTree(HuffmanNode<T> &ht1, HuffmanNode<T> &ht2, HuffmanNode<T> *&parent);
};
template<class T>
HuffmanTree<T>::HuffmanTree(T w[], int n) {
	MinHeap<HuffmanNode<T>> hp;    //使用最小堆存放森林
	HuffmanNode<T> *parent = nullptr;
	HuffmanNode<T> cur;
	for (int i = 0; i < n; i++) {  //森林各棵树初始化
		cur.data = w[i];  //各个结点的权值
		cur.leftChild = nullptr;
		cur.rightChild = nullptr;
		cur.parent = nullptr;
		hp.Insert(cur);   //将各树存入堆中
	}
	for (int i = 0; i < n - 1; i++) { //做n-1趟，形成Huffman树
		HuffmanNode<T> *first = new HuffmanNode<T>;
		HuffmanNode<T> *second = new HuffmanNode<T>;
		hp.RemoveMin(*first);
		hp.RemoveMin(*second);  //选择两个权值最小的树
		mergeTree(*first, *second, parent);   //合并，形成一棵树
		hp.Insert(*parent);  // 将新树重新插入到最小堆中
		if (i != n - 2)
			delete parent;
	}
	root = parent;
}
template<class T>
void HuffmanTree<T>::mergeTree(HuffmanNode<T>& bt1, HuffmanNode<T>& bt2, HuffmanNode<T>* &parent) {  //合并子树
	parent = new HuffmanNode<T>;
	parent->leftChild = &bt1;
	parent->rightChild = &bt2;
	parent->data = bt1.data + bt2.data;
	bt1.parent = bt2.parent = parent;
}
void CreateHuffmanTree(int a[], int len) {
	HuffmanTree<int> myHuffmanTree(a, len);
	myHuffmanTree.PrintBTree(myHuffmanTree.root);
}
/*int main()
{
	int power[10] = { 1,2,7,4,5 };
	/*HuffmanTree<int> myHuffmanTree(power, 5);
	std::cout << myHuffmanTree.root->data << std::endl;
	//myHuffmanTree.root->leftChild->data = 1000;
	if(myHuffmanTree.root->leftChild!=nullptr)
		std::cout << myHuffmanTree.root->leftChild->data<< std::endl;
	std::cout << myHuffmanTree.root->rightChild->data << std::endl;
	std::cout <<"广义表输出"<< std::endl;
	myHuffmanTree.PrintBTree(myHuffmanTree.root);
	CreateHuffmanTree(power, 5);
	return 0;

}*/