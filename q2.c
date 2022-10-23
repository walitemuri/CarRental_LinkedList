
/*
    File Owned By: Wali Temuri 1183379
    CIS-2520 A2, Question # 2
*/

//Including all the libraries

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

//Initialize Variables for the Stack
int top = -1;
int size;

float stack [100];

/*
    Function: Pushes float input onto the stack
    in: float 
    out: void
*/
void push(float);

/*
    Function: Pops the element at the top of the Stack
    in: float 
    out: void
*/
int pop(void);


/*
    Function: This function is responsible for the final computation of the Equation
    in: char []
    out: void
*/
void reversePol_Evaluation(char []);

/* Main Begins */

int main(int c,char *argv[])
{
	reversePol_Evaluation(argv[1]);
	printf("Evaluation of given expression is = %.2f\n", stack[top]);
}

void reversePol_Evaluation(char s[size])
{
    //Declaring variables to perform operations
	int i,d1,d2;

	printf("%s\n",s);
    
    //Looping through the String to push appropriate elemnts on stack and perform arithemetic operations
	for(i=0;s[i]!='\0';i++)
	{
        //Checking for operators
		if(s[i]=='+' || s[i]=='-' || s[i]=='*' || s[i]=='/')
		{
            //Popping first two ints when found operator
			d1=pop();
			d2=pop();
            
            //Handles which operation to perform
			switch(s[i])
			{
				case '+':
					push(d2+d1);
					break;
				
				case '-':
					push(d2-d1);
					break;
				
				case '*':
					push(d2*d1);
					break;
				
				case '/':
					push((float)d2/d1);
					break;
					
	
					
			
			}
		}
        //Handles the case where there is a digit
		
        
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
