#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include "list.h"
#include "tree.h"
extern char *strdup(const char *);

struct item
{
  char *name;
  char *description;
  int price;
  list_t *shelf_list; //En bokstav foljd av en eller flera siffror maste ha check.
};

struct list
{
  link_t *first;
  link_t *last; 
};

struct link
{
  int value;
  char *shelfname;
  link_t *next;
};

typedef union {
  int   i;
  float f;
  char *s;
  list_t *shelf;
} answer_t;

typedef struct list list_t;

typedef struct item item_t;

typedef bool(*check_func)(char *);

typedef answer_t(*convert_func)(char *);

bool not_empty(char *str);

bool is_number(char *str);

void clear_input_buffer();

int read_string(char *buf, int buf_siz );

int ask_question_int(char *question);

char *ask_question_string(char *question);

answer_t ask_question(char *question, check_func check, convert_func convert);

#endif
