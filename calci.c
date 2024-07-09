#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include "calci.h"
#include "stack.h"


//evaluation of input to nodes 
node* solveExpr(char *expr){
    char *postfix = infixToPostfix(expr);
	node *result = evaluatePostfix(postfix);
    return result;
}

//delete or free of list of nodes(number)
void freeLL(List *L) {
    node *temp = NULL;
    while (*L) {
        temp = *L;
        (*L) = (*L)->next;
        free(temp);
    }
}

//insertion in a list
void insertNode(List *L, int temp){
	node* newnode = (node *)malloc(sizeof(node));
	newnode->sign = 1;
	newnode->data = temp;
    newnode->next = NULL;

	if(!(*L)){
		*L = newnode;
		return;
	}

	node *p = (*L);

	while(p->next){
		p = p->next;
	}
	p->next = newnode;

	return;
}

// Function to copy a linked list:
node *copyLL(List L){
	List newList = NULL;

	while(L){
		insertNode(&newList, L->data);
		L = L->next;
	}

	return newList;
}

//returns 1 if temp is greater, 0 if temp and L2 are equal and returns -1 if L2 is greater.
int compareLL(List L1, List L2){
	List newL1 = copyLL(L1);
	List newL2 = copyLL(L2);

	reverseLL(&newL1);
	reverseLL(&newL2);

	node *p = newL1;
	node *q = newL2;

	while (p && q)
	{
		p = p->next;
		q = q->next;
	}

	if (!p && q)
	{
		return -1;
	}
	else if (p && !q)
	{
		return 1;
	}
	else
	{
		node *temp1 = newL1;
		node *temp2 = newL2;

		while (temp1 != NULL && temp2 != NULL)
		{
			if (temp1->data > temp2->data)
			{
				return 1;
			}
			if (temp1->data < temp2->data)
			{
				return -1;
			}

			temp1 = temp1->next;
			temp2 = temp2->next;
		}
		return 0;
	}
}

// Function to reverse a linked list:
void reverseLL(List *L){
	if(!(*L)){
		return;
	}

	node *p = *L;
	node *q = p->next;

	p->next = NULL;
	node *temp = NULL;

	while(q){
		temp = q->next;
		q->next = p;
		p = q;
		q = temp;
	}

	*L = p;
	return;
}

// to get linked list from string array
node* charToLL(char* num){
	node *L = NULL;

	// If number is zero:
	if(strlen(num) == 0){
		node *newnode = (node *)malloc(sizeof(node));
		newnode->data = 0;
		newnode->sign = 1;
		newnode->next = NULL;

		L = newnode;

		return L;
	}

	// If number is not zero:
	for(int i = 0; num[i] != '\0'; i++){
		int temp = num[i] - '0';
		insertNode(&L, temp);
	}

	return L;
}

// display of linked list 
void displayLL(List L){
	if(!L){
		return;
	}

	if(L->sign == -1){
		printf("-");
		L->sign = 1;
	}

	displayLL(L->next);
	printf("%d", L->data);

	return;
}

// Supporting function for subtract function
void removeZeroes(List* L) {
    node *p = *L;
    node *lastNonZero = NULL;
    while (p) {
        if (p->data) {
            lastNonZero = p;
        }
        p = p->next;
    }

    if (lastNonZero) {
        p = lastNonZero->next;
        lastNonZero->next = NULL;
        freeLL(&p);
    }
}

// addition function
node* addition(List L1, List L2){
	List result = NULL;

	int carry = 0;

	while(L1 || L2){
		int sum = carry;

		if(L1){
			sum += L1->data;
			L1 = L1->next;
		}
		if(L2){
			sum += L2->data;
			L2 = L2->next;
		}

		carry = sum / 10;
		sum = sum % 10;

		insertNode(&result, sum);

	}

	if(carry){
		insertNode(&result, carry);
	}

	return result;	
}

// subtracton function 
node* subtraction(List L1, List L2){
	int finalsign = 1;

    	if(compareLL(L1, L2) == 0){
        	// if the numbers are equal then return 0
	        node *newnode = (node*) malloc(sizeof(node));
        	newnode->data = 0;
			newnode->sign = 1;
        	newnode->next = NULL;
	        
		return newnode;
    	}
		else if(compareLL(L1, L2) < 0){
		finalsign = -1;

		List tmp = L1;
		L1 = L2;
		L2 = tmp;
		//free(tmp);
	}

    List result = NULL;
	int borrow = 0;

	while(L1){
        	int diff = borrow;
        	if(L1){
            	diff += L1->data;
            	L1 = L1->next;
        	}
        	if(L2){
			diff -= L2->data;
			L2 = L2->next;
		}

		if(diff < 0){
                        diff += 10;
                        borrow = -1;
                }
                else{
                        borrow = 0;
                }

                insertNode(&result, diff);
        }

	removeZeroes(&result);

	if(!result){
                node *newnode = (node*) malloc(sizeof(node));
                newnode->data = 0;
		newnode->sign = 1;
                newnode->next = NULL;
                
		return newnode;
        }

	result->sign = finalsign;

        return result;
}

// multiply function 
node* multiply(List L1, List L2){
    List result = NULL;
	List prevResult = NULL;
	List temp = NULL;
	int carry = 0;
	int product = 0;
	int k = 0;

	// Iterating through each digit of num2:
	while(L2){
		carry = 0;
		temp = L1;
		result = NULL;

		while(temp){
			product = (L2->data * temp->data) + carry;
			carry = product / 10;
			product %= 10;

			// Creating a new node:
			insertNode(&result, product);

            		temp = temp->next;
		}

		if (carry) {
			insertNode(&result, carry);
        	}
		k++;

		// Shift the result to left by one place i.e insert node at starting:
		for(int i = 1; i < k; i++){
			node *newnode = (node *)malloc(sizeof(node));
			newnode->data = 0;
			newnode->sign = 1;
			newnode->next = result;
			result = newnode;
		}

	        // Add the shifted result to the previous result
        	prevResult = addition(result, prevResult);
        	freeLL(&result);
        	L2 = L2->next;
    	}

	return prevResult;
}

// to compare continuous subtraction during division
int divideInSub(List *temp, List L2){
	int ans = 0;
	List newLL = NULL;

	reverseLL(temp);

	while(compareLL(*temp, L2) >= 0){
		newLL = subtraction(*temp, L2);
		freeLL(temp);
		*temp = newLL;
		ans++;
	}

	return ans;
}


// Function to perform division:
node* divide(List L1, List L2) {
	// Check for division by zero
	node *zeroNode = (node *)malloc(sizeof(node));
	zeroNode->data = 0;
	zeroNode->sign = 1;
	zeroNode->next = NULL;

	if(compareLL(L2, zeroNode) == 0){
		printf("Can't divide by zero!\n");
		exit(1);
	}
	
	if (compareLL(L1, zeroNode) == 0) {
        	return zeroNode;
    	}
	
	reverseLL(&L1);

	List temp = NULL;
	insertNode(&temp, 0);
    	List result = NULL;

	node *p = L1;
	int k = 0;

	while(p){
		reverseLL(&temp);
		if(temp->data == 0){
			temp->data = p->data;
		}
		else{
			insertNode(&temp, p->data);
		}
		k = divideInSub(&temp, L2);
		insertNode(&result, k);
		p = p->next;
	}

	reverseLL(&result);

	removeZeroes(&result);

	return result;
}

// Function to find exponent:
node* expon(List L1, List L2){
	List result = NULL;
	insertNode(&result, 1);

	List temp1 = NULL;
	List temp2 = NULL;

	node *oneNode = (node *)malloc(sizeof(node));
        oneNode->data = 1;
	oneNode->sign = 1;
        oneNode->next = NULL;

	while((L2->data > 0) || (L2->next != NULL)){
		temp1 = multiply(result, L1);
		freeLL(&result);
		result = temp1;

		temp2 = subtraction(L2, oneNode);
		freeLL(&L2);
		L2 = temp2;
	}

	return result;
}

