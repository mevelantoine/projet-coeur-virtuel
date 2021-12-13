#include "core.h"

void initCore(core coreToInit){
    coreToInit.compFlag=0;
    coreToInit.zeroFlag=0;
    coreToInit.signFlag=0;

    for(int i=0;i<15;i++){
        coreToInit.registers[i]=0;
    }
}