#include "assert.h"
#include "arraylist.h"

void test_arraylist()
{
  ArrayList *arraylist;
  int values[] = {1,2,3,4,5,6,7,8,9,0};

  arraylist = arraylist_new(3);
  arraylist_append(arraylist, &values[0]);
  arraylist_append(arraylist, &values[1]);

  assert(arraylist->length == 2);
  assert(arraylist->_allocated = 3);
  assert(arraylist->data[0] == values[0]);
  assert(arraylist->data[1] == values[1]);

  arraylist_prepend(arraylist, &values[2]);
  arraylist_prepend(arraylist, &values[3]);

  assert(arraylist->length == 4);
  assert(arraylist->_allocated = 6);
  assert(arraylist->data[0] == values[3]);
  assert(arraylist->data[1] == values[2]);
  assert(arraylist->data[2] == values[0]);
  assert(arraylist->data[3] == values[1]);
}

int main(int argc, char *argv[])
{
  test_arraylist();
  return 0;
}
