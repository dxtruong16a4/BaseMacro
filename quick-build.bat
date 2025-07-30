@echo off
echo Quick build for development...

REM Build only (no deploy)
call build.bat

echo.
echo Quick build completed!
echo Use F5 in VS Code to run with debugger
echo Use deploy.bat for complete deployment
pause 