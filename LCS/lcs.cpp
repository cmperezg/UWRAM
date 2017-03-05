#include <cstdio>
#include <string>
#include <iostream>

//compile = g++ -o lcs -g lcs.cpp -std=c++11

int max(int a, int b);

void printmatrix(int** T, int m, int n){
	
	for(int i = 0; i<m; i++){
		for(int j = 0; j<n; j++){
			std::cout<< T[i][j] << " ";
		}
		std::cout<< "\n";
	}
}
  
/* Returns length of LCS for X[0..m-1], Y[0..n-1] */
int lcs( std::string X, std::string Y, int m, int n )
{
   //int L[m+1][n+1];
   int** L = (int**)calloc(m+1,sizeof(int*));
	for(int i = 0; i<m+1; i++){
		L[i] = (int*)calloc(n+1,sizeof(int));
	}
   int i, j;
  
   /* Following steps build L[m+1][n+1] in bottom up fashion. Note 
      that L[i][j] contains length of LCS of X[0..i-1] and Y[0..j-1] */
   for (i=0; i<=m; i++)
   {
     for (j=0; j<=n; j++)
     {
       if (i == 0 || j == 0)
         L[i][j] = 0;
  
       else if (X[i-1] == Y[j-1])
         L[i][j] = L[i-1][j-1] + 1;
  
       else
         L[i][j] = max(L[i-1][j], L[i][j-1]);
     }
   }
   printmatrix(L, m+1, n+1);
    for(int i = 0; i<m+1; i++){
		free(L[i]);
	}
	free(L);
   /* L[m][n] contains length of LCS for X[0..n-1] and Y[0..m-1] */
   return L[m][n];
}
  
/* Utility function to get max of 2 integers */
int max(int a, int b)
{
    return (a > b)? a : b;
}
  
/* Driver program to test above function */
int main()
{
  //std::string X = "AGGTAB";
  //std::string Y = "GXTXAYB";
  
  std::string Y = "abbarb";
	std::string X = "abcdefabcac";
  //LCS is "GTAB"
  int m = X.size();
  int n = Y.size();
  
  printf("Length of LCS is %d\n", lcs( X, Y, m, n ) );
 
  return 0;
}
