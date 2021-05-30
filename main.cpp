#include<iostream>
#include<assert.h>
#include"LinearList.h"
#include"SeqList.h"
#include"LinkList.h"
#include"LinkList2.h"
#include"LinearList2.h"
#include"DblList.h"
#include"Stack.h"
#include"SeqStack.h"
#include"Queue.h"
#include"SeqQueue.h"
#include"LinkQueue.h"
#include"Priority_Queue.h"
#include"BinaryTree.h"
#include"BinarySearchTree.h"
#include"BinarySearchTree2.h"
#include"AVLTree.h"
#include"heap.h"
#include"UFSets.h"
#include"MSTree.h"
#include"HuffmanTree.h"
#include"Graph.h"
#include"GraphLink.h"
#include"Graphmtx.h"
#include"Graphmtx2.h"
int HuffmanArray[50];
void print_Menu() {
	std::cout << "请按下方各数据结构的序号，输入一个数字表示要使用的数据结构" << std::endl;
	std::cout << "************************\n"
		      << "*  1 顺序表            *\n"
		      << "*  2 链表实现的表      *\n"
		      << "*  3 双向线性表        *\n"
		      << "*  4 栈                *\n"
		      << "*  5 基于数组的队列    *\n"
		      << "*  6 链表实现的队列    *\n"
		      << "*  7 二叉树            *\n"
		      << "*  8 二叉搜索树        *\n"
		      << "*  9 哈夫曼树          *\n"
		      << "* 10 图               *\n"
		      << "************************\n";
}

void Menu() {
	while (true) {
		print_Menu();
		int n;
		int len;
		std::cin >> n;
		switch (n)
		{
		case 1: {
			std::cout << "线性表" << std::endl;
			SeqList<int> mylist(defaultSize);
			Menu1<int>(mylist);
			break;
		}
		case 2: {
			std::cout << "链表实现的线性表" << std::endl;
			MyList<int> mylist;
			Menu2<int>(mylist);
			break;
		}
		case 3: {
			std::cout << "双向线性表" << std::endl;
			DblList<int> mylist(-1);
			Menu3<int>(mylist);
			break;
		}
		case 4: {
			std::cout << "栈" << std::endl;
			SeqStack<int> mystack(10);
			Menu4<int>(mystack);
			break;
		}
		case 5: {
			std::cout << "队列" << std::endl;
			SeqQueue<int> myQueue(50);
			Menu5<int>(myQueue);
			break;
		}
		case 6: {
			std::cout << "链表实现的队列" << std::endl;
			LinkedQueue<int> myQueue;
			Menu6<int>(myQueue);
			break;
		}
		case 7: {
			std::cout << "二叉树" << std::endl;
			BinaryTree<int> mytree;
			Menu7<int>(mytree);
			break;
		}
		case 8: {
			std::cout << "二叉搜索树" << std::endl;
			BST<int, int> myBinarySearchTree = BST<int, int>();
			Menu8(myBinarySearchTree);
			break;
		}
		case 9: {
			std::cout << "请输入哈夫曼树带权结点的个数: ";
			std::cin >> len;
			std::cout << "请依次输入" << len << "个结点的权值" << std::endl;
			for (int i = 0; i < len; i++) {
				std::cin >> HuffmanArray[i];
			}
			std::cout << "生成的哈夫曼树为" << std::endl;
			CreateHuffmanTree(HuffmanArray, len);
			std::cout << std::endl;
			break;
		}
		case 10: {
			std::cout << "图" << std::endl;
			Graphmtx<int, int> myGraph = Graphmtx<int, int>(50);
			Menu9(myGraph);
			break;
		}
		default:
			std::cout << "洛:结束了" << std::endl;
			return ;
		}
	}
}

using namespace std;
int main()
{
	Menu();
	std::cout << "Hello world" << std::endl;
	return 0;
}
