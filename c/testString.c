/*

gcc -o testString testString.c `pkg-config --cflags --libs dbus-glib-1`

*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <glib.h>
#include <glib/gprintf.h>

void printString(char * str)
{

const gchar *some_strings= "HelloYYY";
GVariant *new_variant;
new_variant =g_variant_new ("s",some_strings);

char* c=malloc(256);
g_variant_get(new_variant,"s",&c);

printf("STR::%s\n",c);

//memcpy(str,c,strlen(c));
strcpy(str,c);

printf("STR::%s\n",str);

}


char* printStringc(char * str)
{

const gchar *some_strings= "Hello";
GVariant *new_variant;
new_variant =g_variant_new ("s",some_strings);


g_variant_get(new_variant,"s",&str);



printf("STR::%s\n",str);

return str;
}

int main()
{



//char *str="Hello Jyoti";
char *str=malloc(256);

//str=printStringc(str);
printString(str);

printf("STR::%s\n",str);
return 0;
}

