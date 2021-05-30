// 堆
#pragma once
#pragma once
#include<iostream>
const int DefaultSize1 = 10;
template<class E>
class MinHeap {
public:
	MinHeap(int sz = DefaultSize1);
	MinHeap(E arr[], int n);
	~MinHeap()
	{
		delete[]heap;  //析构堆
	}
	bool Insert(const E& x);
	bool RemoveMin(E& x);
	bool IsEmpty()const {  //判断堆是否为空
		return currentSize == 0 ? true : false;  //判断currentSize是否为0
	}
	bool IsFull()const {   //判断堆是否满
		return currentSize == maxHeapSize ? true : false;
	}
	void MakeEmpty() {
		currentSize = 0;  //置空堆
	}
	void OutputHeap() {   //输出堆
		if (this->IsEmpty()) {
			std::cout << "堆为空" << std::endl;
			return;
		}
		else {
			for (int i = 0; i < currentSize; ++i) {
				std::cout << heap[i] << " ";
			}
			std::cout << std::endl;
			return;
		}
	}
private:
	E* heap;      //堆数组
	int currentSize;   //最小堆当前元素个数
	int maxHeapSize;  //最小堆最多允许的元素个数
	void siftDown(int start, int m);
	void siftUp(int start);
};
template<class E>
MinHeap<E>::MinHeap(int sz) {
	this->maxHeapSize = (DefaultSize1 < sz ? sz : DefaultSize1);  //构造函数
	this->heap = new E[maxHeapSize];
	currentSize = 0;  // 当前个数为0
}
template<class E>
MinHeap<E>::MinHeap(E arr[], int n) {
	this->maxHeapSize = (DefaultSize1 < n ? n : DefaultSize1);
	this->heap = new E[maxHeapSize];
	for (int i = 0; i < n; ++i)
	{
		heap[i] = arr[i];
	}
	currentSize = n;
	int currentPos = (currentSize - 2) / 2;
	while (currentPos >= 0) {
		siftDown(currentPos, currentSize - 1);
		currentPos--;
	}                                           //复制完后，进行排序
}
// 最重要的两个函数
template<class E>
void MinHeap<E>::siftDown(int start, int m) {  //重新调整为最小堆的方式1：分别与子女比较大小，递归实现(迭代实现)，前提是左右子女都为最小堆
	int i = start;
	int j = 2 * i + 1;  //j为i的左子女位置
	E temp = heap[i];
	while (j <= m) {   //检查是否到最后位置
		if (j<m&&heap[j]>heap[j + 1]) //让j指向两子女中的小者
			j++;
		if (temp <= heap[j])  //小则不做调整
			break;
		else {
			heap[i] = heap[j]; //小者上移，i,j改变，继续往子女搜
			i = j;
			j = 2 * j + 1;  //i,j变换
		}
	}
	heap[i] = temp;//赋值
}
template<class E>
void MinHeap<E>::siftUp(int start) {  //自下而上
	int j = start;
	int	i = (j - 1) / 2;  //i为j的父节点
	E temp = heap[j];  //子节点
	while (j > 0) {
		if (heap[i] <= temp)
			break;
		else {
			heap[j] = heap[i];
			j = i;
			i = (j - 1) / 2;
		}
	}
	heap[j] = temp;
}
template<class E>
bool MinHeap<E>::Insert(const E& x) {
	if (currentSize == maxHeapSize) {
		std::cerr << "Heap Full" << std::endl;
		return false;
	}                               //判断是否已满
	heap[currentSize] = x; //未满，插入
	siftUp(currentSize);  //重新调整为最小堆
	currentSize++;
	return true;
}
template<class E>
bool MinHeap<E>::RemoveMin(E& x) {
	if (!currentSize) {
		std::cout << "Heap Empty" << std::endl;
		return false;
	}
	x = heap[0];     //返回堆中最小的元素
	heap[0] = heap[currentSize - 1];  //恰好将最后元素放在heap[0]
	currentSize--;    //长度减1
	siftDown(0, currentSize - 1);  //重新调整为最小堆
	return true;
}