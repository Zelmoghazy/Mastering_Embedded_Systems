* The keyword volatile forces the compiler to generate an executable, which always loads the variable value from the memory whenever this variable is read, and always stores the variable in memory whenever it is written.

* A C program should declare any variable that represents the data of a memory-mapped I/O register as `volatile`.

* Memory-mapped I/O has been widely used to access peripheral devices. 
* Data and control registers of external devices are mapped to specific memory addresses, and a program can use memory pointers to access these hardware registers,

* To prevent the compiler from optimizing out these memory pointers incorrectly, software must declare these pointers as `volatile`.

* In sum, a variable should be declared as `volatile` to prevent the compiler from optimizing it away when 
    * (1) this variable is updated by external memory-mapped hardware
    * (2) this variable is global and is changed by interrupt handlers or by multiple threads.