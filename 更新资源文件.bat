@echo off
chcp 65001 >nul
REM ====================================
REM Qt Resources 资源文件自动更新工具
REM ====================================

title 更新 Qt 资源文件

echo.
echo ========================================
echo    Qt Resources 资源文件更新工具
echo ========================================
echo.

REM 检查 Python 是否安装
python --version >nul 2>&1
if %errorlevel% neq 0 (
    echo [错误] 未检测到 Python！
    echo.
    echo 请先安装 Python 3.x：
    echo https://www.python.org/downloads/
    echo.
    pause
    exit /b 1
)

REM 显示 Python 版本
echo [信息] Python 版本：
python --version
echo.

REM 检查是否在正确的目录
if not exist "update_resources.py" (
    echo [错误] 找不到 update_resources.py 文件！
    echo 请确保在项目根目录下运行此脚本。
    echo.
    pause
    exit /b 1
)

if not exist "images" (
    echo [警告] 找不到 images 文件夹！
    echo.
)

REM 运行 Python 脚本
echo [信息] 正在运行资源更新脚本...
echo.
python update_resources.py

REM 检查执行结果
if %errorlevel% equ 0 (
    echo.
    echo ========================================
    echo    资源文件更新成功！
    echo ========================================
    echo.
    echo [提示] 接下来需要重新编译 Qt 项目
    echo        以便生成新的资源文件。
    echo.
) else (
    echo.
    echo ========================================
    echo    执行失败，请检查错误信息
    echo ========================================
    echo.
)

pause

