#include <stdio.h>
#include <string.h>
#include "calci.h"

int main(){
	printf("\nEnter \"exit\" to exit the program.\n");
	printf("write expressions as your inputs");
	
	int flag = 0;
	char expr[500];
	List ans;

	do{
		printf("\n>> ");
		fgets(expr, 1000, stdin);
		expr[strcspn(expr, "\n")] = '\0';

		if(!strcmp(expr, "exit")){
			flag = 1;
			printf("Do visit again :)");
		}
		else{
			ans = solveExpr(expr);
			displayLL(ans);
            printf("\n");
            freeLL(&ans);
            ans = NULL;           
		}

	} while(!flag);
	
	return 0;
}
