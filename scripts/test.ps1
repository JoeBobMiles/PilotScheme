# This is the Windows test script

.\scripts\lib-build.ps1

clang `
    -I includes `
    -o .\bin\test.exe `
    .\test\test.c .\lib\libpilot.lib

.\bin\test.exe
