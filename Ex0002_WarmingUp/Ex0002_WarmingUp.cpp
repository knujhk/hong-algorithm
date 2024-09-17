#include <iostream>
#include <string>
using namespace std;

int main()
{
	// swap
	int a(1);
	int b(3);

	a = a ^ b ;
	b = a ^ b ; 
	a = a ^ b ;

	cout << "결과" << a << b << "\n";

	// 문제 1. 10진수 -> 2진수
	{
		int decimal = 105;
		string binary;

		//TODO:
		int r;
		while(decimal>0){
			r = decimal % 2;	//가장 먼저 나오는 r이 이진수의 lsb
			decimal /= 2; 
			binary = string(1,char(r + 48)) + binary; // 0은 아스키 코드로 48 -> char(r + '0') 도 동일
													  
		}

		cout << binary << endl; // 1101001
	}

	// 문제 2. 문자열 뒤집기
	{
		string input = "Hello, World!";

		// // TODO:
		// string temp;
		// for(auto c : input){
		// 	temp = c + temp;
		// }
		// input = temp;
		// cout << input << endl; // !dlroW ,olleH

		// size_t len = input.size();
		// for(size_t i = 0 ; i < (len/2) ; i++){
		// 	swap(input[i],input[(len-1)-i]);
		// }
		// cout << input << endl;

		int left = 0;
		int right = input.size() - 1;
		while(left < right){
			swap(input[left],input[right]);
			left++;
			right--;
		}
		cout << input << endl;
	}

	// 문제 3. 모든 자리 다 더하기
	{
		string n = "789789";

		// TODO:
		int sum = 0;
		while(n.size() > 1){
			for(char c : n){
				sum += c - '0';
			}
			n = to_string(sum);
			cout << n << endl;
			//문자열 -> 정수 : stoi
			//문자 - > 정수 : int - '0'
			//정수 -> 문자열 : to_string(int)
			//정수 -> 문자 : int + '0'
			//sum을 문자열로
			sum = 0;
		}

		cout << "result : " << n << endl;
	}

	return 0;
}
