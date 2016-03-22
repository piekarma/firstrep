#include <stdio.h>
#include <stdlib.h>

void pushValStack(int stack[], int *top, int value);
int popValStack(int stack[], int *top);
void pushOpStack(char *stack[], int *top, char *value);
char *popOpStack(char *stack[], int *top);

int main(int argc, char* argv[]) {

	int valstack[50];
	int valtop = 0;
	int *aValTop = &valtop;

	char *opStack[50];
	int opTop = 0;
	int *aOpTop = &opTop;
	
	char *input[argc-1];
	int m;

	for(m = 1; m < argc; m++) { 
		input[m-1] = argv[m];
	}
	for(m = 0; m < argc-1; m++) {
		if(*input[m] == '+' || *input[m] == 'x' || *input[m] == '[') {
			char *value = input[m];
			pushOpStack(opStack, aOpTop, value);
		}
		else if(*input[m] == ']') {
			char *temp = popOpStack(opStack, aOpTop);
			while(*temp != '[') {
				int firstval = popValStack(valstack, aValTop);
				int secondval = popValStack(valstack, aValTop);
				int final;
				if(*temp == 'x') {
					final = firstval*secondval;
				}
				else if(*temp == '+') {
					final = firstval+secondval;
				}
				pushValStack(valstack, aValTop, final);
				temp = popOpStack(opStack, aOpTop);
			}
		}
		else {
			int final = atoi(input[m]);
			pushValStack(valstack, aValTop, final);
		}
	}

	int z;
	char *temp;
	while(*aOpTop != 0) {
		temp = popOpStack(opStack, aOpTop);
		int firstval = popValStack(valstack, aValTop);
		int secondval = popValStack(valstack, aValTop);
		int final;
		if(*temp == 'x') {
			final = firstval*secondval;
		}
		else if(*temp == '+') {
			final = firstval+secondval;
		}
		pushValStack(valstack, aValTop, final);
	}
	printf("%d\n", valstack[0]); 
}

void pushValStack(int stack[], int *top, int value) {
	stack[*top] = value;
	*top = *top + 1;
}

int popValStack(int stack[], int *top) {
	*top = *top-1;
	int value = stack[*top];
	return value;
}

void pushOpStack(char *stack[], int *top, char *value) {
	stack[*top] = value;
	*top = *top+1;
}

char *popOpStack(char *stack[], int *top) {
	*top = *top-1;
	char *value = stack[*top];
	return value;
}


