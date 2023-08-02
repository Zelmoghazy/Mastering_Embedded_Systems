<div style="border-radius: 30px; overflow: hidden;">
    <p align="center">
        <img src="Images/Result.png"
             width="100%" 
             style="border-radius: 30px;"/>
    </p>
</div>

## Toolchain
* `arm-none-eabi-gcc`     : Compiler,linker and assembler
* `arm-none-eabi-as`      : Assembler
* `arm-none-eabi-ld`      : Linker
* `arm-none-eabi-objcopy` : Format converter
* `arm-none-eabi-objdump` : Display information from object files
* `arm-none-eabi-readelf` : display information about ELF files
* `arm-none-eabi-nm`      : list symbols from object files

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