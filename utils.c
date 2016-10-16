#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

bool not_empty(char *str)
{
  return strlen(str) > 0;
}

bool is_number(char *str)
{
  for(int i = 0; i < strlen(str); i++)
    {
      char c = str[i];
      if (isdigit(c) == false)
        {
          return false;
        }
    }
  return true;
}

void clear_input_buffer()
{
  int c;
   do
     {
       c = getchar();
     }
   while (c != '\n');
}   

int read_string(char *buf, int buf_siz )
{
  int counter = 0;
  int c;
  do
        {
          c = getchar();
          buf[counter] = c;
          counter++;
        }
  while (c != '\n' && counter < buf_siz);
  if (buf[counter] != '\n')
          {
            //lear_input_buffer();
          }
  buf[counter-1] = '\0';
 
  return (counter-1);
  }

answer_t ask_question(char *question, check_func check, convert_func convert) 
 { 
   int buf_siz = 254; 
   int control = 0;
   char buf[buf_siz];
   do 
     { 
       printf("%s", question); 
       read_string(buf, buf_siz);
       if (check(buf)) 
         { 
           control++;
         } 
       else 
         { 
           puts("Please enter a valid input!"); 
         } 
     } 
   while (control == 0); 
   return convert(buf);
 } 

int ask_question_int(char *question)
{
  answer_t answer = ask_question(question, is_number, (convert_func) atoi);
  return answer.i; // svaret som ett heltal
}

char *ask_question_string(char *question)
{
  return ask_question(question, not_empty, (convert_func) strdup).s;
}

/*
int main(void)
{
    int buf_siz = 255;
    char *read = 0;
    char buf[buf_siz];
    char *question = "Läs in en sträng:";
    
    ask_question_string(question, buf, buf_siz);
    printf("%s", buf);
    
    return 0;
}
*/
