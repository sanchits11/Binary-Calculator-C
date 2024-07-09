typedef struct node{
	int data;
	int sign;
	struct node* next;
} node;

typedef node* List;


//List operations and functions for calculator
void freeLL(List *L);
void insertNode(List *L, int temp);
void reverseLL(List *L);
void removeZeroes(List* L);
int compareLL(List L1, List L2);


void displayLL(List L);

node* addition(List L1, List L2);
node* subtraction(List L1, List L2);
node* multiply(List L1, List L2);
node* divide(List L1, List L2);
node* expon(List L1, List L2);
node* square(List L1);

node* handleFunctions(char *expr, int k);

node* solveExpr(char *expr);
