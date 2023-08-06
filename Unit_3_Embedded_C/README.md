## Cross-Compilation Toolchain
* `arm-none-eabi-gcc`     : Compiler, linker and assembler
* `arm-none-eabi-as`      : Assembler
* `arm-none-eabi-ld`      : Linker
* `arm-none-eabi-objcopy` : Format converter
* `arm-none-eabi-objdump` : Display information from object files
* `arm-none-eabi-readelf` : Display information about ELF files
* `arm-none-eabi-nm`      : List symbols from object files

## Compiler Flags

|Flag|Meaning|
|:---:|:---:|
|`-B <directory>`| Add `<directory>` to the compiler's search paths.|
|`-v`|Display the programs invoked by the compiler.|
|`-E`|Preprocess only; do not compile, assemble or link.|
|`-S`|Compile only; do not assemble or link.|
|`-c`|Compile and assemble, but do not link.|
|`-o <file>`|Place the output into `<file>`.|
|`-save-temps`|Do not delete intermediate files.|
|`-time`|Time the execution of each subprocess.|
|`-std=<standard>`|Assume that the input sources are for `<standard>`.|
|`-march=<arch name>`|Specify the name of the target architecture.|
|`-mcpu=<cpu name>`|Specify the name of the target CPU., architecture is derived|
|`-mtune=`|Tune code for the given processor.|
|`-O<level>`|Optimization Level {0,1,2,3,s,fast,g}|
|`-g`|Produce debugging information|
|`-ggdb`|Produce debugging information for use by GDB.|
|`-gdwarf-2`|Produce debugging information in DWARF format (Proteus).|

## Compilation Process

<div style="border-radius: 30px; overflow: hidden;">
    <p align="center">
        <img src="Images/CompilationProcess.png"
             width="100%" 
             style="border-radius: 30px;"/>
    </p>
</div>

## ELF Format

* **ELF** : Executable and Linkable Format
  * ELF is a standard file format for object files and executable files in GCC
* A file format standard describes a way of organizing various elements (data, read-only data, code, uninitialized data,etc.) of a program in different sections.

<div style="border-radius: 30px; overflow: hidden;">
    <p align="center">
        <img src="Images/ELF.png"
             width="50%" 
             style="border-radius: 30px;"/>
    </p>
</div>

* `.text`: The machine code of the compiled program.
* `.rodata`: Read-only data 
* `.data`: Initialized global C variables.
  * Local C variables are maintained at run time on the stack, and do not appear in either the `.data` or `.bss` sections.
* `.bss:` Uninitialized global C variables.
  * This section occupies no actual space in the object file; it is merely a place holder.
  * Object file formats distinguish between initialized and uninitialized variables for space efficiency
  * uninitialized variables do not have to occupy any actual disk space in the object file.

## Relocatable object files

* `.o` files contains machine specific code and data of the program
  * it doesnt contain any absolute addresses.
* `arm-none-eabi-objdump` : display information from object files

### Objdump Flags

|Flag|Meaning|
|:---:|:---:|
|`-h`|Display the contents of the section headers|
|`-x`|Display the contents of all headers|
|`-d`|Display assembler contents of executable sections|
|`-D`|Display assembler contents of all sections|
|`-S`|Intermix source code with disassembly|


```c
#include "uart.h"

unsigned char string_buffer[100] = "Zeyad Ahmed Ibrahim"; // .data
char *rodata = "read only data"; // .rodata

void main(void)
{
    uart_send_string(string_buffer);
}
```

<div style="border-radius: 30px; overflow: hidden;">
    <p align="center">
        <img src="Images/Objdump.png"
             width="100%" 
             style="border-radius: 30px;"/>
    </p>
</div>

* `ALLOC` – Section will have space allocated in the process when loaded.
  *  Set for all sections except those containing debug information.
* `LOAD` – Section will be loaded from the file into the child process memory.
  * Set for pre-initialized code and data, clear for .bss sections.
* `RELOC` – Section needs to be relocated before loading.
* `READONLY` – Section cannot be modified by the child process.
* `CODE` – Section contains executable code only.
* `DATA` – Section contains data only (no executable code).

---

## Start-up File

* Startup file is responsible for setting up the enviroment for the main user code to run.
* Code written in startup file runs before `main()`.
* Some parts of the startup code is target dependent.
* **Startup code takes care of :**
  * Vector table placement.
  * Stack reinitialization.
* Startup code is responsible of `.data` , `.bss` section initialization in main memory
  * Copy `.data` section to RAM.
  * Initialize the `.bss` section to zero in RAM.

<div style="border-radius: 30px; overflow: hidden;">
    <p align="center">
        <img src="Images/ROM-RAM.png"
             width="100%" 
             style="border-radius: 30px;"/>
    </p>
</div>

* Section boundary information and sizes need to be exported from a **linker script** to the startup file.

## Linker Script

* Linker script is a text file which explains how different sections of the object files should be merged to create an output file.
* Linker and locator assign absolute addresses to different section of the output file by referring to address information mentioned in the linker script.
* Linker script also includes the code and data memory address and size information.
* Linker scripts are written using the GNU Linker command Language and has the file extension `.ld`.

### Linker Script Commands

|Command|Meaning|
|:---:|:---:|
|`ENTRY`|command specifically for defining the first executable instruction in an output file (its entry point).|
|`MEMORY`|describes the location and size of blocks of memory in the target.|
|`SECTIONS`|controls exactly where input sections are placed into output sections, their order in the output file, and to which output sections they are allocated.|


* `ENTRY(symbol)` 

```
MEMORY 
  {
    name (attr) : ORIGIN = origin, LENGTH = len
    ...
  }
```

* `MEMORY`: you can describe which memory regions may be used by the linker, and which memory regions it must avoid.
  * `attr` define the attribute list of the memory region.
  * `name` is a name used internally by the linker to refer to the region.
  * `origin` is the start address of the region in physical memory.
  * `len` is the size in bytes of the region (an expression). 


|attr|Meaning|
|:---:|:---:|
|`R`|Read-only sections.|
|`W`|Read/write sections.|
|`X`|Sections containing executable code.|
|`A`|Allocated sections.|
|`I`|Initialized sections.|

```
SECTIONS { ...
  secname : {
    contents
  }
... }
```
* `SECTION` specifies the properties of an output section.
  * its location, alignment, contents, fill pattern, and target memory region.
  * The linker will not create output sections which do not have any contents. 
  * `secname` must meet the constraints of your output format.

* In the following example, the command script arranges the output file into three consecutive sections, named `.text`, `.data`, and `.bss`, taking the input for each from the correspondingly named sections of all the input files:


```
SECTIONS { 
  .text : 
  {
    *(.text)                   // merge .text section of all input files
    *(.rodata)
  }>(vma) AT> (lma)

  .data :
  {
    *(.data) 
  }>(vma) AT> (lma)

  .bss :
  {
    *(.bss)
    *(COMMON) 
  }>(vma) AT> (lma) 
}
```

* `AT ( ldadr )` The expression `ldadr` that follows the `AT` keyword specifies the load address of the section. 
* `>region` Assign this section to a previously defined region of memory. 

* **Location Counter :** The special linker variable dot `.` always contains the current output location counter. 
  * it must always appear in an expression within a `SECTIONS` command. 
  * Assigning a value to the `.` symbol will cause the location counter to be moved.
    * This may be used to create holes in the output section.
  * The location counter **cannot** moved backwards.
  * You can use this symbol inside the linker script to track and define boundaries of various sections.

```
SECTIONS
{
  output :
  {
  . = 0x10000;  
  file1(.text)
  . = . + 1000;
  file2(.text)
  . += 1000;
  file3(.text)
  } = 0x1234;
}
```

### Linker Script symbols
* A symbol is the name of an address

<div style="border-radius: 30px; overflow: hidden;">
    <p align="center">
        <img src="Images/SymbolTable.png"
             width="100%" 
             style="border-radius: 30px;"/>
    </p>
</div>

* `T` : The symbol is in the text (code) section.
* `D` : The symbol is in the initialized data section.
* `U` : The symbol is undefined.

## Linking

* `arm-none-eabi-ld`      : Linker

|Flag|Meaning|
|:---:|:---:|
|`-T script`|Use script as the linker script.|
|`-nostdlib`|Do not use the standard system startup files or libraries when linking.|
|`-Map=<file.map>`|Write a linker map to `<file>`|

* Linking is the process of collecting and combining the various pieces of code and data that a program needs in order to be loaded (copied) into memory and executed. 
* Linkers play a crucial role in software development because they enable separate compilation.
  * Instead of organizing a large application as one source file, we can decompose it into smaller, more manageable modules that can be modified and compiled separately.
  * When we change one of these modules, we simply recompile it and relink the application, without having to recompile the other files.
* Linker program take as input a collection of relocatable object files and command line arguments and generate as output a fully linked executable object file that can be loaded and run.
  * The input relocatable object files consist of various code and data sections.
  * Instructions are in one section (`.text`), initialized global variables are in another section (`.data`), and uninitialized variables are in yet another section (`.bss`).
* To build the executable, the linker must perform two main tasks:
  * **Symbol resolution :** Object files define and reference symbols.
    * The purpose of symbol resolution is to associate each symbol reference with exactly one symbol definition.
  * **Relocation :** Compilers and assemblers generate code and data sections that start at address zero.
    * The linker relocates these sections by associating a memory location with each symbol definition, and then modifying all of the references to those symbols so that they point to this memory location.
* A linker concatenates blocks together, decides on run-time locations for the concatenated blocks, and modifies various locations within the code and data blocks. 

<div style="border-radius: 30px; overflow: hidden;">
    <p align="center">
        <img src="Images/MemoryMap.png"
             width="100%" 
             style="border-radius: 30px;"/>
    </p>
</div>

### Final Executable Symbol Table

<div style="border-radius: 30px; overflow: hidden;">
    <p align="center">
        <img src="Images/Symbol_exec.png"
             width="45%" 
             style="border-radius: 30px;"/>
    </p>
</div>

---
## Makefile

* **Target :** things you want to build.
* **Dependencies :** Things that need to be built before the Target is built.
* **Rules :** define how you go from a complete list of dependencies to the given target

* `%` wild card -> any
* `$*` variable matches whatever `%` was
* `$@` variable matches the name of the target
* make with no arguments -> builds first target


## GDB

`gdb-multiarch`

### GDB Flags

### GDB Commands

* `start` : break at first instruction
* `run` : Run the program. 
* `n` : Step over next C instruction
* `s` : Step into next C instruction
* `l` : print lines of code around where you at
* `b <l>` : break at a line  
* `b <function name>` : break at a function first instruction
* `c` : continue until a break point.
* `finish` :  Continue running until just after function in the selected stack frame returns.
* `watch <var>` : break when value of variable changes. 
* `i+b` : all set breakpoints and watchpoints
* `delete` : delete all breakpoints and watchpoints
* `q` : quit
* `p <var>` : print current value of a variable
* `display <var>` : for every step print the value of var, `undisplay <id>` 
* `whatis <var>` : print the data type of the variable and the last value in the value history.
* `up` / `down` : peak up and down the call stack
* `bt` : backtrace the entire call stack
* `disas` : Disassembly of code
* `shell <command>` : execute commands from terminal (ex `clear`)
* `python <commands>` : full python interpreter inside gdb
* **Reverse debugging**
  * `target record-full` : record everything from this point
  * `rn` : step back over
  * `rs` : step back into
* `set var <name>=<value>` : change the value of variable during debugging.


### TUI Mode
* `Ctrl+X+A` : TUI Mode
* `Ctrl+X` + `2` : Cycle views (Disassembly, registers, source code)
* `Ctrl+L` : Refresh Screen
* `Ctrl+p`: previous command in tui
* `Ctrl+n` : next command in tui mode

* **Note :** To enable source syntax highlighting
  * `pip install Pygments` 


<div style="border-radius: 30px; overflow: hidden;">
    <p align="center">
        <img src="Images/TUI.png"
             width="75%" 
             style="border-radius: 30px;"/>
    </p>
</div>
