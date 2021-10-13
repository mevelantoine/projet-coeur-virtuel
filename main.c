//Les flags correspondent à des boolean (int)
//Les registres correspondent à des long (64bits)
//Le PC est un long (vu qu'il correspond à une adresse)

#include <stdio.h>

int main(int argc, char **argv){
    FILE *input;
    input = fopen(argv[1],"r");

    char line[100];
if( fgets (line, 100, input)!=NULL ) {
      /* writing content to stdout */
      puts(line);
   }

    fclose(input);
}
