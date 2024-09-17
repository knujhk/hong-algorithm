#include <iostream>
#include <vector>
#include <random>
#include <limits>
#include <fstream>
#include <chrono>
#include <numeric>
#include <iomanip>
#include <string>
using namespace std;

template<typename T>
void Print(vector<T>& arr)
{
	for (auto& a : arr)
		cout << a << " ";
	cout << endl;
}

void checksorted(vector<string> arr){
	int n = arr.size();
	

	for(int i = 1; i < n; i++){
		for(int j = 0; j < 3; j++){
			if(arr[i][j] < arr[i-1][j]){
				cout << "not sorted\n"; 
				return;
			}
			else if(arr[i][j] > arr[i-1][j])
				break;
		}
	}
	cout << "sorted\n";
}

void CountingSort(vector<string>& arr, int k, int d)
{
	vector<string> temp = arr; // 복사
	//std::fill(arr.begin(), arr.end(), "   "); // 디버깅 편의

	// TODO:
	vector<int> count(k+1,0);
	
	for(int i = 0; i < temp.size(); i++){
		count[temp[i][d]-'A']++;
	}
	for(int i=1;i<count.size();i++){
		count[i] += count[i-1];
	}

	for(int i = arr.size()-1; i >= 0; i--){
		arr[count[temp[i][d]-'A']-1] = temp[i];
		count[temp[i][d]-'A'] -= 1;
	}
}

void RadixSort(vector<string>& arr)
{
	// TODO:
	int m = 3;//글자수
	int k = 'Z'-'A';

	for(int d = m-1; d >= 0; d--){
		CountingSort(arr,k,d);
	}
	
}

int main()
{
	// CLRS 8.3-1
	vector<string> arr = { "COW", "DOG", "SEA", "RUG",
		"ROW", "MOB", "BOX", "TAB", "BAR", "EAR", "TAR",
		"DIG", "BIG", "TEA", "NOW", "FOX" };

	Print(arr);

	RadixSort(arr);
	checksorted(arr);

	Print(arr);

	return 0;
}