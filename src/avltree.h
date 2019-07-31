/**
 * @file avltree.h
 *
 * @author hutusi (hutusi@outlook.com)
 *
 * @brief AVL tree.
 *
 * @date 2019-07-30
 *
 * @copyright Copyright (c) 2019, hutusi.com
 *
 */

#ifndef RETHINK_C_AVL_TREE_H
#define RETHINK_C_AVL_TREE_H

/**
 * @brief The type of a key to be stored in a @ref AVLTree.
 *        (void *) can be changed to int, char *, or other types if needed.
 */
typedef void *AVLTreeKey;

/**
 * @brief The type of a key to be stored in a @ref AVLTree.
 *        (void *) can be changed to int, char *, or other types if needed.
 */
typedef void *AVLTreeValue;

/**
 * @brief Definition of a @ref AVLTreeEntity.
 *
 */
typedef struct _AVLTreeEntity {
    AVLTreeValue value;
    struct _AVLTreeEntity *next;
} AVLTreeEntity;

/**
 * @brief Definition of a @ref AVLTreeNode.
 *
 */
typedef struct _AVLTreeNode {
    /** Key of the node. */
    AVLTreeKey key;
    /** Values of the node. */
    AVLTreeEntity *data;
    /** Parent node pointer. */
    struct _AVLTreeNode *parent;
    /** Left child node pointer. */
    struct _AVLTreeNode *left;
    /** Right child node pointer. */
    struct _AVLTreeNode *right;

    /** Node's height in the AVLTree. */
    unsigned int height;
} AVLTreeNode;

typedef int (*AVLTreeCompareFunc)(AVLTreeValue data1, AVLTreeValue data2);
typedef void (*AVLTreeFreeKeyFunc)(AVLTreeKey key);
typedef void (*AVLTreeFreeValueFunc)(AVLTreeValue value);

/**
 * @brief Definition of a @ref AVLTree.
 *
 */
typedef struct _AVLTree {
    /** Root node of the @ref AVLTree pointer. */
    struct _AVLTreeNode *root;
    /** Compare two node value when do searching in AVLTree. */
    AVLTreeCompareFunc compare_func;
    AVLTreeFreeKeyFunc free_key_func;
    AVLTreeFreeValueFunc free_value_func;
    /** The number of nodes of the @ref AVLTree. */
    unsigned int num_nodes;
} AVLTree;

/**
 * @brief Allcate a new AVLTree.
 *
 * @param compare_func      Compare two node value when do searching in AVLTree.
 * @param free_key_func     Free key callback function.
 * @param free_value_func   Free value callback function.
 * @return AVLTree*          The new AVLTree if success, otherwise return NULL.
 */
AVLTree *avl_tree_new(AVLTreeCompareFunc compare_func,
                    AVLTreeFreeKeyFunc free_key_func,
                    AVLTreeFreeValueFunc free_value_func);

/**
 * @brief Delete a AVLTree and free back memory.
 *
 * @param tree      The AVLTree to delete.
 */
void avl_tree_free(AVLTree *tree);

/**
 * @brief Free a AVLTreeNode in a AVLTree.
 * 
 * @param tree  The AVLTree
 * @param node  The AVLTreeNode.
 */
void avl_tree_free_node(AVLTree *tree, AVLTreeNode *node);

/**
 * @brief Get the leftmost child node of a AVLTreeNode.
 *
 * @param node              The AVLTreeNode.
 * @return AVLTreeNode*      The leftmost AVLTreeNode. If the AVLTreeNode has
 *                          no left child, return itself.
 */
AVLTreeNode *avl_tree_leftmost_node(AVLTreeNode *node);

/**
 * @brief Get the rightmost child node of a AVLTreeNode.
 *
 * @param node              The AVLTreeNode.
 * @return AVLTreeNode*      The rightmost AVLTreeNode. If the AVLTreeNode has
 *                          no right child, return itself.
 */
AVLTreeNode *avl_tree_rightmost_node(AVLTreeNode *node);

/**
 * @brief Insert a AVLTreeValue to a AVLTree.
 *
 * @param tree          The AVLTree.
 * @param data          The value to insert.
 * @return AVLTreeNode*  The new inserted AVLTreeNode if success,
 *                      otherwise return NULL.
 */
AVLTreeNode *avl_tree_insert(AVLTree *tree, AVLTreeKey key, AVLTreeValue value);

/**
 * @brief Remove a AVLTreeNode from a AVLTree.
 *
 * @param tree          The AVLTree.
 * @param node          The AVLTreeNode.
 * @return AVLTreeNode*  The removed AVLTreeNode if success,
 *                      otherwise return NULL.
 */
AVLTreeNode *avl_tree_remove_node(AVLTree *tree, AVLTreeNode *node);

/**
 * @brief Find a AVLTreeNode value in a AVLTree.
 * 
 * @param tree          The AVLTree.
 * @param key           The AVLTreeNode value to lookup.
 * @return AVLTreeNode*  The matched AVLTreeNode if success, otherwise NULL.
 */
AVLTreeNode *avl_tree_find_node(AVLTree *tree, AVLTreeKey key);

/**
 * @brief Traverse AVLTree callback function.
 * 
 */
typedef void (*AVLTreeTraverseFunc)(AVLTreeNode *node, void *args);

/**
 * @brief Traverse AVLTree by preorder.
 *
 * @param tree          The AVLTree.
 * @param callback      The callback function do to each AVLTreeNode in traverse.
 * @param cb_args       The callback function's args.
 */
void avl_tree_preorder_traverse(AVLTree *tree,
                               AVLTreeTraverseFunc callback,
                               void *cb_args);

/**
 * @brief Traverse AVLTree by inorder.
 *
 * @param tree          The AVLTree.
 * @param callback      The callback function do to each AVLTreeNode in traverse.
 * @param cb_args       The callback function's args.
 */
void avl_tree_inorder_traverse(AVLTree *tree,
                              AVLTreeTraverseFunc callback,
                              void *cb_args);

/**
 * @brief Traverse AVLTree by postorder.
 *
 * @param tree          The AVLTree.
 * @param callback      The callback function do to each AVLTreeNode in traverse.
 * @param cb_args       The callback function's args.
 */
void avl_tree_postorder_traverse(AVLTree *tree,
                                AVLTreeTraverseFunc callback,
                                void *cb_args);

/**
 * @brief A subtree's height in a AVLTree.
 * 
 * @param node            The subtree's root node.
 * @return unsigned int   The height.
 */
unsigned int avl_tree_subtree_height(AVLTreeNode *node);

/**
 * @brief Print a subtree.
 * 
 * @param node      The subtree's root node.
 * @param depth     The subtree's depth.
 */
void avl_tree_subtree_print(AVLTreeNode *node, int depth);

#endif /* #ifndef RETHINK_C_AVL_TREE_H */
