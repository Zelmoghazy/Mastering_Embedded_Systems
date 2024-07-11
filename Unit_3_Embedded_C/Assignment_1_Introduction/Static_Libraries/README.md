* `ar` is generally used only to create and update static library files that the link editor or linker uses 


|Flag|Meaning|
|:---:|:---:|
|`r` | insert files into the archive, it is used to add or replace files in the archive.|
|`c` | Create the archive if it does not already exist.|
|`s` | Write an object-file index into the archive, or update an existing one, even if no other change is made to the archive. |

## Commands

1. `gcc -c Lib.c -o Lib.o`
2. `ar rcs Lib.a Lib.o`
3. `gcc Main.c -o Main.exe Lib.a`
4. `./Main.exe`

---

* Static libraries on Linux have the `.a` file extension. Static libraries on Windows have the `.lib` file extension.
* Dynamic libraries on Windows have the `.dll` extension; in order to link against a DLL, an import library is required. The import library is a static library. It contains the code required to load the DLL. 
* GCC has another file extension convention for import libraries, it should be called `*.dll.a` or `*.a`
* Import libraries (`.lib` with MSVC or `.dll.a` with GCC) are static libraries: they contain the code to load the DLL

* A DLL may have functions that are exported and functions that are not exported. An import library has to know which functions are exported and which aren't. 

---

static:

is always linked to the executable; that is, when you link an executable to a static library the library's contents are copied to the executable, the executable grows (very similar mechanism to having compiled multiple source files)

extensions: Windows: lib, a, Unix: a

dynamic (also known as shared):

is a separate object containing compiled code; very similar to executable file but it does not contain an entry point (no main function)

extensions: Windows: dll, Unix: so, macOS: dynlib

when you link an executable to such library it will contain a small extra metadata that points what is needed

requires underlying platform support: being able to run dynamically linked code is a feature of the operating system (many embedded systems do not have it)

multiple shared libraries can be reused by multiple executables at the same time, shared libraries are loaded only once into system's memory (so multiple executables using the same shared library will save RAM)

may have worse performance than statically linked library (from negligible to significant difference)

easier to reverse-engineer (mostly a security concern)

If it is ABI-stable, can be updated in-place without having to recompile the executable - if there is a long dependency chain this can save a lot of time

If it is ABI-stable, can be un/reloaded at runtime => this enables runtime plugin support