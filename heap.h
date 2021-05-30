// ��
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
		delete[]heap;  //������
	}
	bool Insert(const E& x);
	bool RemoveMin(E& x);
	bool IsEmpty()const {  //�ж϶��Ƿ�Ϊ��
		return currentSize == 0 ? true : false;  //�ж�currentSize�Ƿ�Ϊ0
	}
	bool IsFull()const {   //�ж϶��Ƿ���
		return currentSize == maxHeapSize ? true : false;
	}
	void MakeEmpty() {
		currentSize = 0;  //�ÿն�
	}
	void OutputHeap() {   //�����
		if (this->IsEmpty()) {
			std::cout << "��Ϊ��" << std::endl;
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
	E* heap;      //������
	int currentSize;   //��С�ѵ�ǰԪ�ظ���
	int maxHeapSize;  //��С����������Ԫ�ظ���
	void siftDown(int start, int m);
	void siftUp(int start);
};
template<class E>
MinHeap<E>::MinHeap(int sz) {
	this->maxHeapSize = (DefaultSize1 < sz ? sz : DefaultSize1);  //���캯��
	this->heap = new E[maxHeapSize];
	currentSize = 0;  // ��ǰ����Ϊ0
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
	}                                           //������󣬽�������
}
// ����Ҫ����������
template<class E>
void MinHeap<E>::siftDown(int start, int m) {  //���µ���Ϊ��С�ѵķ�ʽ1���ֱ�����Ů�Ƚϴ�С���ݹ�ʵ��(����ʵ��)��ǰ����������Ů��Ϊ��С��
	int i = start;
	int j = 2 * i + 1;  //jΪi������Ůλ��
	E temp = heap[i];
	while (j <= m) {   //����Ƿ����λ��
		if (j<m&&heap[j]>heap[j + 1]) //��jָ������Ů�е�С��
			j++;
		if (temp <= heap[j])  //С��������
			break;
		else {
			heap[i] = heap[j]; //С�����ƣ�i,j�ı䣬��������Ů��
			i = j;
			j = 2 * j + 1;  //i,j�任
		}
	}
	heap[i] = temp;//��ֵ
}
template<class E>
void MinHeap<E>::siftUp(int start) {  //���¶���
	int j = start;
	int	i = (j - 1) / 2;  //iΪj�ĸ��ڵ�
	E temp = heap[j];  //�ӽڵ�
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
	}                               //�ж��Ƿ�����
	heap[currentSize] = x; //δ��������
	siftUp(currentSize);  //���µ���Ϊ��С��
	currentSize++;
	return true;
}
template<class E>
bool MinHeap<E>::RemoveMin(E& x) {
	if (!currentSize) {
		std::cout << "Heap Empty" << std::endl;
		return false;
	}
	x = heap[0];     //���ض�����С��Ԫ��
	heap[0] = heap[currentSize - 1];  //ǡ�ý����Ԫ�ط���heap[0]
	currentSize--;    //���ȼ�1
	siftDown(0, currentSize - 1);  //���µ���Ϊ��С��
	return true;
}