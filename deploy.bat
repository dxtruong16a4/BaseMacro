@echo off
echo Deploying Qt DLLs for BaseMacro...

REM Build the project first
call build.bat

REM Wait a moment for build to complete
timeout /t 2 /nobreak >nul

REM Deploy Qt DLLs using windeployqt
echo.
echo Deploying Qt DLLs...
if exist "build\BaseMacro.exe" (
    cmd /c "C:\Qt\6.8.1\mingw_64\bin\windeployqt.exe" --no-translations --no-system-d3d-compiler build\BaseMacro.exe
    echo.
    echo Deployment completed successfully!
    echo You can now run: build\BaseMacro.exe
) else (
    echo ERROR: BaseMacro.exe not found in build directory!
    echo Please check if the build was successful.
)

pause 