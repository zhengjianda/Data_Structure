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
			std::cout << "请输入顶点的信息" << std::endl;
			T v;
			std::cin >> v;
			G.insertVertex(v);
			std::cout << "顶点插入成功" << std::endl;
			break;
		case 2:
			std::cout << "插入边: 请一次输入边的两个顶点和权重" << std::endl;
			std::cin >> v1 >> v2 >> weight;
			G.insertEdge(v1, v2, weight);
			break;
		case 3:
			std::cout << "删除一个顶点,请输入顶点的序号" << std::endl;
			std::cin >> v1;
			G.removeVertex(v1);
			std::cout << "顶点删除成功" << std::endl;
			break;
		case 4:
			std::cout << "删除边，请依次输入两个边的顶点的序号" << std::endl;
			std::cin >> v1 >> v2;
			G.removeEdge(v1, v2);
			std::cout << "边删除成功" << std::endl;
			break;
		case 5:
			std::cout << "顶点的个数为" << G.NumberOfVertices() << std::endl;
			break;
		case 6:
			std::cout << "边的条数为" << G.NumberOfEdges() << std::endl;
			break;
		case 7:
			std::cout << "获取顶点的序号，请输入顶点的相关信息" << std::endl;
			std::cin >> v1;
			G.getVertexPos(v);
			break;
		case 8:
			std::cout << "图中的所有连通分量为:" << std::endl;
			Components(G);
			std::cout << std::endl;
			break;
		case 9:
			std::cout << "输出图:" << std::endl;
			G.Output();
			std::cout << std::endl;
			break;
		default:
			std::cout << "结束了洛" << std::endl;
			return;
		}
	}
}
/*int main()
{
	Graphmtx<int, int> myGraph = Graphmtx<int, int>(50);

	//GraphLink<int, int> myGraphLink = GraphLink<int, int>(100);
	Menu(myGraph);
	//myGraph.Output();
	//DFS(myGraph, 0);
	std::cout << "Hello world" << std::endl;
	return 0;
}*/