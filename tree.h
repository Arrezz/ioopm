#ifndef __tree_h__
#define __tree_h__

#include <stdbool.h>

/// Define struct tree in your .c file not here! (why?)
typedef struct tree tree_t;

/// \file tree.h

/// Creates a new tree
///
/// \returns: empty tree
tree_t *tree_new();

/// Get the size of the tree 
///
/// \returns: the number of nodes in the tree
int tree_size(tree_t *tree);

/// Get the depth of the tree 
///
/// \returns: the depth of the deepest subtree
int tree_depth(tree_t *tree);

/// Insert a node into the tree.

struct tree *tree_insert(int value, tree_t **tree);

/// This does not need implementation until Assignment 2
bool tree_remove(tree_t *tree);

#endif
