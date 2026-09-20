# V4VM 8-bit CPU CORE

## V4VM — 8-bit virtual machine

V4VM — компактная 8-битная виртуальная машина с регулярным RISC-подобным набором команд и 16-битной адресацией кода.

* **Data width:** 8 bit
* **Address / PC:** 16 bit
* **Registers:** `A`, `B`, `C`, `D` — 4×8 bit
* **Temporary register:** `T` — 8 bit
* **Memory:** 2 KiB code + 2 KiB data
* **Data stack:** 512 bytes
* **Return stack:** 256 × 16-bit
* **Memory addressing:** 8-bit offset + `MEMH` page register
* **I/O:** 8-bit external ports
* **Branches:** conditional and relative jumps/calls
* **Subroutines:** separate return stack
* **Instruction encoding:** 8-bit opcode; upper 2 bits select the register, lower 6 bits select the operation
* **Operations:** data movement, arithmetic, logic, comparison, shifts, memory, stack, I/O and control flow

The architecture is designed around a **simple and regular instruction encoding**, making the VM suitable for small interpreters, embedded systems and experimental CPU/FPGA implementations.



|       | 0         | 1       | 2        | 3   | 4        | 5       | 6        | 7       | 8       | 9     | A         | B         | C          | D        | E         | F          |
| ----- | --------- | ------- | -------- | --- | -------- | ------- | -------- | ------- | ------- | ----- | --------- | --------- | ---------- | -------- | --------- | ---------- |
| **0** | NOP       | RET     | —        | —   | —        | —       | —        | —       | CLR A   | SET A | TMP A     | —         | INC A      | DEC A    | RMEMI A   | WMEMI A    |
| **1** | PUSH A    | POP A   | MOV A,T  | —   | AND A,T  | OR A,T  | XOR A,T  | CMP A,0 | CMP A,1 | —     | SHR A     | SHL A     | —          | ADD A,T  | SUB A,T   | CMP A,T    |
| **2** | INIT A,M8 | IN A,M8 | OUT M8,A | —   | AND A,M8 | OR A,M8 | XOR A,M8 | —       | —       | —     | RMEM A,M8 | WMEM M8,A | MEMPAGE M8 | ADD A,M8 | SUB A,M8  | CMP A,M8   |
| **3** | JE        | JNE     | JL       | JNL | JB       | JNB     | JZ*      | JNZ*    | JSS0    | JSS1  | JOVER*    | JNOVER*   | JPOS*      | JNEG*    | RJMP      | RCALL      |
| **4** | —         | —       | —        | —   | —        | —       | —        | —       | CLR B   | SET B | TMP B     | —         | INC B      | DEC B    | RMEMI B   | WMEMI B    |
| **5** | PUSH B    | POP B   | MOV B,T  | —   | AND B,T  | OR B,T  | XOR B,T  | CMP B,0 | CMP B,1 | —     | SHR B     | SHL B     | —          | ADD B,T  | SUB B,T   | CMP B,T    |
| **6** | INIT B,M8 | IN B,M8 | OUT M8,B | —   | AND B,M8 | OR B,M8 | XOR B,M8 | —       | —       | —     | RMEM B,M8 | WMEM M8,B | —          | ADD B,M8 | SUB B,M8  | CMP B,M8   |
| **7** | —         | —       | —        | —   | —        | —       | —        | —       | —       | —     | —         | —         | —          | —        | —         | —          |
| **8** | —         | —       | —        | —   | —        | —       | —        | —       | CLR C   | SET C | TMP C     | —         | INC C      | DEC C    | RMEMI C   | WMEMI C    |
| **9** | PUSH C    | POP C   | MOV C,T  | —   | AND C,T  | OR C,T  | XOR C,T  | CMP C,0 | CMP C,1 | —     | SHR C     | SHL C     | —          | ADD C,T  | SUB C,T   | CMP C,T    |
| **A** | INIT C,M8 | IN C,M8 | OUT M8,C | —   | AND C,M8 | OR C,M8 | XOR C,M8 | —       | —       | —     | RMEM C,M8 | WMEM M8,C | —          | ADD C,M8 | SUB C,M8  | CMP C,M8   |
| **B** | —         | —       | —        | —   | —        | —       | —        | —       | —       | —     | —         | —         | —          | —        | —         | —          |
| **C** | —         | —       | —        | —   | —        | —       | —        | —       | CLR D   | SET D | TMP D     | —         | INC D      | DEC D    | RMEMI D   | WMEMI D    |
| **D** | PUSH D    | POP D   | MOV D,T  | —   | AND D,T  | OR D,T  | XOR D,T  | CMP D,0 | CMP D,1 | —     | SHR D     | SHL D     | —          | ADD D,T  | SUB D,T   | CMP D,T    |
| **E** | INIT D,M8 | IN D,M8 | OUT M8,D | —   | AND D,M8 | OR D,M8 | XOR D,M8 | —       | —       | —     | RMEM D,M8 | WMEM M8,D | —          | ADD D,M8 | SUB D,M8  | CMP D,M8   |
| **F** | —         | —       | —        | —   | —        | —       | —        | —       | —       | —     | —         | —         | —          | —        | JMPABS/16 | CALLABS/16 |


