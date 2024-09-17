#include <vector>
#include <iostream>
using namespace std;

void Print(vector<int>& arr)
{
	for (int i = 0; i < arr.size(); i++)
		cout << arr[i] << " ";
	cout << endl;
}

int main()
{
	//vector<int> arr = { 5, 2, 7, 3, 8, 5, 6, 4 };
	//vector<int> arr = { 2, 8, 7, 1, 3, 5, 6, 4 };
	vector<int> arr = { 9, 8, 7, 6, 4, 3, 2, 1, 5 };
	//vector<int> arr = { 5, 2, 7, 3, 4, 4, 6, 4 };

	int lo = 0;  // 첫 인덱스
	int hi = arr.size() - 1;  // 마지막 인덱스
	int x = arr[hi]; // 분할 기준으로 사용하는 pivot 4

	int i = lo - 1; // pivot보다 작거나 같은 것들중 가장 큰 인덱스

	Print(arr);

	// 퀵소트 방식
	// int j = hi;

	// while(1){
	// 	do{
	// 		++i;
	// 	}while(arr[i] < x);

	// 	do{
	// 		--j;
	// 	}while(arr[j] > x);

	// 	if(i >= j)
	// 		break;
	// 	else
	// 		swap(arr[i],arr[j]);
	// }
	
	// swap(arr[i], arr[hi]);
	// Print(arr);

	// cout << i  << endl; // 피벗 이하인 값들의 마지막 인덱스

	//다른 방식, 왼쪽부터 탐색하며 피벗이하의 값으로 구성된 부분 배열을 키워나가는 방식
	int j = 0;

	while(j < hi){
		if(arr[j] <= x)
			swap(arr[++i],arr[j]);
		j++;
	}

	swap(arr[i+1], arr[hi]);
	Print(arr);

	cout << i + 1 << endl; // 피벗 이하인 값들의 마지막 인덱스
}
