#include<iostream>
#include<stdio.h>
#include<string.h>
#include<string>


using namespace std;

int row = 0;
int flag = 0;
int flag1 = 0;
char arr[20];

const char h[10]= "#include";
FILE *fin;
FILE *fout;
char ah;
const char keyword[13][10] = {"main","if","else","do","while","for","switch","case","int","double","float","long","void"};
//const char header[7][10] = {"iostream","iomanip","algorithm","string","vector","queue","stack"};

void init(){
	for(int i = 0;i < 10;++ i){
		arr[i] = NULL;
	}
}

int token(){
	init();
	if(flag == 0)ah = getc(fin);
	flag = 1;
	while(ah == ' ' || ah == '\t' || ah == '\n'){
		if(ah = '\n'){
			row++;
			//cout << row << endl;
		}
		ah = getc(fin);
	}
	int num = 0;
	if(flag1 == 1){
		if(ah != '<' && ah != '"'){
			//cout << ah << endl;
			return -2;
		}
		arr[num++] = ah;
		ah = getc(fin);
		if(ah >= 'a' && ah <= 'z' || ah >= 'A' && ah <= 'Z'){
			while(ah >= 'a' && ah <= 'z' || ah >= 'A' && ah <= 'Z' || ah == '.'){
				arr[num++] = ah;
				ah = getc(fin);
			}
			arr[num++] = ah;
			if(ah != '>' && ah != '"')return -2;
			ah = getc(fin);flag1 = 0;
			//arr[num++] = '\0';	
			return 41;
		}
	}	//cout << flag1 << endl;
	
	if(ah >= 'a' && ah <= 'z' || ah >= 'A' && ah <= 'Z'){
		while(ah >= 'a' && ah <= 'z' || ah >= 'A' && ah <= 'Z' || ah >= '0' && ah <= '9'){
			arr[num] = ah;
			num++;
			ah = getc(fin);
		}
		arr[num++] = '\0';
		for(int i = 0;i < 13;++ i){
			if(strcmp(arr,keyword[i]) == 0){
				//cout << i << endl; 
				return i;
			}
		}
		return 13;
	}
	if(ah >= '0' && ah <= '9'){
		while(ah >= '0' && ah <= '9' || ah == '.'){
			arr[num++] = ah;
			ah = getc(fin);
		}
		return 14;
	}
	else{
		arr[num++] = ah;
		switch(ah){
			case '(':
				ah = getc(fin);
				return 15;
			case ')':
				ah = getc(fin);
				return 16;
			case '{':
				ah = getc(fin);
				return 17;
			case '}':
				ah = getc(fin);
				return 18;
			case '+':
				ah = getc(fin);
				if(ah == '+'){
					arr[num++] = ah;
					flag = 0;
					return 20;
				}
				if(ah == '='){
					arr[num++] = ah;
					flag = 0;
					return 38;
				} 
				return 19;
			case '-':
				ah = getc(fin);
				if(ah == '-'){
					arr[num++] = ah;
					flag = 0;
					return 40;
				}
				if(ah == '='){
					arr[num++] = ah;
					flag = 0;
					return 39;
				}
				return 21;
			case '*':
				ah = getc(fin);
				if(ah == '/'){
					arr[num++] = ah;
					flag = 0;
					return 22;
				}
				return 23;
			case '/':
				ah = getc(fin);
				if(ah == '*'){
					arr[num++] = ah;
					ah = getc(fin);
					while(ah != '*'){
						ah = getc(fin);
						if(ah == '*'){
							arr[num++] = ah;
							ah = getc(fin);
							if(ah == '/'){
								arr[num++] = ah;
								break;
							}
						}
					}
					flag = 0;
					return 25;
				}
				if(ah == '/'){
					while(ah != '\n'){
						arr[num++] = ah;
						ah = getc(fin);
					}
				}
				return 24;
			case '=':	
				ah = getc(fin);
				if(ah == '='){
					arr[num++] =ah;
					ah = getc(fin);
					return 27;
				}
				return 26;
			case '>':
				ah = getc(fin);
				if(ah == '='){
					arr[num++] = ah;
					ah = getc(fin);
					return 29;
				}
				return 28;
			case '<':
				ah = getc(fin);
				if(ah == '='){
					arr[num++] = ah;
					ah = getc(fin);
					return 31;
				}
				return 30;
			case ';':
				ah = getc(fin);
				return 32;
			case '"':
				//arr[num++] = ah;
				ah = getc(fin);
				while(ah >= ' ' && ah <= '~' && ah != '"'){
					arr[num++] = ah;
					ah = getc(fin);
				}
				arr[num++] = ah;
				ah = getc(fin);
				return 33;
			case '!':
				ah = getc(fin);
				if(ah == '='){
					arr[num++] = ah;
					ah = getc(fin);
					return 35;
				}
				return 34;
			case '#':
				ah = getc(fin); 
				if(ah >= 'a' && ah <= 'z' || ah >= 'A' && ah <= 'Z'){
					while(ah >= 'a' && ah <= 'z' || ah >= 'A' && ah <= 'Z' || ah >= '0' && ah <= '9'){
						//cout << arr << endl;
						arr[num++] = ah;
						ah = getc(fin);
						//cout << ah << endl;
					}
				}
				arr[num++] = '\0';
				//cout << arr << endl;
				if(strcmp(arr,h) == 0){
					flag1 = 1;
					return 41;
				}
				return 36;
			case ',':
				ah = getc(fin);
				return 37;
			case EOF:
				return -1; 
			default:
				ah = getc(fin);
				return -2;
		}
	}
}

void getword(){
	int temp = 0;
	while(true){
		temp = token();
		if(temp == -1){
			break;
		}
		if(temp == -2){
			fprintf(fout,"第%d行出现错误\n",row); 
		}
		else{
			cout << temp << "," << arr << endl;
			fprintf(fout,"%d , %s\n",temp,arr);
		}
	}
}

int main(){
	fout = fopen("token.txt","w");
	fin = fopen("complier.c","r");
	getword();
	return 0;
} 
