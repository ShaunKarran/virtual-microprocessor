# Virmic
Very simple virtual microprocessor based on the one created by Dr Frederic Maire.  
Thanks also to Tristan Strathearn for his version. http://pixls.com.au/apps/vmc/

### How to use Virmic

Virmic takes a binary file as a single argument. The binary file is loaded into memory and executed.

eg. './virmic test.prog'

The processor will halt on the instruction 0x00, or any non-valid instruction. See full instruction set below.

### Instruction Set

##### Note:  
(n) indicates a value stores at address n.  
A is shorthand for (pc + 1).  

| Opcode | Instruction         |
| ------ | ------------------- |
| 0x00   | Halt CPU            |
| 0x01   | R0 <- R0 + R1       |
| 0x02   | R0 <- R0 - R1       |
| 0x03   | R0 <- R0 + 1        |
| 0x04   | R1 <- R1 + 1        |
| 0x05   | R0 <- R0 - 1        |
| 0x06   | R1 <- R1 - 1        |
| 0x07   | Print (A)           |
| 0x08   | R0 <- (A)           |
| 0x09   | R1 <- (A)           |
| 0x0a   | (A) <- R0           |
| 0x0b   | (A) <- R1           |
| 0x0c   | Jump to A           |
| 0x0d   | Jump to A if R0 == 0|
| 0x0e   | Jump to A if R0 != 0|
