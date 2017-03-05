#include <cstdio>
#include <string>
#include <iostream>

//compile = g++ -o rectest -g rectest.cpp -std=c++11

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
   
	int** H = (int**)calloc(m+1,sizeof(int*));
	int** V = (int**)calloc(m+1,sizeof(int*));
	for(int i = 0; i<m+1; i++){
		H[i] = (int*)calloc(n+1,sizeof(int));
		V[i] = (int*)calloc(n+1,sizeof(int));
	}
   int i, j;
  
   /* Following steps build L[m+1][n+1] in bottom up fashion. Note 
      that L[i][j] contains length of LCS of X[0..i-1] and Y[0..j-1] */
   for (i=1; i<=m; i++)
   {
     for (j=1; j<=n; j++)
     {
       int EQ = 0;
	   if(X.at(i-1)==Y.at(j-1)){
		   EQ=1;
	   }
	 int v = max(max(EQ - H[i-1][j] , V[i][j-1] - H[i-1][j]),0);
	 int h = max(max(EQ - V[i][j-1] , H[i-1][j] - V[i][j-1]),0);
	 
	 V[i][j] = v;
	 H[i][j] = h;
     }
   }
   int length;
   for(int c = 0; c<n+1; c++){
		length = length + H[m][c];
	}
   std::cout<<"H: \n";
   printmatrix(H, m+1, n+1);
   std::cout<<"V: \n";
   printmatrix(V, m+1, n+1);
   for(int i = 0; i<m; i++){
		free(V[i]);
		free(H[i]);
	}
	free(H);
	free(V);
   /* L[m][n] contains length of LCS for X[0..n-1] and Y[0..m-1] */
   return length;
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
  
  std::string Y = "agwgwtawbw";
	std::string X = "gxtxxayxbxy";
  //LCS is "GTAB"
  int m = X.size();
  int n = Y.size();
  
  printf("Length of LCS is %d\n", lcs( X, Y, m, n ) );
 
  return 0;
}
