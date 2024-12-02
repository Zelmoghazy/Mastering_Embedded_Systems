# ARM

<p align="center">
  <img src="./workflow.svg"
       width="100%" 
       style="border-radius: 30px;"/>
</p>

* **ARM Architecture Versions** 
    * Progressive iterations of ARM's processor design specification.
    * ex: ARMv1, ARMv7, ARMv8

* **Specific Processor Implementation Families** 
    * Distinct microarchitecture designs implementing ARM architecture.
    * ex: ARM7TDMI, Cortex-M
* **Instruction Set Architecture**
    * Complete set of machine language instructions a processor can execute.
    * ex: Thumb, ARM32

* Various versions of the ARM Architecture exist for the different ARM processors released over the years.
    * For example, the Cortex-M3 and Cortex-M4 processors are both implementations of ARMv7-M Architecture.
* An Instruction Set Architecture can be implemented with various implementations of micro-architecture; for example, different numbers of pipeline stages, different types of bus interface protocol, etc.

![alt text](image-3.png)

<p align="center">
  <img src="./Armv4 to v8-1.jpg"
       width="100%"/>
</p>

![alt text](image-6.png)

## Instruction Set Architectures


* ARM processors support mainly four different assembly instruction sets:
    * `Thumb`
    * `Thumb-2`
    * `ARM32`
    * `ARM64`

* The legacy ARM instruction set includes 32-bit instructions.
* All instructions in the Thumb instruction set have only 16 bits. The Thumb-2 consists of all 16-bit Thumb instructions as well as many 32-bit instructions

![alt text](image.png)


* These instruction sets play different tradeoffs between **code density** and **performance**
    * Code density measures the size of a binary executable program.
    * A high code density means that the binary program has a less number of bytes so it is often preferred in embedded systems because less memory is required, thereby directly reducing cost and power consumption.

* `Thumb` The objective of the Thumb instruction set is to improve the code density.
    * The Thumb instruction set is a subset of the ARM instruction set, re-encoded to 16 bits.
    * Instruction in Thumb has only 16 bits in length so the size of their executable files is small.
    * The space saving is achieved by :
        * Reducing the possibilities of operands
        * Limiting the number of registers that are accessible by an instruction. 

* `ARM32` Each instruction in ARM32 has 32 bits and provides more coding flexibility than a Thumb instruction. 
    * More operand options
    * more flexible memory addressing schemes
    * larger immediate numbers
    * More addressable registers can be encoded in a 32-bit word.
    * ARM32 instructions run faster than Thumb because an instruction can perform more operations or include more operands.
    * However, the disadvantage is its code density.

* `Thumb-2` It provides an outstanding compromise between ARM32 and Thumb as it allows a mixture of 16-bit and 32-bit instructions.
    * It optimizes the tradeoff between code density and processor performance.
    * It consists of 16-bit Thumb instructions and a subset of 32-bit ARM32 instructions.
    * The goal of Thumb-2 is to achieve higher code density like Thumb and fast performance comparable to ARM32.

* `ARM64` ARM 64-bit processors are often used in desktops and servers. 
    * These processors have a set of 64-bit assembly instructions.

![alt text](image-2.png)

---

## Specific Processor Implementation Families

<p align="center">
  <img src="./arm_families.jpg"
       width="100%" />
</p>

![alt text](image-8.png)

* One prominent ARM family is `Cortex` processors, which have three groups:
    * `Cortex-M` series for microcontrollers (M stands for microcontroller),
    * `Cortex-R` series for real-time embedded systems (R stands for real-time), and
    * `Cortex-A` series for high-performance applications (A stands for application).

* `Cortex-A` processors are specially designed based on the ARMv7-A or ARMv8-A architecture to provide fast performance for sophisticated devices, such as smartphones and tablets.
    * They often support full-fledged operating systems such as Linux, iOS, and Android.

* `Cortex-R` processors are designed for mission-critical real-time systems that require high reliability, fault-tolerance, and most importantly, deterministic real-time responsiveness.
    * In real-time systems, the correctness of computation is determined not only by the logical correctness but also by whether it is consistently completed within certain time constraints.

* `Cortex-M` processors offer an excellent tradeoff between performance, cost, and energy efficiency. 
    * They are suitable for a broad range of microcontroller applications, such as home appliances, robotics, industrial control, smart watch, and internet-of-things (IoT).
    * In contrast to general-purpose processors in desktops, a microcontroller is a small processor with a processor core, memory, and many integrated I/O peripherals.

* The `Cortex-M` family includes Cortex-M0, Cortex-M0+, Cortex-M1, Cortex-M3, Cortex-M4, and Cortex-M7.
    * The former three are Von Neumann architecture, and the latter three are Harvard architecture. 
    * Moreover, Cortex-M0/M0+/M1 are ARMv6-M, and Cortex-M3/M4/M7 are ARMv7-M.

    
* ARMv7-M architecture, including Cortex-M3, Cortex-M4, and Cortex-M7 only supports the `Thumb-2` instruction set and is not compatible with `ARM32` it do not its instructions at all.

* In classic ARM processors, for example, the ARM7TDMI, the processor has two operation states: a 32-bit ARM state and a 16-bit Thumb state. 
    * In the ARM state,the instructions are 32-bit and the core can execute all supported instructions with very high performance. 
    * In Thumb state, the instructions are 16-bit, which provides excellent code density, but Thumb instructions do not have all the functionality of ARM instructions and more instructions may be needed to complete certain types of operation.

* Cortex-M processors can run a mix of 16-bit and 32-bit `Thumb-2` instructions without changing the processor state, thus eliminating the overhead of state switching.
    * There is overhead (in terms of both execution time and instruction count) to switch between the states, and the separation of two states can increase the complexity of the software compilation process and make it harder for inexperienced developers to optimize the software

![alt text](image-10.png)

* `Cortex-M` processors are **backward compatible**
    * Cortex-M3 series extends Cortex-M0 series by adding More instructions for advanced data processing and bit field manipulations. 
    * Cortex-M4 extends Cortex-M3 by adding digital signal processing and floating-point arithmetic instructions.
        * a binary program compiled for Cortex-M3 can run on Cortex-M4 without any modification.

![alt text](image-1.png)


* The floating-point unit (FPU), which is a coprocessor for floating-point operations, is optional on Cortex-M4 and Cortex-M7.

* Cortex-M4 and M7 also provide single-instruction multiple-data (SIMD) and multiply-and-accumulate (MAC) instructions for digital signal processing applications (DSP).


---

## Cortex-M3 Case Study

![alt text](image-4.png)

![alt text](image-9.png)

* The processor implements the ARM v7-M architecture.
    * Includes the entire 16-bit Thumb instruction set and the base Thumb-2 32-bit instruction set architecture.

* The Cortex-M3 processor is built on a high-performance processor core, with a 3-stage pipeline Harvard architecture

### Cortex-M3 core peripherals
* Nested Vectored Interrupt Controller
    * The NVIC is an embedded interrupt controller that supports low latency interrupt processing.
* System Control Block
    * The System Control Block (SCB) is the programmers model interface to the processor. It provides system implementation information and system control, including configuration, control, and reporting of system exceptions.
* System timer
    * The system timer, SysTick, is a 24-bit count-down timer. Use this as a Real Time Operating System (RTOS) tick timer or as a simple counter.
* Memory Protection Unit
    * The MPU improves system reliability by defining the memory attributes for different memory regions. It provides up to eight different regions, and an optional predefined background region


### Privelage Levels
* Unprivileged
    * limited access to the `MSR` and `MRS` instructions, and cannot use the `CPS` instruction
    * cannot access the system timer, NVIC, or system control block
    * might have restricted access to memory or peripherals.
    * Unprivileged software can use the `SVC` instruction to make a supervisor call to transfer control to privileged software.
* Privileged 
    * The software can use all the instructions and has access to all resources.

### Operating Modes
* **Thread mode** is entered on Reset, and can be entered as a result of an exception return.
    * Used to execute application software.
    * Privileged and User (Unprivileged) code can run in Thread mode.
    * In Thread mode, the `CONTROL` register controls whether software execution is privileged or
unprivileged
* **Handler mode** is entered as a result of an exception. 
    * All code is privileged in Handler mode.
    * The processor returns to Thread mode when it has finished all exception processing.

### Operating states
* **Thumb state** This is normal execution running 16-bit and 32-bit halfword aligned Thumb and Thumb-2 instructions.
    * If the processor is running program code (Thumb instructions), it is in the Thumb state.
    * Unlike classic ARM processors like ARM7TDMI, there is no ARM state because the Cortex-M processors do not support the ARM instruction set.
* **Debug State** This is the state when in halting debug

<p align="center">
  <img src="./image-5.png"
       width="100%" 
       style="border-radius: 30px;"/>
</p>

---
## Registers

In general, there are three types of instruction set architecture (ISA).
* **Accumulator-based instruction set**. One of the ALU source operands is implicitly stored in a special register called accumulator, and the ALU result is saved into the accumulator.
    * The programmer does not have to specify this operand and the
destination register in the program.
    * The accumulator-based instruction set was popular in the 1950s.
* **Stack-based instruction set.** All ALU operands are assumed to be on top of the stack, and the ALU result is also placed on top of the stack.
    * The stack is a special region of memory. Thus, programmers need to push the value of operands onto the stack before an ALU operation is called. 
    * The stack-based instruction set was used in the 1960s.
* **Load-store instruction set**. ALU source or destination operands can be any general-purpose registers. 
    * ALU cannot directly use data stored in memory as operands. 
    * ALU can only access data in memory by using load or store instructions. Most modern processors are based on a load-store instruction set.

* In the ARM architecture, if data in memory is to be processed, it has to be loaded from the memory to registers in the register bank, processed inside the processor, and then written back to the memory, if needed (load-store architecture) 
* By having a sufficient number of registers in the register bank, this arrangement is easy to use, and allows efficient program code to be generated using C compilers.

<p align="center">
  <img src="./regs.png"
       width="100%" 
       style="border-radius: 30px;"/>
</p>

---

![alt text](image-7.png)