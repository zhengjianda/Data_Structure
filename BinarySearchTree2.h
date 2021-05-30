#include<iostream>
#include "BinarySearchTree.h"
const int Mymin = -999999999;
const int Mymax = 999999999;
template<class E, class K>
bool IsBST2(BSTNode<E, K>* node, int min, int max) {
	if (node == nullptr) {
		return true;  //空树为二叉搜索树
	}
	else if (node->data <= min || node->data >= max) {
		return false;  //不符合二叉搜索树的规定
	}
	else {
		return (IsBST2(node->left, min, node->data) && IsBST2(node->right, node->data, max));
	}


}
template<class E, class K>
bool IsBST1(BSTNode<E, K>* ptr) {   //指定Mymin为-无穷，Mymax为+无穷
	return (IsBST2(ptr, Mymin, Mymax));
}
void print_menu8() {
	std::cout << " 1------插入一个元素\n"
		<< " 2------输出树中的结点元素\n"
		<< " 3------删除树中的结点元素\n"
		<< " 4------查找树中元素的位置\n"
		<< " 5------树中的最小值\n"
		<< " 6------树中的最大值\n"
		<< " 7------退出\n"
		<< " 请输入您要进行的操作: ";
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
			std::cout << "请输入要插入的元素" << std::endl;
			std::cin >> x;
			myBinarySearchTree.Insert(x);
			break;
		case 2:
			std::cout << "输出搜索树的结点" << std::endl;
			myBinarySearchTree.PrintTree();
			break;
		case 3:
			std::cout << "请输入要删除的元素" << std::endl;
			std::cin >> x;
			myBinarySearchTree.Remove(x);
			std::cout << x << "已经删除" << std::endl;
			break;
		case 4:
			std::cout << "请输入要查找的元素" << std::endl;
			std::cin >> x;
			myBinarySearchTree.Search(x);
			break;
		case 5:
			std::cout << "搜索树的最小值为" << myBinarySearchTree.Min() << std::endl;
			break;
		case 6:
			std::cout << "搜索树的最大值为" << myBinarySearchTree.Max() << std::endl;
			break;
		default:
			std::cout << "洛：结束了" << std::endl;
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
	myBinarySearchTree.Insert(10);  //插入
	myBinarySearchTree.Insert(15);
	myBinarySearchTree.Insert(2);
	myBinarySearchTree.Insert(24);
	myBinarySearchTree.PrintTree();  //输出
	myBinarySearchTree.Remove(23);  //删除
	myBinarySearchTree.PrintTree();
	bool judge=myBinarySearchTree.Search(24);
	std::cout << judge << std::endl;
	std::cout << std::endl;
	std::cout<<"最小值为" << myBinarySearchTree.Min() << std::endl;
	std::cout << "最大值为" << myBinarySearchTree.Max() << std::endl;
	bool Judge = false;
	Judge=IsBST1<int, int>(myBinarySearchTree.Getroot());
	std::cout << "是否为二叉搜索树" << Judge << std::endl;
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