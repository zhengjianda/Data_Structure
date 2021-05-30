#pragma once
// 邻接表表示的图  注意顶点是从0开始的
#include"Graph.h"
template<class T, class E>
struct Edge {   //同一个顶点关联的各条边
	int dest; //边的另一顶点的位置
	int weight; //边的权重
	Edge<T, E>* next;  //下一条边链指针
	Edge() {

	};
	Edge(int num, E weight1) :dest(num), weight(weight1), next(nullptr) {

	};
	bool operator !=(Edge<T, E>& R) const {  //判断边不相等
		return (dest != R.dest) ? true : false;
	}
};
template<class T, class E>
struct Vertex { //顶点的定义	
	T data;   //顶点的名字(信息，可用数值表示)
	Edge<T, E>* adj; //边链表头指针
};
template<class T, class E>
class GraphLink :public Graph<T, E> {
protected:
	Vertex<T, E>* NodeTable; //顶点表 //各边链表的头结点
	int maxVertices;//图中最大顶点数
	int numEdges; //当前边数
	int numVertices; //当前顶点数
	int getVertexPos(const T vertex) {
		for (int i = 0; i < numVertices; ++i) {
			if ((NodeTable[i].data) == vertex)
				return i;
		}
		return -1;
	}
public:
	GraphLink(int sz = DefaultSize);
	~GraphLink();
	T getValue(int i) {
		return (i > 0 && i < numVertices) ? NodeTable[i].data : 0;
	}
	E getWeight(int v1, int v2);
	int NumberOfVertices() {   //返回当前顶点数
		return this->numVertices;
	}
	int NumberOfEdges() {
		return numEdges;
	}
	bool insertVertex(const T& vertex);
	bool removeVertex(int v);
	bool insertEdge(int v1, int v2, E cost);
	bool removeEdge(int v1, int v2);
	int getFirstNeighbor(int v);
	int getNextNeighbor(int v, int w);
	void Output() {
		Edge<T, E>* q = nullptr;
		for (int i = 0; i < numVertices; ++i) {
			q = NodeTable[i].adj;
			while (q != nullptr) {
				std::cout << "(" << i << "," << q->dest << "," << q->weight << ")" << "   ";
				q = q->next;
			}
			std::cout << std::endl;
		}
	}
};
template<class T, class E>
GraphLink<T, E>::GraphLink(int sz) {  //建立一个空的邻接表
	maxVertices = sz;
	numEdges = 0;
	numVertices = 0;
	NodeTable = new Vertex<T, E>[maxVertices]; //创建顶点表数组
	for (int i = 0; i < maxVertices; ++i) {
		NodeTable[i].adj = nullptr;
	}
}
template<class T, class E>
GraphLink<T, E>::~GraphLink() {
	//析构函数，删除一个邻接表
	for (int i = 0; i < maxVertices; ++i) {
		Edge<T, E>* p = NodeTable[i].adj;   //找到其对应边链的首结点
		while (p != nullptr)
		{
			NodeTable[i].adj = p->next;
			delete p;  //成功删除了一条边
			p = NodeTable[i].adj;
		}
	}
	delete[]NodeTable;
}
// 顶点表上函数的实现都是顶点表与某个边链表的联合操作
template<class T, class E>
int GraphLink<T, E>::getFirstNeighbor(int v) {
	if (v != -1) {
		Edge<T, E>* p = NodeTable[v].adj;  //边链表的头结点
		if (p != nullptr) {
			return p->dest;  //找到目标终点
		}
	}
	return -1;
}
template<class T, class E>
int GraphLink<T, E>::getNextNeighbor(int v, int w) {
	if (v != -1) {
		Edge<T, E>* p = NodeTable[v].adj;
		while (p != nullptr&&p->dest != w) {  //搜索就完事了，寻找邻接顶点w
			p = p->next;
		}
		if (p != nullptr&&p->next != nullptr)
			return p->next->dest;//返回w的下一个顶点
	}
	return -1;
}
template<class T, class E>
E GraphLink<T, E>::getWeight(int v1, int v2) {
	//函数返回边（v1,v2)上的权值，若该边不在图中，则函数返回权值0
	if (v1 != -1 && v2 != -1) {
		Edge<T, E>* p = NodeTable[v1].adj;  //获得边链表的头结点
		while (p != nullptr&&p->dest != v2) {
			p = p->next;  //寻找边终点
		}
		if (p != nullptr) {
			return p->weight;
		}
	}
	return 0;
}
template<class T, class E>
bool GraphLink<T, E>::insertVertex(const T& vertex) {
	if (numVertices == maxVertices)
		return false;
	NodeTable[numVertices++].data = vertex;
	return true;
}
template<class T, class E>
bool GraphLink<T, E>::removeVertex(int v) {
	//在图中删除一个指定顶点v，v是顶点号，删除成功返回True，失败返回false
	if (numVertices == 1 || v < 0 || v >= numVertices)
		return false;
	Edge<T, E> *p, *s, *t;
	int  k;
	while (NodeTable[v].adj != nullptr) {   //删除第v个边链表中的所有结点
		p = NodeTable[v].adj;
		k = p->dest;  //取邻接顶点k
		s = NodeTable[k].adj; //找对称存放（邻接顶点）的边头结点
		t = nullptr;
		while (s != nullptr&&s->dest != v) {   //删除对称存放的边
			t = s;        //保留前驱
			s = s->next;  //找到对应的边
		}
		if (s != nullptr) {
			if (t == nullptr)                     //t为空，说明边刚好是第一条
				NodeTable[k].adj = s->next;
			else
				t->next = s->next;  //边不是第一条
			delete s;
		}
		NodeTable[v].adj = p->next;
		delete p;
		numEdges--;  //相关联的边数-1
	}
	numVertices--;  //顶点数-1
	NodeTable[v].data = NodeTable[numVertices].data;   //填充工作，用原来最后一个顶点填充被删除的顶点
	p = NodeTable[v].adj = NodeTable[numVertices].adj; //顶点交接
	while (p != nullptr) {
		s = NodeTable[p->dest].adj; //对称点的边也要形成
		while (s != nullptr) {
			if (s->dest == numVertices) {
				s->dest = v;  //原来指向numVertices的，现在都要指向v了
				break;
			}
			else
				s = s->next;//没有指向，继续搜
		}
	}
	return true;
}
template<class T, class E>
bool GraphLink<T, E>::insertEdge(int v1, int v2, E weight1) {
	// 在带权图中插入一条边(v1,v2),若此边存在或参数不合理返回false
	if (v1 > -1 && v1<numVertices&&v2>-1 && v2 < numVertices) {
		Edge<T, E>*q, *p = NodeTable[v1].adj;   //去v1的边链头结点
		while (p != nullptr&&p->dest != v2)
			p = p->next;
		if (p != nullptr)
			return false;  //找到此边，不再插入
		p = new Edge<T, E>;
		q = new Edge<T, E>; //创建新的边链节点
		p->dest = v2;
		p->weight = weight1;
		p->next = NodeTable[v1].adj; //链入v1边链表,头插入
		NodeTable[v1].adj = p;
		q->dest = v1;
		q->weight = weight1;
		q->next = NodeTable[v2].adj;  //链入v2边链表
		NodeTable[v2].adj = q;
		numEdges++;  //边的数量+1
		return true;
	}
	std::cout << "插入边失败了" << std::endl;
	return false;
}
template<class T, class E>
bool GraphLink<T, E>::removeEdge(int v1, int v2) {
	//在图中删除掉一条边（v1,v2）
	if (v1 != -1 && v2 != -1) {
		Edge<T, E>* p = NodeTable[v1].adj, *q = nullptr, *s = p;
		while (p != nullptr&&p->dest != v2)
		{
			q = p;  //q为前驱结点
			p = p->next;
		}
		if (p != nullptr) {
			if (p == s)
				NodeTable[v1].adj = p->next;  //刚好为第一条边
			else
				q->next = p->next;
			delete p;
		}
		else
			return false;
		p = NodeTable[v2].adj;
		q = nullptr;
		s = p;
		while (p->dest != v1) {
			q = p;
			p = p->next;
		}
		if (p == s)
			NodeTable[v2].adj = p->next;
		else
			q->next = p->next;
		delete p;
		return true;
	}
	return false;
}