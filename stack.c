#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "calci.h"
#include "stack.h"
#include "nodestack.h"


// stack operations
void initStack(Stack *s, int n){
	s->arr = (char *)malloc((sizeof(char)) * n);
	s->size = n;
	s->top = -1;
}

int isFull(Stack *s){
	return ((s->top) == (s->size) - 1);
}

int isEmpty(Stack *s){
	return ((s->top) == -1);
}

void push(Stack *s, char val){
	if(isFull(s)){
		return;
	}
	(s->top)++;
	s->arr[s->top] = val;
}

char pop(Stack *s){
	if(isEmpty(s)){
		return '\0';
	}
	char val = s->arr[s->top];
	(s->top)--;
	return val;
}

char peek(Stack *s){
	if(isEmpty(s)){
		return '\0';
	}
	char val = s->arr[s->top];
	return val;
}


//nodestack operations 
void initNodeStack(nodeStack *s, int n){
	s->numLL = (node **)malloc((sizeof(node*)) * n);
	s->size = n;
	s->top = -1;
}

int isNodeStackFull(nodeStack *s){
	return ((s->top) == (s->size) - 1);
}

int isNodeStackEmpty(nodeStack *s){
    return ((s->top) == -1);
}

void pushNode(nodeStack *s, node *val){
	if(isNodeStackFull(s)){
		return;
	}
	(s->top)++;
	s->numLL[s->top] = val;
}

node* popNode(nodeStack *s){
    if(isNodeStackEmpty(s)){
        return NULL;
    }
    node *val = s->numLL[s->top];
    (s->top)--;
    return val;
}

node* peekNode(nodeStack *s){
    if(isNodeStackEmpty(s)){
        return NULL;
    }
    node *val = s->numLL[s->top];
    return val;
}

//postfix evation operations
int isOperand(char ch){
	return isdigit(ch);
}

int isSpace(char ch){
	if(ch == ' '){
		return 1;
	}
	else{
		return 0;
	}
}

int precedence(char op) {
    if (op == '+' || op == '-'){
        return 1;
    } 
    else if (op == '*' || op == '/'){
        return 2;
    }
    else if (op == '^'){
	return 3;
    }
    else{
        return 0;
    }
}

char *infixToPostfix(char *expr){
	Stack *s = (Stack *)malloc(sizeof(Stack));
	int n = strlen(expr);
	initStack(s, n);

	char *postfix = (char *)malloc((sizeof(char)) * (s->size + 1));
	int k = -1;

	for(int i = 0; expr[i] != '\0'; i++){
		if(expr[i] == ' '){
			continue;
		}
		else if(isdigit(expr[i])){
			//taking whole operand as string
			int j = i;
			char operand[100];
			int p = 0;
			
			while(isdigit(expr[j])){
				operand[p++] = expr[j++];
			}
			operand[p] = '\0';

			// copying to postfix string array
			for(int q = 0; operand[q] != '\0'; q++){
				postfix[++k] = operand[q];
			}

			postfix[++k] = ' ';

			i = j - 1;
		}
		else if(expr[i] == '('){
			push(s, expr[i]);
		}
		else if(expr[i] == ')'){
			while(peek(s) != '('){
				postfix[++k] = pop(s);
			}
			pop(s);
		}
		else{
			while(s->top != -1 && precedence(expr[i]) <= precedence(peek(s))){
				postfix[++k] = pop(s);
				postfix[++k] = ' ';
			}
			push(s, expr[i]);
		}
	}

	while(s->top != -1){
		postfix[++k] = pop(s);
		postfix[++k] = ' ';
	}

	postfix[++k] = '\0';
	
	return postfix;
}

node* evaluatePostfix(char *expr){
	nodeStack *s = (nodeStack *)malloc(sizeof(nodeStack));
	int n = strlen(expr);
    initNodeStack(s, n);

	node *x = NULL;
	node *y = NULL;
	node *result = NULL;
	
	for(int i = 0; expr[i] != '\0'; i++){
		if(expr[i] == ' '){
			continue;
		}	
		else if(isdigit(expr[i])){
			int j = i;

			node *operand = NULL;

			while(isdigit(expr[j])){
				node *newnode = (node *)malloc(sizeof(node));
				newnode->data = expr[j++] - '0';
				newnode->next = operand;
				operand = newnode;
			}

			pushNode(s, operand);

			i = j - 1;
		}
		else{
			y = popNode(s);
			x = popNode(s);
			
			switch(expr[i]){
				case '+':
					result = addition(x, y);
					break;
				case '-':
					
					result = subtraction(x, y);
					break;
				case '*':
					result = multiplication(x, y);
					break;
				case '/':
					result = division(x, y);
					break;
				case '^':
					result = exponent(x, y);
					break;
			}
			pushNode(s, result);
		}
	}
	return popNode(s);
}

