#include <stdio.h>
#include <string.h>

int main (int argc, char ** argv)
{
    FILE *config;
    char inStr[20];

    (argc == 2) ? (config = fopen(argv[1],"r"))
                : (config = fopen("default","r"));

    fscanf(config, "%s", inStr);
    printf("-- %s --\n",inStr);

    printf("string length: %lu\n",strlen(inStr));

    return 0;
}
