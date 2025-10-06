#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STATES 10
#define MAX_SYMBOLS 10
#define MAX_DFA_STATES 100

int nfaStates, nSymbols;
char symbols[MAX_SYMBOLS];
int nfa[MAX_STATES][MAX_SYMBOLS][MAX_STATES];
int nfaCount[MAX_STATES][MAX_SYMBOLS];

int dfaStates[MAX_DFA_STATES][MAX_STATES];
int dfaTransitions[MAX_DFA_STATES][MAX_SYMBOLS];
int dfaCount = 0;

int equalState(int a[], int b[])
{
	for (int i = 0; i < nfaStates; i++)
	{
		if (a[i] != b[i])
			return 0;
	}
	return 1;
}

int existingState(int state[][MAX_STATES], int count, int set[])
{
	for (int i = 0; i < count; i++)
		if (equalState(state[i], set))
			return i;
	return -1;
}

void addtoSet(int set[], int val)
{
	if (!set[val])
		set[val] = 1;
}

void printDFA()
{
	printf("\nDFA Transitions:\n");
	for (int i = 0; i < dfaCount; i++)
	{
		printf("DFA State %d:", i);
		for (int j = 0; j < nSymbols; j++)
			printf(" -- %c --> %d", symbols[j], dfaTransitions[i][j]);
		printf("\n");
	}
}

int main()
{
	int nTransitions, from, to;
	char symbol;
	
	printf("Enter number of States: ");
	scanf("%d", &nfaStates);
	
	printf("Enter number of symbols: ");
	scanf("%d", &nSymbols);
	
	printf("Enter symbols: ");
	for (int i = 0; i < nSymbols; i++)
		scanf(" %c", &symbols[i]);
		
	printf("Enter number of transitions: ");
	scanf("%d", &nTransitions);
	
	printf("Enter transitions:\n");
	for (int i = 0; i < nTransitions; i++)
	{
		scanf("%d %c %d", &from, &symbol, &to);
		int symIdx = -1;
		for (int j = 0; j < nSymbols; j++)
		{
			if (symbol == symbols[j])
			{
				symIdx = j;
				break;
			}
		}
		if (symIdx != -1)
			nfa[from][symIdx][nfaCount[from][symIdx]++] = to;
		else
		{
			printf("Invalid symbol.\n");
			return 1;
		}
	}
	
	int initial[MAX_STATES] = {0};
	initial[0] = 1;
	memcpy(dfaStates[0], initial, sizeof(initial));
	dfaCount = 1;
	
	for (int i = 0; i < dfaCount; i++)
	{
		for (int j = 0; j < nSymbols; j++)
		{
			int newSet[MAX_STATES] = {0};
			for (int s = 0; s < nfaStates; s++)
			{
				if (dfaStates[i][s])
				{
					for (int t = 0; t < nfaCount[s][j]; t++)
						addtoSet(newSet, nfa[s][j][t]);
				}
			}
			int existingIndex = existingState(dfaStates, dfaCount, newSet);
			if (existingIndex == -1)
			{
				memcpy(dfaStates[dfaCount], newSet, sizeof(newSet));
				dfaTransitions[i][j] = dfaCount++;
			}
			else
				dfaTransitions[i][j] = existingIndex;
		}		
	}
	
	printDFA();
	
	return 0;
}
