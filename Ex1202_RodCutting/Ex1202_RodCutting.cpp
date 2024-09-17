#include <iostream>
#include <math.h>
#include <vector>
#include <iomanip>
using namespace std;

// CLRS 4판 14.1 Rod Cutting

int RecurCutRod(const vector<int>& prices, int length)
{
	if (length == 0)
		return 0; // return length* prices[0];

	int max_price = numeric_limits<int>::min();
	int price;

	for (int i = 1; i <= length; i++)
	{
		// TODO:
		price = prices[i] + RecurCutRod(prices,length-i);
		if(price > max_price)
			max_price = price;
	}

	return max_price;
}

int MemoizedCutRodHelper(const vector<int>& prices, int length, vector<int>& memo)
{
	if (memo[length] >= 0)
		return memo[length];

	// TODO:
	//아래 코드는 length가 1이상일 때 유효함. 
	//위의 조건문에 의해 length는 0이면 return돼서 ㄱㅊ

	int max_price = numeric_limits<int>::min();
	int price;

	for(int i = 1; i <= length; i++){
		price = prices[i] + MemoizedCutRodHelper(prices,length-i,memo);
		if(price > max_price)
			max_price = price;
	}
	memo[length] = max_price;

	for (auto& t : memo) cout << setw(3) << t; cout << endl;

	return memo[length];
}

int MemoizedCutRod(const vector<int>& prices, int length)
{
	vector<int> memo(length + 1, -1);
	memo[0] = 0;

	return MemoizedCutRodHelper(prices, length, memo);
}

int BottomUpCutRod(const vector<int>& prices, int length)
{
	vector<int> table(length + 1, -1); // 가격은 음수가 될 수 없으니까 디버깅 편의를 위해 -1로 초기화
	table[0] = 0; // length* prices[0];

	for (int j = 1; j <= length; j++)
	{
		int max_price = numeric_limits<int>::min();

		// TODO:
		for(int i = 1; i <= j; i++){
			if(prices[i] + table[j-i] > max_price)
				max_price = prices[i] + table[j-i];
		}
		table[j] = max_price;

		for (auto& t : table) cout << setw(3) << t; cout << endl;
	}

	return table[length];
}

// 어떻게 자르는지까지 출력하는 버전 (실행 예시 참고)
int ExtendedBottomUpCutRod(const vector<int>& prices, int length)
{
	vector<int> table(length + 1, -1); // 가격은 음수가 될 수 없으니까 디버깅 편의를 위해 -1로 초기화
	table[0] = 0; // length* prices[0];
	vector<int> cut(length+1,-1);	//길이 n철근은 cut[n]길이 하나와 n-cut[n]을 최적으로 자른 도막들로 나눠짐
	
	// TODO:
	for (int j = 1; j <= length; j++)
	{
		int max_price = numeric_limits<int>::min();
		// TODO:
		for(int i = 1; i <= j; i++){
			if(prices[i] + table[j-i] > max_price){
				cut[j] = i;
				max_price = prices[i] + table[j-i];
			}//가장 마지막에 실행된 if문에서 cut[j]에 들어간 i가
			//길이 j철근을 최적으로 자르기 위한 partition임
			//길이 j철근 -> 길이 i짜리와 j-i를 최적으로 자른 도막들
		}
		table[j] = max_price;
	}

	cout << "split : ";
	int remain = length;
	while(remain > 0){
		cout << cut[remain] << '(' << prices[cut[remain]] << ") ";
		remain = remain - cut[remain];
	}
	
	cout << '\n';
	
	return table[length];
}

int main()
{
	// Length:                  0  1  2  3  4   5   6   7   8   9  10
	//vector<int> price_table = { 0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30 };
	vector<int> price_table = { 0, 3, 5, 8, 9, 10, 17, 17, 20, 24, 30 };

	// 주의: price_table은 문제에서 주어진 조건입니다. 메모가 아닙니다.

	cout << "Naive recursion" << endl;
	for (int length = 0; length < price_table.size(); length++)
	{
		int revenue = RecurCutRod(price_table, length);
		cout << "Optimal revenue for length " << length << ": " << revenue << endl;
	}
	cout << endl;

	cout << "TopDown with Memoization" << endl;
	cout << "Optimal revenue for length " << 10 << ": \n" << MemoizedCutRod(price_table, 10) << endl;
	cout << endl;

	cout << "BottomUpTabulation" << endl;
	cout << "Optimal revenue for length " << 10 << ": \n" << BottomUpCutRod(price_table, 10) << endl;
	cout << endl;

	for (int length = 0; length < price_table.size(); length++)
	{
		cout << "Length: " << length << endl;
		int revenue = ExtendedBottomUpCutRod(price_table, length);
		cout << "Optimal revenue: " << revenue << endl;
	}

	return 0;
}
