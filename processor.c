#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define RAM_SIZE		16 /* in bytes */
#define NUM_REGISTERS	2

typedef struct {
	char ram[RAM_SIZE];
	char reg[NUM_REGISTERS];
	char *pc;
	char current_instruction;
	bool running;
} processor;

void print_cpu_state(processor &cpu);

int main(int argc, char *argv[])
{
	processor cpu;

	// for debug
	cpu.ram[0] = 3;
	cpu.ram[1] = 5;
	cpu.ram[2] = 5;
	cpu.ram[3] = 1;

	cpu.pc = cpu.ram; /* Point pc to start of ram at beginning of execution */
	cpu.running = true;

	while (cpu.running && cpu.pc < (cpu.ram + RAM_SIZE)) {
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
		}

		printf("pc: %d\n", *(cpu.pc)); // for debug

		cpu.pc++;
	} /* End while */

	return EXIT_SUCCESS;
}

void print_cpu_state(processor &cpu)
{
	
}
