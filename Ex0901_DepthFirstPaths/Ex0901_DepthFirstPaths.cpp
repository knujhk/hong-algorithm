#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

// Vertex에는 용도에 따라서 int 외에 string 같은 다른 정보들도 저장할 수 있습니다.
// 삽입/삭제가 많으면 list, 접근(읽기/쓰기)이 많으면 vector 권장

struct Vertex
{
	Vertex(int v) { value = v; }

	int value = -1;// 변수 이름은 value지만 실질적으로는 배열에 이 정점이 저장된 인덱스입니다.
	bool visited = false;

	vector<Vertex*> out_neighbors; // 나가는 방향의 이웃 vertex들에 대한 포인터
};

class Graph
{
public:
	Graph(int num_vertices)
	{
		vertices.resize(num_vertices);
		for (int i = 0; i < num_vertices; i++)
			vertices[i] = new Vertex(i);
		prev.resize(num_vertices,nullptr);
	}

	~Graph()
	{
		for (auto* v : vertices)
			delete v;
	}

	void AddDiEdge(int v, int w) // 단방향 간선
	{
		vertices[v]->out_neighbors.push_back(vertices[w]);
	}

	void AddBiEdge(int v, int w) // 양방향 간선
	{
		vertices[v]->out_neighbors.push_back(vertices[w]);
		vertices[w]->out_neighbors.push_back(vertices[v]);
	}

	void DFS(int source)
	{
		cout << "Depth-first Search: ";
		for (auto* v : this->vertices)
			v->visited = false;
		DFS(vertices[source]);
		cout << endl;
	}
	void DFS(Vertex* source)
	{
		cout << source->value << " ";
		source->visited = true;
		for (auto* w : source->out_neighbors)
			if (!w->visited)
				DFS(w);
	}

	// source에서 sink로 가는 경로(path) 찾기
	void DepthFirstPath(int source, int sink)
	{
		cout << "Paths from " << vertices[source]->value << " to " << vertices[sink]->value << endl;

		for (auto* v : this->vertices)
			v->visited = false;

		DepthFirstPathHelper(vertices[source], vertices[sink], vector<Vertex*>());
	}

private:
	vector<Vertex*> vertices;
	vector<Vertex*> prev;

	// 힌트: 인수 path는 호출될때마다 매번 복사가 됩니다.
	void DepthFirstPathHelper(Vertex* source, Vertex* sink, vector<Vertex*> path)
	{
		//path.push_back(source);
		//PrintPath(path);
		//path 벡터를 매번 복사할 필요가 없고 각 정점의 이전에 방문한 prev 벡터
		//하나만 있으면 됨(클래스 멤버 변수, 공용으로 사용)
		//왜냐하면 dfs중 끝까지 도달한 뒤에 마지막 갈림길로 돌아온다 하더라도
		//prev벡터에는 해당 갈림길까지의 경로가 그대로 저장되어있으므로
		//이어서 기록해나가면 됨.

		// TODO:
		if(source == sink){
			cout << "FOUND : ";
			//PrintPath(path);
			PrintPrev(sink);
		}
		else{
			source->visited = true;
			for(auto v : source->out_neighbors){
				if(!v->visited){
					prev[v->value] = source;
					DepthFirstPathHelper(v,sink,path);
				}
			}
			source->visited = false;
		}
		return;
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
	void PrintPrev(Vertex* sink)
	{
		stack<Vertex*> s;
		while(sink){
			s.push(sink);
			sink = prev[sink->value];
		}
		while(!s.empty()){
			Vertex* v = s.top();
			s.pop();
			cout << v->value << "->";
		}
		cout << '\n';
	}
};

int main()
{
	// 한 경로 안에서 한 번 방문한 정점은 다시 방문하지 않는다.

	// 간단한 경우
	{
		// 0: 애피타이저
		// 1: 메인요리
		// 2: 디저트

		Graph g(3);
		g.AddDiEdge(0, 1); // 애피타이저 -> 메인요리
		g.AddDiEdge(1, 2); // 메인요리 -> 디저트
		g.AddDiEdge(0, 2); // 애피타이저 -> 디저트

		g.DFS(0);
		g.DepthFirstPath(0, 2);
	}

	// Sedgewick Algorithm 4.1 p.536 (조금 달라요)
	{
		Graph g(6);

		g.AddDiEdge(0, 2);
		g.AddDiEdge(2, 1);
		g.AddDiEdge(2, 3);
		g.AddDiEdge(3, 4);
		g.AddDiEdge(1, 5);
		g.AddDiEdge(2, 4);
		g.AddBiEdge(3, 5); // 주의: 양방향 간선

		g.DFS(2);
		g.DepthFirstPath(2, 4);
	}

	return 0;
}

