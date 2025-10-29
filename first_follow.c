#include <stdio.h> 
#include <string.h> 
#include <ctype.h> 

#define MAX 50 
#define NT 26 // Non-terminals A-Z 

char prods[MAX][MAX];     // productions 
int n;                    // number of productions 
char firstSet[NT][MAX]; 
char followSet[NT][MAX];
 
int isNonTerminal(char c) 
{ 
	return (c >= 'A' && c <= 'Z'); 
} 

int isInSet(char set[], char c) 
{ 
	for (int i = 0; set[i] != '\0'; i++) 
		if (set[i] == c) 
			return 1; 
	return 0; 
} 

void addToSet(char set[], char c) 
{ 
	if (c == ' ') 
		return; 
	if (!isInSet(set, c)) 
	{ 
		int len = strlen(set); 
		set[len] = c; 
		set[len + 1] = '\0'; 
	} 
} 

void computeFirst() 
{ 
	int changed; 
	do 
	{ 
		changed = 0; 
		for (int i = 0; i < n; i++) 
		{ 
			char lhs = prods[i][0]; 
			int j = (prods[i][1] == '-' && prods[i][2] == '>') ? 3 : (prods[i][1] == '=' ? 2 : 1);
			int beforeLen = strlen(firstSet[lhs - 'A']); 
			for (; prods[i][j] != '\0'; j++) 
			{ 
				char sym = prods[i][j]; 
				if (!isNonTerminal(sym)) 
				{ 
					addToSet(firstSet[lhs - 'A'], sym); //If current symbol is a terminal, add that to FIRST(lhs)
                    			break; 
                		} 
                		else 
                		{ 
                    			for (int k = 0; firstSet[sym - 'A'][k] != '\0'; k++) 
                        			if (firstSet[sym - 'A'][k] != 'e') 
                            				addToSet(firstSet[lhs - 'A'], firstSet[sym - 'A'][k]); //Find the first of that non terminal and them to FIRST(lhs)
 
                    			// if sym's FIRST has epsilon, continue to next symbol 
                    			if (isInSet(firstSet[sym - 'A'], 'e')) 
                        			continue; 
                    			else 
                        			break; 
                		} 
            		} 
            		// if all symbols can produce epsilon, add epsilon to LHS 
            		int allEpsilon = 1; 
            		for (int k = (prods[i][1] == '-' && prods[i][2] == '>') ? 3 : (prods[i][1] == '=' ? 2 : 1); prods[i][k] != '\0'; k++) 
            		{ 
                		if (!isInSet(firstSet[prods[i][k] - 'A'], 'e')) 
                		{ 
                    			allEpsilon = 0; 
                    			break; 
                		}	 
            		} 
            		if (allEpsilon) 
            			addToSet(firstSet[lhs - 'A'], 'e'); 
            		if (strlen(firstSet[lhs - 'A']) > beforeLen) 
                		changed = 1; //There was a change in firstSet in the computation of first
        	} 
    	} while (changed); 
} 
 
void computeFollow()
{ 
    int changed; 
    addToSet(followSet[prods[0][0] - 'A'], '$'); // Start symbol 
 
    do 
    { 
    	changed = 0; 
	for (int i = 0; i < n; i++) 
        { 
		char lhs = prods[i][0]; 
 		int j = (prods[i][1] == '-' && prods[i][2] == '>') ? 3 : (prods[i][1] == '=' ? 2 : 1);

            	for (; prods[i][j] != '\0'; j++) 
            	{ 
                	char B = prods[i][j]; 
                	if (!isNonTerminal(B)) 
                		continue; 
                	int beforeLen = strlen(followSet[B - 'A']); 
                	int k = j + 1; 
                	while (prods[i][k] != '\0') //From next symbol after beta
                	{ 
                    		char beta = prods[i][k]; 
                     		if (!isNonTerminal(beta)) 
                     		{ 
                        		addToSet(followSet[B - 'A'], beta); //if terminal, add to FOLLOW(beta)
                        		break; 
                    		} 
                    		else 
                    		{ 
                        		for (int m = 0; firstSet[beta - 'A'][m] != '\0'; m++) 
                            			if (firstSet[beta - 'A'][m] != 'e') 
                                			addToSet(followSet[B - 'A'], firstSet[beta - 'A'][m]); //if non-terminal, find the first of that non-terminal and add it to FOLLOW(beta)
                        			if (isInSet(firstSet[beta - 'A'], 'e')) 
                        			{ 
                            				k++; //skip epsilon
                            				if (prods[i][k] == '\0') 
                            				{ 
                                				// epsilon at end, add FOLLOW(lhs) 
                                				for (int m = 0; followSet[lhs - 'A'][m] != '\0'; m++) 
                                    					addToSet(followSet[B - 'A'], followSet[lhs - 'A'][m]); 
                            				} 
                        			} 
                        			else 
                        				break; 
                    		} 
                	} 
                	if (prods[i][j + 1] == '\0') 
                	{ 
                		// B at end, add FOLLOW(lhs) 
                    		for (int m = 0; followSet[lhs - 'A'][m] != '\0'; m++) 
                        		addToSet(followSet[B - 'A'], followSet[lhs - 'A'][m]); 
                	} 
                	if (strlen(followSet[B - 'A']) > beforeLen) 
                    		changed = 1; //There was a change in followSet in the computation of first
            } 
        } 
    } while (changed); 
} 

int main() 
{ 
	printf("Enter number of productions: "); 
    	scanf("%d", &n); 
    	printf("Enter productions (e.g., E->E+T or E=E+T):\n"); 
    	for (int i = 0; i < n; i++) 
        	scanf("%s", prods[i]); 
    	for (int i = 0; i < 26; i++) 
    		firstSet[i][0] = followSet[i][0] = '\0'; 
    	computeFirst(); 
    	computeFollow(); 
    	int printed[26] = {0}; 
     	printf("\nFIRST sets:\n"); 
    	for (int i = 0; i < n; i++)
    	{ 
        	char nt = prods[i][0]; 
        	if (!printed[nt - 'A']) 
        	{ 
           		printf("%c : %s\n", nt, firstSet[nt - 'A']); 
           		printed[nt - 'A'] = 1; 
        	} 
    	} 
    	memset(printed, 0, sizeof(printed)); 
    	printf("\nFOLLOW sets:\n"); 
    	for (int i = 0; i < n; i++) 
    	{ 
      		char nt = prods[i][0]; 
		if (!printed[nt - 'A']) 
		{ 
			printf("%c : %s\n", nt, followSet[nt - 'A']); 
			printed[nt - 'A'] = 1; 
		} 
	} 
	return 0;
} 
