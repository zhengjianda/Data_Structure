#include"Graphmtx.h"
#include"Graph.h"
#include"GraphLink.h"
template<class T, class E>
void Menu9(Graph<T, E>& G) {
	while (true) {
		print_menu9();
		int n;
		int v1, v2;
		E weight;
		std::cin >> n;
		switch (n)
		{
		case 1:
			std::cout << "�����붥������Ϣ" << std::endl;
			T v;
			std::cin >> v;
			G.insertVertex(v);
			std::cout << "���������ɹ�" << std::endl;
			break;
		case 2:
			std::cout << "������: ��һ�������ߵ�����������Ȩ��" << std::endl;
			std::cin >> v1 >> v2 >> weight;
			G.insertEdge(v1, v2, weight);
			break;
		case 3:
			std::cout << "ɾ��һ������,�����붥��������" << std::endl;
			std::cin >> v1;
			G.removeVertex(v1);
			std::cout << "����ɾ���ɹ�" << std::endl;
			break;
		case 4:
			std::cout << "ɾ���ߣ����������������ߵĶ���������" << std::endl;
			std::cin >> v1 >> v2;
			G.removeEdge(v1, v2);
			std::cout << "��ɾ���ɹ�" << std::endl;
			break;
		case 5:
			std::cout << "�����ĸ���Ϊ" << G.NumberOfVertices() << std::endl;
			break;
		case 6:
			std::cout << "�ߵ�����Ϊ" << G.NumberOfEdges() << std::endl;
			break;
		case 7:
			std::cout << "��ȡ���������ţ������붥����������Ϣ" << std::endl;
			std::cin >> v1;
			G.getVertexPos(v);
			break;
		case 8:
			std::cout << "ͼ�е�������ͨ����Ϊ:" << std::endl;
			Components(G);
			std::cout << std::endl;
			break;
		case 9:
			std::cout << "����ͼ:" << std::endl;
			G.Output();
			std::cout << std::endl;
			break;
		default:
			std::cout << "��������" << std::endl;
			return;
		}
	}
}
