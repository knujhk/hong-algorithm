#include <vector>
#include <iostream>
#include <iomanip> // setfill(), setw()
#include <numeric> // iota
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

// Sedgewick p. 273
class TopDownMerge
{
public:
	void Sort(vector<int>& a)
	{
		count = 0; // 분석용
		aux.resize(a.size());

		SortHelper(a, 0, a.size() - 1);
	}

private:
	void Merge(vector<int>& a, int lo, int mid, int hi)
	{
		cout << "Before: ";
		Print(a, lo, hi);

		int i = lo, j = mid + 1;

		//최선의 경우
		if(a[mid] <= a[mid+1])
			return;

		for (int k = lo; k <= hi; k++)
			aux[k] = a[k];

		for (int k = lo; k <= hi; k++)	//output 배열의 low부터 채워나가기
		{
			if (i > mid)	//왼쪽 리스트 다 소진한 경우
				a[k] = aux[j++];
			else if (j > hi)	//오른쪽 리스트 다 소진한 경우
				a[k] = aux[i++]; 
			else if (aux[j] < aux[i])
				a[k] = aux[j++]; 
			else a[k] = aux[i++];
		}

		cout << "After : ";
		Print(a, lo, hi);

		count += hi - lo + 1;
		cout << "Count : " << hi - lo + 1 << ", " << count << endl; // 누적 카운트 (디버깅용)
	}

	void SortHelper(vector<int>& a, int lo, int hi)
	{
		if (hi <= lo) return;

		int mid = lo + (hi - lo) / 2;

		//TODO:
		SortHelper(a,lo,mid);
		//TODO:
		SortHelper(a,mid+1,hi);

		Merge(a, lo, mid, hi);
	}

	vector<int> aux; // 추가 메모리 필요
	int count = 0;   // 연산 횟수 세보기용
};

int main()
{
	vector<int> my_vector(16);
	std::iota(my_vector.begin(), my_vector.end(), 0);
	std::reverse(my_vector.begin(), my_vector.end());

	cout << "        ";
	Print(my_vector, 0, my_vector.size() - 1);

	TopDownMerge merge;
	merge.Sort(my_vector);

	cout << "        ";
	Print(my_vector, 0, my_vector.size() - 1);
}
