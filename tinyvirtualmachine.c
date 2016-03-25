#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define N_REGISTERS     16

#define ADD  0x01
#define SUB  0x02
#define MUL  0x03
#define DIV  0x04
#define AND  0x05
#define OR   0x06
#define XOR  0x07
#define MOD  0x08
#define BITWISE_L 0x09
#define BITWISE_R 0x0A
#define NOT  0x0B

#define PRNT_I 0x20
#define PRNT_C 0x21
#define GET_I  0x22

struct s_cpu {
    long int        reg[N_REGISTERS];
    long int        size;      
    unsigned        ins;        
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

    for(int i = 0; i < N_REGISTERS; ++i)
        cpu->reg[i] = 0;

    return cpu;
}

void cpu_destroy(CPU *cpu) {
    if(cpu)
        free(cpu);
}

long get_input(void) {
    long    res = 0;
    bool    err = false;
    char    str[16] = {'\0'};
    
    fgets(str, 16, stdin);

    if(isalpha(str[0]))
        res = (int)str[0];
    else {
        for(unsigned i = 0; i < strlen(str) - 1 && !err; ++i)
            if(!isdigit(str[i])) {
                err = true;
                break;
             }
        if(!err)
            res = atol(str);
    }
    return res;
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
                if(cpu->ins + 2 < cpu->size) {\
                    cpu->reg[cpu->code[cpu->ins]] = cpu->code[cpu->ins + 1] op cpu->code[cpu->ins + 2]; \
                    cpu->ins += 2; \
                } \
                break; \
            }

            OPERATION(ADD, +)
            OPERATION(SUB, -)
            OPERATION(MUL, *)
            OPERATION(DIV, /)
            OPERATION(AND, &)
            OPERATION(OR,  |)
            OPERATION(XOR, ^)
            OPERATION(MOD, %)
            OPERATION(BITWISE_L, <<)
            OPERATION(BITWISE_R, >>)
            
            #undef OPERATION
            case NOT:
                ++cpu->ins;
                if(cpu->ins + 1 <= cpu->size) {
                    cpu->reg[cpu->code[cpu->ins]] = ~cpu->code[cpu->ins + 1];
                    ++cpu->ins;
                }
            case PRNT_I:
                ++cpu->ins;
                printf("Register[%u] = %ld\n", cpu->code[cpu->ins], cpu->reg[cpu->code[cpu->ins]]);
                break;
            case PRNT_C:
                ++cpu->ins;
                printf("Register[%u] = %c\n", cpu->code[cpu->ins], (isalnum(cpu->reg[cpu->code[cpu->ins]]))?(char)cpu->reg[cpu->code[cpu->ins]]:' ');
                break;
            case GET_I:
                ++cpu->ins;
                printf("? ");                
                    
                cpu->reg[cpu->code[cpu->ins]] = get_input();
                break;
        }
        ++cpu->ins;
    }
}

int main(int argc, char *argv[]) {
    (void)argc;
    
    unsigned char *code = NULL;
    long int  size;

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

    fread(code, sizeof(unsigned), size, file);
    fclose(file);

    cpu = cpu_create(code, size);

    if(!cpu)
        return -1;

    cpu_run(cpu);
    cpu_destroy(cpu);

    free(code);

    return 0;
}
