#pragma once
// �ڽӱ��ʾ��ͼ  ע�ⶥ���Ǵ�0��ʼ��
#include"Graph.h"
template<class T, class E>
struct Edge {   //ͬһ����������ĸ�����
	int dest; //�ߵ���һ�����λ��
	int weight; //�ߵ�Ȩ��
	Edge<T, E>* next;  //��һ������ָ��
	Edge() {

	};
	Edge(int num, E weight1) :dest(num), weight(weight1), next(nullptr) {

	};
	bool operator !=(Edge<T, E>& R) const {  //�жϱ߲����
		return (dest != R.dest) ? true : false;
	}
};
template<class T, class E>
struct Vertex { //����Ķ���	
	T data;   //���������(��Ϣ��������ֵ��ʾ)
	Edge<T, E>* adj; //������ͷָ��
};
template<class T, class E>
class GraphLink :public Graph<T, E> {
protected:
	Vertex<T, E>* NodeTable; //����� //���������ͷ���
	int maxVertices;//ͼ����󶥵���
	int numEdges; //��ǰ����
	int numVertices; //��ǰ������
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
	int NumberOfVertices() {   //���ص�ǰ������
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
GraphLink<T, E>::GraphLink(int sz) {  //����һ���յ��ڽӱ�
	maxVertices = sz;
	numEdges = 0;
	numVertices = 0;
	NodeTable = new Vertex<T, E>[maxVertices]; //�������������
	for (int i = 0; i < maxVertices; ++i) {
		NodeTable[i].adj = nullptr;
	}
}
template<class T, class E>
GraphLink<T, E>::~GraphLink() {
	//����������ɾ��һ���ڽӱ�
	for (int i = 0; i < maxVertices; ++i) {
		Edge<T, E>* p = NodeTable[i].adj;   //�ҵ����Ӧ�������׽��
		while (p != nullptr)
		{
			NodeTable[i].adj = p->next;
			delete p;  //�ɹ�ɾ����һ����
			p = NodeTable[i].adj;
		}
	}
	delete[]NodeTable;
}
// ������Ϻ�����ʵ�ֶ��Ƕ������ĳ������������ϲ���
template<class T, class E>
int GraphLink<T, E>::getFirstNeighbor(int v) {
	if (v != -1) {
		Edge<T, E>* p = NodeTable[v].adj;  //�������ͷ���
		if (p != nullptr) {
			return p->dest;  //�ҵ�Ŀ���յ�
		}
	}
	return -1;
}
template<class T, class E>
int GraphLink<T, E>::getNextNeighbor(int v, int w) {
	if (v != -1) {
		Edge<T, E>* p = NodeTable[v].adj;
		while (p != nullptr&&p->dest != w) {  //�����������ˣ�Ѱ���ڽӶ���w
			p = p->next;
		}
		if (p != nullptr&&p->next != nullptr)
			return p->next->dest;//����w����һ������
	}
	return -1;
}
template<class T, class E>
E GraphLink<T, E>::getWeight(int v1, int v2) {
	//�������رߣ�v1,v2)�ϵ�Ȩֵ�����ñ߲���ͼ�У���������Ȩֵ0
	if (v1 != -1 && v2 != -1) {
		Edge<T, E>* p = NodeTable[v1].adj;  //��ñ������ͷ���
		while (p != nullptr&&p->dest != v2) {
			p = p->next;  //Ѱ�ұ��յ�
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
	//��ͼ��ɾ��һ��ָ������v��v�Ƕ���ţ�ɾ���ɹ�����True��ʧ�ܷ���false
	if (numVertices == 1 || v < 0 || v >= numVertices)
		return false;
	Edge<T, E> *p, *s, *t;
	int  k;
	while (NodeTable[v].adj != nullptr) {   //ɾ����v���������е����н��
		p = NodeTable[v].adj;
		k = p->dest;  //ȡ�ڽӶ���k
		s = NodeTable[k].adj; //�ҶԳƴ�ţ��ڽӶ��㣩�ı�ͷ���
		t = nullptr;
		while (s != nullptr&&s->dest != v) {   //ɾ���Գƴ�ŵı�
			t = s;        //����ǰ��
			s = s->next;  //�ҵ���Ӧ�ı�
		}
		if (s != nullptr) {
			if (t == nullptr)                     //tΪ�գ�˵���߸պ��ǵ�һ��
				NodeTable[k].adj = s->next;
			else
				t->next = s->next;  //�߲��ǵ�һ��
			delete s;
		}
		NodeTable[v].adj = p->next;
		delete p;
		numEdges--;  //������ı���-1
	}
	numVertices--;  //������-1
	NodeTable[v].data = NodeTable[numVertices].data;   //��乤������ԭ�����һ��������䱻ɾ���Ķ���
	p = NodeTable[v].adj = NodeTable[numVertices].adj; //���㽻��
	while (p != nullptr) {
		s = NodeTable[p->dest].adj; //�ԳƵ�ı�ҲҪ�γ�
		while (s != nullptr) {
			if (s->dest == numVertices) {
				s->dest = v;  //ԭ��ָ��numVertices�ģ����ڶ�Ҫָ��v��
				break;
			}
			else
				s = s->next;//û��ָ�򣬼�����
		}
	}
	return true;
}
template<class T, class E>
bool GraphLink<T, E>::insertEdge(int v1, int v2, E weight1) {
	// �ڴ�Ȩͼ�в���һ����(v1,v2),���˱ߴ��ڻ������������false
	if (v1 > -1 && v1<numVertices&&v2>-1 && v2 < numVertices) {
		Edge<T, E>*q, *p = NodeTable[v1].adj;   //ȥv1�ı���ͷ���
		while (p != nullptr&&p->dest != v2)
			p = p->next;
		if (p != nullptr)
			return false;  //�ҵ��˱ߣ����ٲ���
		p = new Edge<T, E>;
		q = new Edge<T, E>; //�����µı����ڵ�
		p->dest = v2;
		p->weight = weight1;
		p->next = NodeTable[v1].adj; //����v1������,ͷ����
		NodeTable[v1].adj = p;
		q->dest = v1;
		q->weight = weight1;
		q->next = NodeTable[v2].adj;  //����v2������
		NodeTable[v2].adj = q;
		numEdges++;  //�ߵ�����+1
		return true;
	}
	std::cout << "�����ʧ����" << std::endl;
	return false;
}
template<class T, class E>
bool GraphLink<T, E>::removeEdge(int v1, int v2) {
	//��ͼ��ɾ����һ���ߣ�v1,v2��
	if (v1 != -1 && v2 != -1) {
		Edge<T, E>* p = NodeTable[v1].adj, *q = nullptr, *s = p;
		while (p != nullptr&&p->dest != v2)
		{
			q = p;  //qΪǰ�����
			p = p->next;
		}
		if (p != nullptr) {
			if (p == s)
				NodeTable[v1].adj = p->next;  //�պ�Ϊ��һ����
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