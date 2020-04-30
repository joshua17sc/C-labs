#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

void *malloc(size_t size);

int main() {
  //I am declaring two variables for heap storage.
  char *char_ptr;
  int *int_ptr;
  //This initializes a variable for storage in the stack.
  char test[] = "stack, not heap!";

  //This allocates heap memory for the two heap variables.
  char_ptr = (char *)malloc(40*sizeof(char));
  int_ptr = (int *)malloc(2*sizeof(int));

  //This initializes the heap allocated storage with a string and an integer.
  strcpy(char_ptr, "This is a test!");
  *int_ptr = 22;

  //This segment demonstrate that heap allocated variables are stored separately from stack storage.
  printf("char_ptr (%p) --> %s\n", &char_ptr, char_ptr);
  printf("int_ptr (%p) --> %d\n", &int_ptr, *int_ptr);
  printf("test (%p) --> %s\n", test, test);
}

void *malloc(size_t size) {
  /* Description: I allocated a block of free heap memory by calling sbrk().
  *  size - amount of memory to be allocated
  *  returns address for start of allocated memory, or a NULL pointer
  */
  void *ptr, *new;
  ptr = sbrk(0);
  new = sbrk(size);
  uintptr_t i = (uintptr_t) new;
  if (i % 8 == 0){
  if (new == (void *)-1) {
    return NULL;
  } else {
    return ptr;
  }
  } else {
    int align = i % 8;
    ptr = sbrk(align);
    ptr = sbrk(0);
    new = sbrk(size);
    if (new == (void *)-1) {
    return NULL;
  } else {
    return ptr;
  }
  }
}
