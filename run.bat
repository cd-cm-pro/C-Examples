@if not exist result md result
@gcc "examples/%~1/main.c" -o .\result\main.exe %~2
@.\result\main.exe