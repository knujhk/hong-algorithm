#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include <queue>
#include <map>
#include <unordered_map>
#include <cassert>
using namespace std;

struct Vertex
{
	string name = "";
	vector<string> priority; // 선호도 우선순위
	int current = -1; // 현재 자신의 몇 "순위"와 연결되어 있는지 기록

	// Vertex(){}	//변환 생성자가 존재해서 기본 생성자가 자동으로 만들어지지 않음

	// Vertex(string para_name, vector<string> para_priority)
	// {
	// 	name = para_name;
	// 	priority = para_priority;
	// }

	int Rank(string name)
	{
		for (int i = 0; i < priority.size(); i++)
			if (priority[i] == name) return i;

		assert(false);

		return -1;

		// Rank() 반환값이 작을 수록 우선순위가 높다
		// unordered_map<이름, 우선순위>를 만들어서 더 빠르게 확인 가능
	}

	string ConnectedName()
	{
		if (current == -1) return "NA";
		else return priority[current];
	}

	void Print()
	{
		cout << name << "(";
		for (auto& p : priority)
			cout << p;
		cout << ")";
	}
};

void Print(map<string, Vertex>& interns, unordered_map<string, Vertex>& teams)
{
	for (auto& i : interns)
	{
		i.second.Print();
		cout << " - ";
		if (i.second.current == -1)
			cout << "No Team";
		else {
			teams[i.second.ConnectedName()].Print();
			if (i.second.name != teams[i.second.ConnectedName()].ConnectedName())
				cout << "*"; // 서로 연결이 아니라면 임시라는 의미로 * 추가
		}
		cout << endl;
	}
}

int main()
{
	map<string, Vertex> interns; // 디버깅할때 순서대로 보기 위해 map 사용, unordered_map 사용 가능
	interns["A"] = Vertex{"A", {"X", "Y", "Z"}};
	interns["B"] = Vertex{ "B", {"Y", "X", "Z"} };
	interns["C"] = Vertex{ "C", {"Y", "Z", "X"} };

	unordered_map<string, Vertex> teams;
	teams["X"] = Vertex{ "X", {"B", "A", "C"} };
	teams["Y"] = Vertex{ "Y", {"A", "B", "C"} };
	teams["Z"] = Vertex{ "Z", {"B", "C", "A"} };
	teams["X"] = Vertex{ "X", {"B", "A", "C"} };
	teams["Y"] = Vertex{ "Y", {"A", "C", "B"} };
	teams["Z"] = Vertex{ "Z", {"B", "C", "A"} };

	queue<Vertex*> free_interns;
	for (auto& i : interns)
		free_interns.push(&i.second); // 모든 인턴을 free 큐에 넣기

	while (!free_interns.empty())
	{
		Vertex* i = free_interns.front();
		free_interns.pop();

		cout << "Intern " << i->name << endl;

		i->current += 1; //꺼낼 때마다 1씩 낮은 우선순위의 팀과 매칭

		Vertex* t = &teams[i->ConnectedName()]; //현재 우선순위에 맞는 팀

		if (t->current == -1)
		{
			t->current = t->Rank(i->name);	//팀 입장에서 인턴의 우선순위
		}
		else
		{
			if (t->Rank(i->name) < t->current)	//새 인턴의 우선순위가 이미 매칭되어있는 인턴의 우선순위보다 높은 경우
			{
				free_interns.push(&interns[t->ConnectedName()]); //vertex* 를 집어넣어야 함 
				t->current = t->Rank(i->name);
			}
			else {
				free_interns.push(i);
			}
		}

		Print(interns, teams);
	}

	return 0;
}
