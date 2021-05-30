#pragma once
// ͼ�Ļ���
#include<iostream>
#include<queue>
const int DefaultSize22 = 30;
template<class T, class E>
class Graph {
protected:
	int maxVertices;//ͼ����󶥵���
	int numEdges; //��ǰ����
	int numVertices; //��ǰ������
	 //��������verter��ͼ�е�λ��
public:
	Graph(int sz = DefaultSize22) {
		maxVertices = sz;
	}
	//~Graph();
	bool GraphEmpty() const {
		return (numEdges == 0 ? true : false); //�ޱ߼�Ϊ��
	}
	bool GraphFull() const {
		if (numVertices == maxVertices || numEdges == maxVertices * (maxVertices - 1) / 2)
			return true;
		return false;
	}
	virtual int NumberOfVertices() {   //���ص�ǰ������
		std::cout << "Ϊɶ�����ﰡ" << std::endl;
		return numVertices;
	}
	virtual int NumberOfEdges() {
		return numEdges;
	}
	virtual void Output() {
		std::cout << "���ǰ�" << std::endl;
	}
	virtual T getValue(int i) {
		return 0;

	};  //ȡ����i��ֵ����������0
	virtual T getWeight(int v1, int v2) {
		return 0;
	}; //ȡ��(v1,v2���ϵ�Ȩֵ
	virtual int getFirstNeighbor(int v) {
		return 0;
	}; //ȡ����v�ĵ�һ���ڽӶ���
	virtual int getNextNeighbor(int v, int w) {
		//std::cout << "����������ɣ�����" << std::endl;
		return 0;
	}//ȡ�ڽӶ���w����һ���ڽӶ���
	virtual bool insertVertex(const T& vertex) {
		std::cout << "���ǰ�" << std::endl;
		return true;
	}; //����һ������vertex
	virtual bool insertEdge(int v1, int v2, E cost) {
		std::cout << "����Ĳ����" << std::endl;
		return true;
	}//�����(v1,v2) ȨΪcost
	virtual bool removeVertex(int v) {
		return true;
	}//ɾȥ����v���������������
	virtual bool removeEdge(int v1, int v2) {
		return true;
	}//ɾȥ�ߣ�v1,v2��
	virtual int getVertexPos(T vertex) {
		return -1;
	}
};
template<class T, class E>
void DFS(Graph<T, E>& G, const T& v) {    //vΪ�������Ϣ
	// �Ӷ���v��ʼ����ͼG����������ȱ�����������
	int  loc, n = G.NumberOfVertices();//ȡͼ�ж������
	bool* visited = new bool[n]; //�����������飬�������
	for (int i = 0; i < n; i++)
		visited[i] = 0; //��ʼ����ȫΪfalse
	std::cout << std::endl;
	loc = G.getVertexPos(v);  //���ݶ�����Ϣȷ��������±�
	DFS(G, loc, visited);
	delete[] visited;
}
template<class T, class E>
void DFS(Graph<T, E>& G, int v, bool viisted[]) {  //vΪ������±�
	// �Ӷ���λ��v��������������ȵĴ���������Կɶ������δ���ʹ��Ķ���
	//std::cout << G.getValue(v) << " ";  //���ʵ����㣬�����ֱ�ʾ
	std::cout << v << " ";
	viisted[v] = true;  //�������Ϊtrue
	int w = G.getFirstNeighbor(v);
	while (w != -1) {
		if (viisted[w] == false) {
			DFS(G, w, viisted);
		}
		w = G.getNextNeighbor(v, w);//ȡw����һ�����
	}
}
template<class T, class E>
void BFS(Graph<T, E>& G, const T& v) {
	//�Ӷ���v�������Թ�����ȵĴ����������ͼ���㷨��Ҫʹ�õ����У������ص㣩
	int w, n = G.NumberOfVertices();  //ȡ����ĸ���Ϊn
	bool* visited = new bool[n];
	for (int i = 0; i < n; ++i)
		visited[i] = false;  //��ʼ������
	int loc = G.getVertexPos(v); //��ȡ������±�
	//std::cout << G.getValue(loc) << " ";
	std::cout << loc << " ";
	visited[loc] = true;
	std::queue<int> Q;
	Q.push(loc);//��ջ
	while (!Q.empty()) {
		loc = Q.front();
		Q.pop();//ȡ���ͷ����ͷ����
		w = G.getFirstNeighbor(loc);
		while (w != -1) {
			if (visited[w] == false) {
				std::cout << w << " ";
				visited[w] = true;
				Q.push(w);  //���
			}
			w = G.getNextNeighbor(loc, w); //��w����һ������
		}
	}
	delete[] visited;
}
// ������������������������ͨͼ����ͨ��������
template<class T, class E>
void Components(Graph<T, E>& G) {
	//ͨ��DFS���ҳ�����ͼ��������ͨ����
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
void print_menu9() //�˵�����
{
	std::cout << "1------�����в���һ������\n"
		<< "2------�߲���\n"
		<< "3------����ɾ��\n"
		<< "4------��ɾ��\n"
		<< "5------��ö���ĸ���\n"
		<< "6------��ñߵĸ���\n"
		<< "7------��ȡ��������\n"
		<< "8------��ȡͼ�����е���ͨ����\n"
		<< "9------���ͼ\n"
		<< " 10-----�˳�\n"
		<< "��������Ҫ���еĲ�����1-10��: ";
}