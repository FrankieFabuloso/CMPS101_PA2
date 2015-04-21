/*-----------------------------------------------------------------------------
 * Lex.c
 *
 * Name: Francisco Rocha
 * User ID: frocha
 * Program name: pa2
 * Source code: Professor Tantalo
 *
*///---------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"

#define MAX_LEN 160

int main(int argc, char * argv[]){   
   int n, count=0;
   FILE *in, *out;
   char line[MAX_LEN];
   char tokenlist[MAX_LEN];
   char* token;

   // check command line for correct number of arguments
   if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

   // open files for reading and writing 
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   if( in==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
   if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }

   /* read each line of input file, then count and print tokens */
   while( fgets(line, MAX_LEN, in) != NULL)  {
      count++;
      n = 0;
      token = strtok(line, " \n");
      tokenlist[0] = '\0';
      while( token!=NULL ){
         strcat(tokenlist, "   ");
         strcat(tokenlist, token);
         strcat(tokenlist, "\n");
         n++;
         token = strtok(NULL, " \n");
      }
   }

   fclose(in);

   char** words;
   words = malloc(sizeof(char*) * (count)); //made array 
   in = fopen(argv[1], "r");

   char wordsSize [MAX_LEN];

/* - -fills array with the file input - - */
   int i;
   for(i=0; i<count; i++){
      char* x = fgets(wordsSize, MAX_LEN, in);
      if(x == NULL){
      break;
      }

      char* position = strchr(wordsSize, '\n');
      if(position != NULL){
      position = ('\0');
      }

      size_t strlen(position);
      words[i] = calloc(length + 1, sizeof(char*));
      strcpy(words[i], wordsSize);
   }  
/* -- checking to see if array was make correctly -- *  
   int k;
   for(k=0; k<count; k++){
   fprintf(stdout, "%s", words[k]);
   }  
   fprintf(out, "\n");

*/
/*------using read in String[] named tokens alphebetize words in array-----*/

   List new1 = newList();
   int j;

/* ------ sort the new list ----*/
   prepend(new1, 0);

   for(j= 1; j<count; j++ ){
      while(getIndex(new1) != -1 && strcmp(words[getElement(new1)], words[j]) < 0){
      moveNext(new1);
      }
      if(getIndex(new1) == -1){
      append(new1, j);
      moveTo(new1, 0);
      }
      else if(strcmp(words[getElement(new1)], words[j]) >= 0){
      insertBefore(new1, j);
      moveTo(new1, 0);
      }
   }

   printList(stdout, new1);

   moveTo(new1, 0);

   while(getIndex(new1) > -1){
      fprintf(out, "%s", words[getElement(new1)]);
      moveNext(new1);
   }

   for(j=0; j < count; j++){
      free(words[j]);
   }
   clear(new1);
   free(words);
   freeList(&new1);

   fclose(in);
   fclose(out);

   return(0);
}
