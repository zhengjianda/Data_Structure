#pragma once
#include<iostream>
using namespace std;
template<class T>
struct ThreadNode {
	int ltag, rtag;
	ThreadNode<T>* leftChild, *rightChild;
	T data;
	ThreadNode(const T item) :data(item), leftChild(nullptr), rightChild(nullptr), ltag(0), rtag(0) {

	}
};
template<class T>
class ThreadTree {
protected:
	ThreadNode<T>* root;
public:
	void CreateInThread(ThreadNode<T>* current, ThreadNode<T>* &pre);  //中序线索二叉树
	ThreadNode<T>* parent(ThreadNode<T>* t);
	ThreadTree<T>() : root(nullptr) {

	}
	void createInThread();
	ThreadNode<T>* First(ThreadNode<T>* current); //寻找中序下第一个结点
	ThreadNode<T>* Last(ThreadNode<T>* current); //寻找中序下的最后一个结点
	ThreadNode<T>* Next(ThreadNode<T>* current); //寻找中序下的后继结点
	ThreadNode<T>* Prior(ThreadNode<T>* current); //寻找中序下的前驱结点
	void InOrder();  //中序遍历
	void PreOrder();  //前序遍历
	void postOrder(); //后序遍历
};
template<class T>
ThreadNode<T>* ThreadTree<T>::First(ThreadNode<T>* current) {
	// 函数返回以* current为根的中序线索二叉树中中序序列下的第一个结点
	ThreadNode<T>* p = current;
	while (p->ltag == 0) {
		p = p->leftChild; //等于0说明有左子女，一直搜到最左下的结点，为中序下的第一个结点
	}
	return p;
}
template<class T>
ThreadNode<T>* ThreadTree<T>::Next(ThreadNode<T>* current) {
	// 函数返回在中序线索二叉树中结点current在中序下的后继结点
	if (current->rtag == 1) {   //又子女存的是后继结点，直接返回
		return current->rightChild;
	}
	else {
		return First(current->rightChild);  //存在右子女，寻找右子女在中序遍历下的第一个结点，调用函数First
	}
}
template<class T>
ThreadNode<T>* ThreadTree<T>::Last(ThreadNode<T>* current) {
	// 函数返回以* current为根的中序线索二叉树中序序列下的最后一个结点
	ThreadNode<T>* l = current;
	while (l->ltag == 0) {
		l = l->rightChild;      //最右下结点(不一定是叶结点)
	}
	return p;
}
template<class T>
ThreadNode<T>* ThreadTree<T>::Prior(ThreadNode<T>* current) {
	//函数返回在中序线索二叉树中结点current在中序下的前驱结点
	if (current->ltag == 1) {
		return current->leftChild;
	}
	else {
		return Last(current->leftChild);
	}
}
template<class T>
void ThreadTree<T>::InOrder() {
	ThreadNode<T>* p;
	for (p = First(root); p != nullptr; p = Next(p)) {
		std::cout << p->data;
	}
}
template<class T>
void ThreadTree<T>::createInThread() {
	ThreadNode<T>* pre = nullptr; //前驱结点指针
	if (root != nullptr) {
		CreateInThread(root, pre);  //非空二叉树，线索化
		pre->rightChild = nullptr; // 后处理中序最后一个结点
		pre->rtag = 1;
	}
}
template<class T>
void ThreadTree<T>::CreateInThread(ThreadNode<T>* current, ThreadNode<T>* &pre) {
	//通过中序遍历，对二叉树进行线索化
	if (current = nullptr)
		return;
	CreateInThread(current->leftChild, pre);  //递归，左子树线索化
	if (current->leftChild == nullptr) { //建立当前结点的前驱搜索
		current->leftChild = pre;
		current->ltag = 1;
	}
	if (pre != nullptr&&pre->rightChild == nullptr) {  //建立当前结点的后继线索
		pre->rightChild = current;
		pre->rtag = 1;
	}
	pre = current; //前驱跟上
	CreateInThread(current->rightChild, pre);//递归右子树的线索化
}
template<class T>
void ThreadTree<T>::PreOrder() {
	ThreadNode<T>* p = root;
	while (p != nullptr) {
		std::cout << p->data << " "; //访问根结点
		if (p->ltag == 0) {            //有左子女，即为后继
			p = p->leftChild;
		}
		else if (p->rtag == 0) {   //有右子女，也有后继
			p = p->rightChild;
		}
		else {  //沿中序后续线索检测  知道找到一个有右子女结点的结点，结点的右子女即为当前点的前序后继结点
			while (p != nullptr&&p->rtag == 1) {
				p = p->rightChild;
			} //找到有右子女的结点
			if (p != nullptr)
				p = p->rightChild;  //右子女结点即为后继
		}
	}
}
template<class T>
void ThreadTree<T>::postOrder() {
	ThreadNode<T>* t = root;
	while (t->ltag == 0 || t->rtag == 0) {  //寻找后序的第一个结点
		if (t->ltag == 0) {
			t = t->leftChild;
		}
		else if (t->rtag == 0) {
			t = t->rightChild;
		}
	}
	std::cout << t->data << " ";   //访问第一个结点
	ThreadNode<T>* p;
	while ((p == parent(t)) != nullptr) {
		if (p->rightChild == t || p->rtag == 1)  //如果t是父节点的右子女 ，或者t是左子女但右子女不存在 即t的后续结点是父结点 t=父节点
			t = p;
		else {   //存在右子女，则继续搜索右子树下的后序第一结点
			t = p->rightChild;
			while (t->ltag == 0 || t->rtag == 0) {
				if (t->ltag == 0) {
					t = t->leftChild;
				}
				else if (t->rtag == 0) {
					t = t->rightChild;
				}
			}
		}
		std::cout << t << " ";   //访问结点
	}
}
template<class T>
ThreadNode<T>* ThreadTree<T>::parent(ThreadNode<T>* t) {
	ThreadNode<T> *p;
	if (t == root)  //根结点无父节点
		return nullptr;
	for (p = t; p->ltag == 0; p = p->leftChild);  //找中序前驱
	if (p->leftChild != nullptr) {
		for (p = p->leftChild; p != nullptr&&p->leftChild != t && p->rightChild != t; p = p->rightChild); //往右下找父节点
	}  //
	if (p == nullptr || p->leftChild == nullptr) { //第一条路径失败
		for (p = t; p->rtag == 0; p->rightChild); //找中序后继
		for (p = p->rightChild; p != nullptr&&p->leftChild != t && p->rightChild != t; p = p->leftChild);
	}
	return p;



}