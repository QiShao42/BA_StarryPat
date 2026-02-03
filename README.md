# 星空摸头机 (BA_StarryPat)

<div align="center">

![Version](https://img.shields.io/badge/version-1.0.0-blue)
![License](https://img.shields.io/badge/license-GPL--3.0-green)
![Qt](https://img.shields.io/badge/Qt-6.8.2-brightgreen)
![Platform](https://img.shields.io/badge/platform-Windows-lightgrey)

一个用于《蔚蓝档案》的自动化辅助工具

[功能特性](#功能特性) • [快速开始](#快速开始) • [使用说明](#使用说明) • [构建指南](#构建指南) • [免责声明](#免责声明)

</div>

---

**本软件仅供学习和研究使用，请勿用于任何商业用途。**

## 功能特性

- 🎯 自动化任务执行
- 🖼️ 基于图像识别的智能操作
- ⏰ 定时任务管理
- 👥 学生邀请自动化
- 🎨 现代化的UI界面
- 📊 详细的日志记录

## 快速开始

### 方式一：直接下载（推荐新手）

1. 前往 [Releases](https://github.com/QiShao42/BA_StarryPat/releases) 页面
2. 下载最新版本的 `ARONA.exe`
3. 双击运行程序

**首次运行安全提示：**
```
由于程序未经数字签名，Windows可能会显示安全警告。
这是正常现象，点击"更多信息" → "仍要运行"即可。
你也可以：
1. 右键点击exe文件 → 属性
2. 勾选底部的"解除锁定"
3. 点击确定
```

### 方式二：从源码构建

详见 [构建指南](#构建指南) 部分。

## 使用说明

### 基本配置

1. **首次启动**
   - 程序会自动创建配置文件 `arona_config.ini`
   - 可以根据需要调整配置参数

2. **设置扫荡任务**
   - 点击"扫荡设置"按钮
   - 配置要执行的任务
   - 设置重复次数和间隔时间

3. **学生邀请**
   - 点击"学生邀请"按钮
   - 选择要邀请的学生
   - 设置自动邀请参数

### 高级功能

- **定时任务**：设置特定时间自动执行任务
- **日志查看**：实时查看程序运行日志
- **截图功能**：用于调试和记录

## 构建指南

### 环境要求

- **操作系统**：Windows 10/11
- **编译器**：MSVC 2022 或更高版本
- **Qt**：6.8.2 或兼容版本
- **CMake**：3.16 或更高版本
- **Python**：3.6+ (用于资源文件管理，可选)

### 构建步骤

1. **克隆仓库**
```bash
git clone https://github.com/QiShao42/BA_StarryPat.git
cd BA_StarryPat
```

2. **配置Qt环境**
```bash
# 确保Qt的bin目录在PATH中
set PATH=C:\Qt\6.8.2\msvc2022_64\bin;%PATH%
```

3. **生成构建文件**
```bash
mkdir build
cd build
cmake .. -G "Ninja" -DCMAKE_BUILD_TYPE=Release
```

4. **编译**
```bash
cmake --build . --config Release
```

5. **运行**
```bash
.\ARONA.exe
```

### 更新资源文件（可选）

如果你添加了新的图片资源：

```bash
python update_resources.py
```

详见 [README_resources.md](README_resources.md)

## 项目结构

```
BA_StarryPat/
├── main.cpp                    # 程序入口
├── arona.cpp/h                 # 主窗口实现
├── timerdialog.cpp/h           # 定时器对话框
├── studentinvitedialog.cpp/h   # 学生邀请对话框
├── sweepsettingsdialog.cpp/h   # 扫荡设置对话框
├── aboutdialog.cpp/h           # 关于对话框
├── resources.qrc               # Qt资源文件
├── CMakeLists.txt              # CMake配置
├── LICENSE                     # MIT许可证
├── images/                     # 图片资源
│   ├── position_templates/     # 位置识别模板
│   ├── student_avatar/         # 学生头像
│   ├── skills/                 # 技能图标
│   └── ...
└── build/                      # 构建输出目录
```

## 技术栈

- **GUI框架**：Qt 6.8.2
- **编程语言**：C++17
- **构建系统**：CMake
- **图像处理**：OpenCV (通过Qt集成)

## 开发路线图

- [ ] 支持更多自动化任务
- [ ] 优化图像识别算法
- [ ] 添加多语言支持
- [ ] 提供更详细的使用文档
- [ ] 云配置同步功能

## 常见问题

### Q: 程序无法启动或闪退？
**A:** 请确保已安装 [Visual C++ Redistributable](https://aka.ms/vs/17/release/vc_redist.x64.exe)

### Q: 图像识别不准确？
**A:** 请确保游戏分辨率设置正确，推荐使用1920x1080分辨率

### Q: 如何更新程序？
**A:** 下载最新版本的exe文件替换即可，配置文件会自动保留

### Q: Windows报毒或安全警告？
**A:** 这是因为程序未签名导致的误报，你可以：
- 在 [VirusTotal](https://www.virustotal.com/) 上传检测
- 查看完整源代码确认安全性
- 自行从源码编译

## 贡献指南

欢迎提交 Issue 和 Pull Request！

1. Fork 本仓库
2. 创建特性分支 (`git checkout -b feature/AmazingFeature`)
3. 提交更改 (`git commit -m 'Add some AmazingFeature'`)
4. 推送到分支 (`git push origin feature/AmazingFeature`)
5. 开启 Pull Request

## 免责声明

**本软件仅供学习和研究使用，不得用于任何商业用途。**

本软件按"现状"提供，不提供任何明示或暗示的保证。使用本软件所产生的一切后果（包括但不限于账号封禁、数据丢失、游戏进度损失等）均由使用者自行承担，开发者不承担任何法律责任。

**警告：** 使用本软件可能违反游戏服务条款，可能导致账号被永久封禁。请在充分了解风险后谨慎使用。

## 版权声明

Copyright © 2026 星空的诺言

本项目基于 [GNU General Public License v3.0](LICENSE) 开源。

**GPL v3 保护说明**：
- ✅ 允许自由使用、修改和分发
- ✅ 允许用于商业目的
- ⚠️ **任何基于本代码的衍生作品必须同样采用 GPL v3 许可证开源**
- ⚠️ **禁止将本代码用于闭源商业产品**

### 第三方组件

- **Qt Framework** - LGPL v3 - © The Qt Company
- **游戏素材** - 所有游戏相关素材、截图、商标归《蔚蓝档案》及 NEXON Games 所有
- **图标资源** - 部分图标来自第三方创作者或AI生成

**本软件与《蔚蓝档案》官方无任何关联，非官方授权产品。**

## 联系方式

- **GitHub Issues**: [提交问题](https://github.com/QiShao42/BA_StarryPat/issues)
- **GitHub Discussions**: [参与讨论](https://github.com/QiShao42/BA_StarryPat/discussions)

---

<div align="center">

**⭐ 如果这个项目对你有帮助，请给它一个Star！⭐**

Made with ❤️ by 星空的诺言

</div>

