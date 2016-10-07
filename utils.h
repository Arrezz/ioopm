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

struct shelf
{
 char * shelfname;
 int amount;
};

typedef struct shelf shelf_t;

struct item
{
  char *name;
  char *description;
  int price;
  shelf_t *shelf; //En bokstav foljd av en eller flera siffror maste ha check.
};

typedef struct item item_t;

typedef union {
  int   i;
  float f;
  char *s;
  shelf_t shelf;
} answer_t;

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
