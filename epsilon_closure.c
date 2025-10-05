#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 200

int nStates;
int epsilonCount[MAX];
int epsilonTransition[MAX][MAX];
int epsilonClosure[MAX][MAX];
int closureCount[MAX];
int visited[MAX];

void dfs(int state, int current)
{
	for (int i = 0; i < epsilonCount[state]; i++)
	{
		int next = epsilonTransition[state][i];
		if (!visited[next])
		{
			visited[next] = 1;
			epsilonClosure[current][closureCount[current]++] = next; //Include the state that is reached through epsilon
			dfs(next, current); //Going with epsilon as deep as possible from the current state
		}
	}
}

void computeClosure()
{
	for (int i = 0; i < nStates; i++)
	{
		memset(visited, 0, sizeof(visited));
		visited[i] = 1;
		closureCount[i] = 0;
		epsilonClosure[i][closureCount[i]++] = i; //Epsilon closure on current state itself
		dfs(i, i);
	}
}

void printClosure()
{
	printf("\nEpsilon closure of all states:\n");
	for (int i = 0; i < nStates; i++)
	{
		printf("e-closure (q%d): { ", i);
		for (int j = 0; j < closureCount[i]; j++)
			printf("q%d ", epsilonClosure[i][j]);
		printf("}\n");
	}
}

int main()
{
	int nTransitions;
	int from, to;
	char symbol;
	
	printf("Enter number of states: ");
	scanf("%d", &nStates);
		
	printf("Enter number of transitions: ");
	scanf("%d", &nTransitions);
	
	for (int i = 0; i < nStates; i++)
		epsilonCount[i] = 0; 
	
	printf("Enter transitions:\n");
	for (int i = 0; i < nTransitions; i++)
	{
		scanf("%d %c %d", &from, &symbol, &to);
		if (symbol == 'e')
			epsilonTransition[from][epsilonCount[from]++] = to; //Only consider epsilon transitions
	}
	
	computeClosure();
	printClosure();
	
	return 0;
}
