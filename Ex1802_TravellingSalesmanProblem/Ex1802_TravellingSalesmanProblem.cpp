#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct Edge
{
	int u = 0;
	int v = 0;
	int weight = 0;
};

struct Vertex
{
	Vertex(int v) { value = v; }

	int value = -1;// 변수 이름은 value지만 실질적으로는 배열에 이 정점이 저장된 인덱스입니다.
	bool visited = false;

	vector<Edge> out_neighbors; // 나가는 방향의 이웃 vertex들에 대한 포인터
};

class Graph
{
public:
	Graph(int num_vertices)
	{
		vertices.resize(num_vertices);
		for (int i = 0; i < num_vertices; i++)
			vertices[i] = new Vertex(i);
	}

	~Graph()
	{
		for (auto* v : vertices)
			delete v;
	}

	void AddDiEdge(int u, int v, int weight) // 단방향 간선
	{
		vertices[u]->out_neighbors.push_back(Edge{ u, v, weight });
	}

	void AddBiEdge(int u, int v, int weight) // 양방향 간선
	{
		vertices[u]->out_neighbors.push_back(Edge{ u, v, weight });
		vertices[v]->out_neighbors.push_back(Edge{ v, u, weight });
	}

	void TravellingSalesman(int source)
	{
		cout << "Start : " << vertices[source]->value << endl;

		minimum_path.clear();

		for (auto* v : this->vertices)
			v->visited = false;

		TravellingSalesmanHelper(vertices[source], vertices[source], vector<Vertex*>(), 0);

		cout << "Minimum cost : " << min_wsum << endl;
		cout << "Minimum path : ";
		PrintPath(minimum_path);
	}

private:
	vector<Vertex*> vertices;
	vector<Vertex*> minimum_path;
	int min_wsum = 1000000; // large number

	void TravellingSalesmanHelper(Vertex* source, Vertex* sink, vector<Vertex*> path, int wsum)
	{
		// TODO:
		path.push_back(source);
		//wsum엔 현재 정점으로 오는 경로의 가중치가 합산되어있음
		//PrintPath(path);

		if(source == sink && path.size() > 1){
			if(path.size() == vertices.size()+1){
				cout << "found : "; 
				PrintPath(path);
				cout << "cost : " << wsum  << '\n';

				if(wsum < min_wsum){
					min_wsum = wsum;
					minimum_path = path;
				}
			}
			else{
				cout << "discard : "; 
				PrintPath(path);
			}
		}
		else{
			if(source != sink)
				source->visited = true;
			for(auto edge : source->out_neighbors){
				if(!vertices[edge.v]->visited)
					TravellingSalesmanHelper(vertices[edge.v],sink,path,wsum + edge.weight);
			}
			source->visited = false;
		}


		// for(auto edge : source->out_neighbors){
		// 	int v = edge.v;
		// 	if(vertices[v] == sink){
		// 		if(path.size() == vertices.size()){
		// 			cout << "found : "; 
		// 			PrintPath(path); //sink를 따로 출력해줘야됨, path에 들어가있지 않음
		// 			cout << "->" <<sink->value << '\n';
		// 			cout << "cost : " << wsum + edge.weight << '\n';
		// 			if(wsum + edge.weight < min_wsum){
		// 				min_wsum = wsum + edge.weight;
		// 				minimum_path = path;
		// 			}
		// 		}
		// 		else{
		// 			cout << "discard : "; 
		// 			PrintPath(path); //sink를 따로 출력해줘야됨, path에 들어가있지 않음
		// 			cout << "->" << sink->value << '\n';
		// 		}
		// 	}
		// 	else if(!vertices[v]->visited){
		// 		source->visited = true;
		// 		TravellingSalesmanHelper(vertices[v],sink,path,wsum + edge.weight);
		// 		source->visited = false;
		// 	}
		// }
	}

	void PrintPath(vector<Vertex*> path)
	{
		for (auto& v : path) {
			cout << v->value;
			if (&v != &path.back())
				cout << " -> ";
		}
		cout << endl;
	}
};

int main()
{
	Graph g(4);

	// 주의: 양방향 간선 (undirected graph)
	g.AddBiEdge(0, 1, 20);
	g.AddBiEdge(0, 2, 25);
	g.AddBiEdge(0, 3, 30);
	g.AddBiEdge(1, 2, 10);
	g.AddBiEdge(2, 3, 35);
	g.AddBiEdge(3, 1, 15);

	g.TravellingSalesman(0);

	return 0;
}

