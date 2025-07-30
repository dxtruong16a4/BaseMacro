@echo off
echo Building BaseMacro project...

REM Create build directory if it doesn't exist
if not exist "build" mkdir build
cd build

REM Configure with CMake
echo Configuring with CMake...
"C:\Program Files\CMake\bin\cmake.exe" .. -G "MinGW Makefiles" -DCMAKE_PREFIX_PATH="C:/Qt/6.8.1/mingw_64"

REM Build the project
echo Building project...
"C:\Program Files\CMake\bin\cmake.exe" --build .

REM Check if build was successful
if %ERRORLEVEL% EQU 0 (
    echo.
    echo Build successful! Executable created at: build\BaseMacro.exe
    echo.
    echo To run the program, use: build\BaseMacro.exe
) else (
    echo.
    echo Build failed! Check the error messages above.
)

REM Return to original directory
cd ..

pause 