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

#include <stddef.h>

/**
 * @author Robert Christian Taylor
 * @file avl_tree.h
 * @brief Public Interface to avl_tree
 *
 * This file is the public interface to an
 * implementation of an avl binary search tree. All
 * functions and structres are arbrevated with avl_.
 * The function syntax is
 * avl_(action)(avl_tree_t *tree, params....)
 * excluding the destructor and constructor.
 */
/**
 * The key used to identify nodes
 */
 typedef unsigned int avl_key;
/**
 * Constant state for AVL Tree walking.
 * Makes the function go left and right
 * all the way to the bottom of the tree.
 */
 #define AVL_GOLEFT 0
/**
 * Constant state for AVL Tree walking.
 * Makes the function walk right or go up
 */
 #define AVL_GORIGHT 1
/**
 * This structure is used to store information associated with each node.
 *
 * @param key The key of the node.
 * @param value The value associated with the key.
 * @param leftheight The height of the left subtree.
 * @param rightheight the height of the right subtree.
 * @param parent The parent of the node.
 * @param left The left child of the node.
 * @param right The right child of the node.
 */
typedef struct avl_node_t
{
 avl_key key; 	/*The key of the node*/
 void * value; 			/*the data pointer*/
 int leftheight;			/*height of left tree*/
 int rightheight;			/*height of right tree*/
 struct avl_node_t *parent; 	/*pointer to parent*/
 struct avl_node_t *left; 	/*pointer to left node*/
 struct avl_node_t *right; 	/*pointer to right node*/
} avl_node_t;
/**This structure is just a information structure for the Avl Binary Search Tree
 *
 * @param root The root node of the avl tree. NULL if the tree has no nodes.
 */
typedef struct avl_tree_t
{
 avl_node_t * root;
} avl_tree_t;

/**
 * Takes a node and rotates it left around it's parent.
 *
 * @param node A valid pointer to the node to be rotated.
 */
void avl_rotate_left(avl_node_t * node);
/**
 * Takes a node and rotates it right around it's parent.
 *
 * @param node A valid pointer to the node to be rotated.
 */
void avl_rotate_right(avl_node_t * node);
/**
 * Creates a new empty avl_tree.
 *
 * @return A valid address to an avl_tree_t on success else NULL.
 */
avl_tree_t * avl_newtree(avl_tree_t * tree);
/**
 * Deletes an avl tree and frees all of it's data.
 *
 * @param tree A valid pointer to an avl_tree_t that will be deleted.
 * @return NULL on success.
 */
avl_tree_t *avl_deletetree(avl_tree_t * tree);
/**
 * Inserts a new key, value pair into the binary search tree.
 *
 * @param tree A valid pointer to an avl_tree_t.
 * @param key The key that will be used to retrieve the value from the binary search tree.
 * @param value The value that will be stored in the binary search tree.
 * @return 1 on success.
 */
int avl_insert(avl_tree_t * tree,avl_key key,void *value);
/**
 * Finds the value associated with the key and returns it.
 *
 * @param tree A valid pointer to an avl_tree_t.
 * @param key A key used to find the desired value.
 * @return The value associated with the key else NULL.
 */
void * avl_find(avl_tree_t * tree,avl_key key);
/**
 * Removes the key and its value from the binary search tree.
 *
 * @param tree A valid pointer to an avl_tree_t.
 * @param key The id of the key,value pair to be removed.
 * @return The value associated with the key else NULL.
 */
int avl_remove(avl_tree_t * tree,avl_key key);
/**
 * This function is used to walk the tree. A callback function will
 * be supplied. It will be called for every key, value pair encountered.
 * If the callback wants to exit it must return an integer not equal to one.
 *
 * @param tree A valid pointer to an avl_tree_t.
 * @param callback A valid pointer to a callback function.
 * int callback(unsigned intavl_key key, void *value, int *p);
 * @param p The pointer that will be supplied to the callback.
 * @return 1 on success, else -1 on internal error or the return value of the callback.
 */
int avl_walk(avl_tree_t * tree,
 int (* callback)(avl_key,void *, void *),
 void * p);

