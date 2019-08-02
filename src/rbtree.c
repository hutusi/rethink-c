/**
 * @file rbtree.c
 * @author hutusi (hutusi@outlook.com)
 * @brief Refer to rbtree.h
 * @date 2019-07-28
 *
 * @copyright Copyright (c) 2019, hutusi.com
 *
 */

#include "rbtree.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef ALLOC_TESTING
#include "alloc-testing.h"
#endif

#define RB_TREE_NIL NULL

RBTree *rb_tree_new(RBTreeCompareFunc compare_func,
                    RBTreeFreeKeyFunc free_key_func,
                    RBTreeFreeValueFunc free_value_func)
{
    RBTree *tree = (RBTree *)malloc(sizeof(RBTree));
    tree->compare_func = compare_func;
    tree->free_key_func = free_key_func;
    tree->free_value_func = free_value_func;
    tree->root = RB_TREE_NIL;
    tree->num_nodes = 0;
    return tree;
}

void rb_tree_free_node(RBTree *tree, RBTreeNode *node)
{
    RBTreeEntity *data = node->data;
    while (data) {
        RBTreeEntity *prev = data;
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

static void rb_tree_free_node_callback(RBTreeNode *node, void *args)
{
    // printf("free node: [%d]\n", *((int *)(node->data)));
    RBTree *tree = (RBTree *)args;
    rb_tree_free_node(tree, node);
}

void rb_tree_free(RBTree *tree)
{
    // free all nodes
    rb_tree_postorder_traverse(tree, rb_tree_free_node_callback, tree);
    free(tree);
}

static RBTreeNode *rb_tree_node_new(RBTreeKey key, RBTreeValue value)
{
    RBTreeNode *node = (RBTreeNode *)malloc(sizeof(RBTreeNode));

    node->key = key;
    node->data = (RBTreeEntity *)malloc(sizeof(RBTreeEntity));
    node->data->value = value;
    node->data->next = NULL;

    node->parent = NULL;
    node->left = node->right = RB_TREE_NIL;
    node->color = RED;
    return node;
}

static RBTreeEntity *rb_tree_node_append_value(RBTreeNode *node,
                                               RBTreeValue value)
{
    RBTreeEntity *entity = (RBTreeEntity *)malloc(sizeof(RBTreeEntity));
    entity->value = value;
    entity->next = NULL;

    RBTreeEntity *data = node->data;
    while (data->next) {
        data = data->next;
    }
    data->next = entity;
    return entity;
}

// static inline RBTreeNode *rb_tree_uncle_node(RBTreeNode *node)
// {
//     RBTreeNode *parent = node->parent;
//     if (!parent)
//         return NULL;
//     RBTreeNode *grandparent = parent->parent;
//     if (!grandparent)
//         return NULL;
//     return grandparent->left == parent ? grandparent->right :
//     grandparent->left;
// }

static inline RBTreeNode *rb_tree_sibling_node(RBTreeNode *node)
{
    RBTreeNode *parent = node->parent;
    if (!parent)
        return NULL;
    return parent->left == parent ? parent->right : parent->left;
}

static inline void rb_tree_link_to_right(RBTreeNode *parent, RBTreeNode *node)
{
    if (node)
        node->parent = parent;
    parent->right = node;
}

static inline void rb_tree_link_to_left(RBTreeNode *parent, RBTreeNode *node)
{
    if (node)
        node->parent = parent;
    parent->left = node;
}

static RBTreeNode *rb_tree_left_rotate(RBTree *tree, RBTreeNode *focus)
{
    if (focus->right == NULL)
        return focus;

    RBTreeNode *new_focus = focus->right;
    new_focus->parent = focus->parent;

    rb_tree_link_to_right(focus, new_focus->left);
    rb_tree_link_to_left(new_focus, focus);

    if (new_focus->parent == NULL) {
        tree->root = new_focus;
    } else if (new_focus->parent->right == focus) {
        new_focus->parent->right = new_focus;
    } else {
        new_focus->parent->left = new_focus;
    }

    return new_focus;
}

static RBTreeNode *rb_tree_right_rotate(RBTree *tree, RBTreeNode *focus)
{
    if (focus->left == NULL)
        return focus;

    RBTreeNode *new_focus = focus->left;
    new_focus->parent = focus->parent;

    rb_tree_link_to_left(focus, new_focus->right);
    rb_tree_link_to_right(new_focus, focus);

    if (new_focus->parent == NULL) {
        tree->root = new_focus;
    } else if (new_focus->parent->right == focus) {
        new_focus->parent->right = new_focus;
    } else {
        new_focus->parent->left = new_focus;
    }

    return new_focus;
}

/**
 * @brief Red black tree insert fixup: case1
 *
 * if (focus parent is left child) example:
 *
 * c: focus, p:parent, g: grandparent, u: uncle
 *
 * case1 : focus node's uncle is RED
 *
 *               g[B]                 g[R]  <- focus
 *              /    \               /    \
 *             p[R]   u[R]    =>   p[B]   u[B]
 *            /                    /
 *  focus-> c[R]                 c[R]
 *
 * then goto case2.
 *
 * else (focus parent is right child): do the same as 'if' with 'left' and
 *                                     'right' exchanged.
 *
 * @param tree
 * @param focus
 * @param uncle
 * @return RBTreeNode*
 */
static RBTreeNode *
rb_tree_insert_case1(RBTree *tree, RBTreeNode *focus, RBTreeNode *uncle)
{
    RBTreeNode *parent = focus->parent;
    RBTreeNode *grandparent = parent->parent;

    parent->color = BLACK;
    uncle->color = BLACK;
    grandparent->color = RED;

    return grandparent;
}

typedef RBTreeNode *(*RBTreeRotateFunc)(RBTree *tree, RBTreeNode *focus);

/**
 * @brief Red black tree insert fixup: case2
 *
 * if (focus parent is left child) example:
 *
 * c: focus, p:parent, g: grandparent, u: uncle
 *
 * case2 : focus node's uncle is BLACK and focus node is a right child
 *
 *               g[B]                             g[B]
 *              /                                 /
 *            p[R]        left rotate(c)         c[R]
 *           /   \        -------------->       /   \
 *         e[B]  c[R]  <-focus        focus->  p[R]  b[B]
 *              /    \                        /   \
 *             a[B]   b[B]                 e[B]  a[B]
 *            /                                   /
 *          d[R]                               d[R]
 *
 * goto case3.
 *
 * else (focus parent is right child): do the same as 'if' with 'left' and
 *                                     'right' exchanged.
 *
 * @param tree
 * @param focus
 * @param rotate_func
 * @return RBTreeNode*
 */
static RBTreeNode *rb_tree_insert_case2(RBTree *tree,
                                        RBTreeNode *focus,
                                        RBTreeRotateFunc rotate_func)
{
    focus = focus->parent;
    if (focus)
        rotate_func(tree, focus);
    return focus;
}

/**
 * @brief Red black tree insert fixup: case3
 *
 * if (focus parent is left child) example:
 *
 * c: focus, p:parent, g: grandparent, u: uncle
 *
 * case 3: focus node's uncle is BLACK and focus node is a left child
 *
 *               g[B]    right rotate(c)           p[B]
 *              /        -------------->         /      \
 *            p[R]                     focus-> c[R]     g[R]
 *           /   \                            /   \      /
 * focus-> c[R]  b[B]                       e[R]  a[B]  b[B]
 *        /    \                                  /
 *      e[B]   a[B]                             d[R]
 *            /
 *          d[R]
 *
 * else (focus parent is right child): do the same as 'if' with 'left' and
 *                                     'right' exchanged.
 *
 * @param tree
 * @param focus
 * @param rotate_func
 * @return RBTreeNode*
 */
static RBTreeNode *rb_tree_insert_case3(RBTree *tree,
                                        RBTreeNode *focus,
                                        RBTreeRotateFunc rotate_func)
{
    if (focus->parent && focus->parent->parent) {
        RBTreeNode *grandparent = focus->parent->parent;
        focus->parent->color = BLACK;
        grandparent->color = RED;
        rotate_func(tree, grandparent);
    }
    return focus;
}

static void rb_tree_insert_fixup(RBTree *tree, RBTreeNode *focus)
{
    while (focus && focus->parent && focus->parent->color == RED) {
        RBTreeNode *grandparent = focus->parent->parent;
        if (!grandparent) {
            break;
        }

        if (focus->parent == grandparent->left) {
            RBTreeNode *uncle = grandparent->right;

            if (uncle && uncle->color == RED) {
                focus = rb_tree_insert_case1(tree, focus, uncle);
                continue;
            }

            if (focus == focus->parent->right) {
                focus = rb_tree_insert_case2(tree, focus, rb_tree_left_rotate);
            }

            rb_tree_insert_case3(tree, focus, rb_tree_right_rotate);
        } else {
            /**
             * else : focus parent is right child, do the
             *        same as 'if' with 'left' and 'right' exchanged.
             */
            RBTreeNode *uncle = grandparent->left;

            if (uncle && uncle->color == RED) {
                focus = rb_tree_insert_case1(tree, focus, uncle);
                continue;
            }

            if (focus == focus->parent->left) {
                focus = rb_tree_insert_case2(tree, focus, rb_tree_right_rotate);
            }

            rb_tree_insert_case3(tree, focus, rb_tree_left_rotate);
        }
    }

    tree->root->color = BLACK;
}

RBTreeNode *rb_tree_insert(RBTree *tree, RBTreeKey key, RBTreeValue value)
{
    RBTreeNode *rover = tree->root;
    RBTreeNode *insert = RB_TREE_NIL;
    int comp = 0;

    while (rover != RB_TREE_NIL) {
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
            rb_tree_node_append_value(rover, value);
            return rover;
        }
    }

    RBTreeNode *new_node = rb_tree_node_new(key, value);
    new_node->parent = insert;
    ++(tree->num_nodes);

    if (insert == RB_TREE_NIL) {
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
        rb_tree_insert_fixup(tree, new_node);

    return new_node;
}

RBTreeNode *rb_tree_leftmost_node(RBTreeNode *node)
{
    RBTreeNode *rover = node;
    while (rover->left != NULL) {
        rover = rover->left;
    }
    return rover;
}

RBTreeNode *rb_tree_rightmost_node(RBTreeNode *node)
{
    RBTreeNode *rover = node;
    while (rover->right != NULL) {
        rover = rover->right;
    }
    return rover;
}

static RBTreeNode *
rb_tree_replace_node(RBTree *tree, RBTreeNode *node, RBTreeNode *replace)
{
    RBTreeNode *parent = node->parent;
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

/**
 * @brief Red black tree delete fixup: case1
 *
 * if (focus is left child) example:
 *
 * c: focus, p:parent, g: grandparent, u: uncle, s: sibling
 *
 * case1: focus node's sibling is RED.
 *
 *
 *            p[B]       left rotate(p)       s[B]
 *           /    \     -------------->      /    \
 * focus-> c[B]    s[R]                    p[R]     b[B]
 *                /   \                   /    \
 *              a[B]  b[B]              c[B]   a[B] <-new sibling (return)
 *
 * goto case2.
 *
 * else (focus is right child): do the same as 'if' with 'left' and 'right'
 *                              exchanged.
 *
 * @param tree
 * @param focus
 * @param sibling
 * @param rotate_func
 * @return RBTreeNode*
 */
static RBTreeNode *rb_tree_delete_fixup_case1(RBTree *tree,
                                              RBTreeNode *focus,
                                              RBTreeNode *sibling,
                                              RBTreeRotateFunc rotate_func)
{
    sibling->color = BLACK;
    focus->parent->color = RED;
    rotate_func(tree, focus->parent);
    return rb_tree_sibling_node(focus);
}

/**
 * @brief Red black tree delete fixup: case2
 *
 * if (focus is left child) example:
 *
 * c: focus, p:parent, g: grandparent, u: uncle, s: sibling
 *
 * case2: focus node's sibling is BLACK, and both of sibling's children are
 *        BLACK.
 *
 *
 *            p[R]                            p[B] <-focus
 *           /    \     -------------->      /    \
 * focus-> c[B]    s[B]                    c[B]   s[R]
 *                /   \                          /    \
 *              a[B]  b[B]                     a[B]   b[B]
 *
 * goto case3.
 *
 * else (focus is right child): do the same as 'if' with 'left' and 'right'
 *                              exchanged.
 *
 * @param tree
 * @param focus
 * @param sibling
 * @return RBTreeNode*
 */
static RBTreeNode *
rb_tree_delete_fixup_case2(RBTree *tree, RBTreeNode *focus, RBTreeNode *sibling)
{
    sibling->color = RED;
    return focus->parent;
}

/**
 * @brief Red black tree delete fixup: case3
 *
 * if (focus is left child) example:
 *
 * c: focus, p:parent, g: grandparent, u: uncle, s: sibling
 *
 * case3: focus node's sibling is BLACK, sibling's left child is RED, and
 *        sibling's right child is BLACK.
 *
 *            p[R]      right rotate(s)     p[B]
 *           /    \     -------------->    /    \
 * focus-> c[B]    s[B]                  c[B]   a[B] <-new sibling (return)
 *                /   \                            \
 *              a[R]  b[B]                          s[R]
 *                                                    \
 *                                                     b[B]
 *
 * goto case4.
 *
 * else (focus is right child): do the same as 'if' with 'left' and 'right'
 *                              exchanged.
 *
 * @param tree
 * @param focus
 * @param sibling
 * @param sibling_side
 * @param rotate_func
 * @return RBTreeNode*
 */
static RBTreeNode *rb_tree_delete_fixup_case3(RBTree *tree,
                                              RBTreeNode *focus,
                                              RBTreeNode *sibling,
                                              RBTreeNode *sibling_side,
                                              RBTreeRotateFunc rotate_func)
{
    if (sibling_side)
        sibling_side->color = BLACK;
    sibling->color = RED;
    rotate_func(tree, sibling);
    return rb_tree_sibling_node(focus);
}

/**
 * @brief Red black tree delete fixup: case4
 *
 * if (focus is left child) example:
 *
 * c: focus, p:parent, g: grandparent, u: uncle, s: sibling
 *
 * case4: focus node's sibling is BLACK, and focus node's right child is RED.
 *
 *            p[R]      left rotate(p)      s[R]
 *           /    \     -------------->    /    \
 * focus-> c[B]    s[B]                  p[B]   b[B]
 *                /   \                  /  \
 *              a[R]  b[R]            c[B]  a[R]
 *
 * break loop.
 *
 * else (focus is right child): do the same as 'if' with 'left' and 'right'
 *                              exchanged.
 *
 * @param tree
 * @param focus
 * @param sibling
 * @param sibling_side
 * @param rotate_func
 * @return RBTreeNode*
 */
static RBTreeNode *rb_tree_delete_fixup_case4(RBTree *tree,
                                              RBTreeNode *focus,
                                              RBTreeNode *sibling,
                                              RBTreeNode *sibling_side,
                                              RBTreeRotateFunc rotate_func)
{
    sibling->color = focus->parent->color;
    focus->parent->color = BLACK;
    if (sibling_side)
        sibling_side->color = BLACK;
    rotate_func(tree, focus->parent);
    return tree->root;
}

static void rb_tree_delete_fixup(RBTree *tree, RBTreeNode *focus)
{
    RBTreeNode *sibling;

    while (focus && focus != tree->root && focus->color == BLACK) {
        if (focus == focus->parent->left) {
            sibling = focus->parent->right;
            if (sibling && sibling->color == RED) {
                sibling = rb_tree_delete_fixup_case1(
                    tree, focus, sibling, rb_tree_left_rotate);
            }

            if (sibling && sibling->left && sibling->left->color == BLACK &&
                sibling->right && sibling->right->color == BLACK) {
                focus = rb_tree_delete_fixup_case2(tree, focus, sibling);
            } else if (sibling && sibling->right &&
                       sibling->right->color == BLACK) {
                sibling = rb_tree_delete_fixup_case3(
                    tree, focus, sibling, sibling->left, rb_tree_right_rotate);
            }

            focus = rb_tree_delete_fixup_case4(
                tree, focus, sibling, sibling->right, rb_tree_left_rotate);
        } else {
            /**
             * else (focus is right child): do the same as 'if' with 'left' and
             *                              'right' exchanged.
             */
            sibling = focus->parent->left;
            if (sibling && sibling->color == RED) {
                sibling = rb_tree_delete_fixup_case1(
                    tree, focus, sibling, rb_tree_right_rotate);
            }

            if (sibling && sibling->right && sibling->right->color == BLACK &&
                sibling->left && sibling->left->color == BLACK) {
                focus = rb_tree_delete_fixup_case2(tree, focus, sibling);
            } else if (sibling && sibling->left &&
                       sibling->left->color == BLACK) {
                sibling = rb_tree_delete_fixup_case3(
                    tree, focus, sibling, sibling->right, rb_tree_left_rotate);
            }

            focus = rb_tree_delete_fixup_case4(
                tree, focus, sibling, sibling->left, rb_tree_right_rotate);
        }
    }
}

RBTreeNode *rb_tree_remove_node(RBTree *tree, RBTreeNode *node)
{
    RBTreeNode *fixup = NULL;
    RBTreeColor original_color = node->color;

    if (node->left == NULL && node->right == NULL) {
        rb_tree_replace_node(tree, node, NULL);
    } else if (node->left == NULL) {
        fixup = node->right;
        rb_tree_replace_node(tree, node, node->right);
    } else if (node->right == NULL) {
        fixup = node->left;
        rb_tree_replace_node(tree, node, node->left);
    } else {
        RBTreeNode *replace = rb_tree_leftmost_node(node->right);
        original_color = replace->color;
        fixup = replace->right;

        if (replace != node->right) {
            rb_tree_replace_node(tree, replace, replace->right);
            replace->right = node->right;
            node->right->parent = replace;
        }
        rb_tree_replace_node(tree, node, replace);
        replace->left = node->left;
        node->left->parent = replace;
    }

    if (original_color == BLACK)
        rb_tree_delete_fixup(tree, fixup);

    --(tree->num_nodes);
    return node;
}

RBTreeNode *rb_tree_find_node(RBTree *tree, RBTreeKey key)
{
    RBTreeNode *rover = tree->root;
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

unsigned int rb_tree_subtree_height(RBTreeNode *node)
{
    if (node == NULL) {
        return 0;
    }

    unsigned int left_height = rb_tree_subtree_height(node->left);
    unsigned int right_height = rb_tree_subtree_height(node->left);

    if (left_height < right_height) {
        return left_height + 1;
    } else {
        return right_height + 1;
    }
}

void rb_tree_subtree_print(RBTreeNode *node, int depth)
{
    if (node == NULL) {
        return;
    }

    rb_tree_subtree_print(node->left, depth + 1);

    for (int i = 0; i < depth * 6; ++i) {
        printf(" ");
    }

    printf("%d[%c]\n", *(int *)node->key, node->color == RED ? 'R' : 'B');

    rb_tree_subtree_print(node->right, depth + 1);
}

static void rb_tree_preorder_internal(RBTreeNode *node,
                                      RBTreeTraverseFunc callback,
                                      void *cb_args)
{
    if (node != NULL) {
        if (callback != NULL) {
            callback(node, cb_args);
        }
        rb_tree_preorder_internal(node->left, callback, cb_args);
        rb_tree_preorder_internal(node->right, callback, cb_args);
    }
}

void rb_tree_preorder_traverse(RBTree *tree,
                               RBTreeTraverseFunc callback,
                               void *cb_args)
{
    rb_tree_preorder_internal(tree->root, callback, cb_args);
}

static void rb_tree_inorder_internal(RBTreeNode *node,
                                     RBTreeTraverseFunc callback,
                                     void *cb_args)
{
    if (node != NULL) {
        rb_tree_inorder_internal(node->left, callback, cb_args);
        if (callback != NULL) {
            callback(node, cb_args);
        }
        rb_tree_inorder_internal(node->right, callback, cb_args);
    }
}

void rb_tree_inorder_traverse(RBTree *tree,
                              RBTreeTraverseFunc callback,
                              void *cb_args)
{
    rb_tree_inorder_internal(tree->root, callback, cb_args);
}

static void rb_tree_postorder_internal(RBTreeNode *node,
                                       RBTreeTraverseFunc callback,
                                       void *cb_args)
{
    if (node != NULL) {
        rb_tree_postorder_internal(node->left, callback, cb_args);
        rb_tree_postorder_internal(node->right, callback, cb_args);
        if (callback != NULL) {
            callback(node, cb_args);
        }
    }
}

void rb_tree_postorder_traverse(RBTree *tree,
                                RBTreeTraverseFunc callback,
                                void *cb_args)
{
    rb_tree_postorder_internal(tree->root, callback, cb_args);
}
