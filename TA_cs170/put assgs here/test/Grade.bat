@echo off

setlocal enabledelayedexpansion
set "submited_files=list.cpp"
set "inputs=input.txt 0.in 1.in 2.in 3.in 4.in 5.in h0.in h1.in h2.in h3.in h4.in"
set "outputs=output.txt 0.out 1.out 2.out 3.out 4.out 5.out h0.out h1.out h2.out h3.out h4.out"
set "exe=out.exe"
set /A large_timeout=900

set /A PRINT_SUBMITTED_FILES=0
set DONE_TEXT=---DONE---
set /A DELETE_OUTPUTS=1

set DIRECT_COMPILE_FILES=main.cpp list.cpp

FOR %%a IN (%submited_files%) DO ( 
  if NOT exist %%a ( 
    echo Can't find %%a as a submitted file
    exit
  )
)


echo ---Checking inputs/outputs---
set /A input_num=0

FOR %%a IN (%inputs%) DO ( 
  set inputArr[!input_num!]=%%a
  set /A input_num+=1
  
  if NOT exist %%a ( 
    echo Can't find %%a as input
    exit
  )
)


set /A output_num=0

FOR %%a IN (%outputs%) DO ( 
  set outputArr[!output_num!]=%%a
  set /A output_num+=1
  
    if NOT exist %%a ( 
    echo Can't find %%a as in\\output
    exit
  )
)

if NOT %input_num%==%output_num% ( 
  echo !!! Number of Inputs and Outputs are imbalanced, please check it again
  exit
)

echo %DONE_TEXT%
echo.

echo ---Clearing directories---
rm -rf gnu
rm -rf ms
echo %DONE_TEXT%
echo.

echo ---Creating directories---

mkdir gnu
mkdir ms
echo %DONE_TEXT%
echo.


echo ---Making .exe---

echo ..--- GNU ---
if exist makefile.gnu (
  make -f makefile.gnu
) else (
  echo MISSING GNU MAKEFILE
  echo Compiling directly...
  g++ -std=c++14 -pedantic -Wall -Wextra -Werror %DIRECT_COMPILE_FILES% -o %~dp0gnu\%exe%
  
)

echo ..--- MS ---
if exist makefile.ms (
  make -f makefile.ms
) else (
  echo MISSING MS MAKEFILE
  echo Compiling directly...
  cl /nologo /W4 /EHsc /Za %DIRECT_COMPILE_FILES% /Fe%~dp0ms\%exe%
)

echo %DONE_TEXT%
echo.

set /A "size=%input_num%-1"

echo ---Test GNU---
if NOT exist %~dp0gnu\%exe% (
  echo Cannot find %~dp0gnu\%exe%, please check if their makefile output as %exe% or if makefile failed to compile
) else (
  FOR /L %%a IN (0, 1, %size%) DO (
    
    echo ---Test !inputArr[%%a]!---
    
    set my_output_path=myout_gnu.%%a
    
    %~dp0gnu\%exe% !inputArr[%%a]! > !my_output_path!
    diff --strip-trailing-cr --ignore-blank-lines !my_output_path! !outputArr[%%a]!
    
    ::echo ---Removing !my_output_path!---
    if NOT %DELETE_OUTPUTS% == 0 (
      ::echo ---Printing submitted files---
      rm !my_output_path!
    )
    
    
    echo ---Test !inputArr[%%a]! DONE---
    echo.
  )

  echo %DONE_TEXT%
  echo.
)

echo ---Test MS---
if NOT exist %~dp0ms\%exe% (
  echo Cannot find %~dp0ms\%exe%, please check if their makefile output as %exe% or if makefile failed to compile
) else (
  FOR /L %%a IN (0, 1, %size%) DO (
    
    echo ---Test !inputArr[%%a]!---
    
    set my_output_path=myout_ms.%%a
    
    %~dp0ms\%exe% !inputArr[%%a]! > !my_output_path!
    diff --strip-trailing-cr --ignore-blank-lines !my_output_path! !outputArr[%%a]!
    
    if NOT %DELETE_OUTPUTS% == 0 (
      ::echo ---Printing submitted files---
      rm !my_output_path!
    )
    
    
    echo ---Test !inputArr[%%a]! DONE---
    echo.
  )

  echo %DONE_TEXT%
  echo.
)


echo ---Test Memleak---
g++ -std=c++14 -w main.cpp list.cpp SimpleMemoryLeakDetector.cpp -o mem.exe
mem.exe 0.in > 0.mem_out
diff --strip-trailing-cr --ignore-blank-lines 0.mem_out 0.out
if NOT %DELETE_OUTPUTS% == 0 (
  rm 0.mem_out
)
rm mem.exe

echo ---Memleak DONE---
echo.

if exist tmpLarge.txt (
  rm tmpLarge.txt
)

if exist timing.txt (
  rm timing.txt
)

if exist my_output_large.txt (
  rm my_output_large.txt
)

echo --- Test Large, please wait... ---
g++ -std=c++14 mainLarge.cpp list.cpp -o large.exe
set /A numLoop=((large_timeout - 1)/ 5) + 1

start /b large.exe input_large.txt > my_output_large.txt
call :checkloop


if NOT exist tmpLarge.txt (
  echo Processing complete...
  cat timing.txt
  diff --strip-trailing-cr --ignore-blank-lines output_large.txt my_output_large.txt 
) else (
  cat tmpLarge.txt
)

rm large.exe
echo.
echo ---Large DONE---
echo.

rm NUL
rm *.obj

if NOT %PRINT_SUBMITTED_FILES% == 0 (
  echo ---Printing submitted files---
  cat %submited_files%
  echo %DONE_TEXT%
  echo.
)


:checkloop
tasklist|findstr "large.exe" 
if %ERRORLEVEL% == 0 ( 
    if !numLoop! gtr 0 (
      sleep 5
      set /A numLoop=numLoop-1
      goto :checkloop
    ) else (
      taskkill /f /im large.exe > NUL
      goto :EOF
    )
)



