#include <vector>
#include <iostream>
#include <iomanip>
#include <numeric> // std::iota
#include <algorithm>

using namespace std;

void Print(vector<int>& arr, int lo, int hi)
{
	// setfill(), setw()는 줄맞춤에 사용

	for (int i = 0; i < lo; i++)
		cout << "   ";
	for (int i = lo; i <= hi; i++)
		cout << setfill(' ') << setw(3) << arr[i];
	cout << endl;
}

bool CheckSorted(vector<int>& a)
{
	for (int i = 0; i < a.size() - 1; i++)
	{
		if (a[i] > a[i + 1])
			return false;
	}

	return true;
}

// Sedgewick p. 278
class BottomupMerge
{
public:
	void Sort(vector<int>& a)
	{
		aux.resize(a.size());

		int N = a.size();
		// TODO: 재귀호출 사용하지 않습니다.
		for(int sz = 1; sz < N; sz *= 2){ //병합 대상인 배열 사이즈
			for(int low = 0; low+sz < N; low += 2*sz){	//low+sz >= N이면 low ~ N-1까지는 정렬되어있으므로 stop
				Merge(a,low,low+sz-1,std::min(low+2*sz-1,N-1));
			}
		}
	}

private:
	void Merge(vector<int>& a, int lo, int mid, int hi)
	{
		// TODO: Top-down과 동일
		if(hi <= lo)
			return;

		int i = lo;
		int j = mid + 1;

		if(a[mid] <= a[j])
			return; //최선의 경우

		cout << "Before: ";
        Print(a, lo, hi);

		for(int k = lo; k <= hi; ++k){
			aux[k] = a[k];
		}

		for(int k = lo; k <= hi; ++k){
			if(i > mid) a[k] = aux[j++];
			else if(j > hi) a[k] = aux[i++];
			else if(aux[i] <= aux[j]) a[k] = aux[i++];
			else a[k] = aux[j++];
		}

		cout << "after:  ";
        Print(a, lo, hi);

	}

	vector<int> aux; // 추가 메모리
};

int main()
{
	vector<int> my_vector(34);
	std::iota(my_vector.begin(), my_vector.end(), 0);
	std::reverse(my_vector.begin(), my_vector.end());

	cout << "        ";
	Print(my_vector, 0, my_vector.size() - 1);

	BottomupMerge merge;
	merge.Sort(my_vector);

	cout << "        ";
	Print(my_vector, 0, my_vector.size() - 1);

	return 0;
}
