@echo off
chcp 65001 >nul
echo ============================================
echo    C++设计模式示例项目 - 构建脚本
echo ============================================
echo.

:: 检查是否使用控制台版本
set /p version="选择版本 (1=控制台, 2=GUI): "

if "%version%"=="1" (
    set CMAKE_FILE=CMakeLists.console.txt
    set BUILD_DIR=build_console
    echo 已选择: 控制台版本
) else (
    set CMAKE_FILE=CMakeLists.txt
    set BUILD_DIR=build
    echo 已选择: GUI版本
)

echo.
echo 正在创建构建目录...
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"

echo.
echo 正在配置项目...
cd /d "%~dp0%BUILD_DIR%"
cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release

if %ERRORLEVEL% neq 0 (
    echo.
    echo [错误] CMake配置失败!
    echo 请确保已安装:
    echo   - CMake 3.16+
    echo   - MinGW/GCC 或 MSVC
    if "%version%"=="2" (
        echo   - SFML 2.5
    )
    echo.
    pause
    exit /b 1
)

echo.
echo 正在编译项目...
cmake --build . --config Release

if %ERRORLEVEL% neq 0 (
    echo.
    echo [错误] 编译失败!
    echo.
    pause
    exit /b 1
)

echo.
echo ============================================
echo    编译成功!
echo ============================================
echo.
echo 运行程序: bin\DesignPatternDemo.exe
echo.
set /p run="是否立即运行? (y/n): "
if /i "%run%"=="y" (
    bin\DesignPatternDemo.exe
)

pause
