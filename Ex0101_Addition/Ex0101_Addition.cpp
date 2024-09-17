#include <string>
#include <vector>
#include <iostream>

using namespace std;
/*
string Add(string str1, string str2)
{
	// TODO:
	// 두 피연산자의 자릿수가 다른 경우, 짧은 수의 최상위 자리까지 
	//더한 뒤에 어떻게 처리?? 
	// 1. 짧은 수의 자릿수만큼 반복 -> 긴 수의 자릿수 - 짧수자리수 만큼 또 반복
	// 2. 짧은 수의 상위 자리에 0을 채워 두 수의 길이를 맞춰주고 한 번에 계산
	//매 반복 시 디버깅을 위한 출력도 따로 해 주면 시간 단축 가능할 듯
	int carry = 0, residue = 0;
	int partial_sum = 0;
	size_t n = 0;
	string longer, shorter;
	string result;

	if( str1.size() > str2.size() ){
		longer = str1;
		shorter = str2;
	}
	else{
		longer = str2;
		shorter = str1;
	}
	
	for( n = 0; n < shorter.size(); n++){
		partial_sum = carry + (longer[longer.size()-(n+1)] - '0') + (shorter[shorter.size()-(n+1)] - '0');
		carry = partial_sum / 10;
		residue = partial_sum % 10;

		result = to_string(residue) + result;

		partial_sum = 0;
	}
	//더 긴 피연산자와 캐리 덧셈
	for( ; n < longer.size();n++){
		partial_sum = carry + (longer[longer.size()-(n+1)] - '0');
		carry = partial_sum / 10;
		residue = partial_sum % 10;

		result = to_string(residue) + result;

		partial_sum = 0;
	}
	if(carry)
		result = to_string(carry) + result;
	return result;
}
*/
string Add(string str1, string str2)
{
	size_t len = max(str1.size(),str2.size());
	string result(len,'0');

	//자릿수 맞춰주기
	str2 = string( len-str2.size(), '0') + str2;
	str1 = string( len-str1.size(), '0') + str1;
	
	
	int carry = 0, partial_sum = 0, residue = 0;
	for(int n = len-1; n >= 0; n--){
		partial_sum = carry + (str1[n] - '0') + (str2[n] - '0');
		carry = partial_sum / 10;
		residue = partial_sum % 10;

		result[n] = residue + '0';
		//중간과정 출력
		cout << "partial sum : " << partial_sum << " carry : " << carry << " result : " << result << "\n" ;
	}
	if(carry)
		result = to_string(carry) + result;

	return result;
}



int main()
{
	vector<vector<string>> tests = {
		{"12", "34", to_string(12 + 34)}
		, {"123", "45", to_string(123 + 45)}
		, {"54544", "44545", to_string(54544 + 44545)}
		, {"5555", "55", to_string(5555 + 55)}
		, {"5555", "5555", to_string(5555 + 5555)}
		, {"9823471235421415454545454545454544", "1714546546546545454544548544544545", "11538017781967960909090003089999089"}
	};

	for (const auto& t : tests)
	{
		const string str1 = t[0];     // "12"
		const string str2 = t[1];     // "34"
		const string expected = t[2]; // "46"

		cout << str1 << " + " << str2 << " = " << expected << endl;

		const string result = Add(str1, str2);

		cout << result << " " << expected << " ";

		if (result == expected)
			cout << "OK" << endl;
		else {
			cout << "Not OK" << endl;
			exit(-1);
		}
		cout << endl << endl;
	}

	cout << "Congratulations. All OK!" << endl;

	return 0;
}