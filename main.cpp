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
	std::cout << "�밴�·������ݽṹ����ţ�����һ�����ֱ�ʾҪʹ�õ����ݽṹ" << std::endl;
	std::cout << "************************\n"
		      << "*  1 ˳���            *\n"
		      << "*  2 ����ʵ�ֵı�      *\n"
		      << "*  3 ˫�����Ա�        *\n"
		      << "*  4 ջ                *\n"
		      << "*  5 ��������Ķ���    *\n"
		      << "*  6 ����ʵ�ֵĶ���    *\n"
		      << "*  7 ������            *\n"
		      << "*  8 ����������        *\n"
		      << "*  9 ��������          *\n"
		      << "* 10 ͼ               *\n"
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
			std::cout << "���Ա�" << std::endl;
			SeqList<int> mylist(defaultSize);
			Menu1<int>(mylist);
			break;
		}
		case 2: {
			std::cout << "����ʵ�ֵ����Ա�" << std::endl;
			MyList<int> mylist;
			Menu2<int>(mylist);
			break;
		}
		case 3: {
			std::cout << "˫�����Ա�" << std::endl;
			DblList<int> mylist(-1);
			Menu3<int>(mylist);
			break;
		}
		case 4: {
			std::cout << "ջ" << std::endl;
			SeqStack<int> mystack(10);
			Menu4<int>(mystack);
			break;
		}
		case 5: {
			std::cout << "����" << std::endl;
			SeqQueue<int> myQueue(50);
			Menu5<int>(myQueue);
			break;
		}
		case 6: {
			std::cout << "����ʵ�ֵĶ���" << std::endl;
			LinkedQueue<int> myQueue;
			Menu6<int>(myQueue);
			break;
		}
		case 7: {
			std::cout << "������" << std::endl;
			BinaryTree<int> mytree;
			Menu7<int>(mytree);
			break;
		}
		case 8: {
			std::cout << "����������" << std::endl;
			BST<int, int> myBinarySearchTree = BST<int, int>();
			Menu8(myBinarySearchTree);
			break;
		}
		case 9: {
			std::cout << "���������������Ȩ���ĸ���: ";
			std::cin >> len;
			std::cout << "����������" << len << "������Ȩֵ" << std::endl;
			for (int i = 0; i < len; i++) {
				std::cin >> HuffmanArray[i];
			}
			std::cout << "���ɵĹ�������Ϊ" << std::endl;
			CreateHuffmanTree(HuffmanArray, len);
			std::cout << std::endl;
			break;
		}
		case 10: {
			std::cout << "ͼ" << std::endl;
			Graphmtx<int, int> myGraph = Graphmtx<int, int>(50);
			Menu9(myGraph);
			break;
		}
		default:
			std::cout << "��:������" << std::endl;
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
