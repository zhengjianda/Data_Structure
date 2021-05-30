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
	void CreateInThread(ThreadNode<T>* current, ThreadNode<T>* &pre);  //��������������
	ThreadNode<T>* parent(ThreadNode<T>* t);
	ThreadTree<T>() : root(nullptr) {

	}
	void createInThread();
	ThreadNode<T>* First(ThreadNode<T>* current); //Ѱ�������µ�һ�����
	ThreadNode<T>* Last(ThreadNode<T>* current); //Ѱ�������µ����һ�����
	ThreadNode<T>* Next(ThreadNode<T>* current); //Ѱ�������µĺ�̽��
	ThreadNode<T>* Prior(ThreadNode<T>* current); //Ѱ�������µ�ǰ�����
	void InOrder();  //�������
	void PreOrder();  //ǰ�����
	void postOrder(); //�������
};
template<class T>
ThreadNode<T>* ThreadTree<T>::First(ThreadNode<T>* current) {
	// ����������* currentΪ�����������������������������µĵ�һ�����
	ThreadNode<T>* p = current;
	while (p->ltag == 0) {
		p = p->leftChild; //����0˵��������Ů��һֱ�ѵ������µĽ�㣬Ϊ�����µĵ�һ�����
	}
	return p;
}
template<class T>
ThreadNode<T>* ThreadTree<T>::Next(ThreadNode<T>* current) {
	// �������������������������н��current�������µĺ�̽��
	if (current->rtag == 1) {   //����Ů����Ǻ�̽�㣬ֱ�ӷ���
		return current->rightChild;
	}
	else {
		return First(current->rightChild);  //��������Ů��Ѱ������Ů����������µĵ�һ����㣬���ú���First
	}
}
template<class T>
ThreadNode<T>* ThreadTree<T>::Last(ThreadNode<T>* current) {
	// ����������* currentΪ���������������������������µ����һ�����
	ThreadNode<T>* l = current;
	while (l->ltag == 0) {
		l = l->rightChild;      //�����½��(��һ����Ҷ���)
	}
	return p;
}
template<class T>
ThreadNode<T>* ThreadTree<T>::Prior(ThreadNode<T>* current) {
	//�������������������������н��current�������µ�ǰ�����
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
	ThreadNode<T>* pre = nullptr; //ǰ�����ָ��
	if (root != nullptr) {
		CreateInThread(root, pre);  //�ǿն�������������
		pre->rightChild = nullptr; // �����������һ�����
		pre->rtag = 1;
	}
}
template<class T>
void ThreadTree<T>::CreateInThread(ThreadNode<T>* current, ThreadNode<T>* &pre) {
	//ͨ������������Զ���������������
	if (current = nullptr)
		return;
	CreateInThread(current->leftChild, pre);  //�ݹ飬������������
	if (current->leftChild == nullptr) { //������ǰ����ǰ������
		current->leftChild = pre;
		current->ltag = 1;
	}
	if (pre != nullptr&&pre->rightChild == nullptr) {  //������ǰ���ĺ������
		pre->rightChild = current;
		pre->rtag = 1;
	}
	pre = current; //ǰ������
	CreateInThread(current->rightChild, pre);//�ݹ���������������
}
template<class T>
void ThreadTree<T>::PreOrder() {
	ThreadNode<T>* p = root;
	while (p != nullptr) {
		std::cout << p->data << " "; //���ʸ����
		if (p->ltag == 0) {            //������Ů����Ϊ���
			p = p->leftChild;
		}
		else if (p->rtag == 0) {   //������Ů��Ҳ�к��
			p = p->rightChild;
		}
		else {  //����������������  ֪���ҵ�һ��������Ů���Ľ�㣬��������Ů��Ϊ��ǰ���ǰ���̽��
			while (p != nullptr&&p->rtag == 1) {
				p = p->rightChild;
			} //�ҵ�������Ů�Ľ��
			if (p != nullptr)
				p = p->rightChild;  //����Ů��㼴Ϊ���
		}
	}
}
template<class T>
void ThreadTree<T>::postOrder() {
	ThreadNode<T>* t = root;
	while (t->ltag == 0 || t->rtag == 0) {  //Ѱ�Һ���ĵ�һ�����
		if (t->ltag == 0) {
			t = t->leftChild;
		}
		else if (t->rtag == 0) {
			t = t->rightChild;
		}
	}
	std::cout << t->data << " ";   //���ʵ�һ�����
	ThreadNode<T>* p;
	while ((p == parent(t)) != nullptr) {
		if (p->rightChild == t || p->rtag == 1)  //���t�Ǹ��ڵ������Ů ������t������Ů������Ů������ ��t�ĺ�������Ǹ���� t=���ڵ�
			t = p;
		else {   //��������Ů������������������µĺ����һ���
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
		std::cout << t << " ";   //���ʽ��
	}
}
template<class T>
ThreadNode<T>* ThreadTree<T>::parent(ThreadNode<T>* t) {
	ThreadNode<T> *p;
	if (t == root)  //������޸��ڵ�
		return nullptr;
	for (p = t; p->ltag == 0; p = p->leftChild);  //������ǰ��
	if (p->leftChild != nullptr) {
		for (p = p->leftChild; p != nullptr&&p->leftChild != t && p->rightChild != t; p = p->rightChild); //�������Ҹ��ڵ�
	}  //
	if (p == nullptr || p->leftChild == nullptr) { //��һ��·��ʧ��
		for (p = t; p->rtag == 0; p->rightChild); //��������
		for (p = p->rightChild; p != nullptr&&p->leftChild != t && p->rightChild != t; p = p->leftChild);
	}
	return p;



}