# 贡献指南

感谢你考虑为 BA_StarryPat 做出贡献！

## 行为准则

- 尊重所有贡献者
- 接受建设性的批评
- 专注于对社区最有利的事情
- 保持友好和专业的态度

## 如何贡献

### 报告Bug

在提交Bug报告前，请：

1. **检查是否已有相关Issue**
2. **确认使用的是最新版本**
3. **准备详细的重现步骤**

提交Bug时请包含：

- **清晰的标题**
- **详细的描述**
- **重现步骤**
- **预期行为 vs 实际行为**
- **环境信息**：Windows版本、Qt版本、程序版本
- **截图或日志**（如果适用）

### 建议新功能

提交功能建议时请：

1. **描述问题或需求**
2. **说明建议的解决方案**
3. **列出替代方案**（如果有）
4. **说明该功能对用户的价值**

### 提交代码

#### 开发环境设置

1. Fork 本仓库
2. 克隆你的Fork
```bash
git clone https://github.com/YOUR_USERNAME/BA_StarryPat.git
cd BA_StarryPat
```

3. 设置上游仓库
```bash
git remote add upstream https://github.com/QiShao42/BA_StarryPat.git
```

4. 创建特性分支
```bash
git checkout -b feature/your-feature-name
```

#### 编码规范

- **C++风格**：
  - 使用驼峰命名法（camelCase）for 变量和函数
  - 使用帕斯卡命名法（PascalCase）for 类名
  - 缩进使用4个空格
  - 大括号采用Allman风格

- **注释**：
  - 为复杂逻辑添加注释
  - 使用中文或英文注释（保持一致）
  - 公共API必须有文档注释

- **提交信息**：
  ```
  type: 简短描述（不超过50字符）
  
  详细说明（如果需要）
  - 列出主要变更
  - 说明原因和影响
  ```
  
  类型（type）可以是：
  - `feat`: 新功能
  - `fix`: Bug修复
  - `docs`: 文档更新
  - `style`: 代码格式调整
  - `refactor`: 代码重构
  - `perf`: 性能优化
  - `test`: 测试相关
  - `chore`: 构建/工具相关

#### 提交流程

1. **确保代码可以编译**
```bash
cmake --build build --config Release
```

2. **测试你的更改**
   - 运行程序验证功能
   - 确保没有引入新的Bug

3. **提交更改**
```bash
git add .
git commit -m "feat: 添加新功能描述"
```

4. **同步上游更改**
```bash
git fetch upstream
git rebase upstream/main
```

5. **推送到你的Fork**
```bash
git push origin feature/your-feature-name
```

6. **创建Pull Request**
   - 前往GitHub创建PR
   - 填写PR模板
   - 等待审查

#### Pull Request 指南

- **一个PR只做一件事**
- **更新相关文档**
- **确保没有合并冲突**
- **响应审查意见**
- **保持PR较小和聚焦**

### 改进文档

文档改进同样重要！

- 修正错别字
- 改进说明的清晰度
- 添加使用示例
- 翻译文档

## 项目结构

```
BA_StarryPat/
├── main.cpp                    # 程序入口
├── arona.cpp/h                 # 主窗口（核心逻辑）
├── timerdialog.cpp/h           # 定时器功能
├── studentinvitedialog.cpp/h   # 学生邀请功能
├── sweepsettingsdialog.cpp/h   # 扫荡设置功能
├── aboutdialog.cpp/h           # 关于对话框
├── resources.qrc               # Qt资源配置
├── images/                     # 图片资源
└── CMakeLists.txt              # 构建配置
```

## 许可证

通过贡献代码，你同意你的贡献将在 [GNU General Public License v3.0](LICENSE) 下发布。

## 问题？

如有疑问，欢迎：
- 提交Issue
- 在Discussions中讨论
- 查看现有的PR和Issue

---

再次感谢你的贡献！ 🎉

