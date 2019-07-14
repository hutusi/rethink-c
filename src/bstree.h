#ifndef RETHINK_C_BS_TREE_H
#define RETHINK_C_BS_TREE_H

typedef void *BSTreeValue;

typedef struct _BSTreeNode {
    BSTreeValue data;
    struct _BSTreeNode *parent;
    struct _BSTreeNode *left;
    struct _BSTreeNode *right;
} BSTreeNode;

typedef int (*BSTreeCompareFunc)(BSTreeValue data1, BSTreeValue data2);

typedef struct _BSTree {
    struct _BSTreeNode *root;
    BSTreeCompareFunc compare_func;
    unsigned int num_nodes;
} BSTree;

BSTree *bs_tree_new(BSTreeCompareFunc compare_func);
void bs_tree_free(BSTree *tree);

BSTreeNode *bs_tree_leftmost_node(BSTreeNode *node);
BSTreeNode *bs_tree_rightmost_node(BSTreeNode *node);

BSTreeNode *bs_tree_insert(BSTree *tree, BSTreeValue data);
BSTreeNode *bs_tree_remove_node(BSTree *tree, BSTreeNode *node);
BSTreeNode *bs_tree_lookup_data(BSTree *tree, BSTreeValue data);

typedef void (*BSTreeTraverseFunc)(BSTreeNode *node, void *args);
void bs_tree_preorder_traverse(BSTree *tree, BSTreeTraverseFunc callback, void *cb_args);
void bs_tree_inorder_traverse(BSTree *tree, BSTreeTraverseFunc callback, void *cb_args);
void bs_tree_postorder_traverse(BSTree *tree, BSTreeTraverseFunc callback, void *cb_args);

#endif /* #ifndef RETHINK_C_BS_TREE_H */
