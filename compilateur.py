import sys

dictOpcode = {
    "0x0" : "AND",
    "0x1" : "ORR",
    "0x2" : "EOR",
    "0x3" : "ADD",
    "0x4" : "ADC",
    "0x5" : "CMP",
    "0x6" : "SUB",
    "0x7" : "SBC",
    "0x8" : "MOV",
    "0x9" : "LSH",
    "0xa" : "RSH"
}

file = open(sys.argv[1],"rb")
byte=file.read(1)

while byte:
    print(byte)
    byte=file.read(1)

file.close()