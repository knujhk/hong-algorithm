﻿#include <iostream>
#include <vector>
#include <random>
#include <limits>
#include <fstream>
#include <chrono>
#include <numeric>
#include <iomanip>
using namespace std;

void Print(vector<float>& arr)
{
	for (auto& a : arr)
		cout << a << " ";
	cout << endl;
}

void PrintBuckets(vector<vector<float>>& buckets)
{
	for (int i = 0; i < buckets.size(); i++)
	{
		cout << i << ": ";
		for (int j = 0; j < buckets[i].size(); j++)
			cout << buckets[i][j] << " ";
		cout << endl;
	}
}

// 다른 정렬을 사용해도 됩니다.
void InsertionSort(vector<float>& bucket)
{
	for (int i = 1; i < bucket.size(); ++i) {
		float key = bucket[i];
		int j = i - 1;
		while (j >= 0 && bucket[j] > key) {
			bucket[j + 1] = bucket[j];
			j--;
		}
		bucket[j + 1] = key;
	}
}

void BucketSort(vector<float>& arr, int num_buckets)
{
	vector<vector<float>> buckets(num_buckets);

	// TODO:
	int max = 1;
	int min = 0;

	float section_size = float(max - min) / num_buckets;

	for(int i = 0; i < arr.size(); i++){
		buckets[int((arr[i]-min) / section_size)].push_back(arr[i]);
	}


	cout << "Before sorting" << endl;
	PrintBuckets(buckets);

	// TODO:
	for(int i = 0; i < num_buckets; i++){
		InsertionSort(buckets[i]);
	}
	
	cout << "After sorting" << endl;
	PrintBuckets(buckets);

	// TODO:
	//첫번째버킷부터 memcpy해도됨
	// int bucket = num_buckets-1;
	// int i = arr.size()-1;
	// while(bucket >= 0){	
	// 	if(buckets[bucket].empty())
	// 		bucket--;
	// 	else{
	// 		arr[i--] = buckets[bucket].back();
	// 		buckets[bucket].pop_back();
	// 	}
	// }

	int pos = 0;
	for(int i = 0; i < num_buckets; i++){
		memcpy(&arr[pos],&buckets[i][0],buckets[i].size() * sizeof(buckets[i][0]));
		pos += buckets[i].size();
	}
}

int main()
{
	vector<float> arr = { 0.78f, 0.17f, 0.39f, 0.26f, 0.72f, 0.94f, 0.21f, 0.12f, 0.23f, 0.67f };

	Print(arr);

	BucketSort(arr, 10);

	Print(arr);

	return 0;
}