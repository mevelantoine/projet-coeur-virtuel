//Les flags correspondent à des boolean (int)
//Les registres correspondent à des long (64bits)
//Le PC est un long (vu qu'il correspond à une adresse)

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
    FILE *input;
    
    input = fopen(argv[1],"r");

    printf("%s",input);
    fclose(input);
}