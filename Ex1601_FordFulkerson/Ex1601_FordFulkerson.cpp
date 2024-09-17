#include <limits.h>
#include <string.h>
#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>
#include <assert.h>
#include <list>

using namespace std;

class FlowEdge
{
public:
	int v = -1;
	int w = -1;
	double capacity = 0.0; // 최대 용량
	double flow = 0.0;     // 현재 유량

	FlowEdge()
		:v(-1), w(-1), capacity(0.0), flow(0.0)
	{}

	FlowEdge(int v, int w, double capacity)
		: v(v), w(w), capacity(capacity), flow(0.0)
	{}

	FlowEdge(int v, int w, double capacity, double flow)
		: v(v), w(w), capacity(capacity), flow(flow)
	{}

	int From() { return v; }
	int To() { return w; }
	double Capacity() { return capacity; }
	double Flow() { return flow; }
	int Other(int vertex)
	{
		if (vertex == v) return w;
		else if (vertex == w) return v;
		else {
			assert(false);
			return -1;
		}
	}

	double ResidualCapacityTo(int vertex)
	{
		if (vertex == v) return flow;
		else if (vertex == w) return capacity - flow;

		assert(false);

		return 0.0;
	}

	void AddResidualFlowTo(int vertex, double delta)
	{
		if (vertex == v) flow -= delta;
		else if (vertex == w) flow += delta;
		else assert(false);
	}

	void Print()
	{
		cout << v << "->" << w << " " << flow << "/" << capacity << endl;
	}

	int Either() { return v; }
};

class FlowNetwork
{
public:
	int V;
	int E;
	vector<vector<FlowEdge*>> adj;	//벡터가 아니라 리스트로 만들어야 하는 이유?
									//엣지를 삽입 삭제를 여러번 하는 게 아니라
									//탐색, 업데이트만 자주 하지 않나?
									//둘 다 가능한데 벡터가 나을 듯

	FlowNetwork(int V)
		: V(V), E(0), adj(V)
	{}

	void AddEdge(FlowEdge e)
	{
		FlowEdge* newEdge = new FlowEdge(e);
		int v = e.Either();
		int w = e.Other(v);
		adj[v].push_back(newEdge); // v의 out_neighbor
		adj[w].push_back(newEdge); // w의 in_neighbor, 이거 왜 필요함? w위치에서 augmenting path이어나갈 때
														//v->w flow를 다른 방향으로 우회시켜주는 방식으로
														//새 path를 찾을 수도 있음
														//residual graph를 따로 만들지않아도 된다.
	}

	vector<FlowEdge*>& Adj(int v)
	{
		return adj[v];
	}

	vector<FlowEdge*> AllEdges() {
		vector<FlowEdge*> b;
		for (int v = 0; v < V; v++)
			for (auto& e : this->Adj(v))
				if (e->Other(v) > v)	//edge 추가할 때 v-w 연결을 v와w adj[v]와 adj[w]에 모두 달아줬기 때문에
					b.push_back(e);
		return b;
	}
};

class FordFulkerson
{
public:
	vector<bool> marked;
	vector<FlowEdge*> prev;
	double value;

	FordFulkerson(FlowNetwork& g, int s, int t)
		: marked(g.V), prev(g.V), value(0.0)
	{
		//모든 edge들의 유량들이 0으로 초기화되어 있는 상황.
		while (HasAugmentingPath(g, s, t))
		{
			// TODO:
			double bottle_neck = INT_MAX;

			for(int i = t; i != s; i = prev[i]->From()){
				bottle_neck = min(bottle_neck, prev[i]->ResidualCapacityTo(i));
			}
			
			//경로상의 모든 edge의 유량을 bottle_neck 만큼 증가시키기
			for(int i = t; i != s; i = prev[i]->From()){
				prev[i]->AddResidualFlowTo(i,bottle_neck);
			}

			value += bottle_neck;

			Print(g);
		}
		
	}

	bool HasAugmentingPath(FlowNetwork& g, int s, int t)
	{
		fill(marked.begin(), marked.end(), false);

		queue<int> q; // BFS

		marked[s] = true;
		q.push(s);

		while (!q.empty())
		{
			int v = q.front();
			q.pop();

			for (FlowEdge* e : g.Adj(v))
			{
				int w = e->Other(v);
				if (!marked[w] && e->ResidualCapacityTo(w) > 0) // <- TODO: BFS와의 차이 확인
				{					//edge가 v->w가 아니라 w->v 방향 엣지인 경우
									//v로 들어오는 flow를 다른데로 돌릴 수 있는 지 확인하게 됨.
									//line 48, 91 참고
					prev[w] = e;
					marked[w] = true;
					q.push(w);
				}
			}
		}

		return marked[t];
	}

	void Print(FlowNetwork& g)
	{
		cout << "Result:" << endl;
		for (int v = 0; v < g.V; v++)
			for (FlowEdge* e : g.Adj(v))
				if (v == e->From())
					e->Print();
		cout << value << endl;
	}
};

int main()
{
	// 강의 영상에 나오는 예시
	// FlowNetwork g(4);
	// for (const auto& e : vector<FlowEdge>{ {0, 1, 4.0}, {0, 2, 8.0}, {1, 2, 6.0}, {1, 3, 2.0}, {2, 3, 3.0} })
	// {
	// 	g.AddEdge(e);
	// }

	FlowNetwork g(6); // CLRS 예제
	g.AddEdge({ 0, 1, 16.0 });
	g.AddEdge({ 0, 2, 13.0 });
	g.AddEdge({ 1, 3, 12.0 });
	g.AddEdge({ 2, 1, 4.0 });
	g.AddEdge({ 2, 4, 14.0 });
	g.AddEdge({ 3, 2, 9.0 });
	g.AddEdge({ 3, 5, 20.0 });
	g.AddEdge({ 4, 3, 7.0 });
	g.AddEdge({ 4, 5, 4.0 });

	FordFulkerson f(g, 0, g.V - 1);

	return 0;
}
