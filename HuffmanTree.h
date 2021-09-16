#include<iostream>
#include"heap.h"
const int DefaultSize11 = 20;
template<class T>
struct HuffmanNode    //Huffman���������ඨ��
{
	T data;    //��������                                           //�������������͸�����
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
	HuffmanTree(T w[], int n);  //���캯��
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
			std::cout << "�����������ϻ���Ϊ��" << std::endl;
		}
	}
	HuffmanNode<T>* root;
protected:
	void deleteTree(HuffmanNode<T> *t);
	void mergeTree(HuffmanNode<T> &ht1, HuffmanNode<T> &ht2, HuffmanNode<T> *&parent);
};
template<class T>
HuffmanTree<T>::HuffmanTree(T w[], int n) {
	MinHeap<HuffmanNode<T>> hp;    //ʹ����С�Ѵ���ɭ��
	HuffmanNode<T> *parent = nullptr;
	HuffmanNode<T> cur;
	for (int i = 0; i < n; i++) {  //ɭ�ָ�������ʼ��
		cur.data = w[i];  //����������Ȩֵ
		cur.leftChild = nullptr;
		cur.rightChild = nullptr;
		cur.parent = nullptr;
		hp.Insert(cur);   //��������������
	}
	for (int i = 0; i < n - 1; i++) { //��n-1�ˣ��γ�Huffman��
		HuffmanNode<T> *first = new HuffmanNode<T>;
		HuffmanNode<T> *second = new HuffmanNode<T>;
		hp.RemoveMin(*first);
		hp.RemoveMin(*second);  //ѡ������Ȩֵ��С����
		mergeTree(*first, *second, parent);   //�ϲ����γ�һ����
		hp.Insert(*parent);  // ���������²��뵽��С����
		if (i != n - 2)
			delete parent;
	}
	root = parent;
}
template<class T>
void HuffmanTree<T>::mergeTree(HuffmanNode<T>& bt1, HuffmanNode<T>& bt2, HuffmanNode<T>* &parent) {  //�ϲ�����
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
