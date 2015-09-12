#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MEM_SIZE        16 /* in bytes */
#define NUM_REGISTERS   2

typedef struct processor {
    char mem[MEM_SIZE];
    char r[NUM_REGISTERS];
    char *pc;
    char current_instruction;
    bool running;
} processor;

void load_program_to_mem(char file_name[], processor *cpu);

void print_cpu_state(processor *cpu);

int main(int argc, char *argv[])
{
    processor cpu;

    memset(cpu.mem, 0, MEM_SIZE * sizeof(char)); /* Initialise ram to 0's */
    cpu.pc = cpu.mem; /* Point pc to start of mem */

    /* Load the specified program into mem. */
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
            case 0:	        /* Halt processor */
                cpu.running = false;
                break;
            case 1:	        /* Add R0 & R1 */
                cpu.r[0] += cpu.r[1];
                break;
            case 2:	        /* Subtract R1 from R0 */
                cpu.r[0] -= cpu.r[1];
                break;
            case 3:	        /* Increment R0 */
                cpu.r[0]++;
                break;
            case 4:	        /* Increment R1 */
                cpu.r[1]++;
                break;
            case 5:	        /* Degrement R0 */
                cpu.r[0]--;
                break;
            case 6:	        /* Decrement R1 */
                cpu.r[1]--;
                break;
            case 7:	        /* Load value at *(pc + 1) into R0 */
                cpu.r[0] = cpu.mem[*(++cpu.pc)];
                break;
            case 8:	        /* Load value at *(pc + 1) into R1 */
                cpu.r[1] = cpu.mem[*(++cpu.pc)];
                break;
            case 9:	        /* Save value in R0 into *(pc + 1) */
                cpu.mem[*(++cpu.pc)] = cpu.r[0];
                break;
            case 10:        /* Save value in R1 into *(pc + 1) */
                cpu.mem[*(++cpu.pc)] = cpu.r[1];
                break;
            case 11:        /* Jump to *(pc + 1) */
                cpu.pc = cpu.mem + *(cpu.pc + 1) - 1; /* -1 to negate pc++ after switch */
                break;
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

    for (int i = 0; i < NUM_REGISTERS; i++) {
        printf("Register %d = %d\n", i, cpu->r[i]);
    }

    printf("RAM:");
    for (int i = 0; i < MEM_SIZE; i++) {
        if (i % 4 == 0)
            printf("\n");
        printf("%d ", cpu->mem[i]);
    }

    printf("\n\n");
}
