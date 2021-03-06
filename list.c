/// !! OBS -- du kommer att behöva ändra lite i denna fil. 
/// !! Detta är en lista som endast hanterar heltal. Men det 
/// !! kommer inte att räcka för oss här eftersom vi skall ha
/// !! andra data (vilka??) i vår (enda) lista.
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
/// Define struct list in your .c file not here! (why?)
typedef struct list list_t;

typedef struct link link_t;

struct link
{
  int value;
  char *shelf;
  link_t *next;
};

struct list
{
  link_t *first;
  link_t *last; 
};

/// \file list.h
///
/// \author Tobias Wrigstad
/// \version 1.0
/// \date 2015-08-28
/// \bug None known. But this code is untested so there are likely bigs in it. 


/// Creates a new list
///
/// \returns: empty list
list_t *list_new()
{
  list_t *createdlist = malloc(sizeof(list_t));
  createdlist->first = NULL;
  createdlist->last = NULL;
  return createdlist;
}


link_t *link_new()
{
  link_t *createdlink = malloc(sizeof(link_t));

  createdlink->value = NULL;
  createdlink->next = NULL;
  createdlink->shelf = NULL;

  
  return createdlink;
  
}


char *list_getshelfname(list_t *list, int index)
{
  int i = 0;
  char *str = " ";
  struct link *travlist;

  travlist = list->first;
  
  for(;(i < index && travlist->next != 0); i++)
    {
      travlist = travlist->next;
    }
  str = travlist->shelf; 
  return str;	
}


/// Inserts a new element at the end of the list
///
/// \param list pointer to the list
/// \param elem the integer to be appended
void list_append(list_t *list, int elem)
{
  
  link_t *new_l = link_new(); 
  new_l->value = elem;
  

  if (list->last == 0){
    
    list->last = new_l;
    list->first= new_l;
  }

  else {
    list->last->next = new_l;
    
  }
  
  
  
}
/// Inserts a new element at the beginning of the list
///
/// \param list pointer to the list
/// \param elem the integer to be prepended

void list_prepend(list_t *list, int elem)
{
  
  link_t *new_l = link_new();
  new_l->value = elem; 


  if (list->last == 0){
    
    list->last = new_l;
    list->first= new_l;
  }

  else {
    new_l->next = list->first;
    list->first = new_l;
    }   
}

/// Inserts a new element at a given index. 
///
/// Valid indexes are [0..size]. 
///
/// Example:
///
/// list_t *l = list_new(); // l == []
/// list_insert(l, 0, 42);  // l == [42]
/// list_insert(l, 0, 43);  // l == [43, 42]
/// list_insert(l, 1, 44);  // l == [43, 44, 42]
/// list_insert(l, 5, 45);  // l == [43, 44, 42]
///
/// The last case fails (and returns false) because
/// size is 3, meaning 5 is not a valid index. 
///
/// Note that insert at index 0 is the same as prepend 
/// and insert index size is the same as append. 
///
/// Negative indexes should be supported:
///
/// list_insert(l, -1, 45);       // l == [43, 44, 42, 45]
///
/// A positive index can be calculated from a 
/// negative like this: pos_i = size + 1 + neg_i.
/// 
/// \param list  pointer to the list
/// \param index the index for elem to be inserted at
/// \param elem  the integer to be prepended
/// \returns true if succeeded, else false
bool list_insert(list_t *list, int index, int elem)
{
 
  struct link *travlist;
  struct link *travlist_prev = 0;
  
     
  
      
      if (list->first == 0) {

	if (index != 0) {
	  puts("ej tillåtet index");
	  return false;
	}

	 link_t *new = link_new();
	 new->value = elem;  
	 list->first = new;
	 list->last = new;
	 return true;
      }



      
      travlist = list->first;
      



      for(int i = 0; i < index; i++)
	{

	 
	  if (travlist->next == 0) {
	     puts("ej tillåtet index");
	       return false;
	}
	  travlist_prev = travlist;
	  travlist = travlist->next;
	 
	}
      
      

      //}
       
      
      
     

      link_t *new = link_new();
      new->value = elem;    
      new->next = travlist;
      
     
      if (travlist_prev != 0) travlist_prev->next = new;
 
      
      if (index == 0)
	{
	  list->first = new;
	}
      return true;
      
  
}
// haer legger vi in not


/// Removes an element from a list.
///
/// Example: (assume l == [43, 44, 42, 45])
///
/// int elem;
/// list_remove(l, 1, &elem);  // l = [43, 42, 45], elem == 44
/// list_remove(l, -1, &elem); // l = [43, 42], elem == 45
///
/// \param list  pointer to the list
/// \param index the index to be removed
/// \param elem a pointer to where the element can be stored
/// \returns true if succeeded, else 
bool list_remove(list_t *list, int index, int *elem)
{
  struct link *travlist;
  //struct link *travlist_prev;
  if (list->first != 0)
    {
      travlist = list->first;
      for(int i = 0; (i = index || travlist->next == 0); i++)
	{
	  //travlist_prev = travlist;
	  travlist = travlist->next;
	}
      if (travlist == 0) return false; 
      else
	{
	  elem = &travlist->value;
	  //travlist_prev = travlist->next;
	  return true;
	}
    }
  return false;
}

/// Returns the element at a given index
/// \param list  pointer to the list
/// \param index the index to be returns
/// \returns a pointer to the element at index index
int *list_get(list_t *list, int index)
{
  int i = 0;
  int *value = 0;
  struct link *travlist;

  travlist = list->first;
  
  for(;(i < index && travlist->next != 0); i++)
    {
      travlist = travlist->next;
    }
  value = &travlist->value; 
  return value;	
}

/// Returns the length of the list. It is undefined
/// whether the length is calculated in O(n) time or
/// whether there is a size counter in the list object
/// that is manipulated by insert, remove, etc. 
/// \param list the list
/// \returns the length of list
int list_length(list_t *list)
{
  
  int i = 0;
  struct link *travlist;
  if (list->first != 0)
    {

      travlist = list->first;
      for(i = 1; travlist->next != 0; i++)
	{
	  	  travlist = travlist->next;
	}
      
      return i;
      
    }

      return 0; 
}

int list_sum(list_t *list)
{
  
  int i = 0;
  int sum = 0;
  struct link *travlist;
  if (list->first != 0)
    {

      travlist = list->first;
      for(i = 1; travlist->next != 0; i++)
	{
          sum = sum + travlist->value;
	  travlist = travlist->next;
	}
      
      return sum;
      
    }
  return 0; 
}
/// A convenience for list_get(list, 0)
int *list_first(list_t *list)
{  
  return (list_get(list, 0));
}

/// A convenience for list_get(list, -1)
int *list_last(list_t *list)
{
  return (list_get(list, list_length(list)));
}


void clear(void) {
 int u;
  do {
    u = getchar();
  }
  while (u != '\n');
}

int main()
{
  list_t *list = list_new();
  
  int ind;
  int val;
  char c;
  
  
  while (true) {
    int len = list_length(list);
    printf("Langden av listan: %d\n", len);
    puts(" [a]dd index value\n app[e]nd value\n [p]repend value\n [g]et index value\n [f]irst element in list\n [l]ast element in list");
        
    scanf("%c", &c);
    switch (c) {
      
    case 'a':
      clear();
      
      scanf("%d %d", &ind, &val);
      printf("index: %d\nvalue: %d\n",ind,val);
      
        
      list_insert(list , ind, val);
      clear();
      break;
      
      
    case 'g': 
      clear();
      puts("vilket index vill du visa value i:");
      scanf("%d", &ind);
      
      
      if (len < ind || len == 0) printf("det finns inget element vid index %d\n",ind);
      else {
	int *index_value_get = list_get(list, ind);
	printf("index %d elementet i listan e: %d\n",ind, *index_value_get);
      }
      clear();
      break;
 

    case 'f':
      clear();
      if (len == 0) puts("listan e tom, det finns inget first element");
      else {
	int *first = list_first(list);
	printf("Forsta elementet i listan ar: %d\n", *first);
      }      
      break;
  
    case 'l':
      clear();
      if (len == 0) puts("listan e tom, det finns inget last element");
      else {
	int *last = list_last(list);
	printf("sista elementet i listan e: %d\n", *last);
      }
      break;
      
    case 'e':
      clear();
      puts("vilket value vill du appenda:");
      scanf("%d", &ind);
      
      list_append(list, ind);
      int *last = list_last(list);
      printf("sista elementet i listan ar nu: %d\n", *last);
            
      clear();
      break;

      
    case 'p':
      
      clear();
      puts("vilket value vill du appenda:");
      scanf("%d", &ind);
      
      list_prepend(list, ind);
      int *first = list_first(list);
      printf("forsta elementet i listan ar nu: %d\n", *first);
      clear();
      break;
      
    }
  }
return 0;
}
