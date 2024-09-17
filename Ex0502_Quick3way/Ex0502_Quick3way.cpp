#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;

void Print(vector<int>& arr, int lo, int hi, string sep = "")
{
	//cout << "Index: ";
	//for (int i = 0; i < arr.size(); i++)
	//	cout << setfill(' ') << setw(3) << i;
	//cout << endl;

	cout << "Value: ";
	for (int i = 0; i < arr.size(); i++) {

		if (lo <= i && i <= hi)
			cout << setfill(' ') << setw(3) << arr[i] << sep;
		else
			cout << "   ";
	}
	cout << endl;
}

// Quicksort with 3-way partitioning, Sedgewick p299
// (Dijkstra's Dutch national flag problem)
void Quick3way(vector<int>& arr, int lo, int hi)
{
	if (hi <= lo) return;

	int lt = lo, i = lo, gt = hi-1;	
	int v = arr[hi];	

	//lt - 1 인덱스까지는 피벗보다 작은 값 -> 집어넣고 ++
	//gt + 1 ~ hi 까지는 피벗보다 큰 값 -> 집어넣고 --

	while (i <= gt)
	{
		if(arr[i] < v){
			swap(arr[lt++],arr[i++]);	//i왼쪽의 배열은 피봇이하의 값만 있음. 스왑하게 된다면 i자리에 오게 되는것은 피봇과 같은 
										//값일 것.
		}
		else if(arr[i] > v)
			swap(arr[gt--],arr[i]);//swap하고나서 i자리에 존재하는 게 피봇보다 작을수도 있고 클 수도 있으므로 
									//바로 i++하는 게 아니라 다시 확인해야 한다.
		else
			i++;	
	}
	swap(arr[gt+1],arr[hi]);

	Print(arr,lo, hi);

	Quick3way(arr, lo, lt - 1);
	Quick3way(arr, gt + 1, hi);
}

int main()
{
	srand(0);

	vector<int> arr = { 3, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2, 3, 2, 3, 4, 5, 1, 3, 5 };

	Print(arr, 0, arr.size() - 1);

	Quick3way(arr, 0, arr.size() - 1);

	Print(arr, 0, arr.size() - 1);

	return 0;
}
