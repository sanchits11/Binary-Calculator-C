typedef struct nodeStack{
        node **numLL;
        int top;
        int size;
} nodeStack;


//stack operations 
void initNodeStack(nodeStack *s, int n);
int isNodeStackFull(nodeStack *s);
int isNodeStackEmpty(nodeStack *s);
void pushNode(nodeStack *s, node *val);
node* popNode(nodeStack *s);
node* peekNode(nodeStack *s);
