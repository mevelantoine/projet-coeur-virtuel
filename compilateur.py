import sys
import re

import os
#os.chdir("D:\Dev\Cours\projet-coeur-virtuel")

def intTo8Bits(n):
    value = str(bin(int(n)))[2:]
    while len(value) < 8:
        value = "0"+value
    return value
opcodeOperations = {
    "and" : "0000",
    "orr" : "0001",
    "eor" : "0010",
    "add" : "0011",
    "adc" : "0100",
    "cmp" : "0101",
    "sub" : "0110",
    "sbc" : "0111",
    "mov" : "1000",
    "lsh" : "1001",
    "rsh" : "1010"
}

opcodeRegistres = {
    "rax" : "0000",
    "rbx" : "0001",
    "rcx" : "0010",
    "rdx" : "0011",
    "rbp" : "0100",
    "rsi" : "0101",
    "rsp" : "0110",
    "rip" : "0111",
    "r8" : "1000",
    "r9" : "1001",
    "r10" : "1010",
    "r11" : "1011",
    "r12" : "1100",
    "r13" : "1101",
    "r14" : "1110",
    "r15" : "1111"
}

opcodeBCC = {
    "B" : "1000",
    "BEQ" : "1001",
    "BNE" : "1010",
    "BLE" : "1011",
    "BGE" : "1100",
    "BL" : "1101",
    "BG" : "1110"
}

#file = open(sys.argv[1],"rb")
input = open("4plus4-correction.asm","r")
output = open("out.o","wb")
for line in input:
    if re.match("^\s*$",line):
        pass
    newline=[]
    for character in line:
        if (character == ";"):
            break
        elif (character == "\t" or character == "\n"):
            pass
        else:
            newline.append(character)
    if ((newline != []) and (newline != ['\n']) and (newline != ['','\n'])):
        newline = "".join(newline).replace(",","")+" \n"
        print(newline)
        elements = newline.split(" ")
        print(elements[:3])
        IV = 0
        try:
            opcd = opcodeOperations.get(elements[0])
            ope1 = opcodeRegistres.get(elements[1])
            if elements[2][:2]=="0x":
                ope2="0000"
                IV="1"
                immval=intTo8Bits(elements[2][2:])
                dest = ope1
                bcc="0000"
            elif elements[0]=="cmp":
                pass
            else:
                ope2 = opcodeRegistres.get(elements[2])
                IV="0"
                immval="00000000"
                dest = ope1
                bcc="0000"
            output.write(bcc+"000"+IV+opcd+ope1+ope2+dest+immval)
        except:
            pass

        print("--------------------")


input.close()

'''
11110001000011110000111100000000
00000000001111001101110000000000
BCC 000IOpcdOpe1Ope2DestImmVal
       V
'''