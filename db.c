#include "utils.h"
#include "list.h"
#include "tree.h"


void print_item(item_t *item)
{
  printf("Name:%s\nDescription:%s\nPrice:%d.%d\n", item->name, item->description, item->price, item->price/100);
  for (int i = 0; i < list_length(item->shelf); i++)
    {
      int * currpos = list_get((item->shelf), i); 
      printf(("%s, %d") , currpos);
    }
}

item_t make_item(char *name, char *description, int price, shelf_t *shelf)
{
  item_t createditem;
  createditem->name = name;
  createditem->description= description;
  createditem.price = price;
  shelf_t *shelves = list_new();
  for (int i = 0; i < list_length(shelves) ; i++)
    {
      list_insert(shelves, i,shelves[i]->value);
    }
  return createditem;
  ///Nagon listfunktion for att ta in alla shelves?
}

bool is_shelf(shelf_t *shelf)
{
  if ((isdigit(shelf->shelfname[0])))
    {
      return false;
    }
  for (int i = 1; i < strlen(shelf->shelfname); i++)
    {
      if (!isdigit(shelf->shelfname[i]))
	{
	  return false;
	}
    }
  return true;
}
  
shelf_t *ask_question_shelf(char *question)
{
  return ask_question(question, is_shelf ,(convert_func) strdup).s;
}


item_t input_item()
{
  char *name;
  char *description;
  int price;
  shelf_t shelf;
  name = ask_question_string("Vad heter varan?");
  description = ask_question_string("Vad ar varans beskrivning?");
  price = ask_question_int("Vad ar varans pris?");
  shelf = ask_question_shelf("Vilken hyllplats ar varan pa?");
  item_t item = (make_item(name, description, price, shelf));
  return item;
  ///tree_insert bor anvandas har
}

char * magick(char *firstarray[], char *secondarray[], char *thirdarray[], int lengthofarray)
{
  int buf_siz = 255;
  char buf[buf_siz];
  int index = 0;
  char c;
  int i = 0;
  char *firstword = firstarray[rand() % lengthofarray];
  char *secondword = secondarray[rand() % lengthofarray];
  char *thirdword = thirdarray[rand() % lengthofarray];
 
  for(i = 0; i <= strlen(firstword) ; ++i )
    {
      c = firstword[i];
      buf[index] = c;
      if (c == '\0')
	{
	  buf[index] = '-';
	}
      ++index;
    }
  for(i = 0 ; i <= strlen(secondword) ; ++i)
    {
      c = secondword[i];
      buf[index] = c;
      if (c == '\0')
	{
	  buf[index] = ' ';
	}
      ++index;
    }
  for(i = 0 ;i <= strlen(thirdword); ++i )
    {
      c = thirdword[i];
      buf[index] = c;
      if (c == '\0')
	{
	  buf[index] = '\0';
	}
      ++index;
    }
   
  return strdup(buf);
}



void list_db(item_t *items, int no_items)
{
  for(int i = 0; i <  no_items; ++i)
    {
      printf("%d. %s\n",i+1, items[i].name);
    }
}


item_t *edit_db(item_t *db, int db_siz)
{
  list_db(db, db_siz); //Lists database
  int pos = ask_question_int("\nVilken vara skall editeras?");
  while (pos > 16 || pos<1)
    {
      pos = ask_question_int("Du måste välja en vara mellan 1-16!\nVilken vara skall editeras?");
    }
  print_item(&db[pos-1]);  //Varför '&'???
  printf("\nVill du ersätta vara %d med en ny vara?", pos);
  char *choice =  ask_question_string("(Y/N)");
  if (*choice == 'Y' || *choice == 'y')
    {
      db[pos-1] = input_item();
      puts("\n");
      return db;
    }
  puts("\n");
  return db;
}

void add_item_to_db(item_t *db, int *db_siz)
{
  item_t newitem = input_item();
  db[*db_siz] = newitem;
  *db_siz = *db_siz + 1;
}

void remove_item_from_db(item_t *db, int *db_siz)
{
  list_db(db, *db_siz);
  int pos = ask_question_int("\nVilken vara skall tas bort?");
  while (pos > 16 || pos<1)
    {
      pos = ask_question_int("Du måste välja en vara mellan 1-16!\nVilken vara skall editeras?");
    }
  for ( int index = pos; 16 > index ; ++index)
    {
      db[index-1] = db[index];
    }
  *db_siz = *db_siz-1;
}

void print_menu()
{
  puts("\n[L]ägga till en vara\n");
  puts("[T]a bort en vara\n");
  puts("[R]edigera en vara\n");
  puts("Ån[g]ra senaste ändringen\n");
  puts("Lista [h]ela varukatalogen\n");
  puts("[A]vsluta");
}

char ask_question_menu()
{
  print_menu();
  char *answer = ask_question("\nValj ett alternativ\n", not_empty, (convert_func) strdup).s;
  char uppercaseanswer = (toupper(answer[0]));
  if (uppercaseanswer == 'L' || 'T' || 'R' || 'G' || 'H' || 'A')
    {
      return uppercaseanswer;
    }
  else
    {
      puts("Invalid input!");
      ask_question_menu();
    }
}

void event_loop (item_t *db, int *db_siz)
{
  char choice = ask_question_menu();
  int control = 0;
  while( control == 0)
    {
      if (choice == 'L')
        {
          if (*db_siz >= 16)
            {
              puts("For manga element!");
              choice = ask_question_menu();
            }
          else
            {
	      add_item_to_db(db, db_siz);
	      choice = ask_question_menu();
            }
        }
      else if (choice == 'T')
        {
          remove_item_from_db(db, db_siz);
          choice = ask_question_menu();
        }
      else if (choice == 'R')
        {
          edit_db(db, *db_siz);
          choice = ask_question_menu();
        }
      else if (choice == 'G')
        {
          puts("Not yet implemented");
          choice = ask_question_menu();
        }
      else if (choice == 'H')
        {
          list_db(&db[0], *db_siz);
          choice = ask_question_menu();
        }
      else if (choice == 'A')
        {
          control = control + 1;
        }
      else
        {
          puts("Error with character check");
        }
    }
}

int main(int argc, char *argv[])
{
  char *array1[] = { "Laser",        "Polka",    "Extra" };
  char *array2[] = { "förnicklad",   "smakande", "ordinär" };
  char *array3[] = { "skruvdragare", "kola",     "uppgift" };
  if (argc < 2)
    {
      printf("Usage: %s number\n", argv[0]);
    }
  else
    {
      item_t db[16]; // Array med plats för 16 varor
      int db_siz = 0;    // Antalet varor i arrayen just nu

      int items = atoi(argv[1]); // Antalet varor som skall skapas

      if (items > 0 && items <= 16)
	{
	  for (int i = 0; i < items; ++i)
	    {
	      // Läs in en vara, lägg till den i arrayen, öka storleksräknaren
	      item_t item = input_item();
	      db[db_siz] = item;
	      ++db_siz;
	    }
	}
      else    {
	puts("Sorry, must have [1-16] items in database.");
	return 1; // Avslutar programmet!
      }

      for (int i = db_siz; i < 16; ++i)
	{
	  char *name = magick(array1, array2, array3, 3); /// Lägg till storlek
	  char *desc = magick(array1, array2, array3, 3); /// Lägg till storlek
	  int price = rand() % 200000;
	  char shelf[] = { rand() % ('Z'-'A') + 'A',
			   rand() % 10 + '0',
			   rand() % 10 + '0',
			   '\0' };
	  item_t item = make_item(name, desc, price, strdup(shelf));

	  db[db_siz] = item;
	  ++db_siz;
	}

      // Skriv ut innehållet
      list_db(&db[0], db_siz);
      event_loop(db, &db_siz);
    }
  return 0;
}
