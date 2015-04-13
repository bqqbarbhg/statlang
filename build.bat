@echo off

call "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\vcvarsall.bat" x64
cd bin

set IgnoreWarn= -wd4100 -wd4706
set CLFlags= -MT -nologo -Od -W4 -WX -Zi %IgnoreWarn% -D_CRT_SECURE_NO_WARNINGS
set LDFlags= -opt:ref

cl %CLFlags% ../src/tests.cpp ../src/string_table.cpp /link %LDFlags% > compile.err
tests > tests.err
type compile.err tests.err > errors.err
cd ..

