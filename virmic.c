#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MEM_SIZE 16 /* bytes */

typedef struct processor {
    char r0;
    char r1;
    char *pc;
    char *mem;
    char current_instruction;
    bool running;
} processor;

void load_program_to_mem(char file_name[], processor *cpu);

void print_cpu_state(processor *cpu);

int main(int argc, char *argv[])
{
    processor cpu;

    cpu.mem = malloc(MEM_SIZE * sizeof(char));
    if (cpu.mem == NULL) {
        perror("Unable to allocate memory.");
        exit(EXIT_FAILURE);
    }
    memset(cpu.mem, 0, MEM_SIZE * sizeof(char)); /* Initialise ram to 0's */
    cpu.pc = cpu.mem; /* Point pc to start of mem */

    /* Load program into mem. */
    if (argc == 2) {
        load_program_to_mem(argv[1], &cpu);
    } else {
        perror("Usage: ./virmic <program>");
        exit(EXIT_FAILURE);
    }

    cpu.running = true;

    while (cpu.running && cpu.pc < (cpu.mem + MEM_SIZE)) {
        print_cpu_state(&cpu);

        printf("Press enter to execute next instruction.\n");
        getchar();

        switch (*(cpu.pc)) {
            case 0x00:	        /* Halt processor */
                cpu.running = false;
                break;
            case 0x01:	        /* Add R0 & R1 */
                cpu.r0 += cpu.r1;
                break;
            case 0x02:	        /* Subtract R1 from R0 */
                cpu.r0 -= cpu.r1;
                break;
            case 0x03:	        /* Increment R0 */
                cpu.r0++;
                break;
            case 0x04:	        /* Increment R1 */
                cpu.r1++;
                break;
            case 0x05:	        /* Degrement R0 */
                cpu.r0--;
                break;
            case 0x06:	        /* Decrement R1 */
                cpu.r1--;
                break;
            case 0x07:         /* Print value at *(pc + 1) */
                printf("Output: %d\n\n", cpu.mem[*(++cpu.pc)]);
                break;
            case 0x08:	        /* Load value at *(pc + 1) into R0 */
                cpu.r0 = cpu.mem[*(++cpu.pc)];
                break;
            case 0x09:	        /* Load value at *(pc + 1) into R1 */
                cpu.r1 = cpu.mem[*(++cpu.pc)];
                break;
            case 0x0a:	        /* Save value in R0 into *(pc + 1) */
                cpu.mem[*(++cpu.pc)] = cpu.r0;
                break;
            case 0x0b:        /* Save value in R1 into *(pc + 1) */
                cpu.mem[*(++cpu.pc)] = cpu.r1;
                break;
            case 0x0c:        /* Jump to *(pc + 1) */
                cpu.pc = cpu.mem + *(cpu.pc + 1) - 1; /* -1 to negate pc++ after switch */
                break;
            case 0x0d:        /* Jump to *(pc + 1) if R0 == 0 */
                if (cpu.r0 == 0) {
                    cpu.pc = cpu.mem + *(cpu.pc + 1) - 1;
                } else {
                    cpu.pc++;
                }
            case 0x0e:        /* Jump to *(pc + 1) if R0 != 0 */
                if (cpu.r0 != 0) {
                    cpu.pc = cpu.mem + *(cpu.pc + 1) - 1;
                } else {
                    cpu.pc++;
                }
            default:
                cpu.running = false;
        }

        cpu.pc++;
    } /* End while */

    printf("Virmic execution halted.\n\n");

    return EXIT_SUCCESS;
}

void load_program_to_mem(char file_name[], processor *cpu)
{
    FILE *file = fopen(file_name, "rb");
    char c;
    int i = 0;

    if (file == NULL) {
        perror("Error loading program.");
        exit(EXIT_FAILURE);
    }

    do {
        c = fgetc(file);
        cpu->mem[i] = c;
        i++;
    } while (c != EOF && i < MEM_SIZE);

    fclose(file);
}

void print_cpu_state(processor *cpu)
{
    printf("--- Processor State ---\n");
    printf("Program Counter = %ld\n", (cpu->pc - cpu->mem));
    printf("Current Instruction = %d\n", *(cpu->pc));

    printf("Register r0 = %d\n", cpu->r0);
    printf("Register r1 = %d\n", cpu->r1);

    printf("RAM:");
    for (int i = 0; i < MEM_SIZE; i++) {
        if (i % 4 == 0)
            printf("\n");
        printf("%d\t", cpu->mem[i]);
    }

    printf("\n\n");
}
