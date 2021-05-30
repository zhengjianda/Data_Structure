#pragma once   //并查集
#include<iostream>
const int DefaultSize = 100;
class UFSets {
public:
	UFSets(int sz = DefaultSize);
	~UFSets()
	{
		delete[]parent;
	}
	UFSets& operator=(UFSets& R);     //集合赋值
	void Union(int Root1, int Root2);  //两个子集合并集
	int Find(int x);  //搜寻集合x的根
	void WeightedUnion(int Root1, int Root2); //加权的合并算法
	void OutPut() {
		for (int i = 0; i < size; ++i) {
			std::cout << i << " " << parent[i] << std::endl;
		}
		std::cout << std::endl;
	}
	int Find_pre(int x) {    //路径压缩算法
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
	//std::cout << "请输入" << size << "个集合元素:" << std::endl;
	for (int i = 0; i < size; ++i) {
		parent[i] = -1;               //每个自成单元素集合
	}
}
int UFSets::Find(int x) {
	while (parent[x] >= 0)
		x = parent[x];          //循环寻找，直到找到父指针域为负值的  即为根
	return x;
}
void UFSets::Union(int Root1, int Root2) {
	// 求两个不相交集合的并，要求Root1和Root2是不同的，且表示这子集合的名字
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