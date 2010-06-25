/*
    Advanced Simulated Filesystem Flora Kernel
    Copyright (C) 2010  Robert Christian Taylor

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 2
    of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <avl_tree.h>
void avl_rotate_left(avl_node_t *node)
{
 avl_node_t *node2 = node->right;
 node->right = node2->left;
 node2->left = node;
 if(node->right!=NULL)
  node->right->parent = node;
 if(node->parent != NULL)
 {
  if(node->parent->left == node)
   node->parent->left = node2;
  else
   node->parent->right = node2;
 }
 node2->parent = node->parent;
 node->parent = node2;
}

void avl_rotate_right(avl_node_t *node)
{
 avl_node_t *node2 = node->left;
 node->left = node2->right;
 node2->right = node;
 if(node->left != NULL)
  node->left->parent = node;
 if(node->parent != NULL)
 {
  if(node->parent->left == node)
   node->parent->left = node2;
  else
   node->parent->right = node2;
 }
 node2->parent = node->parent;
 node->parent = node2;
}

avl_tree_t * avl_newtree(avl_tree_t * tree)
{
 if(tree==NULL)
  return NULL;
 tree->root = NULL;
 return tree;
}

void *avl_find(avl_tree_t *tree,avl_key key)
{
 avl_node_t *node;
 if(tree->root == NULL)
  return NULL;
 node = tree->root;
 while(node!=NULL)
 {
  if(node->key > key)
   node = node->left;
  else if(node->key < key)
   node = node->right;
  else
   break;
 }
 if(node!=NULL)
  return node->value;
 return NULL;
}

int avl_walk(avl_tree_t *tree,int (*callback)(avl_key,void*, void*),void *p)
{
 int state = AVL_GOLEFT;
 int ret;
 avl_node_t *node = tree->root;
 if(node == NULL)
  return -1;
 while(1==1)
 {
  if(state == AVL_GOLEFT)
  {
   if(node->left!=NULL)
    node = node->left;
   else if(node->right!=NULL)
    node = node->right;
   else
   {
    state = AVL_GORIGHT;
    ret = callback(node->key, node->value, p);
    if(ret!=1)
     return ret;
   }
  }
  else if(state == AVL_GORIGHT)
  {
   if(node->parent == NULL)
    return 1;
   if(node == node->parent->right || node->parent->right == NULL)
   {
    state = AVL_GORIGHT;
    node = node->parent;
    ret = callback(node->key, node->value, p);
    if(ret!=1)
     return ret;
   }
   else
   {
     state = AVL_GOLEFT;
     node = node->parent->right;
   }
  }
 }
 return -1;
}

avl_tree_t *avl_deletetree(avl_tree_t *tree)
{
 int state = AVL_GOLEFT;
 avl_node_t *node = tree->root;
 avl_node_t *dnode = NULL;
 free(tree);
 if(node == NULL)
  return NULL;

 while(1==1)
 {
  if(state == AVL_GOLEFT)
  {
   if(node->left!=NULL)
    node = node->left;
   else if(node->right!=NULL)
    node = node->right;
   else
    state = AVL_GORIGHT;
  }
  else if(state == AVL_GORIGHT)
  {
   if(node->parent == NULL)
   {
    free(node);
    return NULL;
   }
   if(node == node->parent->right || node->parent->right == NULL)
   {
    state = AVL_GORIGHT;
    dnode = node;
    node = node->parent;
    free(dnode);
   }
   else
   {
     state = AVL_GOLEFT;
     dnode = node;
     node = node->parent->right;
     free(dnode);
   }
  }
 }
 return NULL;
}

int avl_remove(avl_tree_t *tree,avl_key key){}
int avl_insert(avl_tree_t *tree,avl_key key,void *value){}
