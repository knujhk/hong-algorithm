#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <fstream>
using namespace std;

struct Node
{
	Node(string str, int freq):data(str),freq(freq){};

	string data; // char보다 디버깅 편리
	int freq;
	Node* left = nullptr;
	Node* right = nullptr;
};

// std::priority_queue에서 사용할 MinHeapNode의 비교
struct Compare
{
	bool operator()(Node* l, Node* r)//greater
	{
		// TODO:
		return l->freq > r->freq;
	}
};

void PrintCodes(Node* root, string str)
{
	if (!root)
		return;

	if (!root->left && !root->right) // left node이면 출력
		cout << root->data << ": " << str << "\n";

	PrintCodes(root->left, str + "0");
	PrintCodes(root->right, str + "1");
}

void HuffmanCoding(vector<char> data, vector<int> freq)
{
	// freq가 작을 수록 우선순위가 높은 힙
	// struct Compare에서 우선순위 비교
	priority_queue<Node*, vector<Node*>, Compare> heap;

	for (int i = 0; i < data.size(); ++i)
		heap.push(new Node{ string(1, data[i]), freq[i] });

	
	while (heap.size() != 1)
	{
		Node* left, * right, * top;

		// TODO:
		left = heap.top();heap.pop();
		right = heap.top();heap.pop();
		top = new Node{left->data + right->data, left->freq + right->freq};
		top->left = left; top->right = right;
		heap.push(top);

		cout << "(" << left->data << ", " << left->freq << ") + (" << right->data << ", " << right->freq << ") -> ";
		cout << "(" << top->data << ", " << top->freq << ")" << endl;
	}
	

	PrintCodes(heap.top(), "");
}

int main()
{
	// vector<char> data = { 'a', 'b', 'c', 'd', 'e', 'f' };
	// vector<int> freq = { 45, 13, 12, 16, 9, 5 };

	//파일 열고 한 번 훑으면서 각 문자 발생횟수 카운트
	//한 번 읽을 때 문자,빈도 쌍을 만들까? 
	//아스키코드를 인덱스로 해서 벡터 요소에다 카운트 저장하는 게 편할듯?
	//텍스트 파일이 utf-8(~4B)이니 char 벡터에다 저장하면 안 됨 

	HuffmanCoding(data, freq);

	return 0;
}
