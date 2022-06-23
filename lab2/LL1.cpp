#include<iostream>
#include<stack>
#include<string>

using namespace std;

string s;
char VN[5] = {'E','X','T','Y','F'};//E'用"X"代替，T'用"Y"代替  
char VT[8] = {'i','+','-','*','/','(',')','#'};
string analyse[6][9] = {
	" ","i", "+","-","*","/","(", ")","#",
	"E","TX"," "," "," "," ","TX"," "," ",
	"X"," ","+TX","-TX"," "," "," ",".",".",
	"T","FY"," "," "," "," ","FY"," "," ",
	"Y"," ",".",".","*FY","/FY"," ",".",".",
	"F","i"," "," "," "," ","(E)"," "," ",
};//空集用"."代替，空格表示不匹配 

int find(char c){
	switch (c) {
	case 'E':
		return 1;
	case 'X':
		return 2;
	case 'T':
		return 3;
	case 'Y':
		return 4;
	case 'F':
		return 5;
	case 'i':
		return 1;
	case '+':
		return 2;
	case '-':
		return 3;
	case '*':
		return 4;
	case '/':
		return 5;
	case '(':
		return 6;
	case ')':
		return 7;
	case '#':
		return 8;
	default:
		return 0;
	}
}

int findA(char c){
	if(c > 64 && c < 123)return 1;
	switch (c) {
	case '+':
		return 2;
	case '-':
		return 3;
	case '*':
		return 4;
	case '/':
		return 5;
	case '(':
		return 6;
	case ')':
		return 7;
	case '#':
		return 8;
	default:
		return 0;
	}
}

void LL(){
	stack<char> as;
	as.push('#');
	as.push('E');
	int j = 0;
	int temp;
	while(true){
		char c = as.top();
		temp = 0;
		//有终结符 
		for(int i = 0;i < 8;++ i){
			if(VT[i] == c){
				if(s[j] == '#' && c == '#'){
					cout << "success!" << endl;
					return;
				}
				if(findA(s[j]) == find(c)){
					as.pop();
					cout << '"' << s[j] << '"' << " match successful!" << endl;
					j++;
					temp = 1;
					
					break;
				}
				else{
					cout << "In input string[" << j << "]: " << endl;
					cout << "Terminator " << s[j] << " does not exist" << endl;
					return; 
				}
			}
		}
		if(temp == 1){
			continue;
		}
		int a = find(c);
		int b = findA(s[j]);
		if(b == 0){
			cout << "In input string[" << j << "]: " << endl;
			cout << "Terminator " << s[j] << " does not exist" << endl;
			return; 
		}
		as.pop();
		if(analyse[a][b] == " "){
			string res = s.substr(0,j);
			cout << res << endl;
			cout << "Match error!" << endl;
			return;
		}
		int len = analyse[a][b].length();
		cout << "push: " << analyse[a][b] << endl;
		for(int i = len-1;i >= 0;-- i){
			if(analyse[a][b][i] == '.')continue;
			as.push(analyse[a][b][i]);
			//cout << analyse[a][b][i] << endl;
		}
		
	} 
}

int main(){
	cout << "请输入要规约的字符串！" << endl;
	cin >> s;
	int length = s.length();
	s[length] = '#';
	LL();
}
