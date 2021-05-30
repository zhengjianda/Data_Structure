#include<iostream>
#include "BinarySearchTree.h"
const int Mymin = -999999999;
const int Mymax = 999999999;
template<class E, class K>
bool IsBST2(BSTNode<E, K>* node, int min, int max) {
	if (node == nullptr) {
		return true;  //����Ϊ����������
	}
	else if (node->data <= min || node->data >= max) {
		return false;  //�����϶����������Ĺ涨
	}
	else {
		return (IsBST2(node->left, min, node->data) && IsBST2(node->right, node->data, max));
	}


}
template<class E, class K>
bool IsBST1(BSTNode<E, K>* ptr) {   //ָ��MyminΪ-���MymaxΪ+����
	return (IsBST2(ptr, Mymin, Mymax));
}
void print_menu8() {
	std::cout << " 1------����һ��Ԫ��\n"
		<< " 2------������еĽ��Ԫ��\n"
		<< " 3------ɾ�����еĽ��Ԫ��\n"
		<< " 4------��������Ԫ�ص�λ��\n"
		<< " 5------���е���Сֵ\n"
		<< " 6------���е����ֵ\n"
		<< " 7------�˳�\n"
		<< " ��������Ҫ���еĲ���: ";
}
template<class T, class E>
void Menu8(BST<T, E> & myBinarySearchTree) {
	while (true) {
		print_menu8();
		int n;
		std::cin >> n;
		switch (n)
		{
			int i;
			T x;
		case 1:
			std::cout << "������Ҫ�����Ԫ��" << std::endl;
			std::cin >> x;
			myBinarySearchTree.Insert(x);
			break;
		case 2:
			std::cout << "����������Ľ��" << std::endl;
			myBinarySearchTree.PrintTree();
			break;
		case 3:
			std::cout << "������Ҫɾ����Ԫ��" << std::endl;
			std::cin >> x;
			myBinarySearchTree.Remove(x);
			std::cout << x << "�Ѿ�ɾ��" << std::endl;
			break;
		case 4:
			std::cout << "������Ҫ���ҵ�Ԫ��" << std::endl;
			std::cin >> x;
			myBinarySearchTree.Search(x);
			break;
		case 5:
			std::cout << "����������СֵΪ" << myBinarySearchTree.Min() << std::endl;
			break;
		case 6:
			std::cout << "�����������ֵΪ" << myBinarySearchTree.Max() << std::endl;
			break;
		default:
			std::cout << "�壺������" << std::endl;
			return;
		}
	}
}
/*int main()
{
	BST<int, int> myBinarySearchTree = BST<int, int>();
	Menu8(myBinarySearchTree);
	/*myBinarySearchTree.Insert(3);
	myBinarySearchTree.Insert(5);
	myBinarySearchTree.Insert(23);
	myBinarySearchTree.Insert(9);
	myBinarySearchTree.Insert(10);  //����
	myBinarySearchTree.Insert(15);
	myBinarySearchTree.Insert(2);
	myBinarySearchTree.Insert(24);
	myBinarySearchTree.PrintTree();  //���
	myBinarySearchTree.Remove(23);  //ɾ��
	myBinarySearchTree.PrintTree();
	bool judge=myBinarySearchTree.Search(24);
	std::cout << judge << std::endl;
	std::cout << std::endl;
	std::cout<<"��СֵΪ" << myBinarySearchTree.Min() << std::endl;
	std::cout << "���ֵΪ" << myBinarySearchTree.Max() << std::endl;
	bool Judge = false;
	Judge=IsBST1<int, int>(myBinarySearchTree.Getroot());
	std::cout << "�Ƿ�Ϊ����������" << Judge << std::endl;
	int a = 0;
	myBinarySearchTree.SortInOrder(myBinarySearchTree.Getroot(), a);
	for (int i = 0; i < 20; i++) {
		std::cout << SortArray[i] << " ";
	}
	myBinarySearchTree.Remove(myBinarySearchTree.Max());
	std::cout << std::endl;
	myBinarySearchTree.RemoveMax(myBinarySearchTree.Getroot());
	myBinarySearchTree.PrintTree();
	return 0;
}*/