#include <stdio.h>

char *stringcopy(char *destination, char *source);

int main(){

char oldstring[] = "Hello Icy One!";
printf("%s\n",oldstring);
stringcopy(oldstring, "Replacement!");
printf("%s\n",oldstring);
char newstring[] = "Still works.";
stringcopy(oldstring, newstring);
printf("%s\n",oldstring);
return 0;
}

char *stringcopy(char *destination, char *source){
    /*  Description: I copy a string from one location to another.
        destination - char * destination of copied string
        source  - char * source of copied string
        returns - char * 
    */
    
    char *start=destination; 
    // Creates a temporary variable as starting point for the new array/string. Needed for return.
    
    while(*source != '\0') 
    // This will make sure we get all of the characters in *source.
    {
        
        *destination = *source; 
        // Copy the character from * source to * destination.
        destination++; 
        // Iterate the address for *destination.
        source++; 
        // Iterate the address for *source.
    }
    *destination = '\0'; 
    // Finish the array/string with null character since we did not copy it over and our source and destination may not be the same length.
    return start; 
    // Returns the address to start the copied string.
}
