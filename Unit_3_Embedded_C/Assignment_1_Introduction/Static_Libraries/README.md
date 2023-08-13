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

