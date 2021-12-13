#ifndef CORE_H
#define CORE_H

typedef struct core
{
    long registers[15];
    int zeroFlag;
    int signFlag;
    int compFlag;
};

#endif