# Base Macro

## Description
Base Macro is a Qt6-based application designed to automate tasks and manage settings through a graphical user interface. It provides a comprehensive macro recording and playback system with support for mouse, keyboard, and window automation.

## Features
- 🖱️ **Mouse Automation**: Click, move, scroll, and drag operations
- ⌨️ **Keyboard Automation**: Key presses, combinations, and text input
- ⏱️ **Delay Management**: Time-based, window-based, and user input delays
- 📋 **Clipboard Operations**: Copy, paste, and clipboard management
- 🪟 **Window Management**: Switch, move, resize, and close windows
- 🔄 **Loop Control**: For loops, while loops, break, and continue
- 🏷️ **Label & Goto**: Jump to specific points in macro execution
- 🎯 **Conditional Logic**: If-else statements and switch cases
- 🎨 **Modern UI**: Clean and intuitive interface with custom styling

## Prerequisites

Before building this project, make sure you have the following installed:

- **Qt 6.8.1** (or compatible version) with MinGW compiler
- **CMake** (version 3.16 or higher)
- **MinGW-w64** (GCC 13.2.0 or compatible)
- **Visual Studio Code** (recommended for development)

## Quick Start

### 1. Clone the Repository
```bash
git clone <repository-url>
cd BaseMacro
```

### 2. Build and Deploy (Recommended)
```bash
# This will build and deploy all necessary Qt DLLs
.\deploy.bat
```

### 3. Run the Application
```bash
# From command line
.\build\BaseMacro.exe

# Or double-click the executable in build folder
```

## Building the Project

### Method 1: Complete Build with Deployment (Recommended)
```bash
# Builds the project and deploys all Qt dependencies
.\deploy.bat
```

### Method 2: Development Build (Fast)
```bash
# Quick build for development (no DLL deployment)
.\quick-build.bat

# Or use VS Code: Press F5 to build and run with debugger
```

### Method 3: Manual Build
```bash
# Build only
.\build.bat

# Then deploy Qt DLLs manually
cmd /c "C:\Qt\6.8.1\mingw_64\bin\windeployqt.exe" --no-translations --no-system-d3d-compiler build\BaseMacro.exe
```

### Method 4: Using Visual Studio Code
1. Open the project folder in VSCode
2. Press **`F5`** to build and run with debugger
3. Press **`Ctrl+F5`** to run without debugger
4. Use **`Ctrl+Shift+B`** to build only

## Running the Application

### From VS Code (Recommended)
- **`F5`**: Build and run with debugger
- **`Ctrl+F5`**: Build and run without debugger

### From Command Line
```bash
# After deployment
.\build\BaseMacro.exe

# Or run directly (if Qt is in PATH)
.\build\BaseMacro.exe
```

## Troubleshooting

### Common Issues

1. **"Entry Point Not Found" error**
   - **Solution**: Run `.\deploy.bat` to deploy Qt DLLs
   - **Cause**: Missing Qt runtime libraries

2. **"QAbstractButton: No such file or directory" error**
   - **Solution**: Use CMake instead of direct g++ compilation
   - **Cause**: Building Qt project without proper Qt libraries

3. **"undefined reference" errors**
   - **Solution**: Verify Qt installation and CMAKE_PREFIX_PATH
   - **Check**: Qt version matches compiler (MinGW vs MSVC)

4. **CMake not found**
   - **Solution**: Install CMake from https://cmake.org/download/
   - **Add**: CMake to your system PATH

5. **Qt not found**
   - **Solution**: Install Qt from https://www.qt.io/download
   - **Important**: Install MinGW version for MinGW compiler
   - **Update**: CMAKE_PREFIX_PATH in build scripts if needed

## Project Structure

```
BaseMacro/
├── src/                    # Source code
│   ├── main.cpp           # Main entry point
│   ├── mainwindow.cpp     # Main window implementation
│   ├── mainwindow.h       # Main window header
│   ├── core/              # Core functionality
│   │   ├── baseaction.cpp # Base action classes
│   │   ├── configmanager.cpp # Configuration management
│   │   ├── dialogpool.cpp # Dialog management
│   │   ├── filemanager.cpp # File operations
│   │   ├── macrobuild.cpp # Macro building logic
│   │   └── threadmanager.cpp # Thread management
│   ├── widgets/           # Custom widgets
│   │   ├── dialogabout.cpp # About dialog
│   │   ├── dialoghowtouse.cpp # Help dialog
│   │   ├── dialogtips.cpp # Tips dialog
│   │   ├── settingswindow.cpp # Settings window
│   │   └── macroeditor.cpp # Macro editor
│   ├── actionmode/        # Action mode dialogs
│   │   ├── dialogclick.cpp # Mouse click dialog
│   │   ├── dialogkeyboard.cpp # Keyboard dialog
│   │   └── dialogdelay.cpp # Delay dialog
│   ├── utils/             # Utility functions
│   │   └── helper.cpp     # Helper functions
│   └── ui/               # UI files (.ui)
├── resources/             # Resources (icons, styles)
│   ├── icon/             # Application icons
│   └── style.qss         # Custom stylesheet
├── .vscode/              # VS Code configuration
├── CMakeLists.txt        # CMake configuration
├── build.bat             # Basic build script
├── deploy.bat            # Complete build + deploy script
├── quick-build.bat       # Fast development build
└── readme.md             # This file
```

## Build Scripts

| Script | Purpose | When to Use |
|--------|---------|-------------|
| `deploy.bat` | Complete build + Qt DLL deployment | Production, distribution |
| `quick-build.bat` | Fast build for development | Daily development |
| `build.bat` | Basic build only | CI/CD, custom workflows |

## Development

### Technology Stack
- **Qt 6.8.1** - GUI framework
- **CMake** - Build system
- **MinGW-w64** - Compiler
- **C++17** - Language standard
- **Visual Studio Code** - IDE (recommended)

### Development Workflow
1. **Daily Development**: Use `F5` in VS Code or `.\quick-build.bat`
2. **Testing**: Use `.\deploy.bat` to test complete deployment
3. **Debugging**: Use VS Code debugger with `F5`
4. **Distribution**: Use `.\deploy.bat` to create portable executable

### Code Style
- Follow Qt coding conventions
- Use meaningful variable and function names
- Add comments for complex logic
- Keep functions small and focused

## Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Test with `.\deploy.bat`
5. Submit a pull request

## License

[Add your license information here]

## Support

For issues and questions:
- Check the troubleshooting section above
- Review the project structure
- Ensure all prerequisites are installed correctly
