//Les flags correspondent à des boolean (int)
//Les registres correspondent à des long (64bits)
//Le PC est un long (vu qu'il correspond à une adresse)

//Ne pas oublier les registres en entrée

#include <stdio.h>
#include <math.h>
#define BUFFER_SIZE 1


struct coeur{
    long registers[15];
    int zeroFlag;
    int signFlag;
    int compFlag;
};

struct instruction{
    short immVal;
    char dest;
    char ope2;
    char ope1;
    char opcd;
    int ivflag;
    char bcc;
};


void fetch(struct coeur core, FILE* input){
    char* line = NULL;
    unsigned long len = 0;
    int read = 0;


    do
    {
        read = getline(&line, len, input);
        while (*line != '\0' && *line != EOF)
        {
            printf("aaaa");
        }
        *line++;
    }while (read != -1);

}

struct instruction decode(struct coeur core, int input){
    int calc;
    int byte;
    int i;
    int bit;
    struct instruction output;
    while (i<8){
        for(int j=0;j<4;j++){
            calc = input/2;
            bit = input%2;
            byte += bit*pow(2,j);
        }
        switch (i){
        //Pas de case 0 car immval prend deux octets
        case 1:
            output.immVal=byte;
            byte=0;
            break;
        case 2:
            output.dest=byte;
            byte=0;
            break;
        case 3:
            output.ope2=byte;
            byte=0;
            break;
        case 4:
            output.ope1=byte;
            byte=0;
            break;
        case 5:
            output.opcd=byte;
            byte=0;
            break;
        case 6:
            output.ivflag=byte;
            byte=0;
            break;
        case 7:
            output.bcc=byte;
            byte=0;
            break;
        default:
            break;
        }
        i++;
    }
}

void execute(struct instruction inst){
    switch (inst.bcc)
    {
    default:
        break;
    }
}

void initCore(struct coeur coreToInit){
    coreToInit.compFlag=0;
    coreToInit.zeroFlag=0;
    coreToInit.signFlag=0;

    for(int i=0;i<15;i++){
        coreToInit.registers[i]=0;
    }
}

int main(int argc, char **argv){
    FILE* file = fopen("test.bin","rb");
    struct coeur testCore;
    initCore(testCore);
    fetch(testCore,file);
    //decode()
}
