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
void init_stack(status*p)//״̬ջ�ĳ�ʼ�� 
{
	if(!p)
		cout<<"��ʼ��״̬ջ����\n";
	p->top=-1;
	p->num = 0;
}
void push(status*p,int x)//��ջ 
{
	if(p->top<MAX-1)//���ջ�Ƿ����� 
	{
		if(x > 9)p->num += 2;
		else{p->num++;}
		p->top++;//δ����������ջ 
		p->stack[p->top]=x;
	}
	else cout<<"\n״̬ջ�����\n";//������ʾ��� 
}
int pop(status*p)//��ջ 
{
	int x;
	if(p->top!=0)//���ջ�Ƿ��ѿ� 
	{
		x=p->stack[p->top];//Ϊ�գ���ջ����x���ͳ�ջ
		if(x > 9)p->num -= 2; 
		else{p->num--;}
		p->top--;
		return x;
	}
	else//�գ�����ʾ״̬ջ�ѿ� 
	{
		cout<<"\n״̬ջ1��!\n";
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
		cout<<"\n״̬ջ2��!\n";
		return 0;
	}
}
void out_stack(status*p)
{
	int i;
	if(p->top<0)
	{
		cout<<"\n״̬ջ3��!\n";
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
void init_stack(symbol_instr*p)//����ջ�����봮��ʼ�� 
{
	if(!p)
		cout<<"\n��ʼ��״̬ջ����\n";
	p->top=-1;
}
void push(symbol_instr*p,char x)//��ջ 
{
	if(p->top<MAX-1)//���ջ�Ƿ����� 
	{
		p->top++;//δ������x����ջ�� 
		p->stack[p->top]=x;
	}
	else cout<<"\n״̬ջ�����\n";//��������ʾ����ջ�����봮��� 
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
		cout<<"����ջ1��!\n";
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
		cout<<"����ջ2��!\n";
		return 0;
	}
}
void out_stack1(symbol_instr*p)
{
	int i;
	if(p->top<0)
	{
		cout<<"����ջ3��!\n";
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
		cout<<"����ջ4��!\n";
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
 
void choose(status* status_p,int a,char x){//ѡ���Լ״̬
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
 	cout<<"��Լ����!\n";
 	if(i==30){
	 	cout<<"��Լ�ɹ�!\n";
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
 	status*status_p;//״̬ջ 
 	symbol_instr*symbol_p,*instr_p;//����ջ�����봮
 	/*���䳤��Ϊsizeof(ststus)�ֽڵ��ڴ�� 
    �������ɹ��򷵻�ָ�򱻷����ڴ��ָ�룬���򷵻ؿ�ָ��NULL�� 
    ���ڴ治��ʹ��ʱ��Ӧʹ��free()�������ڴ���ͷš�*/
 	status_p=(status*)malloc(sizeof(status));
 	symbol_p=(symbol_instr*)malloc(sizeof(symbol_instr));
 	instr_p=(symbol_instr*)malloc(sizeof(symbol_instr));
 	init_stack(status_p);
 	init_stack(symbol_p);
 	init_stack(instr_p);
 	push(status_p,0);//Ϊ״̬ջ�����ʼ״̬ 0 
 	push(symbol_p,'#');//Ϊ����ջ����ջ�׷��� # 
 	cout<<"������Ҫ��Լ�����봮����'#'�ַ�������\n"; 
	do
	{
	 	x=getchar();
	 	if(x!=' '||x!='\t'||x!='\n')//�������ַ���Ϊ�ո񡢻س����Ʒ���ʱ������ջ�� 
	 		push(symbol_p,x);
	}while(x!='#');
	while(symbol_p->top!=0)//��ջ��Ϊ��ʱ 
	{
	 	x=pop(symbol_p);//�ӷ���ջ��ȡ 
	 	push(instr_p,x);//�������봮 
	}
	cout<<"\n";
	cout<<"\n״̬ջ              ����ջ                ���봮\n";
	print(status_p,symbol_p,instr_p);
	action(status_p,symbol_p,instr_p);
	return 0;
}
