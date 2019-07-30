/**
 * @file rbtree.h
 *
 * @author hutusi (hutusi@outlook.com)
 *
 * @brief Red black tree.
 *
 * @date 2019-07-28
 *
 * @copyright Copyright (c) 2019, hutusi.com
 *
 */

#ifndef RETHINK_C_RB_TREE_H
#define RETHINK_C_RB_TREE_H

/**
 * @brief The type of a key to be stored in a @ref RBTree.
 *        (void *) can be changed to int, char *, or other types if needed.
 */
typedef void *RBTreeKey;

/**
 * @brief The type of a key to be stored in a @ref RBTree.
 *        (void *) can be changed to int, char *, or other types if needed.
 */
typedef void *RBTreeValue;

/**
 * @brief Definition of RBTree Colors.
 * 
 */
typedef enum _RBTreeColor { RED = 0, BLACK = 1 } RBTreeColor;

/**
 * @brief Definition of a @ref RBTreeEntity.
 *
 */
typedef struct _RBTreeEntity {
    RBTreeValue value;
    struct _RBTreeEntity *next;
} RBTreeEntity;

/**
 * @brief Definition of a @ref RBTreeNode.
 *
 */
typedef struct _RBTreeNode {
    /** Key of the node. */
    RBTreeKey key;
    /** Values of the node. */
    RBTreeEntity *data;
    /** Parent node pointer. */
    struct _RBTreeNode *parent;
    /** Left child node pointer. */
    struct _RBTreeNode *left;
    /** Right child node pointer. */
    struct _RBTreeNode *right;

    RBTreeColor color;
} RBTreeNode;

typedef int (*RBTreeCompareFunc)(RBTreeValue data1, RBTreeValue data2);
typedef void (*RBTreeFreeKeyFunc)(RBTreeKey key);
typedef void (*RBTreeFreeValueFunc)(RBTreeValue value);

/**
 * @brief Definition of a @ref RBTree.
 *
 */
typedef struct _RBTree {
    /** Root node of the @ref RBTree pointer. */
    struct _RBTreeNode *root;
    /** Compare two node value when do searching in RBTree. */
    RBTreeCompareFunc compare_func;
    RBTreeFreeKeyFunc free_key_func;
    RBTreeFreeValueFunc free_value_func;
    /** The number of nodes of the @ref RBTree. */
    unsigned int num_nodes;
} RBTree;

/**
 * @brief Allcate a new RBTree.
 *
 * @param compare_func      Compare two node value when do searching in RBTree.
 * @param free_key_func     Free key callback function.
 * @param free_value_func   Free value callback function.
 * @return RBTree*          The new RBTree if success, otherwise return NULL.
 */
RBTree *rb_tree_new(RBTreeCompareFunc compare_func,
                    RBTreeFreeKeyFunc free_key_func,
                    RBTreeFreeValueFunc free_value_func);

/**
 * @brief Delete a RBTree and free back memory.
 *
 * @param tree      The RBTree to delete.
 */
void rb_tree_free(RBTree *tree);

/**
 * @brief Free a node in a RBTree.
 * 
 * @param tree  The RBTree
 * @param node  The node.
 */
void rb_tree_free_node(RBTree *tree, RBTreeNode *node);

/**
 * @brief Get the leftmost child node of a RBTreeNode.
 *
 * @param node              The RBTreeNode.
 * @return RBTreeNode*      The leftmost RBTreeNode. If the RBTreeNode has
 *                          no left child, return itself.
 */
RBTreeNode *rb_tree_leftmost_node(RBTreeNode *node);

/**
 * @brief Get the rightmost child node of a RBTreeNode.
 *
 * @param node              The RBTreeNode.
 * @return RBTreeNode*      The rightmost RBTreeNode. If the RBTreeNode has
 *                          no right child, return itself.
 */
RBTreeNode *rb_tree_rightmost_node(RBTreeNode *node);

/**
 * @brief Insert a RBTreeValue to a RBTree.
 *
 * @param tree          The RBTree.
 * @param data          The value to insert.
 * @return RBTreeNode*  The new inserted RBTreeNode if success,
 *                      otherwise return NULL.
 */
RBTreeNode *rb_tree_insert(RBTree *tree, RBTreeKey key, RBTreeValue value);

/**
 * @brief Remove a RBTreeNode from a RBTree.
 *
 * @param tree          The RBTree.
 * @param node          The RBTreeNode.
 * @return RBTreeNode*  The removed RBTreeNode if success,
 *                      otherwise return NULL.
 */
RBTreeNode *rb_tree_remove_node(RBTree *tree, RBTreeNode *node);

/**
 * @brief Find a RBTreeNode value in a RBTree.
 * 
 * @param tree          The RBTree.
 * @param key           The RBTreeNode value to lookup.
 * @return RBTreeNode*  The matched RBTreeNode if success, otherwise NULL.
 */
RBTreeNode *rb_tree_find_node(RBTree *tree, RBTreeKey key);

/**
 * @brief Traverse RBTree callback function.
 * 
 */
typedef void (*RBTreeTraverseFunc)(RBTreeNode *node, void *args);

/**
 * @brief Traverse RBTree by preorder.
 *
 * @param tree          The RBTree.
 * @param callback      The callback function do to each RBTreeNode in traverse.
 * @param cb_args       The callback function's args.
 */
void rb_tree_preorder_traverse(RBTree *tree,
                               RBTreeTraverseFunc callback,
                               void *cb_args);

/**
 * @brief Traverse RBTree by inorder.
 *
 * @param tree          The RBTree.
 * @param callback      The callback function do to each RBTreeNode in traverse.
 * @param cb_args       The callback function's args.
 */
void rb_tree_inorder_traverse(RBTree *tree,
                              RBTreeTraverseFunc callback,
                              void *cb_args);

/**
 * @brief Traverse RBTree by postorder.
 *
 * @param tree          The RBTree.
 * @param callback      The callback function do to each RBTreeNode in traverse.
 * @param cb_args       The callback function's args.
 */
void rb_tree_postorder_traverse(RBTree *tree,
                                RBTreeTraverseFunc callback,
                                void *cb_args);

/**
 * @brief A subtree's height in a RBTree.
 * 
 * @param node            The subtree's root node.
 * @return unsigned int   The height.
 */
unsigned int rb_tree_subtree_height(RBTreeNode *node);

/**
 * @brief Print a subtree.
 * 
 * @param node      The subtree's root node.
 * @param depth     The subtree's depth.
 */
void rb_tree_subtree_print(RBTreeNode *node, int depth);

#endif /* #ifndef RETHINK_C_RB_TREE_H */
