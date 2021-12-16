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
    int carrFlag;
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

long ivalueOrOpe2(struct coeur core, struct instruction inst){
    if (inst.ivflag){
        return inst.immVal;
    }
    else{
        return core.registers[inst.ope2];
    }
}

void add(struct coeur core, struct instruction inst){
    long res = 0;
    res = inst.ope1 + ivalueOrOpe2(core, inst);
    core.registers[inst.dest] = res;
    //Si la valeur maximale dépasse le maximum d'un long
    if (res > 18446744073709551615){core.carrFlag=1;}else{core.carrFlag=0;}
    if (res > 0){core.signFlag=0;}else{core.signFlag=1;}
    if (res != 0){core.zeroFlag=0;}else{core.zeroFlag=1;}
}

void sub(struct coeur core, struct instruction inst){
    long res = 0;
    res = inst.ope1 + ivalueOrOpe2(core, inst);
    core.registers[inst.dest] = res;
    //Si la valeur maximale rentre dans un long
    if (res > -9223372036854775808 && res < 18446744073709551615){core.carrFlag=0;}else{core.carrFlag=1;}
    if (res > 0){core.signFlag=0;}else{core.signFlag=1;}
    if (res != 0){core.zeroFlag=0;}else{core.zeroFlag=1;}
}

void orr(struct coeur core, struct instruction inst){
    long res = 0;
    res = inst.ope1 || ivalueOrOpe2(core, inst);
    core.registers[inst.dest] = res;
    core.carrFlag=0;
    if (res > 0){core.signFlag=0;}else{core.signFlag=1;}
    if (res != 0){core.zeroFlag=0;}else{core.zeroFlag=1;}
}

void and(struct coeur core, struct instruction inst){
    long res = 0;
    res = inst.ope1 && ivalueOrOpe2(core, inst);
    core.registers[inst.dest] = res;
    core.carrFlag=0;
    if (res > 0){core.signFlag=0;}else{core.signFlag=1;}
    if (res != 0){core.zeroFlag=0;}else{core.zeroFlag=1;}
}

void xor(struct coeur core, struct instruction inst){
    long res = 0;
    res = inst.ope1 ^ ivalueOrOpe2(core, inst);
    core.registers[inst.dest] = res;
    core.carrFlag=0;
    if (res > 0){core.signFlag=0;}else{core.signFlag=1;}
    if (res != 0){core.zeroFlag=0;}else{core.zeroFlag=1;}
}

void mov(struct coeur core, struct instruction inst){
    core.registers[inst.dest] = ivalueOrOpe2(core,inst);
}

void adc(struct coeur core, struct instruction inst){
    long res = 0;
    res = inst.ope1 + ivalueOrOpe2(core, inst) + core.carrFlag;
    core.registers[inst.dest] = res;
    if (res > 18446744073709551615){core.carrFlag=1;}else{core.carrFlag=0;}
    if (res > 0){core.signFlag=0;}else{core.signFlag=1;}
    if (res != 0){core.zeroFlag=0;}else{core.zeroFlag=1;}
}

void sbc(struct coeur core, struct instruction inst){
    long res = 0;
    res = inst.ope1 + ivalueOrOpe2(core, inst) + (core.carrFlag - 1);
    core.registers[inst.dest] = res;
    //Si la valeur maximale dépasse le maximum d'un unsigned long
    if (res > -9223372036854775808 && res < 18446744073709551615){core.carrFlag=0;}else{core.carrFlag=1;}
    if (res > 0){core.signFlag=0;}else{core.signFlag=1;}
    if (res != 0){core.zeroFlag=0;}else{core.zeroFlag=1;}
}

void lsh(struct coeur core, struct instruction inst){
    long res = 0;
    res = inst.ope1 << ivalueOrOpe2(core, inst);
    core.registers[inst.dest] = res;
    //Si la valeur de départ est plus grande que 2^63, on aura un overflow vers la gauche
    if (inst.ope1 > pow(2,63)){core.carrFlag=1;}else{core.carrFlag=0;}
    if (res > 0){core.signFlag=0;}else{core.signFlag=1;}
    if (res != 0){core.zeroFlag=0;}else{core.zeroFlag=1;}
}

void lsh(struct coeur core, struct instruction inst){
    long res = 0;
    res = inst.ope1 << ivalueOrOpe2(core, inst);
    core.registers[inst.dest] = res;
    //Si la valeur de départ est impaire, on aura un overflow vers la droite
    if (inst.ope1 % 2 == 1){core.carrFlag=1;}else{core.carrFlag=0;}
    if (res > 0){core.signFlag=0;}else{core.signFlag=1;}
    if (res != 0){core.zeroFlag=0;}else{core.zeroFlag=1;}
}

int fetch(struct coeur core, FILE* input){
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
    return output;
}

void execute(struct coeur core, struct instruction inst, int verbose){
    switch (inst.opcd)
    {
        case 0x0:
            and(core,inst);
            if (verbose){printf("AND %d %d", inst.ope1, inst.ope2);}
            break;
        case 0x1:
            orr(core,inst);
            if (verbose){printf("ORR %d %d", inst.ope1, inst.ope2);}
            break;
        case 0x2:
            xor(core,inst);
            if (verbose){printf("XOR %d %d", inst.ope1, inst.ope2);}
            break;
        case 0x3:
            add(core,inst);
            if (verbose){printf("ADD %d %d", inst.ope1, inst.ope2);}
            break;
        case 0x4:
            adc(core,inst);
            if (verbose){printf("ADC %d %d", inst.ope1, inst.ope2);}
            break;
        case 0x5:
            cmp(core,inst);
            if (verbose){printf("CMP %d %d", inst.ope1, inst.ope2);}
            break;
        case 0x6:
            sub(core,inst);
            if (verbose){printf("SUB %d %d", inst.ope1, inst.ope2);}
            break;
        case 0x7:
            sbc(core,inst);
            if (verbose){printf("SBC %d %d", inst.ope1, inst.ope2);}
            break;
        case 0x8:
            mov(core,inst);
            if (verbose){printf("MOV %d %d", inst.ope1, inst.ope2);}
            break;
        case 0x9:
            lsh(core,inst);
            if (verbose){printf("LSH %d %d", inst.ope1, inst.ope2);}
            break;
        case 0xA:
            rsh(core,inst);
            if (verbose){printf("RSH %d %d", inst.ope1, inst.ope2);}
            break; 
        default:
            break;
    }
}

void initCore(struct coeur coreToInit){
    coreToInit.carrFlag=0;
    coreToInit.zeroFlag=0;
    coreToInit.signFlag=0;

    for(int i=0;i<15;i++){
        coreToInit.registers[i]=0;
    }
}

int main(int argc, char **argv){
    FILE* file = fopen("test.bin","rb");
    struct coeur testCore;
    struct instruction currInst;
    int verbose = 1;
    initCore(testCore);
    execute(testCore,decode(testCore, fetch(testCore,file)),verbose);
}
