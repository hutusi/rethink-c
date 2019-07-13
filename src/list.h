#ifndef RETHINK_C_LIST_H
#define RETHINK_C_LIST_H

typedef void *ListValue;
#define LIST_NULL ((void *)0)

typedef struct _ListNode {
  ListValue data;
  struct _ListNode *prev;
  struct _ListNode *next;
} ListNode;

typedef struct _List {
  struct _ListNode *head;
  struct _ListNode *tail;
  unsigned int length;
} List;

List *list_new();
void list_free(List *list);

int list_prepend(List *list, ListValue data);
int list_append(List *list, ListValue data);

ListNode *list_nth_node(List *list, unsigned int n);
ListValue list_nth_data(List *list, unsigned int n);

ListValue *list_to_array(List *list);


typedef int (*ListCompareFunc)(ListValue value1, ListValue value2);
typedef int (*ListEqualFunc)(ListValue value1, ListValue value2);

ListNode *list_find_node(List *list, ListNode *node);
ListNode *list_find_data(List *list,
                          ListEqualFunc callback,
                          ListValue data);

int list_remove_node(List *list, ListNode *node);
int list_remove_data(List *list, ListEqualFunc callback,
                              ListValue data);

int list_sort(List *list, ListCompareFunc compare_func);

#endif /* #ifndef RETHINK_C_LIST_H */
