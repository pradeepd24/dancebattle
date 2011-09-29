/* Note: The directed edge version of this game is a PSPACE complete problem. I think this undirected edge version is also a PSPACE complete problem. */

#include <stdio.h>
#include <stdlib.h>
#define WIN 1
#define LOSE 0
int **adjacency_matrix;
int number_of_nodes;

int myturn(int from_move);
int yourturn(int from_move);

int main(int argc, char *argv[])
{
 FILE *fp;
 int m,i,j,k,result;

  if(argc < 2) 
  {
   printf("Please specify an input filename in the command line\n");
   return 0;
  }

 fp = fopen(argv[1],"r");
 fscanf(fp,"%d",&number_of_nodes);
 fscanf(fp,"%d",&m); /* m is the number of turns already taken */
 adjacency_matrix = (int **)malloc(sizeof(int *)*number_of_nodes);
 for(i = 0; i < number_of_nodes; i++)
   adjacency_matrix[i] = (int *)malloc(sizeof(int)*number_of_nodes);

 for(i = 0; i < number_of_nodes; i++)
   for(j = 0; j < number_of_nodes; j++)
     adjacency_matrix[i][j] = 1;

 for(k = 0; k < m; k++)
  {
    fscanf(fp,"%d %d",&i,&j);
    adjacency_matrix[i][j] = 0;
    adjacency_matrix[j][i] = 0;
  }

  if(m == 0) j = 0; /* if m==0, start from node 0, (actually, we can start from any node. it doesn't matter.). But j was outside the range 0<=j<=number_of_nodes-1, hence assigning it to 0 */

  if(m % 2 == 0)
   result = myturn(j);
  else
   result = yourturn(j);

  if(result == WIN) printf("Win\n");
  else printf("Lose\n");

 for(i = 0; i < number_of_nodes; i++)
   free(adjacency_matrix[i]);
 
 free(adjacency_matrix);
 fclose(fp);
 
return 0;
}

int myturn(int from_move)
{
 int i;
 int result = LOSE;
 
 for(i = 0; i < number_of_nodes; i++)
  {
    if(adjacency_matrix[from_move][i] == 1)
    { 
     adjacency_matrix[from_move][i] = 0;
     adjacency_matrix[i][from_move] = 0;

     result = result | yourturn(i);   /* during my turn, if there is any one way to win, then it is a win */

     adjacency_matrix[from_move][i] = 1;
     adjacency_matrix[i][from_move] = 1;
     
     if(result == WIN) break;
    }

  }
return(result);

}

int yourturn(int from_move)
{
 int i;
 int result = WIN;
 
 for(i = 0; i < number_of_nodes; i++)
  {
    if(adjacency_matrix[from_move][i] == 1)
    { 
     adjacency_matrix[from_move][i] = 0;
     adjacency_matrix[i][from_move] = 0;
     
     result = result & myturn(i);   /* during the opponent's turn, all moves taken by him should result in a win for us to give us a win */
     
     adjacency_matrix[from_move][i] = 1;
     adjacency_matrix[i][from_move] = 1;
     
     if(result == LOSE) break;
    }

  }
return(result);

}



