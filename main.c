//Les flags correspondent à des boolean (int)
//Les registres correspondent à des long (64bits)
//Le PC est un long (vu qu'il correspond à une adresse)

#include <stdio.h>

int main(int argc, char **argv){
    FILE *input;
    input = fopen(argv[1],"rb");

    char line[100];
    fread(line,100,1,input);
    for(int i = 0; i<100; i++)
    printf("%x ", line[i]);
/*while( fgets (line, 100, input)!=NULL ) {
     
      puts(line);
   }
*/
    fclose(input);
}
