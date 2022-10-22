#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int top=-1,size;

float  stack[100];

void Postfix_Evaluation(char []);

void push(float);

int pop(void);

int main(int c,char *argv[])
{
	Postfix_Evaluation(argv[1]);
	printf("Evaluation of given expression is = %.2f\n",stack[top]);
}

void Postfix_Evaluation(char s[size])
{
	int i,data1,data2;
	printf("%s\n",s);
	for(i=0;s[i]!='\0';i++)
	{
		if(s[i]=='+' || s[i]=='-' || s[i]=='*' || s[i]=='/')
		{
			data1=pop();
			data2=pop();
			switch(s[i])
			{
				case '+':
					push(data2+data1);
					break;
				
				case '-':
					push(data2-data1);
					break;
				
				case '*':
					push(data2*data1);
					break;
				
				case '/':
					push((float)data2/data1);
					break;
			}
		}
		else
		{
            switch(s[i])
            {
                case '0':
                    push(0);
                    break;
                    
                case '1':
                    push(1);
                    break;
                    
                case '2':
                    push(2);
                    break;
                    
                case '3':
                    push(3);
                    break;
                
                case '4':
                    push(4);
                    break;
                    
                case '5':
                    push(5);
                    break;
                    
                case '6':
                    push(6);
                    break;
                    
                case '7':
                    push(7);
                    break;
                    
                case '8':
                    push(8);
                    break;
                    
                case '9':
                    push(9);
                    break;
            }
		}
                
		   
	}
}

void push(float data)
{
	stack[++top]=data;
}

int pop(void)
{
	return stack[top--];
}
