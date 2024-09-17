#include <string>
#include <vector>
#include <iostream>

using namespace std;

string Add(string str1, string str2)
{
	size_t len;
	len = max(str1.size(),str2.size());
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
		//cout << "partial sum : " << partial_sum << " carry : " << carry << " result : " << result << "\n" ;
	}
	if(carry)
		result = to_string(carry) + result;

	return result;
}

string Multiply(string str1, string str2)
{
	//n자리수 * n자리수 -> 내부 곱셈연산은 n^2번, 결과의 자리수는 최대 2n
	// TODO:
	//edge case
	if(!str1.size() || !str2.size())
		return "0";

	//길이 같게 만들어주기
	int N = max(str1.size(),str2.size());
	str1.insert(0,N-str1.size(),'0');
	str2.insert(0,N-str2.size(),'0');

	//부분합 구해서 더하기
	string result(2*N,'0');
	int carry = 0;
	int sum = 0;
	int k = 0;

	for(int i = N-1; i >= 0; i--){	
		carry = 0;
		int n2 = str2[i] - '0';
		for(int j = N-1; j >= 0; j--){
			k = i + j+1;//결과 저장될 곳의 인덱스
			int n1 = str1[j] - '0';
			sum = (result[k] - '0') + n1*n2 + carry;
			carry = sum / 10;
			result[k] = (sum % 10) + '0';		
			cout  << "n1 : " << n1 << " n2 : " << n2 << " K : " << k << " result : " << result << "\n" ;
		}
		// int m = 1;
		// while(carry){
		// 	sum = result[k-m] - '0' + carry;
		// 	carry = sum / 10;
		// 	result[k-m] = (sum % 10) + '0';
		// 	m++;
		// }
		result[k-1] = carry + '0';
		cout  << "carry : " << carry << " result : " << result << "\n" ;
	}

	// for (int i = N - 1; i >= 0; i--) // 역순
    // {
    //     int carry = 0;
    //     int n1 = str1[i] - '0';

    //     int k = N + i; // 결과를 저장할 위치의 인덱스
    //     for (int j = N - 1; j >= 0; j--) // 역순
    //     {
    //         int n2 = str2[j] - '0';
    //         int sum = n1 * n2 + int(result[k] - '0') + carry;
    //         carry = sum / 10;
    //         result[k] = char(sum % 10 + '0'); // 저장할때는 다시 문자로
    //         k -= 1; // <- k가 하나씩 감소

    //         // Trace (변수에 저장된 값들의 변화를 추적)
    //         cout << n1 << " " << n2 << " " << carry << " " << result << endl;
    //     }

    //     // 마지막에는 carry만
    //     result[k] = char(carry + '0');
    // }
	//출력 형태 정리
	// 불필요한 '0' 제거 (예: "078" -> "78")
	// TODO:
	k = 0;
	while(result[k] == '0'){
		k++;
	}
	result = result.substr(k,2*N-k);

	return result;
}

int main()
{
	vector<vector<string>> tests = {
		{"12", "34", std::to_string(12 * 34)},
		{"123", "45", std::to_string(123 * 45)},
		{"5555", "55", std::to_string(5555 * 55)},
		{"5555", "5555", std::to_string(5555 * 5555)},
		{"98234712354214154", "171454654654655", "16842798681791158832220782986870"}
		 , {"9823471235421415454545454545454544", "1714546546546545454544548544544545", "16842798681791114273590624445460185389471221520083884298838480662480"}
	};

	for (const auto& t : tests)
	{
		const string str1 = t[0];
		const string str2 = t[1];
		const string expected = t[2];

		cout << str1 << " * " << str2 << " = " << expected << endl;

		const string result = Multiply(str1, str2);

		cout << result << " " << expected << " ";

		if (result == expected)
			cout << "OK";
		else {
			cout << "Not OK";
			exit(-1);
		}
		cout << endl << endl;
	}

	cout << "Congratulations. All OK!" << endl;

	return 0;
}
