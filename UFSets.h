#pragma once   //���鼯
#include<iostream>
const int DefaultSize = 100;
class UFSets {
public:
	UFSets(int sz = DefaultSize);
	~UFSets()
	{
		delete[]parent;
	}
	UFSets& operator=(UFSets& R);     //���ϸ�ֵ
	void Union(int Root1, int Root2);  //�����Ӽ��ϲ���
	int Find(int x);  //��Ѱ����x�ĸ�
	void WeightedUnion(int Root1, int Root2); //��Ȩ�ĺϲ��㷨
	void OutPut() {
		for (int i = 0; i < size; ++i) {
			std::cout << i << " " << parent[i] << std::endl;
		}
		std::cout << std::endl;
	}
	int Find_pre(int x) {    //·��ѹ���㷨
		if (parent[x] == x)
			return x;
		return parent[x] = Find_pre(parent[x]);
	}
private:
	int *parent;
	int size;
};
UFSets::UFSets(int sz) {
	size = sz;
	parent = new int[size];
	//std::cout << "������" << size << "������Ԫ��:" << std::endl;
	for (int i = 0; i < size; ++i) {
		parent[i] = -1;               //ÿ���Գɵ�Ԫ�ؼ���
	}
}
int UFSets::Find(int x) {
	while (parent[x] >= 0)
		x = parent[x];          //ѭ��Ѱ�ң�ֱ���ҵ���ָ����Ϊ��ֵ��  ��Ϊ��
	return x;
}
void UFSets::Union(int Root1, int Root2) {
	// ���������ཻ���ϵĲ���Ҫ��Root1��Root2�ǲ�ͬ�ģ��ұ�ʾ���Ӽ��ϵ�����
	parent[Root1] += parent[Root2];
	parent[Root2] = Root1;
}
void UFSets::WeightedUnion(int Root1, int Root2) {
	int r1 = Find(Root1);
	int r2 = Find(Root2);
	int temp;
	if (r1 < r2) {
		temp = parent[r1] + parent[r2];
		if (parent[r1] < parent[r2]) {
			parent[r1] = r2;
			parent[r2] = temp;
		}
		else {
			parent[r2] = r1;
			parent[r1] = temp;
		}
	}
}
