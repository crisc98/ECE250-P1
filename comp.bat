@echo off
setlocal
path C:\ECE150\MinGW\bin\;C:\ECE150\MinGW\libexec\gcc\x86_64-w64-mingw32\4.8.1\;%path%
g++ %1.cpp -std=c++11 -o %1.exe
endlocal
echo on
