/**
 * @file bstree.h
 *
 * @author hutusi (hutusi@outlook.com)
 *
 * @brief Binary search tree.
 *
 * @date 2019-07-20
 *
 * @copyright Copyright (c) 2019, hutusi.com
 *
 */

#ifndef RETHINK_C_BS_TREE_H
#define RETHINK_C_BS_TREE_H

/**
 * @brief The type of a value to be stored in a @ref BSTreeNode.
 *        (void *) can be changed to int, long, or other types if needed.
 */
typedef void *BSTreeValue;

/**
 * @brief Definition of a @ref BSTreeNode.
 *
 */
typedef struct _BSTreeNode {
    /** Value of the node. */
    BSTreeValue data;
    /** Parent node pointer. */
    struct _BSTreeNode *parent;
    /** Left child node pointer. */
    struct _BSTreeNode *left;
    /** Right child node pointer. */
    struct _BSTreeNode *right;
} BSTreeNode;

typedef int (*BSTreeCompareFunc)(BSTreeValue data1, BSTreeValue data2);

/**
 * @brief Definition of a @ref BSTree.
 *
 */
typedef struct _BSTree {
    /** Root node of the @ref BSTree pointer. */
    struct _BSTreeNode *root;
    /** Compare two node value when do searching in BSTree. */
    BSTreeCompareFunc compare_func;
    /** The number of nodes of the @ref BSTree. */
    unsigned int num_nodes;
} BSTree;

/**
 * @brief Allcate a new BSTree.
 *
 * @param compare_func  Compare two node value when do searching in BSTree.
 * @return BSTree*      The new BSTree if success, otherwise return NULL.
 */
BSTree *bs_tree_new(BSTreeCompareFunc compare_func);

/**
 * @brief Delete a BSTree and free back memory.
 *
 * @param tree      The BSTree to delete.
 */
void bs_tree_free(BSTree *tree);

/**
 * @brief Get the leftmost child node of a BSTreeNode.
 *
 * @param node              The BSTreeNode.
 * @return BSTreeNode*      The leftmost BSTreeNode. If the BSTreeNode has
 *                          no left child, return itself.
 */
BSTreeNode *bs_tree_leftmost_node(BSTreeNode *node);

/**
 * @brief Get the rightmost child node of a BSTreeNode.
 *
 * @param node              The BSTreeNode.
 * @return BSTreeNode*      The rightmost BSTreeNode. If the BSTreeNode has
 *                          no right child, return itself.
 */
BSTreeNode *bs_tree_rightmost_node(BSTreeNode *node);

/**
 * @brief Insert a BSTreeValue to a BSTree.
 *
 * @param tree          The BSTree.
 * @param data          The value to insert.
 * @return BSTreeNode*  The new inserted BSTreeNode if success,
 *                      otherwise return NULL.
 */
BSTreeNode *bs_tree_insert(BSTree *tree, BSTreeValue data);

/**
 * @brief Remove a BSTreeNode from a BSTree.
 *
 * @param tree          The BSTree.
 * @param node          The BSTreeNode.
 * @return BSTreeNode*  The removed BSTreeNode if success,
 *                      otherwise return NULL.
 */
BSTreeNode *bs_tree_remove_node(BSTree *tree, BSTreeNode *node);

/**
 * @brief Find a BSTreeNode value in a BSTree.
 *
 * @param tree          The BSTree.
 * @param data          The BSTreeNode value to lookup.
 * @return BSTreeNode*  The matched BSTreeNode if success,
 *                      otherwise return NULL.
 */
BSTreeNode *bs_tree_lookup_data(BSTree *tree, BSTreeValue data);

typedef void (*BSTreeTraverseFunc)(BSTreeNode *node, void *args);

/**
 * @brief Traverse BSTree by preorder.
 *
 * @param tree          The BSTree.
 * @param callback      The callback function do to each BSTreeNode in traverse.
 * @param cb_args       The callback function's args.
 */
void bs_tree_preorder_traverse(BSTree *tree,
                               BSTreeTraverseFunc callback,
                               void *cb_args);

/**
 * @brief Traverse BSTree by inorder.
 *
 * @param tree          The BSTree.
 * @param callback      The callback function do to each BSTreeNode in traverse.
 * @param cb_args       The callback function's args.
 */
void bs_tree_inorder_traverse(BSTree *tree,
                              BSTreeTraverseFunc callback,
                              void *cb_args);

/**
 * @brief Traverse BSTree by postorder.
 *
 * @param tree          The BSTree.
 * @param callback      The callback function do to each BSTreeNode in traverse.
 * @param cb_args       The callback function's args.
 */
void bs_tree_postorder_traverse(BSTree *tree,
                                BSTreeTraverseFunc callback,
                                void *cb_args);

#endif /* #ifndef RETHINK_C_BS_TREE_H */
