#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define RAM_SIZE		16 /* in bytes */
#define NUM_REGISTERS	2

typedef struct processor {
	char ram[RAM_SIZE];
	char reg[NUM_REGISTERS];
	char *pc;
	char current_instruction;
	bool running;
} processor;

void print_cpu_state(processor *cpu);

int main(int argc, char *argv[])
{
	processor cpu;

	memset(cpu.ram, 0, RAM_SIZE * sizeof(char)); /* Initialise ram to 0's */

	// test program
	cpu.ram[0] = 7;
	cpu.ram[1] = 3;
	cpu.ram[2] = 0;
	cpu.ram[3] = 4;

	cpu.pc = cpu.ram; /* Point pc to start of ram at beginning of execution */
	cpu.running = true;

	while (cpu.running && cpu.pc < (cpu.ram + RAM_SIZE)) {
		print_cpu_state(&cpu);

		switch (*(cpu.pc)) {
			case 0:			/* Halt processor */
				cpu.running = false;
				break;
			case 1:			/* R0 <- R0 + R1  */
				cpu.reg[0] += cpu.reg[1];
				break;
			case 2:			/* R0 <- R0 - R1  */
				cpu.reg[0] -= cpu.reg[1];
				break;
			case 3:			/* R0 <- R0 + 1   */
				cpu.reg[0]++;
				break;
			case 4:			/* R0 <- R0 - 1   */
				cpu.reg[0]--;
				break;
			case 5:			/* R1 <- R1 + 1   */
				cpu.reg[0]++;
				break;
			case 6:			/* R1 <- R1 - 1   */
				cpu.reg[0]--;
				break;
			case 7:			/* R0 <- *(*(pc+1)) */
				cpu.reg[0] = cpu.ram[*(++cpu.pc)];
				break;
		}

		cpu.pc++;
	} /* End while */

	return EXIT_SUCCESS;
}

void print_cpu_state(processor *cpu)
{
	printf("--- Processor State ---\n");
	printf("Program Counter = %ld\n", (cpu->pc - cpu->ram));
	printf("Current Instruction = %d\n", *(cpu->pc));

	for (int i = 0; i < NUM_REGISTERS; i++) {
		printf("Register %d = %d\n", i, cpu->reg[i]);
	}

	printf("RAM:");
	for (int i = 0; i < RAM_SIZE; i++) {
		if (i % 4 == 0)
			printf("\n");
		printf("%d ", cpu->ram[i]);
	}

	printf("\n\n");
}
