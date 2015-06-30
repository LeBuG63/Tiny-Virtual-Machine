#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ADD 0x00
#define SUB 0x01
#define MUL 0x02
#define DIV 0x03
#define AND 0x04
#define OR  0x05
#define XOR 0x06

#define PRNT_I 0x10
#define PRNT_C 0x11

struct s_cpu {
    unsigned        reg[0xC];  // 12 registres
    unsigned        ins;        // instruction
    long int        size;       // la taille du programme
    unsigned char   *code;
};

typedef struct s_cpu    CPU;

long int getfilesize(FILE *file)
{
    long int size;

    fseek(file, 0, SEEK_END);
    size = ftell(file);

    rewind(file);

    return size;
}

CPU *cpu_create(unsigned char *code, unsigned size)  {
    CPU     *cpu = malloc(sizeof(CPU));

    if(!cpu)
        return NULL;

    cpu->ins = 0;
    cpu->size = size;
    cpu->code = code;

    for(int i = 0; i < 0xC; ++i)
        cpu->reg[i] = 0;

    return cpu;
}

void cpu_destroy(CPU *cpu) {
    if(cpu)
        free(cpu);
}

void cpu_run(CPU *cpu) {
    if(!cpu)
        return;

    cpu->ins = 0;

    while(cpu->ins < cpu->size) {
        switch(cpu->code[cpu->ins]) {
            #define OPERATION(instruction, op) \
            case instruction: {\
                ++cpu->ins; \
                cpu->reg[cpu->code[cpu->ins]] = cpu->code[cpu->ins + 1] op cpu->code[cpu->ins + 2]; \
                cpu->ins += 2; \
                break; \
            }

            OPERATION(ADD, +)
            OPERATION(SUB, -)
            OPERATION(MUL, *)
            OPERATION(DIV, /)
            OPERATION(AND, &)
            OPERATION(OR,  |)
            OPERATION(XOR, ^)
            #undef OPERATION

            case PRNT_I:
                ++cpu->ins;
                printf("Register[%d] = %u\n", cpu->code[cpu->ins], cpu->reg[cpu->code[cpu->ins]]);
                break;
            case PRNT_C:
                ++cpu->ins;
                printf("Register[%d] = %c\n", cpu->code[cpu->ins], cpu->reg[cpu->code[cpu->ins]]);
                break;
        }
        ++cpu->ins;
    }
}

int main(int argc, char *argv[]) {
    unsigned char   *code = NULL;
    long int        size;

    if(argv[1] == NULL)
        return -1;

    CPU     *cpu;
    FILE    *file = fopen(argv[1], "rb");

    if(!file) {
        perror("fopen");
        return -1;
    }

    printf("File loaded\n");

    size = getfilesize(file);
    code = malloc(size);

    fread(code, 1, size, file);
    fclose(file);

    cpu = cpu_create(code, size);

    if(!cpu)
        return -1;

    cpu_run(cpu);
    cpu_destroy(cpu);

    free(code);

    return 0;
}
