#include <stdio.h>

char *stringcopy(char *dest, char *src);

char *stringncopy(char *dest, const char *src, size_t n);

int main()
{

	char oldstring[] = "Hello Icy One!";
	printf("%s\n",oldstring);

	stringcopy(oldstring, "Replacement!");
	printf("%s\n",oldstring);

	char newstring[] = "Still works.";
	stringcopy(oldstring, newstring);
	printf("%s\n",oldstring);

	char nstring[12];
	stringncopy(nstring, oldstring, 8);
	printf("%s\n",nstring);
	return 0;
}

char *stringcopy(char *dest, char *src)
{
    //Copies a string from one location to another in memory.
    size_t i = 0;    
	char *start = &dest[0];
	//our return value is the address of the beginning of our new string
	while(*src) *dest++=*src++;
	//copy each character over while there is a character left in the source
		
	*dest++ = 0;
	//End the new string with a null byte.
	return start;
	//returns the address of the beginning of the new string.   
}
char *stringncopy(char *dest, const char *src, size_t n)
{
    //Copies a string from one location to another in memory, or up to n number of characters from source.
    
    size_t i = 0;    
	char *start = &dest[0];
	//our return value is the address of the beginning of our new string
	while(*src && i < n) 
	{
		*dest++=*src++;
		//copy each character over while there is a character left in the source
		i++;
		//Iterate i for loop n scenario.
	}
	*dest++ = 0;
	//End the new string with a null byte.
	for(; i < n; i++) *dest++=0;
	//Fills remaining n space with 0's.
	return start;
	//returns the address of the beginning of the new string.   
}
