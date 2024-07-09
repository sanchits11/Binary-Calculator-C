typedef struct node{
	int data;
	int sign;
	struct node* next;
} node;

typedef node* List;


//functions for linked list

void displayList(List L);
void freeList(List *L);
void insertNode(List *L, int temp);
node *copyList(List L);
int compareList(List L1, List L2);
void reverseList(List *L);
node* listfromChar(char* num);
void removeZeroes(List* L);
int divideInSub(List *temp1, List temp2);

node* addition(List L1, List L2);
node* subtraction(List L1, List L2);
node* multiplication(List L1, List L2);
node* division(List L1, List L2);
node* exponent(List L1, List L2);
node* solveExpr(char *expr);
