// LR(1).cpp : Defines the entry point for the console application.
// 
/* //////////////////////////////////////////////////////////////

E -> E+T | T
T -> T*F | F
F -> (E) | id

 一，构造DFA
1. 拓广文法

E'->E 
E->E+T (1)
E->T (2)
T->T*F (3)
T->F (4)
F->(E) (5)
F->id (6)

2.构造LR(1)项目集规范族
I0: 

I1:

I2:

I3:

I4:

I5:

I6:

I7:

I8:

I9:

I10:

I11:

I12:

I13:



二. 构造分析表

         i        +       *        (         )        $        E         T         F
_____________________________________________________________________________________
0       S5                         s4                          1	 2	   3
1                 s6                                  acc
2                 r2     S7                 r2        r2                          
3                 r4     r4                 r4        r4
4       s5                         s4
5                                          S11
6                 r6     r6                r6         r6
7                                  S12   
8                                          S13
9                                  r6      r5 
10                                                   r1
11                                                   r3
_____________________________________________________________________________________

*////////////////////////////////////////////////////////////////////////




#include "stdafx.h"
#include "conio.h"

#define E 100
#define T 110       
#define F 120       
#define id 200	    
#define add 300	    
#define mul 400	    
#define lb 500       
#define rb 600       


int nStackPtr;
int nInputPtr;
int stack[100];		// 栈
char strInput[100];	// 存放串

void Push(int n)
{
	nStackPtr ++;

	stack[nStackPtr] = n;
}

void Pop()
{
	nStackPtr--;
}

bool Goto(int n)
{
	if (0 == stack[nStackPtr] && E == n)
	{
		Push(E);
		Push(1);
		return true;
	}

	if (0 == stack[nStackPtr] && T == n)
	{
		Push(T);
		Push(2);
		return true;
	}

	if (0 == stack[nStackPtr] && F == n)
	{
		Push(F);
		Push(3);
		return true;
	}

	if (4 == stack[nStackPtr] && E == n)
	{
		Push(E);
		Push(8);
		return true;
	}

	if (4 == stack[nStackPtr] && T == n)
	{
		Push(T);
		Push(2);
		return true;
	}
	if (4 == stack[nStackPtr] && F == n)
	{
		Push(F);
		Push(3);
		return true;
	}
	if (6 == stack[nStackPtr] && T == n)
	{
		Push(T);
		Push(9);
		return true;
	}
	if (6 == stack[nStackPtr] && F == n)
	{
		Push(F);
		Push(3);
		return true;
	}
	if (7 == stack[nStackPtr] && F == n)
	{
		Push(F);
		Push(10);
		return true;
	}
        return false;

}

void PrintStack()
{
	int i;
	for (i = nStackPtr; i >= 0; i--) 
	{
		switch (stack[i])
		{
		case E: printf("E "); break;
		case T: printf("T "); break;
		case F: printf("F "); break;
	
		case id: printf("i "); break;
		case add: printf("+ "); break;
		case mul: printf("* "); break;
		case lb: printf("( "); break;
		case rb: printf(") "); break;

		default:
			printf("%d ", stack[i]);
			break;
		}
	}
	printf("\n");
}

/////////////////////////////////////////////////////////////////
//错误处理
//
//
/////////////////////////////////////////////////////////////////

void errCtr(int n){
    while(!Goto(n)){
        Pop();
    }
    switch(n)
    {
        case E:
            while(strInput[nInputPtr]!='\0'&&strInput[nInputPtr]!='+'&&strInput[nInputPtr]!=')')
                nInputPtr++;
            break;
        case F:
            while(strInput[nInputPtr]!='\0'&&strInput[nInputPtr]!='+'&&strInput[nInputPtr]!=')'&&strInput[nInputPtr]!='*')
                nInputPtr++;
            break;
        case T:
            while(strInput[nInputPtr]!='\0'&&strInput[nInputPtr]!='+'&&strInput[nInputPtr]!=')'&&strInput[nInputPtr]!='*')
                nInputPtr++;
            break;
        default:
            break;
    }
}









/////////////////////////////////////////////////////////////////
// 利用栈来分析串，判定串是否正确
// 
/////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
	bool bResult;
	bool acc;

	nStackPtr = -1;
	nInputPtr = 0;

	bResult = true;
	acc = false;

	// 输入串，存放在 strInput中
	printf("请输入串：");
	scanf("%s",strInput);
	
	Push(0);//0 status
	//PrintStack();	
	
	while (false ==acc)
	{	
		switch(stack[nStackPtr])
		{
		case 0:
			if ('i' == strInput[nInputPtr]) 
			{
				Push(id);
				Push(5);
				nInputPtr++;
                                printf("移进id\n");
			}
			else if ('(' == strInput[nInputPtr])
				{
					Push(lb);
					Push(4);
					nInputPtr++;
                                        printf("移进（\n");
				}
			else{
                                printf("1error\n");
				bResult = false;
                                errCtr(E);
                        }
			//PrintStack();	
			break;
		case 1:
			if('+' == strInput[nInputPtr]){
				Push(add);
				Push(6);
				nInputPtr++;
                                printf("移进+\n");
			}
			else if ('\0' == strInput[nInputPtr]) 
			{
				acc = true;
                                printf("接受\n");
			}
			else {
                            bResult = false;
                            printf("error\n");
                            errCtr(E);
                        }
			//PrintStack();	
			break;

		case 2:
			if ('+' == strInput[nInputPtr]) 
			{
				Pop();
				Pop();

				Goto(E);
                                printf("按E->T归约\n");
			}
			else if('*' == strInput[nInputPtr])
			{
				Push(mul);
				Push(7);
				nInputPtr++;
                                printf("移进*\n");
			}
			else if (')' == strInput[nInputPtr]) 
			{
				Pop();
				Pop();

				Goto(E);
                                printf("按E->T归约\n");
			}
			else if ('\0' == strInput[nInputPtr]) 
			{
				Pop();
				Pop();

				Goto(E);
                                printf("按E->T归约\n");
			}
			else {
                            bResult = false;
                            printf("error\n");
                            errCtr(E);
                        }
			//PrintStack();	
			break;	
		case 3:
			if ('+' == strInput[nInputPtr])
			{
				Pop();
				Pop();

				Goto(T);
                                printf("按T->F归约\n");
			}
			else if ('*' == strInput[nInputPtr])
			{
				Pop();
				Pop();

				Goto(T);
                                printf("按T->F归约\n");
			}
			else if (')' == strInput[nInputPtr])
			{
				Pop();
				Pop();

				Goto(T);
                                printf("按T->F归约\n");
			}
			else if ('\0' == strInput[nInputPtr])
			{
				Pop();
				Pop();

				Goto(T);
                                printf("按T->F归约\n");
			}
			else {
                            bResult = false;
                            printf("error\n");
                            errCtr(T);
                        }
			//PrintStack();				
			break;
		case 4:
			if ('i' == strInput[nInputPtr]) 
			{
				Push(id);
				Push(5);
				nInputPtr++;
                                printf("移进id\n");
			}
			else if ('(' == strInput[nInputPtr]) 
			{
				Push(lb);
				Push(4);
				nInputPtr++;
                                printf("移进（\n");
			}
			else {
                            bResult = false;
                            printf("error\n");
                            errCtr(F);
                        }
			//PrintStack();							
			break;
		case 5:
			if ('+' == strInput[nInputPtr])
			{
				Pop();
				Pop();

				Goto(F);
                                printf("按F->id归约\n");
			}
			else if ('*' == strInput[nInputPtr])
			{
				Pop();
				Pop();

				Goto(F);
                                printf("按F->id归约\n");
			}
			else if (')' == strInput[nInputPtr])
			{
				Pop();
				Pop();

				Goto(F);
                                printf("按F->id归约\n");
			}
			else if ('\0' == strInput[nInputPtr])
			{
				Pop();
				Pop();

				Goto(F);
                                printf("按F->id归约\n");
			}
			else {
                            bResult = false;
                            printf("error\n");
                            errCtr(F);
                        }
			//PrintStack();	
			break;
		case 6:
			if ('i' == strInput[nInputPtr]) 	
			{
				Push(id);
				Push(5);

				nInputPtr++;
                                printf("移进id\n");
			}
			else if ('(' == strInput[nInputPtr])    
			{
				Push(lb);
				Push(4);
				nInputPtr++;
                                printf("移进（\n");
			}
			else {
                            bResult = false;
                            printf("error\n");
                            errCtr(F);
                        }
			break;

		case 7:
			if ('i' == strInput[nInputPtr]) 	
			{
				Push(id);
				Push(5);

				nInputPtr++;
                                printf("移进id\n");
			}
			else if ('(' == strInput[nInputPtr])    
			{
				Push(lb);
				Push(4);
				nInputPtr++;
                                printf("移进（\n");

			}
			else {
                            bResult = false;
                            printf("error\n");
                            errCtr(F);
                        }
			break;

		case 8:
			if ('+' == strInput[nInputPtr]) 
			{
				Push(add);
				Push(6);
				nInputPtr++;
                                printf("移进+\n");
			}
			else if (')' == strInput[nInputPtr]) 
			{
				Push(rb);
				Push(11);
				nInputPtr++;
                                printf("移进 )\n");
			}
			else {
                            bResult = false;
                            printf("error\n");
                            errCtr(F);
                        }
			//PrintStack();	
			break;
	
		case 9:
			if ('+' == strInput[nInputPtr]) 
			{
				Pop();
				Pop();

				Pop();
				Pop();

				Pop();
				Pop();
				
				Goto(E);
                                printf("按E->E+T归约\n");
			}
			else if ('*' == strInput[nInputPtr]) 
			{
				Push(mul);
				Push(7);

				nInputPtr++;
                                printf("移进*\n");
			}
			else if (')' == strInput[nInputPtr]) 
			{
				Pop();
				Pop();

				Pop();
				Pop();

				Pop();
				Pop();
				
				Goto(E);
                                printf("按E->E+T归约\n");
			}
			else if ('\0' == strInput[nInputPtr]) 
			{
				Pop();
				Pop();

				Pop();
				Pop();

				Pop();
				Pop();
				
				Goto(E);
                                printf("按E->E+T归约\n");
			}
			else {
                            bResult = false;
                            printf("error\n");
                            errCtr(E);
                        }
			break;
		case 10:
			if ('+' == strInput[nInputPtr]) 
			{
				Pop();
				Pop();

				Pop();
				Pop();

				Pop();
				Pop();
				
				Goto(T);
                                printf("按T->T*F归约\n");
			}
			else if ('*' == strInput[nInputPtr]) 
			{
				Pop();
				Pop();

				Pop();
				Pop();

				Pop();
				Pop();
				
				Goto(T);
                                printf("按T->T*F归约\n");
			}
			else if (')' == strInput[nInputPtr]) 
			{
				Pop();
				Pop();

				Pop();
				Pop();

				Pop();
				Pop();
				
				Goto(T);
                                printf("按T->T*F归约\n");
			}
			else if ('\0' == strInput[nInputPtr]) 
			{
				Pop();
				Pop();

				Pop();
				Pop();
				
				Pop();
				Pop();

				Goto(T);
                                printf("按T->T*F归约\n");
			}
			else {
                            bResult = false;
                            printf("error\n");
                            errCtr(T);
                        }
			break;
		case 11:
			if ('+' == strInput[nInputPtr]) 
			{
				Pop();
				Pop();

				Pop();
				Pop();

				Pop();
				Pop();
				
				Goto(F);
                                printf("按F->(E)归约\n");
			}
			else if ('*' == strInput[nInputPtr]) 
			{
				Pop();
				Pop();

				Pop();
				Pop();

				Pop();
				Pop();
				
				Goto(F);
                                printf("按F->(E)归约\n");
			}
			else if (')' == strInput[nInputPtr]) 
			{
				Pop();
				Pop();

				Pop();
				Pop();

				Pop();
				Pop();
				
				Goto(F);
                                printf("按F->(E)归约\n");
			}
			else if ('\0' == strInput[nInputPtr]) 
			{
				Pop();
				Pop();

				Pop();
				Pop();
				
				Pop();
				Pop();

				Goto(F);
                                printf("按F->(E)归约\n");
			}
			else {
                            bResult = false;
                            printf("error\n");
                            errCtr(F);
                        }
			break;

		default: bResult = false; 
                         printf("error\n");
			 break;
		}
	}

	if (bResult == true) printf("串没有问题了\n");
	else printf("串有问题!!\n");

	
	getch();

	return 0;
}



