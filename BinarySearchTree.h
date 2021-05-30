#pragma once
#include<iostream>
#include<stdlib.h>
int SortArray[1005];
template<class E, class K>
struct BSTNode
{
	E data;  //数据域
	BSTNode<E, K> *left, *right;  //左子女，右子女
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
	int Insert1(const E& x) {  //非递归插入
		BSTNode<E, K>* TT, *f, *p;
		TT = root;
		f = 0;
		while (TT != 0) {
			if (x == TT->data) {
				return -1; //搜索成功，不插入
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
	void SortInOrder(BSTNode<E, K>* subTree, int& j = 0) { //利用中序遍历排序
		if (subTree != nullptr) {
			SortInOrder(subTree->left, j);
			SortArray[j++] = subTree->data;
			SortInOrder(subTree->right, j);
		}
	}
	bool RemoveMax(BSTNode<E, K>* subTree) {
		if (subTree == nullptr) {
			return false;  //空树返回失败
		}
		BSTNode<E, K>* tem = subTree;
		BSTNode<E, K>* pre = nullptr;
		while (tem->right != nullptr) {
			pre = tem;
			tem = tem->right;
		}
		if (pre == nullptr) {
			delete tem;  //只有根节点，直接删除
		}
		else {
			pre->right = tem->left;
			delete tem;
		}
		return true;
	}
private:
	BSTNode<E, K> *root;
	K RefValue;  //输入终止符号
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
BSTNode<E, K>* BST<E, K>::Search(const K x, BSTNode<E, K>* ptr) {  //ptr为当前的父节点
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
bool BST<E, K>::Insert(const E& e1, BSTNode<E, K>* &ptr) {  //递归插入，注意ptr是引用
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
		return false;   //已经存在
}
template<class E, class K>
bool BST<E, K>::Remove(const K x, BSTNode<E, K>* &ptr) {
	BSTNode<E, K> *temp;
	if (ptr != nullptr) {
		if (x < ptr->data)      //找删除的位置
			Remove(x, ptr->left);
		else if (x > ptr->data)  //找删除的位置
			Remove(x, ptr->right);        //未找到的两种情况
		else if (ptr->left != nullptr&&ptr->right != nullptr) {  //左子女和右子女同时存在
			temp = ptr->right;
			while (temp->left != nullptr)
				temp = temp->left;
			ptr->data = temp->data;
			Remove(ptr->data, ptr->right);       //找到了元素，左右子树均不为空，找填补:”在右子树上找中序的第一个子女填补，并删除右子树上的这个子女"
		}
		else {
			temp = ptr;
			if (ptr->left == nullptr)    //左子树为空，右子女填补
				ptr = ptr->right;
			else
				ptr = ptr->left;       //右子树为空，左子女填补
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
