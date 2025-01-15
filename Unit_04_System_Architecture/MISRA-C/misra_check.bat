cppcheck --dump quiet .\main.c        
python "C:\Program Files\Cppcheck\addons\misra.py" --rule-texts="C:\Program Files\Cppcheck\addons\misra_rules.txt" .\main.c.dump
rm *.dump
rm *.ctu-info