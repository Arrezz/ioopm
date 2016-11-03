#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "list.h"
/// Define struct tree in your .c file not here! (why?)
struct tree
{
  struct tree *left;
  struct tree *right;
  int key_value;
  item_t node_item;
  ///Vi maste ha funktioner som funkar pa item_t och inte key_value.
};
typedef struct tree tree_t;

/// Creates a new tree
///
/// \returns: empty tree
tree_t *tree_new()
{
  tree_t *createdtree = malloc(sizeof(tree_t));
  createdtree->left = NULL;
  createdtree->right = NULL;
  createdtree->key_value = 0;
    //{ .left = NULL , .right = NULL, .key_value = 0};
  return createdtree;  
}

/// Get the size of the tree 
///
/// \returns: the number of nodes in the tree
int tree_size(tree_t *tree)
{
  if (tree == NULL)
    {
      return 0;
    }
  else
    return (tree_size(tree->left) + 1 + tree_size(tree->right));
}
/// Get the depth of the tree 
///
/// \returns: the depth of the deepest subtree
int tree_depth(tree_t *tree)
{
  if (tree == NULL)
    {
      return 0;
    }
  else
    {
      int left_tree = ((tree_depth(tree->left)+1));
      int right_tree = ((tree_depth(tree->right)+1));
      if (right_tree > left_tree)
        {
          return right_tree;
        }
      else
        {
          return left_tree;
        }
    }
}


struct tree *tree_insert (tree_t *tree, item_t *item){
  int value = list_sum(tree->node_item.shelf_list);
   if (tree == NULL)
    {
     
     tree_t *tree_n = tree_new();       
     tree_n->key_value = value;
     return tree_n; 
    }

  

  
  if (value <= tree->key_value)
    {
      tree->left = tree_insert(tree->left, item);
    }
  else if (value >= tree->key_value)
    {
      tree->right = tree_insert(tree->right, item);
    }
  return tree;
  }

int main()
{
  tree_t *oak = tree_new();
  oak->key_value = 2;
  
   

  while(true)
    {
      int testvalue = 0;
      scanf("%d", &testvalue);    
      tree_insert(testvalue, oak);
     
      int tree_depthresult = tree_depth(oak);
      int tree_sizeresult = tree_size(oak);
      printf("tree depthresult; %d \n tree sizeresult; %d\n", tree_depthresult, tree_sizeresult);
    }
  
  return 0;
  
}





/// This does not need implementation until Assignment 2
bool tree_remove(tree_t *tree)
{
  puts("Not yet implemented");
  return false;
}
