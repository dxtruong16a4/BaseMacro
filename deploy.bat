@echo off
echo Deploying Qt DLLs for BaseMacro...

REM Build the project first
call build.bat

REM Deploy Qt DLLs using windeployqt
echo.
echo Deploying Qt DLLs...
"C:\Qt\6.8.1\mingw_64\bin\windeployqt.exe" --no-translations --no-system-d3d-compiler build\BaseMacro.exe

echo.
echo Deployment completed!
echo You can now run: build\BaseMacro.exe
pause 