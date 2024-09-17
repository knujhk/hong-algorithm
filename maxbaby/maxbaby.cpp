#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <limits>
#include <deque>

using namespace std;

class FlowEdge
{
private:
    int from = -1;
    int to = -1;
    double capacity = 0.0;
    double flow = 0.0;

public:
    //바로 아래 생성자는 현재 문제 특화
    FlowEdge(int from, int to):from(from),to(to),capacity(1.0){}

    FlowEdge(int from, int to, double capacity):from(from),to(to),capacity(capacity){}
    FlowEdge(int from, int to, double capacity, double flow):from(from),to(to),capacity(capacity),flow(flow){}
    ~FlowEdge(){}

    //from,to반환(각각)
    int From(){return from;}
    int To(){return to;}
    int Other(int v)
    {
        if(v == From())
            return To();
        else if(v == To())
            return From();
        else   
            return -1;
    }

    //최대 유량 반환
    double Capacity(){return capacity;}

    //여유 유량 or 현재 유량 반환
    double residualCapTo(int to)
    {
        if(to == To())
            return capacity - flow;
        else if(to == From())
            return flow;
        else   
            return -1;
    }

    //유량 추가
    void addFlowTo(int to, double increment)
    {
        double update = flow + increment;
        if(to == To() && update <= capacity && update >= 0)
            flow += increment;
    }
    void addFlowTo(int to)
    {
        double update = flow + 1;
        if(to == To() && update <= capacity && update >= 0)
            flow += 1;
    }
};

class FlowNetwork
{
private:
    //adjacent list
    int V;
    int E = 0;

    vector<list<FlowEdge*>> adj;

public:
    FlowNetwork(int v):V(v),adj(v){}
    FlowNetwork(int v, vector<FlowEdge> argAdj):V(v),adj(v)
    {
        for(auto edge : argAdj){
            addEdge(edge.From(),edge.To());
        }
    }
    //edge추가
    void addEdge(int from, int to)
    {
        //from, to가 0~V-1 범위인지 확인하는 게 좋지만 여기선 생략
        FlowEdge* newEdge = new FlowEdge(from,to);
        adj[from].push_back(newEdge);
        adj[to].push_back(newEdge);
        E++;
    }

    void addEdge(int from, int to, double capacity)
    {
        FlowEdge* newEdge = new FlowEdge(from,to,capacity);
        adj[from].push_back(newEdge);
        adj[to].push_back(newEdge);
        E++;
    }
    //vertex v에 달린 edge반환
    list<FlowEdge*> Adj(int v) {return adj[v];}

    //v, e 갯수 반환
    int numVertex() {return V;}
    int numEdge() {return E;}

    //모든 엣지 반환 -> 필요에 따라,
    //포드퍼커슨 구현 시엔 불필요
};

class FordFulkerson
{
public:
    //멤버들
    vector<FlowEdge*> prev;
    vector<bool> visited;
    double value;
    FlowNetwork& g;

    //생성자에서 메인 알고리즘 돌려버리기-유량을 늘릴 수 있는 path가 있다면 bottleNeck을 찾고 
    //path의 모든 edge의 유량을 그만큼 늘려줌
    //flow network와 source, sink를 매개변수로 받아야 함
    FordFulkerson(FlowNetwork& g, int src, int sink)
        :g(g),visited(g.numVertex(),false),prev(g.numVertex(),nullptr)
    {

        //while
        while(findAugmentablePath(src,sink)){
            //path역추적하면서bottle_neck 구하기
            
            //경로출력
            deque<int> dq;
            for(auto v = sink; v != src; v = prev[v]->From()){
                dq.push_front(v);
            }
            dq.push_front(src);
            cout << "path : ";
            while(!dq.empty()){
                int k = dq.front();
                dq.pop_front();
                cout << k << "->";
            }
            cout << "\n";

            double bottle_neck = numeric_limits<double>::infinity();

            for(auto v = sink; v != src; v = prev[v]->From()){
                bottle_neck = min(bottle_neck, prev[v]->residualCapTo(v));
            }
            //유량 늘려주기
            for(auto v = sink; v != src; v = prev[v]->From()){
                prev[v]->addFlowTo(v,bottle_neck);
            }
            value += bottle_neck;
            cout << "bottle_neck : " << bottle_neck << "current value : " << value << '\n'; 
            print();
        }

        cout <<"max value: " << value << '\n';
    }
   
    //path를 찾기위한 BFS
    //진리값 반환, prev벡터에 경로 저장,
    FlowEdge* findAugmentablePath(int src, int sink)
    {
        for(auto v: visited) v = false;
        prev[sink] = nullptr;

        queue<int> q;
        visited[src] = true;
        q.push(src);

        cout << "BFS : ";

        while(!q.empty()){
            int v = q.front();
            q.pop();
            cout << v << "->";

            for(auto edge : g.Adj(v)){
                //adj[v]에는 v의 in,out neighbor가 모두 있으므로 out neighbor만 취해야함
                if(edge->From() != v)
                    continue;

                int w = edge->To();
                if(!visited[w] && edge->residualCapTo(w) > 0){
                    prev[w] = edge;
                    visited[w]= true;//dfs면 미리 마킹하면 안 됨.
                    q.push(w);
                }
            }
        }
        cout << "prev[sink] : " << prev[sink] << '\n';
        return prev[sink];
    }

    void print(){
        for(int v = 0; v < g.numVertex(); v++){
            for(auto edge : g.Adj(v)){
                if(edge->From() == v){
                    int w = edge->To();
                    cout << v << "->" << w << ' ' << edge->residualCapTo(v) << '/' << edge->residualCapTo(w) << '\n';
                }
            }
        }
    }
};

int main(){
    //source : 0 
    //sink : 11
    vector<FlowEdge> a = {{1,6},{1,7},{2,6},{3,6},{3,9},{4,8},{4,9},{4,10},{5,7}};
    FlowNetwork g(12,a);
    for(int i = 1; i <=5; i++)
        g.addEdge(0,i);
    for(int i = 6; i <= 10; i++)
        g.addEdge(i,11);

    FordFulkerson(g,0,11);

    return 0;
}