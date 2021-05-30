#pragma once
// 图的基类
#include<iostream>
#include<queue>
const int DefaultSize22 = 30;
template<class T, class E>
class Graph {
protected:
	int maxVertices;//图中最大顶点数
	int numEdges; //当前边数
	int numVertices; //当前顶点数
	 //给出顶点verter在图中的位置
public:
	Graph(int sz = DefaultSize22) {
		maxVertices = sz;
	}
	//~Graph();
	bool GraphEmpty() const {
		return (numEdges == 0 ? true : false); //无边即为空
	}
	bool GraphFull() const {
		if (numVertices == maxVertices || numEdges == maxVertices * (maxVertices - 1) / 2)
			return true;
		return false;
	}
	virtual int NumberOfVertices() {   //返回当前顶点数
		std::cout << "为啥是这里啊" << std::endl;
		return numVertices;
	}
	virtual int NumberOfEdges() {
		return numEdges;
	}
	virtual void Output() {
		std::cout << "不是吧" << std::endl;
	}
	virtual T getValue(int i) {
		return 0;

	};  //取顶点i的值，不合理返回0
	virtual T getWeight(int v1, int v2) {
		return 0;
	}; //取边(v1,v2）上的权值
	virtual int getFirstNeighbor(int v) {
		return 0;
	}; //取顶点v的第一个邻接顶点
	virtual int getNextNeighbor(int v, int w) {
		//std::cout << "不会是这里吧？？？" << std::endl;
		return 0;
	}//取邻接顶点w的下一个邻接顶点
	virtual bool insertVertex(const T& vertex) {
		std::cout << "不是吧" << std::endl;
		return true;
	}; //插入一个顶点vertex
	virtual bool insertEdge(int v1, int v2, E cost) {
		std::cout << "父类的插入边" << std::endl;
		return true;
	}//插入边(v1,v2) 权为cost
	virtual bool removeVertex(int v) {
		return true;
	}//删去顶点v和所有与相关联边
	virtual bool removeEdge(int v1, int v2) {
		return true;
	}//删去边（v1,v2）
	virtual int getVertexPos(T vertex) {
		return -1;
	}
};
template<class T, class E>
void DFS(Graph<T, E>& G, const T& v) {    //v为顶点的信息
	// 从顶点v开始，对图G进行深度优先遍历的主过程
	int  loc, n = G.NumberOfVertices();//取图中顶点个数
	bool* visited = new bool[n]; //创建辅助数组，标记数组
	for (int i = 0; i < n; i++)
		visited[i] = 0; //初始化，全为false
	std::cout << std::endl;
	loc = G.getVertexPos(v);  //根据顶点信息确定顶点的下标
	DFS(G, loc, visited);
	delete[] visited;
}
template<class T, class E>
void DFS(Graph<T, E>& G, int v, bool viisted[]) {  //v为顶点的下标
	// 从顶点位置v出发，以深度优先的次序访问所以可读入的尚未访问过的顶点
	//std::cout << G.getValue(v) << " ";  //访问到顶点，用名字表示
	std::cout << v << " ";
	viisted[v] = true;  //输出完置为true
	int w = G.getFirstNeighbor(v);
	while (w != -1) {
		if (viisted[w] == false) {
			DFS(G, w, viisted);
		}
		w = G.getNextNeighbor(v, w);//取w的下一个结点
	}
}
template<class T, class E>
void BFS(Graph<T, E>& G, const T& v) {
	//从顶点v出发，以广度优先的次序横向搜索图，算法中要使用到队列（广搜特点）
	int w, n = G.NumberOfVertices();  //取顶点的个数为n
	bool* visited = new bool[n];
	for (int i = 0; i < n; ++i)
		visited[i] = false;  //初始化矩阵
	int loc = G.getVertexPos(v); //获取顶点的下标
	//std::cout << G.getValue(loc) << " ";
	std::cout << loc << " ";
	visited[loc] = true;
	std::queue<int> Q;
	Q.push(loc);//入栈
	while (!Q.empty()) {
		loc = Q.front();
		Q.pop();//取完队头，队头出队
		w = G.getFirstNeighbor(loc);
		while (w != -1) {
			if (visited[w] == false) {
				std::cout << w << " ";
				visited[w] = true;
				Q.push(w);  //入队
			}
			w = G.getNextNeighbor(loc, w); //找w的下一个领结点
		}
	}
	delete[] visited;
}
// 利用深度优先搜索建立求非连通图的连通分量的求法
template<class T, class E>
void Components(Graph<T, E>& G) {
	//通过DFS，找出无向图的所有连通分量
	int n = G.NumberOfVertices();
	bool* visited = new bool[n];
	for (int i = 0; i < n; ++i)
		visited[i] = false;
	for (int i = 0; i < n; ++i) {
		if (visited[i] == false) {
			DFS(G, i, visited);
		}
		std::cout << std::endl;
	}
	delete[] visited;
}
void print_menu9() //菜单函数
{
	std::cout << "1------向树中插入一个顶点\n"
		<< "2------边插入\n"
		<< "3------顶点删除\n"
		<< "4------边删除\n"
		<< "5------获得顶点的个数\n"
		<< "6------获得边的个数\n"
		<< "7------获取顶点的序号\n"
		<< "8------获取图中所有的连通分量\n"
		<< "9------输出图\n"
		<< " 10-----退出\n"
		<< "请输入您要进行的操作（1-10）: ";
}