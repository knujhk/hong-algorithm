#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	vector<int> arr = { 8, 2, 3, 5, 9, 1, 9, 4, 3, 7, 6, 7 };

	// TODO:
	//배열 사이즈가 짝수라고 가정하자
	//두개씩 묶어서 비교하고 그 중 작은것은 min과, 큰 것은 max과 비교하면 3번씩*(n/2)번 비교
	int min, max;

	if(arr[0] < arr[1]){
		min = arr[0];
		max = arr[1];
	}
	else{
		min = arr[1];
		max = arr[0];
	}

	for(int i = 2; i+1 < arr.size(); i += 2){
		if(arr[i] < arr[i+1]){
			min = std::min(arr[i],min);
			max = std::max(arr[i+1],max);
		}
		else{
			if(arr[i] > max) swap(arr[i],max);
			if(arr[i+1] < min) swap(arr[i+1],min);
		}
	}

	cout << "Min value = " << min << ", Max value = " << max << endl; // Min value = 1, Max value = 9
}
