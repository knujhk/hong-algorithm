#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include <map>
using namespace std;

struct Vertex
{
	Vertex(int v) { value = v; }

	int value = -1;

	bool visited = false;

	vector<Vertex*> out_neighbors;
	vector<Vertex*> in_neighbors; // Transpose 쉽게 하려고 저장
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

	void AddDiEdge(int v, int w)
	{
		vertices[v]->out_neighbors.push_back(vertices[w]);
		vertices[w]->in_neighbors.push_back(vertices[v]);
	}

	//deque<Vertex*> ReversePostorderDFS()
	void ReversePostorderDFS()
	{
		//revpost = deque<Vertex*>();

		for (auto* v : this->vertices)
			v->visited = false;

		for (auto* v : this->vertices)
			if (!v->visited){
				cout << "ReversePostorderDFS " << v->value << '\n';
				ReversePostorderDFS(v);
				cout << '\n' <<"recursion is done\n";
			}
				

		//return revpost;
	}

	void Transpose()
	{
		// TODO:
		for(auto v: vertices){
			swap(v->in_neighbors,v->out_neighbors);
		}

		// 인접 행렬 표현에서 행렬을 transpose 시키는 것과 동일
	}

	void KosarajuStrongComponents()
	{
		//Transpose(); // 생략하면 출력 순서는 달라지만 결과는 동일

		// deque<Vertex*> revpost = TODO; // 아래 for문 편의상 stack대신 deque 사용

		//cout << "Reverse Post-order: ";
		//for (auto* v : revpost)
		//	cout << v->value << " ";
		//cout << endl;

		//Transpose();

		// TODO:

		//내 맴
		Transpose();
		id.resize(vertices.size(),-1);
		//1. reverse post order 순서로 정점들 나열한 배열 얻기
		ReversePostorderDFS();
		cout << "reverse post order : ";
		for(auto v = revpost.begin(); v != revpost.end();v++)
			cout << (*v)->value << ' ';
		cout << endl;
		//2. 반대 순서로 DFS하기- 몇 번째 강연결요소인지 저장은 DFS안에서
		Transpose();
		for(auto v : vertices)
			v->visited = false;
		for(int i = 0; i < vertices.size(); i++){
			Vertex* v = revpost.front();
			revpost.pop_front();
			if(id[v->value]<0){
				DFS(v);
				count++;
			}
		}

		// 결과 정리 후 출력
		vector<vector<int>> components(count);
		for (int s = 0; s < vertices.size(); s++)
			components[id[s]].push_back(s);
		cout << count << " strong components" << endl;
		for (int i = 0; i < components.size(); i++)
		{
			cout << "Kosaraju strong component " << i + 1 << ": ";
			for (auto v : components[i])
				cout << v << " ";
			cout << endl;
		}

	}

private:
	vector<Vertex*> vertices;
	deque<Vertex*> revpost;	
	vector<int> id;
	int count = 0;

	//void TopologicalSortHelper(Vertex* v)
	void ReversePostorderDFS(Vertex* v)
	{
		// TODO: revpost에 결과 저장하기
		//post order순서로 탐색하며 덱에 앞에다가 집어넣기 -> 결과는 reverse post order
		v->visited = true;
		cout << v->value << "->";
		for(auto w : v->out_neighbors){
			if(!w->visited)
				ReversePostorderDFS(w);
		}
		revpost.push_front(v);
		cout << '\n' << "push(" << v->value <<")\n";
		cout << "post order : ";
		for(auto v = revpost.crbegin(); v != revpost.crend();v++)
			cout << (*v)->value << ' ';
		cout << endl;
	}

	void DFS(Vertex* v)
	{
		// TODO:
		//방문하는 정점들은 count+1번째 강연결요소에 속함
		//이를 id[index] = count; 로 저장
		v->visited = true;
		id[v->value] = count;
		for(auto w : v->out_neighbors){
			if(!w->visited)
				DFS(w);
		}
	}

	// ReversePostorderDFS()도 깊이우선탐색이라서 DSF()와 합칠 수 있으나
	// 여기서는 디버깅 편의를 위해 분리하였습니다.
};

int main()
{
	// Sedgewick p569
	// 방향(directed) 그래프
	vector<vector<int>> edges = {
		{4, 2}, {2, 3}, {3, 2}, {6, 0}, {0, 1},	{2, 0}, {11, 12}, {12, 9}, {9, 10},
		{9, 11}, {7, 9}, {10, 12}, {11, 4}, {4, 3}, {3, 5}, {6, 8}, {8, 6}, {5, 4},
		{0, 5}, {6, 4},	{6, 9}, {7, 6} };
	Graph g(13);

	for (vector<int>& p : edges)
		g.AddDiEdge(p[0], p[1]);

	g.KosarajuStrongComponents();

	return 0;
}
