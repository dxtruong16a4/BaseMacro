@echo off
title BaseMacro Project Manager
color 0A

:menu
cls
echo ========================================
echo         BaseMacro Project Manager
echo ========================================
echo.
echo 1. Build Project (VS Code - CMake)
echo 2. Build Project (Quick - VS Code)
echo 3. Deploy Qt DLLs
echo 4. Run from VS Code Build
echo 5. Run from Qt Creator Build
echo 6. Clean Build Directories
echo 7. Exit
echo.
echo ========================================
set /p choice="Enter your choice (1-7): "

if "%choice%"=="1" goto build
if "%choice%"=="2" goto quick-build
if "%choice%"=="3" goto deploy
if "%choice%"=="4" goto run-vsc
if "%choice%"=="5" goto run-qt
if "%choice%"=="6" goto clean
if "%choice%"=="7" goto exit
goto menu

:build
cls
echo ========================================
echo         Building BaseMacro Project
echo ========================================
echo.

REM Create build directory if it doesn't exist
if not exist "build\vsc-build" mkdir build\vsc-build
cd build\vsc-build

REM Configure with CMake
echo Configuring with CMake...
"C:\Program Files\CMake\bin\cmake.exe" ..\.. -G "MinGW Makefiles" -DCMAKE_PREFIX_PATH="C:/Qt/6.8.1/mingw_64"

REM Build the project
echo Building project...
"C:\Program Files\CMake\bin\cmake.exe" --build .

REM Check if build was successful
if %ERRORLEVEL% EQU 0 (
    echo.
    echo Build successful! Executable created at: build\vsc-build\BaseMacro.exe
    echo.
    echo To run the program, use: build\vsc-build\BaseMacro.exe
) else (
    echo.
    echo Build failed! Check the error messages above.
)

REM Return to original directory
cd ..\..
echo.
pause
goto menu

:quick-build
cls
echo ========================================
echo         Quick Build for Development
echo ========================================
echo.

REM Build only (no deploy)
call :build

echo.
echo Quick build completed!
echo Use F5 in VS Code to run with debugger
echo Use option 3 for complete deployment
echo.
pause
goto menu

:deploy
cls
echo ========================================
echo         Deploying Qt DLLs
echo ========================================
echo.

REM Check VSCode build directory first
if exist "build\vsc-build\BaseMacro.exe" (
    echo Found executable in: build\vsc-build
    echo Deploying Qt DLLs...
    "C:\Qt\6.8.1\mingw_64\bin\windeployqt.exe" --no-translations --no-system-d3d-compiler "build\vsc-build\BaseMacro.exe"
    echo.
    echo Deployment completed for: build\vsc-build
    echo You can now run: build\vsc-build\BaseMacro.exe
    goto :deploy-success
)

REM Check Qt Creator build directory
if exist "build\qt-build\BaseMacro.exe" (
    echo Found executable in: build\qt-build
    echo Deploying Qt DLLs...
    "C:\Qt\6.8.1\mingw_64\bin\windeployqt.exe" --no-translations --no-system-d3d-compiler "build\qt-build\BaseMacro.exe"
    echo.
    echo Deployment completed for: build\qt-build
    echo You can now run: build\qt-build\BaseMacro.exe
    goto :deploy-success
)

REM Find the latest Qt Creator build directory
for /d %%i in (build\Desktop_Qt_6_8_1_MinGW_64_bit-*) do (
    if exist "%%i\BaseMacro.exe" (
        echo Found executable in: %%i
        echo Deploying Qt DLLs...
        "C:\Qt\6.8.1\mingw_64\bin\windeployqt.exe" --no-translations --no-system-d3d-compiler "%%i\BaseMacro.exe"
        echo.
        echo Deployment completed for: %%i
        echo You can now run: %%i\BaseMacro.exe
        goto :deploy-success
    )
)

echo ERROR: No BaseMacro.exe found in any build directories!
echo Please build the project first using option 1 or Qt Creator.
goto :deploy-end

:deploy-success
echo.
echo Deployment completed successfully!

:deploy-end
echo.
pause
goto menu

:run-vsc
cls
echo ========================================
echo         Running from VS Code Build
echo ========================================
echo.

REM Check if executable exists
if exist "build\vsc-build\BaseMacro.exe" (
    echo Starting BaseMacro from VS Code build...
    start "" "build\vsc-build\BaseMacro.exe"
    echo Application started successfully!
) else (
    echo ERROR: BaseMacro.exe not found in build\vsc-build directory!
    echo Please build the project first using option 1
)
echo.
pause
goto menu

:run-qt
cls
echo ========================================
echo         Running from Qt Creator Build
echo ========================================
echo.

REM Check if executable exists
if exist "build\qt-build\BaseMacro.exe" (
    echo Starting BaseMacro from Qt Creator build...
    start "" "build\qt-build\BaseMacro.exe"
    echo Application started successfully!
) else (
    echo ERROR: BaseMacro.exe not found in build\qt-build directory!
    echo Please build the project first using Qt Creator
)
echo.
pause
goto menu

:clean
cls
echo ========================================
echo         Cleaning Build Directories
echo ========================================
echo.

echo This will remove all build directories.
set /p confirm="Are you sure? (y/N): "
if /i not "%confirm%"=="y" goto :clean-cancelled

echo.
echo Removing build directories...
if exist "build\vsc-build" (
    rmdir /s /q "build\vsc-build"
    echo Removed: build\vsc-build
)
if exist "build\qt-build" (
    rmdir /s /q "build\qt-build"
    echo Removed: build\qt-build
)
if exist "build\Desktop_Qt_6_8_1_MinGW_64_bit-*" (
    for /d %%i in (build\Desktop_Qt_6_8_1_MinGW_64_bit-*) do (
        rmdir /s /q "%%i"
        echo Removed: %%i
    )
)
if exist "Makefile*" (
    del Makefile*
    echo Removed: Makefile files
)
if exist "release" (
    rmdir /s /q "release"
    echo Removed: release directory
)
if exist "debug" (
    rmdir /s /q "debug"
    echo Removed: debug directory
)

echo.
echo Clean completed!
goto :clean-end

:clean-cancelled
echo.
echo Clean operation cancelled.

:clean-end
echo.
pause
goto menu

:exit
cls
echo ========================================
echo         Thank you for using
echo         BaseMacro Project Manager
echo ========================================
echo.
echo Goodbye!
timeout /t 2 /nobreak >nul
exit 