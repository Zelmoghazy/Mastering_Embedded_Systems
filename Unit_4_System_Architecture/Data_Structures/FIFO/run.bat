@make && cd .\build && .\Main.exe && cd ..
cppcheck --dump quiet .\FIFO.c
python "C:\Program Files\Cppcheck\addons\misra.py" --rule-texts="C:\Program Files\Cppcheck\addons\misra_rules.txt" .\FIFO.c.dump