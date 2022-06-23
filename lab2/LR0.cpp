#include<iostream>
#include<malloc.h>  
using namespace std;
#define MAX 20
int table[16][13]=
{
	{12,-1,-1,-1,-1,13,-1,-1,1,-1,2,-1,7},
	{-1,-1,-1,-1,-1,-1,-1,30,-1,-1,-1,-1,-1},
	{-1,4,4,-1,-1,-1,23,30,-1,3,-1,-1,-1},
	{21,21,21,21,21,21,21,21,-1,-1,-1,-1,-1},
	{12,-1,-1,-1,-1,13,-1,-1,-1,-1,5,-1,7},
	{-1,4,4,-1,-1,-1,23,30,-1,6,-1,-1,-1},
	{22,22,22,22,22,22,22,22,-1,-1,-1,-1,-1},
	{-1,26,26,9,9,-1,26,30,-1,-1,-1,8,-1},
	{24,24,24,24,24,24,24,24,-1,-1,-1,-1,-1},
	{12,-1,-1,-1,-1,13,-1,-1,-1,-1,-1,-1,10},
	{-1,26,26,9,9,-1,26,30,-1,-1,-1,11,-1},
	{25,25,25,25,25,25,25,25,-1,-1,-1,-1,-1},
	{27,27,27,27,27,27,27,27,-1,-1,-1,-1,-1},
	{12,-1,-1,-1,-1,13,-1,-1,14,-1,2,-1,7},
	{-1,-1,-1,-1,-1,-1,15,-1,-1,-1,-1,-1,-1},
	{28,28,28,28,28,28,28,28,-1,-1,-1,-1,-1}
};

struct rule{
	char x;
	int y;
}r[8]={{'E',2},{'X',3},{'X',0},{'T',2},{'Y',3},{'Y',0},{'F',1},{'F',3}};

char index_char[13]={'i','+','-','*','/','(',')','#','E','X','T','Y','F'};

typedef struct{
	int stack[MAX];
	int top;
	int num;
}status;
void init_stack(status*p)//状态栈的初始化 
{
	if(!p)
		cout<<"初始化状态栈出错！\n";
	p->top=-1;
	p->num = 0;
}
void push(status*p,int x)//入栈 
{
	if(p->top<MAX-1)//检测栈是否已满 
	{
		if(x > 9)p->num += 2;
		else{p->num++;}
		p->top++;//未满则推送入栈 
		p->stack[p->top]=x;
	}
	else cout<<"\n状态栈溢出！\n";//满则显示溢出 
}
int pop(status*p)//出栈 
{
	int x;
	if(p->top!=0)//检测栈是否已空 
	{
		x=p->stack[p->top];//为空，则将栈顶的x推送出栈
		if(x > 9)p->num -= 2; 
		else{p->num--;}
		p->top--;
		return x;
	}
	else//空，则显示状态栈已空 
	{
		cout<<"\n状态栈1空!\n";
		return 0;
	}
}
int get_top(status*p)
{
	int x;
	if(p->top!=-1)
	{
		x=p->stack[p->top];
		return x;
	}
	else
	{
		cout<<"\n状态栈2空!\n";
		return 0;
	}
}
void out_stack(status*p)
{
	int i;
	if(p->top<0)
	{
		cout<<"\n状态栈3空!\n";
	}
	for(i=0;i<=p->top;i++)
	{
		cout<<p->stack[i];
	}
}
 
typedef struct{
	char stack[MAX];
	int top;
}symbol_instr;
void init_stack(symbol_instr*p)//符号栈、输入串初始化 
{
	if(!p)
		cout<<"\n初始化状态栈出错！\n";
	p->top=-1;
}
void push(symbol_instr*p,char x)//入栈 
{
	if(p->top<MAX-1)//检测栈是否已满 
	{
		p->top++;//未满，则将x送入栈中 
		p->stack[p->top]=x;
	}
	else cout<<"\n状态栈溢出！\n";//满，则显示符号栈或输入串溢出 
}
char pop(symbol_instr*p)
{
	char x;
	if(p->top!=-1)
	{
		x=p->stack[p->top];
		p->top--;
		return x;
	}
	else
	{
		cout<<"符号栈1空!\n";
		return 0;
	}
}
char get_top(symbol_instr*p)
{
	char x;
	if(p->top!=-1)
	{
		x=p->stack[p->top];
		return x;
	}
	else
	{
		cout<<"符号栈2空!\n";
		return 0;
	}
}
void out_stack1(symbol_instr*p)
{
	int i;
	if(p->top<0)
	{
		cout<<"符号栈3空!\n";
	}
	for(i=0;i<=p->top;i++)
	{
		cout<<p->stack[i];
	}
}
void out_stack2(symbol_instr*p)
{
	int i;
	if(p->top<0)
	{
		cout<<"符号栈4空!\n";
	}
	for(i=p->top;i>=0;i--)
	{
		cout<<p->stack[i];
	}
}
void print(status*status_p,symbol_instr*symbol_p,symbol_instr*instr_p)
{
	int i;
	out_stack(status_p);
	for(i=0;i<20-status_p->num;i++)
	cout<<" ";
	out_stack1(symbol_p);
	for(i=0;i<20-symbol_p->top;i++)
	cout<<" ";
	out_stack2(instr_p);
	cout<<endl;
 } 
 
int findA(char c){
	if(c > 64 && c < 123)return 0;
	switch (c) {
	case '+':
		return 1;
	case '-':
		return 2;
	case '*':
		return 3;
	case '/':
		return 4;
	case '(':
		return 5;
	case ')':
		return 6;
	case '#':
		return 7;
	case 'E':
	 	return 8;
	case 'X':
		return 9;
	case 'T':
		return 10;
	case 'Y':
		return 11;
	case 'F':
		return 12;
	default:
		return -1;
	}
}

int goto_char(status*status_p,symbol_instr*instr_p){
 	char x;
 	int y,z;
 	x=get_top(instr_p);
 	y=get_top(status_p);
 	z=findA(x);
	/*cout << x << endl;
	cout << y << z << ":" << table[y][z] << endl;*/
 	return table[y][z];
 }
 
void choose(status* status_p,int a,char x){//选择规约状态
	if(x == 'E'){
		if(a == 13)push(status_p,14);
		else{push(status_p,1);}
	}
	if(x == 'T'){
		if(a == 4)push(status_p,5);
		else{push(status_p,2);}
	}
	if(x == 'X'){
		if(a == 5)push(status_p,6);
		else{push(status_p,3);}
	}
	if(x == 'Y'){
		if(a == 10)push(status_p,11);
		else{push(status_p,8);}
	}
	if(x == 'F'){
		if(a == 9)push(status_p,10);
		else{push(status_p,7);}
	}
}

void action(status*status_p,symbol_instr*symbol_p,symbol_instr*instr_p)
{
 	int i,j,x;
 	char a;
 	i=goto_char(status_p,instr_p);
 	if(i==-1)
 	cout<<"归约出错!\n";
 	if(i==30){
	 	cout<<"归约成功!\n";
	}
	 if(i>=0&&i<=17)
 	{
 		push(status_p,i);
 		a=pop(instr_p);
 		push(symbol_p,a);
 		print(status_p,symbol_p,instr_p);
 		action(status_p,symbol_p,instr_p);
	}
	if(i>=21&&i<=28)
	{
	 	x=r[i-21].y;
	 	int c;
	 	for(j=0;j<x;j++)
	 	{
	 		pop(status_p);
	 		pop(symbol_p);
		}
		c = get_top(status_p);
		push(symbol_p,r[i-21].x);
		choose(status_p,c,r[i-21].x);
		print(status_p,symbol_p,instr_p);
		action(status_p,symbol_p,instr_p);
	}
}
 //a*(a+b)-c/(c-d)#
int main()
{
 	char x;
 	status*status_p;//状态栈 
 	symbol_instr*symbol_p,*instr_p;//符号栈、输入串
 	/*分配长度为sizeof(ststus)字节的内存块 
    如果分配成功则返回指向被分配内存的指针，否则返回空指针NULL。 
    当内存不再使用时，应使用free()函数将内存块释放。*/
 	status_p=(status*)malloc(sizeof(status));
 	symbol_p=(symbol_instr*)malloc(sizeof(symbol_instr));
 	instr_p=(symbol_instr*)malloc(sizeof(symbol_instr));
 	init_stack(status_p);
 	init_stack(symbol_p);
 	init_stack(instr_p);
 	push(status_p,0);//为状态栈送入初始状态 0 
 	push(symbol_p,'#');//为符号栈送入栈底符号 # 
 	cout<<"请输入要归约的输入串，以'#'字符结束！\n"; 
	do
	{
	 	x=getchar();
	 	if(x!=' '||x!='\t'||x!='\n')//当输入字符不为空格、回车、制符表时，存入栈中 
	 		push(symbol_p,x);
	}while(x!='#');
	while(symbol_p->top!=0)//当栈不为空时 
	{
	 	x=pop(symbol_p);//从符号栈读取 
	 	push(instr_p,x);//送入输入串 
	}
	cout<<"\n";
	cout<<"\n状态栈              符号栈                输入串\n";
	print(status_p,symbol_p,instr_p);
	action(status_p,symbol_p,instr_p);
	return 0;
}
