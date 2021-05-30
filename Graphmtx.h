#pragma once
// �ڽӾ���(��ά����)��ʾ��ͼ���ඨ��
#include"Graph.h"
#include<iomanip>
template<class T, class E>
class Graphmtx :public Graph<T, E> {
protected:
	T* VerticesList; //�����
	E* *Edge; //�ڽӾ��� ��ά���飬�ö�άָ�� ����ָ��
	int maxVertices;//ͼ����󶥵���
	int numEdges; //��ǰ����
	int numVertices; //��ǰ������
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
		return i >= 0 && i < numVertices ? VerticesList[i] : -1;  //ע��i�ĺϷ��Լ��  ���ض������Ϣ
	}
	E getWeight(int v1, int v2) {
		return v1 != -1 && v2 != -1 ? Edge[v1][v2] : 0;
	}
	int getFirstNeighbor(int v);  //ȡ����v�ĵ�һ���ڽӶ���
	int getNextNeighbor(int v, int w); //ȡv���ڽӶ���w����һ���ڽӶ���
	bool insertVertex(const T& vertex); //���붥��vertex
	bool insertEdge(int v1, int v2, E cost); //����ߣ�v1,v2��ȨֵΪcost
	bool removeVertex(int v); //ɾȥ����v����������������ı�
	bool removeEdge(int v1, int v2);//��ͼ��ɾȥ��(v1,v2��
	int getVertexPos(T vertex) {
		for (int i = 0; i < numVertices; ++i)
			if (VerticesList[i] == vertex)  //vertexΪ�������Ϣ
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
	int NumberOfVertices() {   //���ص�ǰ������
		return numVertices;
	}
	int NumberOfEdges() {
		return numEdges;
	}
};
template<class T, class E>
Graphmtx<T, E>::Graphmtx(int sz) :Graph<T, E>(sz) {
	//���캯��
	maxVertices = sz;
	numEdges = 0;
	numVertices = 0;
	VerticesList = new T[maxVertices];  //�������������
	Edge = (E* *) new E*[maxVertices];  //�����ڽӾ�������
	for (int i = 0; i < maxVertices; ++i) {   //�ڽӾ����ʼ��
		Edge[i] = new E[maxVertices];
	}
	for (int i = 0; i < maxVertices; ++i)
		for (int j = 0; j < maxVertices; ++j)
			Edge[i][j] = (i == j) ? 0 : maxWeight;
}
template<class T, class E>
int Graphmtx<T, E>::getFirstNeighbor(int v) {
	if (v != -1) {  //v>0��
		for (int col = 0; col < numVertices; ++col) {
			if (Edge[v][col] > 0 && Edge[v][col] < maxWeight)
				return col;
		}
	}
	return -1;   //�Ҳ�������
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
	if (numVertices == maxVertices)   //�Ϸ��Լ��
		return false;
	VerticesList[numVertices++] = vertex;  //����ɹ�   //vertexΪ�������Ϣ
	return true;
}
template<class T, class E>
bool Graphmtx<T, E>::removeVertex(int v) {
	//ɾȥ����v����������������ı�
	if (v < 0 || v >= numVertices)  //���㲻��ͼ�У�ɾ��ʧ��
		return false;
	if (numVertices == 1)   //ֻʣ��һ�����㣬ɾ��ʧ��
		return false;
	VerticesList[v] = VerticesList[numVertices - 1];
	for (int i = 0; i < numVertices; ++i) {
		if (Edge[v][i] < 0 && Edge[v][i] < maxWeight) {
			numEdges--;
		}  //���ߴ���
	}
	for (int i = 0; i < numVertices; ++i) {
		Edge[i][v] = Edge[i][numVertices - 1];
	}    //�����һ������v��
	numVertices--;   //��������1 �ܹؼ�
	for (int i = 0; i < numVertices; ++i) {
		Edge[v][i] = Edge[numVertices][i]; //ע���ʱ��numVertices,����Ҫ��1
	} //�����һ������v��
	return true;
}
template<class T, class E>
bool Graphmtx<T, E>::insertEdge(int v1, int v2, E cost) {
	if (v1 > -1 && v1<numVertices&&v2>-1 && v2 < numVertices&&Edge[v1][v2] == maxWeight) {  //�Ϸ��Լ��
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
	//ͨ������������in����n��������Ϣ��e������ߵ���Ϣ�������ĸ��ڽӾ����ʾ��ͼG�������ʼ�������Ѿ��ڹ��캯�������
	int n, m;
	T e1;
	T e2;
	E weight;
	std::cout << "�����붥��ĸ����ͱߵ�������";
	in >> n >> m;  //����n�������m����
	std::cout << "����������" << n << "���������Ϣ";
	for (int i = 0; i < n; ++i) {
		in >> e1;
		G.insertVertex(e1);   //n��������һ����
	}
	int j = 0;
	while (j < m) {
		std::cout << "�밴�󶥵���Ϣ���Ҷ�����Ϣ��Ϣ��Ȩ��һ�������" << j + 1 << "���ߵ���Ϣ: ";
		in >> e1 >> e2 >> weight;
		int i = G.getVertexPos(e1);
		int k = G.getVertexPos(e2);
		if (i == -1 || k == -1) {
			std::cout << "�����˵���Ϣ������������" << std::endl;
		}
		G.insertEdge(i, k, weight);
		j++;
	}
	return in;
}
template<class T, class E>
std::ostream& operator <<(std::ostream& out, Graphmtx<T, E>& G) {
	//���ͼ�е����ж���ͱߵ���Ϣ
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

