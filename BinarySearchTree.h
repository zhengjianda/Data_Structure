#pragma once
#include<iostream>
#include<stdlib.h>
int SortArray[1005];
template<class E, class K>
struct BSTNode
{
	E data;  //������
	BSTNode<E, K> *left, *right;  //����Ů������Ů
	BSTNode() :left(nullptr), right(nullptr) {

	}
	BSTNode(const E d, BSTNode<E, K>*L = nullptr, BSTNode<E, K>* R = nullptr) :data(d), left(L), right(R) {

	}
	~BSTNode()
	{

	}
	void setdata(E d) {
		data = d;
	}
	E getData() {
		return data;
	}
};
template<class E, class K>
class BST {
public:
	BST() :root(nullptr) {

	}
	BST(K value);
	~BST()
	{

	};
	bool Search(const K x) {
		return (Search(x, root) != nullptr) ? true : false;
	}
	BST<E, K>& operator=(const BST<E, K>& R);
	void makeEmpty() {
		makeEmpty(root);
		root = nullptr;
	}
	void PrintTree()const {
		PrintTree(root);
		std::cout << std::endl;
	}
	E Min() {
		BSTNode<E, K>* tem = new BSTNode<E, K>();
		tem = Min(root);
		return tem->data;
	}
	E Max() {
		BSTNode<E, K>* tem = new BSTNode<E, K>();
		tem = Max(root);
		return tem->data;
	}
	bool Insert(const E& e1) {
		return Insert(e1, root);
	}
	int Insert1(const E& x) {  //�ǵݹ����
		BSTNode<E, K>* TT, *f, *p;
		TT = root;
		f = 0;
		while (TT != 0) {
			if (x == TT->data) {
				return -1; //�����ɹ���������
			}
			else if (x < TT->data) {
				f = TT;
				TT = TT->left;
			}
			else {
				f = TT;
				TT = TT->right;
			}
		}
		p = new BSTNode<E, K>;
		p->data = x;
		p->left = p->right = 0;
		if (f == 0) {
			root = p;
		}
		else if (x > f->data) {
			f->right = p;
		}
		else {
			f->left = p;
		}
		return 1;
	}
	bool Remove(const K x) {
		return Remove(x, root);
	}
	BSTNode<E, K>* Getroot() {
		return this->root;
	}
	void SortInOrder(BSTNode<E, K>* subTree, int& j = 0) { //���������������
		if (subTree != nullptr) {
			SortInOrder(subTree->left, j);
			SortArray[j++] = subTree->data;
			SortInOrder(subTree->right, j);
		}
	}
	bool RemoveMax(BSTNode<E, K>* subTree) {
		if (subTree == nullptr) {
			return false;  //��������ʧ��
		}
		BSTNode<E, K>* tem = subTree;
		BSTNode<E, K>* pre = nullptr;
		while (tem->right != nullptr) {
			pre = tem;
			tem = tem->right;
		}
		if (pre == nullptr) {
			delete tem;  //ֻ�и��ڵ㣬ֱ��ɾ��
		}
		else {
			pre->right = tem->left;
			delete tem;
		}
		return true;
	}
private:
	BSTNode<E, K> *root;
	K RefValue;  //������ֹ����
	BSTNode<E, K> *Search(const K x, BSTNode<E, K> *ptr);
	void makeEmpty(BSTNode<E, K> * &ptr);
	void PrintTree(BSTNode<E, K> *ptr) const;
	BSTNode<E, K> *Copy(const BSTNode<E, K> *ptr);
	BSTNode<E, K> *Min(BSTNode<E, K> *ptr) const;
	BSTNode<E, K> *Max(BSTNode<E, K> *ptr) const;
	bool Insert(const E& e1, BSTNode<E, K> * & ptr);
	bool Remove(const K x, BSTNode<E, K> * & ptr);
};
template<class E, class K>
BSTNode<E, K>* BST<E, K>::Search(const K x, BSTNode<E, K>* ptr) {  //ptrΪ��ǰ�ĸ��ڵ�
	if (ptr == nullptr)
		return nullptr;
	else if (x < ptr->data)
		return Search(x, ptr->left);
	else if (x > ptr->data)
		return Search(x, ptr->right);
	else
		return ptr;
}
template<class E, class K>
bool BST<E, K>::Insert(const E& e1, BSTNode<E, K>* &ptr) {  //�ݹ���룬ע��ptr������
	if (ptr == nullptr) {
		ptr = new BSTNode<E, K>(e1);
		return true;
	}
	else if (e1 < ptr->data) {
		return Insert(e1, ptr->left);
	}
	else if (e1 > ptr->data) {
		return Insert(e1, ptr->right);
	}
	else
		return false;   //�Ѿ�����
}
template<class E, class K>
bool BST<E, K>::Remove(const K x, BSTNode<E, K>* &ptr) {
	BSTNode<E, K> *temp;
	if (ptr != nullptr) {
		if (x < ptr->data)      //��ɾ����λ��
			Remove(x, ptr->left);
		else if (x > ptr->data)  //��ɾ����λ��
			Remove(x, ptr->right);        //δ�ҵ����������
		else if (ptr->left != nullptr&&ptr->right != nullptr) {  //����Ů������Ůͬʱ����
			temp = ptr->right;
			while (temp->left != nullptr)
				temp = temp->left;
			ptr->data = temp->data;
			Remove(ptr->data, ptr->right);       //�ҵ���Ԫ�أ�������������Ϊ�գ����:������������������ĵ�һ����Ů�����ɾ���������ϵ������Ů"
		}
		else {
			temp = ptr;
			if (ptr->left == nullptr)    //������Ϊ�գ�����Ů�
				ptr = ptr->right;
			else
				ptr = ptr->left;       //������Ϊ�գ�����Ů�
			delete temp;
			return true;
		}
	}
	return false;
}
template<class E, class K>
BSTNode<E, K>* BST<E, K>::Max(BSTNode<E, K> *ptr) const {
	if (ptr->right != nullptr) {
		Max(ptr->right);
	}
	else {
		return ptr;
	}
}
template<class E, class K>
BSTNode<E, K>* BST<E, K>::Min(BSTNode<E, K> *ptr) const {
	if (ptr->left != nullptr) {
		return Max(ptr->left);
	}
	else {
		return ptr;
	}
}
template<class E, class K>
void BST<E, K>::PrintTree(BSTNode<E, K> *ptr) const {
	if (ptr != nullptr) {
		std::cout << ptr->data;
		if (ptr->left != nullptr || ptr->right != nullptr) {
			std::cout << "(";
			PrintTree(ptr->left);
			std::cout << ",";
			PrintTree(ptr->right);
			std::cout << ")";
		}
	}
}
