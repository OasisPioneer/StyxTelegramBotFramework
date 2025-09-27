# 贡献指南

首先，非常感谢您愿意为 StyxTelegramBotFramework 做出贡献！您的每一份努力都将使这个项目变得更好。

本指南旨在为您提供清晰的贡献流程。

## 行为准则

我们致力于提供一个友好、互相尊重、无骚扰的社区环境。所有贡献者都应遵守我们的 [行为准则](CODE_OF_CONDUCT.md)。

## 如何贡献？

我们欢迎各种形式的贡献，包括但不限于：

- 报告 Bug
- 提交新的功能建议
- 编写或改进文档
- 提交代码修复或新功能

### 报告 Bug

如果您发现了一个 Bug，请通过 [GitHub Issues](https://github.com/OasisPioneer/StyxTelegramBotFramework/issues )
提交。为了让我们能更快地定位和修复问题，请在提交时尽量提供以下信息：

- **清晰的标题**：简要描述问题。
- **复现步骤**：详细说明如何一步步重现这个 Bug。
- **期望行为**：描述在没有 Bug 的情况下，程序应该如何表现。
- **实际行为**：描述实际发生了什么，并附上错误信息或截图。
- **您的环境**：操作系统、C++ 编译器版本、FTXUI 版本等。

### 提交功能建议

如果您有一个很棒的想法，欢迎通过 [GitHub Issues](https://github.com/OasisPioneer/StyxTelegramBotFramework/issues )
提交。请选择 "Feature request" 模板，并详细描述您的想法以及它能解决什么问题。

### 贡献代码

这是我们最推荐的贡献流程：

1. **Fork 仓库**：点击项目主页右上角的 "Fork" 按钮，将项目 Fork 到您自己的 GitHub 账户下。

2. **Clone 您的 Fork**：将您 Fork 的仓库 Clone 到本地。
   ```bash
   git clone https://github.com/YOUR_USERNAME/StyxTelegramBotFramework.git
   cd StyxTelegramBotFramework
   ```

3. **创建新分支**：从 `main` 分支创建一个新的特性分支 。请为分支取一个有意义的名称。
   ```bash
   # 如果是修复 Bug
   git checkout -b fix/some-bug-name
   
   # 如果是开发新功能
   git checkout -b feat/new-feature-name
   ```

4. **进行修改**：在您的本地分支上进行代码修改、添加新功能或修复 Bug。

5. **提交更改**
   ：使用清晰、规范的提交信息来提交您的更改。我们推荐使用 [Angular 提交规范](https://github.com/angular/angular/blob/main/CONTRIBUTING.md#commit )。
   ```bash
   git add .
   git commit -m "feat: 添加了 XYZ 功能"
   # 或者
   git commit -m "fix: 修复了 ABC 问题"
   ```

6. **推送到您的 Fork**：将您的本地分支推送到您在 GitHub 上的 Fork 仓库。
   ```bash
   git push origin feat/new-feature-name
   ```

7. **创建 Pull Request (PR)**：回到您在 GitHub 上的 Fork 仓库页面，点击 "Compare & pull request" 按钮。填写 PR 的标题和描述，然后提交。

我们会尽快审查您的 PR。感谢您的贡献！

## 代码风格

为了保持代码库的绝对一致性，本项目采用统一的命名规范。请所有贡献者严格遵守。

1. **核心命名约定**:
    * **所有命名**，包括但不限于 **类 (Classes)、结构体 (Structs)、函数 (Functions)、变量 (Variables) 和常量 (Constants)**，都
      **必须**使用 **帕斯CAL命名法 (PascalCase)**。
    * **示例**:
        * 类名: `MyPlugin`, `BotManager`
        * 函数名: `SendMessage`, `ProcessEvent`
        * 变量名: `CurrentUser`, `MessageText`
        * 常量名: `MaxConnections`, `DefaultTimeout`

2. **格式化**:
    * 我们使用 `.clang-format` 文件来定义和强制执行代码格式。在提交代码前，请确保您的代码已经通过了 `clang-format` 的格式化。
    * 安装您 IDE 对应的 `clang-format` 插件，可以在保存文件时自动完成格式化。

3. **注释**:
    * 对于所有公开的类和函数，请添加清晰的文档注释，解释其功能、参数和返回值。