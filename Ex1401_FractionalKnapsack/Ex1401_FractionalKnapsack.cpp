#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Item
{
	double value;
	double weight;
};

void Print(vector<Item>& items)
{
	for (auto i : items)
	{
		// (가성비 = value/weight = ratio, value, weight)
		cout << "(" << i.value / i.weight << ", " << i.value << ", " << i.weight << ") ";
	}
	cout << endl;
}

bool Compare(struct Item a, struct Item b)
{
	double ratio_a = a.value / a.weight;
	double ratio_b = b.value / b.weight;

	return ratio_a > ratio_b; // ratio가 큰 쪽이 앞으로 오도록 정렬
}

double FractionalKnapsack(vector<Item> items, double W)
{
	sort(items.begin(), items.end(), Compare); // Compare() 함수를 이용해서 정렬

	cout << "W = " << W << endl;
	Print(items);

	double vsum = 0.0;

	for (auto& i : items)
	{
		// TODO:
		// if(W > 0){
		// 	if(i.weight <= W){ //가성비가 가장 높은 아이템 순서대로 최대한 가져옴,
		// 		vsum += i.value;
		// 		W -= i.weight;
		// 		i.weight = 0;
		// 	}
		// 	else{//공간 한계로 해당 아이템을 다 못가져오는 경우 일부만 가져옴
		// 		vsum += W * (i.value / i.weight);
		// 		i.weight -= W;
		// 		W = 0;
		// 	}
		// 	cout << "W = " << W << endl;
		// 	Print(items);
		// }

		double takes = min(W,i.weight);
		vsum += takes * (i.value / i.weight);
		i.weight -= takes;
		W -= takes;
	}

	return vsum;
}

int main()
{
	double W = 6.0;

	vector<Item> items = { { 10, 1 }, { 28, 4 }, { 12, 2 }, { 12, 3 } };

	cout << FractionalKnapsack(items, W) << endl;

	return 0;
}
