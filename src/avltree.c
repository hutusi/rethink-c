/**
 * @file avltree.c
 * @author hutusi (hutusi@outlook.com)
 * @brief Refer to avltree.h
 * @date 2019-07-30
 *
 * @copyright Copyright (c) 2019, hutusi.com
 *
 */

#include "avltree.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef ALLOC_TESTING
#include "alloc-testing.h"
#endif

#define AVL_TREE_NIL NULL

AVLTree *avl_tree_new(AVLTreeCompareFunc compare_func,
                      AVLTreeFreeKeyFunc free_key_func,
                      AVLTreeFreeValueFunc free_value_func)
{
    AVLTree *tree = (AVLTree *)malloc(sizeof(AVLTree));
    tree->compare_func = compare_func;
    tree->free_key_func = free_key_func;
    tree->free_value_func = free_value_func;
    tree->root = AVL_TREE_NIL;
    tree->num_nodes = 0;
    return tree;
}

void avl_tree_free_node(AVLTree *tree, AVLTreeNode *node)
{
    AVLTreeEntity *data = node->data;
    while (data) {
        AVLTreeEntity *prev = data;
        data = data->next;
        if (tree->free_value_func && prev->value) {
            tree->free_value_func(prev->value);
        }
        free(prev);
    }

    if (tree->free_key_func && node->key) {
        tree->free_key_func(node->key);
    }

    free(node);
}

static void avl_tree_free_node_callback(AVLTreeNode *node, void *args)
{
    // printf("free node: [%d]\n", *((int *)(node->data)));
    AVLTree *tree = (AVLTree *)args;
    avl_tree_free_node(tree, node);
}

void avl_tree_free(AVLTree *tree)
{
    // free all nodes
    avl_tree_postorder_traverse(tree, avl_tree_free_node_callback, tree);
    free(tree);
}

static AVLTreeNode *avl_tree_node_new(AVLTreeKey key, AVLTreeValue value)
{
    AVLTreeNode *node = (AVLTreeNode *)malloc(sizeof(AVLTreeNode));

    node->key = key;
    node->data = (AVLTreeEntity *)malloc(sizeof(AVLTreeEntity));
    node->data->value = value;
    node->data->next = NULL;

    node->parent = NULL;
    node->left = node->right = AVL_TREE_NIL;
    node->height = 0;
    return node;
}

static AVLTreeEntity *avl_tree_node_append_value(AVLTreeNode *node,
                                                 AVLTreeValue value)
{
    AVLTreeEntity *entity = (AVLTreeEntity *)malloc(sizeof(AVLTreeEntity));
    entity->value = value;
    entity->next = NULL;

    AVLTreeEntity *data = node->data;
    while (data->next) {
        data = data->next;
    }
    data->next = entity;
    return entity;
}

unsigned int avl_tree_subtree_height(AVLTreeNode *node)
{
    if (node)
        return node->height;
    else
        return 0;
}

static inline void avl_tree_update_node_height(AVLTreeNode *node)
{
    unsigned int left_height = avl_tree_subtree_height(node->left);
    unsigned int right_height = avl_tree_subtree_height(node->right);

    if (left_height > right_height) {
        node->height = left_height + 1;
    } else {
        node->height = right_height + 1;
    }
}

// static inline AVLTreeNode *avl_tree_uncle_node(AVLTreeNode *node)
// {
//     AVLTreeNode *parent = node->parent;
//     if (!parent)
//         return NULL;
//     AVLTreeNode *grandparent = parent->parent;
//     if (!grandparent)
//         return NULL;
//     return grandparent->left == parent ? grandparent->right :
//     grandparent->left;
// }

// static inline AVLTreeNode *avl_tree_sibling_node(AVLTreeNode *node)
// {
//     AVLTreeNode *parent = node->parent;
//     if (!parent)
//         return NULL;
//     return parent->left == parent ? parent->right : parent->left;
// }

static inline void avl_tree_link_to_right(AVLTreeNode *parent,
                                          AVLTreeNode *node)
{
    if (node)
        node->parent = parent;
    parent->right = node;
}

static inline void avl_tree_link_to_left(AVLTreeNode *parent, AVLTreeNode *node)
{
    if (node)
        node->parent = parent;
    parent->left = node;
}

static AVLTreeNode *avl_tree_left_rotate(AVLTree *tree, AVLTreeNode *focus)
{
    if (focus->right == NULL)
        return focus;

    AVLTreeNode *new_focus = focus->right;
    new_focus->parent = focus->parent;

    avl_tree_link_to_right(focus, new_focus->left);
    avl_tree_link_to_left(new_focus, focus);

    if (new_focus->parent == NULL) {
        tree->root = new_focus;
    } else if (new_focus->parent->right == focus) {
        new_focus->parent->right = new_focus;
    } else {
        new_focus->parent->left = new_focus;
    }

    avl_tree_update_node_height(new_focus->left);
    avl_tree_update_node_height(new_focus);

    return new_focus;
}

static AVLTreeNode *avl_tree_right_rotate(AVLTree *tree, AVLTreeNode *focus)
{
    if (focus->left == NULL)
        return focus;

    AVLTreeNode *new_focus = focus->left;
    new_focus->parent = focus->parent;

    avl_tree_link_to_left(focus, new_focus->right);
    avl_tree_link_to_right(new_focus, focus);

    if (new_focus->parent == NULL) {
        tree->root = new_focus;
    } else if (new_focus->parent->right == focus) {
        new_focus->parent->right = new_focus;
    } else {
        new_focus->parent->left = new_focus;
    }

    avl_tree_update_node_height(new_focus->right);
    avl_tree_update_node_height(new_focus);

    return new_focus;
}

static AVLTreeNode *avl_tree_balance_subtree(AVLTree *tree,
                                             AVLTreeNode *subroot)
{
    AVLTreeNode *left_subtree = subroot->left;
    AVLTreeNode *right_subtree = subroot->right;

    unsigned int left_height = avl_tree_subtree_height(left_subtree);
    unsigned int right_height = avl_tree_subtree_height(right_subtree);

    if (left_height >= right_height + 2) {
        if (avl_tree_subtree_height(left_subtree->left) <
            avl_tree_subtree_height(left_subtree->right)) {
            avl_tree_left_rotate(tree, left_subtree);
        }

        subroot = avl_tree_right_rotate(tree, subroot);
    } else if (right_height >= left_height + 2) {
        if (avl_tree_subtree_height(right_subtree->right) <
            avl_tree_subtree_height(right_subtree->left)) {
            avl_tree_right_rotate(tree, right_subtree);
        }

        subroot = avl_tree_left_rotate(tree, subroot);
    } else {
        // do nothing
    }

    avl_tree_update_node_height(subroot);

    return subroot;
}

static void avl_tree_balance_tree(AVLTree *tree, AVLTreeNode *start)
{
    AVLTreeNode *rover = start;

    while (rover != NULL) {
        rover = avl_tree_balance_subtree(tree, rover);
        rover = rover->parent;
    }
}

AVLTreeNode *avl_tree_insert(AVLTree *tree, AVLTreeKey key, AVLTreeValue value)
{
    AVLTreeNode *rover = tree->root;
    AVLTreeNode *insert = AVL_TREE_NIL;
    int comp = 0;

    while (rover != AVL_TREE_NIL) {
        comp = (tree->compare_func)(key, rover->key);
        insert = rover;

        if (comp < 0) {
            rover = rover->left;
        } else if (comp > 0) {
            rover = rover->right;
        } else {
            // equal, no need to insert a node.
            // free the key. shared key with prev node.
            if (tree->free_key_func)
                tree->free_key_func(key);
            avl_tree_node_append_value(rover, value);
            return rover;
        }
    }

    AVLTreeNode *new_node = avl_tree_node_new(key, value);
    new_node->parent = insert;
    ++(tree->num_nodes);

    if (insert == AVL_TREE_NIL) {
        tree->root = new_node;
    } else if (comp < 0) {
        insert->left = new_node;
    } else if (comp > 0) {
        insert->right = new_node;
    } else {
        // impossible
        assert(0);
    }

    if (new_node)
        avl_tree_balance_tree(tree, new_node);

    return new_node;
}

AVLTreeNode *avl_tree_leftmost_node(AVLTreeNode *node)
{
    AVLTreeNode *rover = node;
    while (rover->left != NULL) {
        rover = rover->left;
    }
    return rover;
}

AVLTreeNode *avl_tree_rightmost_node(AVLTreeNode *node)
{
    AVLTreeNode *rover = node;
    while (rover->right != NULL) {
        rover = rover->right;
    }
    return rover;
}

static AVLTreeNode *
avl_tree_replace_node(AVLTree *tree, AVLTreeNode *node, AVLTreeNode *replace)
{
    AVLTreeNode *parent = node->parent;
    if (parent == NULL) { // root
        tree->root = replace;
    } else if (parent->left == node) {
        parent->left = replace;
    } else {
        parent->right = replace;
    }

    if (replace != NULL) {
        replace->parent = parent;
    }

    return node;
}

AVLTreeNode *avl_tree_remove_node(AVLTree *tree, AVLTreeNode *node)
{
    AVLTreeNode *balance = node->parent;

    if (node->left == NULL && node->right == NULL) {
        avl_tree_replace_node(tree, node, NULL);
    } else if (node->left == NULL) {
        balance = node->right;
        avl_tree_replace_node(tree, node, node->right);
    } else if (node->right == NULL) {
        balance = node->left;
        avl_tree_replace_node(tree, node, node->left);
    } else {
        AVLTreeNode *replace = avl_tree_leftmost_node(node->right);
        if (replace != node->right) {
            balance = replace->parent;

            avl_tree_replace_node(tree, replace, replace->right);
            replace->right = node->right;
            node->right->parent = replace;
        }
        avl_tree_replace_node(tree, node, replace);
        replace->left = node->left;
        node->left->parent = replace;
    }

    avl_tree_balance_tree(tree, balance);
    --(tree->num_nodes);
    return node;
}

AVLTreeNode *avl_tree_find_node(AVLTree *tree, AVLTreeKey key)
{
    AVLTreeNode *rover = tree->root;
    while (rover != NULL) {
        int comp = (tree->compare_func)(key, rover->key);
        if (comp < 0) {
            rover = rover->left;
        } else if (comp > 0) {
            rover = rover->right;
        } else /* (comp == 0) */ {
            return rover;
        }
    }
    return NULL;
}

void avl_tree_subtree_print(AVLTreeNode *node, int depth)
{
    if (node == NULL) {
        return;
    }

    avl_tree_subtree_print(node->left, depth + 1);

    for (int i = 0; i < depth * 6; ++i) {
        printf(" ");
    }

    printf("%d[%u]\n", *(int *)node->key, avl_tree_subtree_height(node));

    avl_tree_subtree_print(node->right, depth + 1);
}

static void avl_tree_preorder_internal(AVLTreeNode *node,
                                       AVLTreeTraverseFunc callback,
                                       void *cb_args)
{
    if (node != NULL) {
        if (callback != NULL) {
            callback(node, cb_args);
        }
        avl_tree_preorder_internal(node->left, callback, cb_args);
        avl_tree_preorder_internal(node->right, callback, cb_args);
    }
}

void avl_tree_preorder_traverse(AVLTree *tree,
                                AVLTreeTraverseFunc callback,
                                void *cb_args)
{
    avl_tree_preorder_internal(tree->root, callback, cb_args);
}

static void avl_tree_inorder_internal(AVLTreeNode *node,
                                      AVLTreeTraverseFunc callback,
                                      void *cb_args)
{
    if (node != NULL) {
        avl_tree_inorder_internal(node->left, callback, cb_args);
        if (callback != NULL) {
            callback(node, cb_args);
        }
        avl_tree_inorder_internal(node->right, callback, cb_args);
    }
}

void avl_tree_inorder_traverse(AVLTree *tree,
                               AVLTreeTraverseFunc callback,
                               void *cb_args)
{
    avl_tree_inorder_internal(tree->root, callback, cb_args);
}

static void avl_tree_postorder_internal(AVLTreeNode *node,
                                        AVLTreeTraverseFunc callback,
                                        void *cb_args)
{
    if (node != NULL) {
        avl_tree_postorder_internal(node->left, callback, cb_args);
        avl_tree_postorder_internal(node->right, callback, cb_args);
        if (callback != NULL) {
            callback(node, cb_args);
        }
    }
}

void avl_tree_postorder_traverse(AVLTree *tree,
                                 AVLTreeTraverseFunc callback,
                                 void *cb_args)
{
    avl_tree_postorder_internal(tree->root, callback, cb_args);
}
