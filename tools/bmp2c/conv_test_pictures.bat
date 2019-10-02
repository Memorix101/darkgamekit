for %%f in (.\test_pictures\*.bmp) do .\bmp2c.exe "NEC touch it.ini" "%%f" "out\%%f.c"
pause


