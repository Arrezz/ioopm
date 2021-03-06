/// !! OBS -- du kommer att behöva ändra lite i denna fil. 
/// !! Detta är en lista som endast hanterar heltal. Men det 
/// !! kommer inte att räcka för oss här eftersom vi skall ha
/// !! andra data (vilka??) i vår (enda) lista. 


#ifndef __list_h__
#define __list_h__
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

/// Define struct list in your .c file not here! (why?)
typedef struct list list_t;

typedef struct link link_t;

/// \file list.h

/// Creates a new list
///
/// \returns: empty list

list_t *list_new();

/// \file link.h
///
/// Creates a new link

link_t *link_new();

/// Inserts a new element at the end of the list
///
/// \param list pointer to the list
/// \param elem the integer to be appended
void list_append(list_t *list, int elem);

/// Inserts a new element at the beginning of the list
///
/// \param list pointer to the list
/// \param elem the integer to be prepended
void list_prepend(list_t *list, int elem);


char *list_getshelfname(list_t *list, int index);

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
bool list_insert(list_t *list, int index, int elem);

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
bool list_remove(list_t *list, int index, int *elem);

/// Returns the element at a given index
/// \param list  pointer to the list
/// \param index the index to be returns
/// \returns a pointer to the element at index index
int *list_get(list_t *list, int index);

/// A convenience for list_get(list, 0)
int *list_first(list_t *list);

/// A convenience for list_get(list, -1)
int *list_last(list_t *list);

/// Returns the length of the list. It is undefined
/// whether the length is calculated in O(n) time or
/// whether there is a size counter in the list object
/// that is manipulated by insert, remove, etc. 
/// \param list the list
/// \returns the length of list
int list_length(list_t *list);

int list_sum(list_t *list);

#endif
