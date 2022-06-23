#include<iostream>
#include<stack>
#include<string>

using namespace std;

string s;
char VN[5] = {'E','X','T','Y','F'};//X代表E'，Y代表T'  
char VT[8] = {'i','+','-','*','/','(',')','#'};
int symbol = 65;
//char ACTION[5] = {'A','S','M','D','P'};
string analyse[6][9] = {
	" ","i", "+","-","*","/","(", ")","#",
	"E","TX"," "," "," "," ","TX"," "," ",
	"X"," ","+TAX","-TSX"," "," "," ",".",".",
	"T","FY"," "," "," "," ","FY"," "," ",
	"Y"," ",".",".","*FMY","/FDY"," ",".",".",
	"F","iP"," "," "," "," ","(E)"," "," ",
};//"."代表空集，" "代表不匹配
//A代表加法，S代表减法，M代表乘法，D代表除法，P代表入栈操作
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

void sym(){
	symbol++;
	if(symbol > 90)symbol = 65;
}

void LL(){
	stack<char> SYN;//语法栈
	stack<char> SEM;//语义栈
	stack<string> QT;//四元式区
	SYN.push('#');
	SYN.push('E');
	char v;
	string a,v1,v2;
	int j = 0;
	int temp;
	char var;
	while(true){
		char c = SYN.top();
		temp = 0;
		//出现终结符
		for(int i = 0;i < 8;++ i){
			if(VT[i] == c){
				if(s[j] == '#' && c == '#'){
					cout << "success!" << endl;
					return;
				}
				if(findA(s[j]) == find(c)){
					SYN.pop();
					var = s[j];
					j++;
					temp = 1;
					break;
				}
				else{
					cout << "Error!" << endl;
					return; 
				}
			}
		}
		
		switch (c)
		{
		
		case 'P':
		{
			SEM.push(var);
			SYN.pop();
			cout << "push: " << var << endl;
			temp = 2;
			break;
		}
		case 'A':
		{
			v1.assign(1,SEM.top());
			SEM.pop();
			v2.assign(1,SEM.top());
			SEM.pop();
			v = symbol;
			a = "(/," + v1 + "," + v2 + ",";
			a.assign(1,v);
			a.assign(1,')');
			cout << "(+," << v1 << "," << v2 << "," << v << ")" << endl;
			sym();
			QT.push(a);
			SEM.push(v);
			SYN.pop();
			temp = 2;
			break;
		}
		case 'S':
		{
			v1.assign(1,SEM.top());
			SEM.pop();
			v2.assign(1,SEM.top());
			SEM.pop();
			v = symbol;
			a = "(/," + v1 + "," + v2 + ",";
			a.assign(1,v);
			a.assign(1,')');
			cout << "(-," << v1 << "," << v2 << "," << v << ")" << endl;
			sym();
			QT.push(a);
			SEM.push(v);
			SYN.pop();
			temp = 2;
			break;
		}
		case 'M':
		{
			v1.assign(1,SEM.top());
			SEM.pop();
			v2.assign(1,SEM.top());
			SEM.pop();
			v = symbol;
			a = "(/," + v1 + "," + v2 + ",";
			a.assign(1,v);
			a.assign(1,')');
			cout << "(*," << v1 << "," << v2 << "," << v << ")" << endl;
			sym();
			QT.push(a);
			SEM.push(v);
			SYN.pop();
			temp = 2;
			break;
		}
		case 'D':
		{
			v1.assign(1,SEM.top());
			SEM.pop();
			v2.assign(1,SEM.top());
			SEM.pop();
			v = symbol;
			a = "(/," + v1 + "," + v2 + ",";
			a.assign(1,v);
			a.assign(1,')');
			cout << "(/," << v1 << "," << v2 << "," << v << ")" << endl;
			sym();
			QT.push(a);
			SEM.push(v);
			SYN.pop();
			temp = 2;
			break;
		}
		default:
			break;
		}; 
		//cout << s[j] << endl;
		if(temp == 1 || temp == 2){
			continue;
		}
		int d = find(c);
		int b = findA(s[j]);
		SYN.pop();
		if(analyse[d][b] == " "){
			cout << "Error!" << endl;
			return;
		}
		int len = analyse[d][b].length();
		cout << d << "," << b << "=" << analyse[d][b] << endl;		
		for(int i = len-1;i >= 0;-- i){
			if(analyse[d][b][i] == '.')continue;
			SYN.push(analyse[d][b][i]);
			//cout << analyse[a][b][i] << endl;
		}		
	} 
}

int main(){
	cout << "请输入要归约的字符串!(用#结尾)" << endl;
	cin >> s;
	LL();
}

