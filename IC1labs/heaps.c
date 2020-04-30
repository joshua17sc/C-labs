#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
  //I am declaring two variables for heap storage.
  char *first_string;
  char *second_string;

  //This allocates heap memory for the two heap variables.
  first_string= (char *)malloc(32);
  second_string = (char *)malloc(32);

  //This shows the memory locations for the start of each of the allocated segments.
  printf("first_string --> (%p)\n", first_string);
  printf("second_string --> (%p)\n", second_string);

  //This copies a string into the first memory location.
  strcpy(first_string, "First!");

  //This copies the string first memory location to the second memory location.
  strcpy(second_string, first_string);

  printf("first_string --> (%p) --> %s\n", first_string, first_string);
  printf("second_string --> (%p) --> %s\n", second_string, second_string);
  
}
