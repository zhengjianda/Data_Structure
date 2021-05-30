#pragma once
// 邻接矩阵(二维数组)表示的图的类定义
#include"Graph.h"
#include<iomanip>
template<class T, class E>
class Graphmtx :public Graph<T, E> {
protected:
	T* VerticesList; //顶点表
	E* *Edge; //邻接矩阵 二维数组，用二维指针 二级指针
	int maxVertices;//图中最大顶点数
	int numEdges; //当前边数
	int numVertices; //当前顶点数
public:
	const E maxWeight = 999999999;
	template<class E, class K> friend std::istream& operator >>(std::istream& in, Graphmtx<T, E>& G);
	template<class E, class K> friend std::ostream& operator <<(std::ostream& out, Graphmtx<T, E>& G);
	Graphmtx(int sz = DefaultSize);
	~Graphmtx()
	{
		delete[]VerticesList;
		delete[]Edge;
	}
	T getValue(int i) {
		return i >= 0 && i < numVertices ? VerticesList[i] : -1;  //注意i的合法性检查  返回顶点的信息
	}
	E getWeight(int v1, int v2) {
		return v1 != -1 && v2 != -1 ? Edge[v1][v2] : 0;
	}
	int getFirstNeighbor(int v);  //取顶点v的第一个邻接顶点
	int getNextNeighbor(int v, int w); //取v的邻接顶点w的下一个邻接顶点
	bool insertVertex(const T& vertex); //插入顶点vertex
	bool insertEdge(int v1, int v2, E cost); //插入边（v1,v2）权值为cost
	bool removeVertex(int v); //删去顶点v和所有与它相关联的边
	bool removeEdge(int v1, int v2);//在图中删去边(v1,v2）
	int getVertexPos(T vertex) {
		for (int i = 0; i < numVertices; ++i)
			if (VerticesList[i] == vertex)  //vertex为顶点的信息
				return i;
		return -1;
	}
	void Output() {
		for (int i = 0; i < numVertices; i++) {
			for (int j = 0; j < numVertices; j++) {
				std::cout << std::setw(9) << Edge[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}
	int NumberOfVertices() {   //返回当前顶点数
		return numVertices;
	}
	int NumberOfEdges() {
		return numEdges;
	}
};
template<class T, class E>
Graphmtx<T, E>::Graphmtx(int sz) :Graph<T, E>(sz) {
	//构造函数
	maxVertices = sz;
	numEdges = 0;
	numVertices = 0;
	VerticesList = new T[maxVertices];  //创建顶点表数组
	Edge = (E* *) new E*[maxVertices];  //创建邻接矩阵数组
	for (int i = 0; i < maxVertices; ++i) {   //邻接矩阵初始化
		Edge[i] = new E[maxVertices];
	}
	for (int i = 0; i < maxVertices; ++i)
		for (int j = 0; j < maxVertices; ++j)
			Edge[i][j] = (i == j) ? 0 : maxWeight;
}
template<class T, class E>
int Graphmtx<T, E>::getFirstNeighbor(int v) {
	if (v != -1) {  //v>0？
		for (int col = 0; col < numVertices; ++col) {
			if (Edge[v][col] > 0 && Edge[v][col] < maxWeight)
				return col;
		}
	}
	return -1;   //找不到顶点
}
template<class T, class E>
int Graphmtx<T, E>::getNextNeighbor(int v, int w) {
	if (v != -1 && w != -1) {
		for (int col = w + 1; col < numVertices; ++col) {
			if (Edge[v][col] > 0 && Edge[v][col] < maxWeight) {
				return col;
			}
		}
	}
	return -1;
}
template<class T, class E>
bool Graphmtx<T, E>::insertVertex(const T& vertex) {
	if (numVertices == maxVertices)   //合法性检查
		return false;
	VerticesList[numVertices++] = vertex;  //插入成功   //vertex为顶点的信息
	return true;
}
template<class T, class E>
bool Graphmtx<T, E>::removeVertex(int v) {
	//删去顶点v和所有与它相关联的边
	if (v < 0 || v >= numVertices)  //顶点不在图中，删除失败
		return false;
	if (numVertices == 1)   //只剩下一个顶点，删除失败
		return false;
	VerticesList[v] = VerticesList[numVertices - 1];
	for (int i = 0; i < numVertices; ++i) {
		if (Edge[v][i] < 0 && Edge[v][i] < maxWeight) {
			numEdges--;
		}  //减边处理
	}
	for (int i = 0; i < numVertices; ++i) {
		Edge[i][v] = Edge[i][numVertices - 1];
	}    //用最后一列填充第v列
	numVertices--;   //顶点数减1 很关键
	for (int i = 0; i < numVertices; ++i) {
		Edge[v][i] = Edge[numVertices][i]; //注意此时是numVertices,不需要减1
	} //用最后一行填充第v行
	return true;
}
template<class T, class E>
bool Graphmtx<T, E>::insertEdge(int v1, int v2, E cost) {
	if (v1 > -1 && v1<numVertices&&v2>-1 && v2 < numVertices&&Edge[v1][v2] == maxWeight) {  //合法性检查
		Edge[v1][v2] = cost;
		numEdges++;
		return true;
	}
	return false;
}
template<class T, class E>
bool Graphmtx<T, E>::removeEdge(int v1, int v2) {
	if (v1 > -1 && v1<numVertices&&v2>-1 && v2 < numVertices&&Edge[v1][v2]>0 && Edge[v1][v2] < maxWeight) {
		Edge[v1][v2] = Edge[v2][v1] = maxWeight;
		numEdges--;
		return true;
	}
	return false;
}
template<class T, class E>
std::istream& operator >>(std::istream& in, Graphmtx<T, E>& G) {
	//通过输入流对象in输入n个顶点信息和e条无向边的信息建立用哪个邻接矩阵表示的图G，矩阵初始化工作已经在构造函数中完成
	int n, m;
	T e1;
	T e2;
	E weight;
	std::cout << "请输入顶点的个数和边的条数：";
	in >> n >> m;  //输入n个顶点和m条边
	std::cout << "请依次输入" << n << "个顶点的信息";
	for (int i = 0; i < n; ++i) {
		in >> e1;
		G.insertVertex(e1);   //n个顶点逐一插入
	}
	int j = 0;
	while (j < m) {
		std::cout << "请按左顶点信息，右顶点信息信息，权重一次输入第" << j + 1 << "条边的信息: ";
		in >> e1 >> e2 >> weight;
		int i = G.getVertexPos(e1);
		int k = G.getVertexPos(e2);
		if (i == -1 || k == -1) {
			std::cout << "边两端点信息有误，重新输入" << std::endl;
		}
		G.insertEdge(i, k, weight);
		j++;
	}
	return in;
}
template<class T, class E>
std::ostream& operator <<(std::ostream& out, Graphmtx<T, E>& G) {
	//输出图中的所有顶点和边的信息
	int i, j, n, m;
	T e1, e2;
	E w;
	n = G.NumberOfVertices();
	m = G.NumberOfEdges();
	out << n << "," << m << std::endl;
	for (i = 0; i < n; i++) {
		for (j = i + 1; j < n; j++) {
			w = G.getWeight(i, j);
			if (w > 0 && w < G.maxWeight) {
				e1 = G.getValue(i);
				e2 = G.getValue(j);
				out << "(" << e1 << "," << e2 << "," << w << ")" << std::endl;
			}
		}
	}
	return out;
}

