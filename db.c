#include "utils.h"
#include "list.h"
#include "tree.h"


void print_item(item_t *item)
{
  printf("Name:%s\nDescription:%s\nPrice:%d.%d\n", item->name, item->description, item->price, item->price/100);
  for (int i = 0; i < list_length(item->shelf_list); i++)
    {
      int *currpos = list_get((item->shelf_list), i);
      list_t *list = item->shelf_list;
      printf("%s, %d", (list_getshelfname(list, i)) , *currpos);
    }
}

item_t make_item(char *name, char *description, int price, list_t *shelf)
{
  item_t createditem;
  createditem.name = name;
  createditem.description= description;
  createditem.price = price;
  list_t *shelves = list_new();
  for (int i = 0; i < list_length(shelf) ; i++)
    {
      list_insert(shelves, i, *list_getshelfname(shelf , i));
    }
  return createditem;
  ///Nagon listfunktion for att ta in alla shelves?
}

bool is_shelf(list_t *shelf)
{
  if ((isdigit(shelf->first->shelfname[0])))
    {
      return false;
    }
  for (int i = 1; i < strlen(shelf->first->shelfname); i++)
    {
      if (!isdigit(shelf->first->shelfname[i]))
	{
	  return false;
	}
    }
  return true;
}
  
list_t *ask_question_shelf(char *question)
{
  return ask_question(question,(check_func) is_shelf ,(convert_func) strdup).shelf;
}

item_t input_item()
{
  char *name;
  char *description;
  int price;
  list_t *shelf;
  name = ask_question_string("Vad heter varan?");
  description = ask_question_string("Vad ar varans beskrivning?");
  price = ask_question_int("Vad ar varans pris?");
  shelf = ask_question_shelf("Vilken hyllplats ar varan pa?");
  item_t item = (make_item(name, description, price, shelf));
  return item;
  ///tree_insert bor anvandas har
}


void list_db(tree_t *tree, int db_siz)
{
for (int i = 0;i > db_siz;i++)
  {
    printf("Vara:%s    Index:%d", tree->items->shelf_list->first->shelfname, db_siz);      ///Rekursiv funktion med left och right tree?
  }
}


tree_t *edit_db(tree_t *db, int db_siz)
{
  list_db(db, db_siz); //Lists database
  int pos = ask_question_int("\nVilken vara skall editeras?");
  while (pos > 16 || pos<1)
    {
      pos = ask_question_int("Du måste välja en vara mellan 1-16!\nVilken vara skall editeras?");
    }
  print_item(*db);  //Varför '&'???
  printf("\nVill du ersätta vara %d med en ny vara?", pos);
  char *choice =  ask_question_string("(Y/N)");
  if (*choice == 'Y' || *choice == 'y')
    {
      db = tree_insert(input_item(),&(*db));
      puts("\n");
      return db;
    }
  puts("\n");
  return db;
}

void add_item_to_db(tree_t *db, int *db_siz)
{
  item_t newitem = input_item();
  db = tree_insert(newitem,&db);
  *db_siz = *db_siz + 1;
}

void remove_item_from_db(tree_t *db, int *db_siz)
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

void event_loop (tree_t *db, int *db_siz)
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

//print_item - listar en vara 
//make_item - om varan inte finns så görs en ny nod i trädet för varan 
//is_shelf - kollar om shelf name är legit
//ask_question_shelf - frågar efter input och vill ha legit shelf som svar 
//input_item - tar user input för all varuinformation
//list_db - printar hela varukorgen
//add_item_to_db - lägger till en vara/nod i trädet
//remove_item_from_db - tar bort en vara/nod i trädet

int main(int argc, char *argv[])
{
  

  tree_t *tree = tree_new(); 


  

}
