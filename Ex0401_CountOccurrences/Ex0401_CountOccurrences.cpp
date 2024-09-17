#include <iostream>
#include <vector>
#include <random>
#include <numeric>
#include <iostream>
#include <algorithm>

using namespace std;

void Print(vector<int>& arr)
{
	for (int i = 0; i < arr.size(); i++)
		cout << arr[i] << " ";
	cout << endl;
}

int binSearch(const vector<int>& arr, int left, int right, int x){
	int mid = (left+right)/2;
	while(left<=right){
		if(arr[mid] < x){
			left = mid+1;
		}
		else if(arr[mid] > x){
			right = mid - 1;
		}
		else
			return mid;
		mid = (left+right)/2;
	}
	return -1;
}

int Count1(const vector<int>& arr, int x)
{
	//TODO: O(n)
	int count = 0;
	for(int i = 0; i < arr.size(); ++i){
		if(arr[i] == x)
			count++;
	}

	return count;
}

int Count2(const vector<int>& arr, int x)
{
	//TODO: O(log(n) + count)
	int left = 0;
	int right = arr.size()-1;
	int mid = (left + right)/2;
	int count = 0;

	int idx = binSearch(arr,left,right,x);

	if(idx == -1)
		return 0;
	else{
		left = idx - 1;
		right = idx + 1;
		while(left >= 0 && arr[left] == x){
			count++;
			left--;
		}
		while(right < arr.size() && arr[right] == x){
			count++;
			right++;
		}
		return count+1;
	}
}
int findfirst(const vector<int>& arr, int left, int right, int x){
	//mid가 x보다 크거나 같으면 right = mid - 1
	if(right < left)
		return -1;

	int mid;

	while(left <= right){
		mid = (left+right)/2;
		if(arr[mid] >= x)
			right = mid - 1;
		else
			left = mid + 1;
	}
	if(arr[left] == x)
		return left;
	else
		return -1;
}
int findlast(const vector<int>& arr, int left, int right, int x){
	//mid가 x보다 작거나 같으면 left = mid + 1
	if(right < left)
		return -1;

	int mid;

	while(left <= right){
		mid = (left+right)/2;
		if(arr[mid] <= x)
			left = mid + 1;
		else
			right = mid - 1;
	}
	if(arr[right] == x)
		return right;
	else
		return -1;
}
int recurfindfirst(const vector<int>& arr, int left, int right, int x){

	if(right < left)
		return -1;

	int mid = (left+right)/2;

	if( arr[mid] == x && (mid == 0 || arr[mid-1] < x) )	//base case
		return mid;
	else if(arr[mid] < x){
		return recurfindfirst(arr,mid+1,right,x);
	}
	else{	//arr[mid] >= x
		return recurfindfirst(arr,left,mid-1,x);
	}

}
int recurfindlast(const vector<int>& arr, int left, int right, int x){

	if(right < left)
		return -1;

	int n = arr.size();
	int mid = (left+right)/2;

	if( arr[mid] == x && (mid == n-1 || arr[mid+1] > x) )	//base case
		return mid;
	else if(arr[mid] > x){
		return recurfindlast(arr,left,mid-1,x);
	}
	else{	//arr[mid] <= x
		return recurfindlast(arr,mid+1,right,x);
	}
}
int Count3(const vector<int>& arr, int x)
{
	//TODO: O(log(n))
	//연속된 x중 가장 왼쪽과 가장 오른쪽 인덱스를 찾으면 끝임
	//1. iterative 버전
	// int leftmost = findfirst(arr,0,arr.size()-1,x);
	// int rightmost = findlast(arr,0,arr.size()-1,x);
	//2. recursive 버전
	int leftmost = recurfindfirst(arr,0,arr.size()-1,x);
	int rightmost = recurfindlast(arr,0,arr.size()-1,x);

	if(leftmost == -1)
		return 0;
	else
		return rightmost - leftmost + 1;
}

int main()
{
	random_device rd;
	mt19937 gen(rd());

	const int n = 20;
	vector<int> my_vector(n);

	int x = 6; // target to find

	for (int r = 0; r < 100; r++)
	{
		uniform_int_distribution<int> value_distribution(1, 10);
		generate(my_vector.begin(), my_vector.end(), [&]() { return value_distribution(gen); });
		sort(my_vector.begin(), my_vector.end());

		Print(my_vector);

		const int expected_count = std::count(my_vector.begin(), my_vector.end(), x);

		cout << "Expected count = " << expected_count << endl;

		// 1. O(n) brute force
		if (Count1(my_vector, x) != expected_count)
		{
			cout << "Wrong count1: " << Count1(my_vector, x) << endl;
			exit(-1);
		}

		// 2. O(log(n) + count)
		if (Count2(my_vector, x) != expected_count)
		{
			cout << "Wrong count2: " << Count2(my_vector, x) << endl;
			exit(-1);
		}

		// 3. O(log(n))
		if (Count3(my_vector, x) != expected_count)
		{
			cout << "Wrong count3: " << Count3(my_vector, x) << endl;
			exit(-1);
		}
	}

	cout << "Good!" << endl;

	return 0;
}
