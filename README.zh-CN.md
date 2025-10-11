<a name="README-TOP"></a>
<p align="center">
    <img src="Styx-Telegram-Bot-Framework.svg" alt="Styx Telegram Bot Framework Logo" width="300"/>
</p>

<hr/>

<p align="center">
  <a href="README.md">🇺🇸 English</a> | <a href="README.zh-CN.md">🇨🇳 中文版</a>
</p>

<hr/>

<p align="center">
  <!-- 核心技术 -->
  <img src="https://img.shields.io/badge/C++-20-blue.svg?style=flat-square&logo=c%2B%2B&logoColor=white" alt="C++20">
  <img src="https://img.shields.io/badge/TUI-FTXUI-blueviolet.svg?style=flat-square" alt="FTXUI">
  <!-- 许可证 -->
  <a href="LICENSE"><img src="https://img.shields.io/badge/License-AGPL_v3-blue.svg?style=flat-square" alt="License"></a>
</p>

<p align="center">
  <!-- 社交徽章 -->
  <a href="https://github.com/OasisPioneer/StyxTelegramBotFramework/stargazers"><img src="https://img.shields.io/github/stars/OasisPioneer/StyxTelegramBotFramework?style=social" alt="Stars"></a>
  <a href="https://github.com/OasisPioneer/StyxTelegramBotFramework/network/members"><img src="https://img.shields.io/github/forks/OasisPioneer/StyxTelegramBotFramework?style=social" alt="Forks"></a>
</p>

<h1 align="center">
冥河电报机器人框架
</h1>

<p align="center">
  <b>为 C++ 开发者打造的模块化电报机器人框架</b>
</p>

## 描述

> 本项目是一个为 C++ 开发者设计的电报 (Telegram) 机器人框架，旨在解决原生 API 开发的复杂性。通过高度模块化的插件系统，您无需再关心底层的网络通信和
> API 交互，只需专注于实现具体功能的插件，即可快速构建功能强大、易于扩展的电报机器人。

## 目录

- [✨ 功能特性](#-功能特点)
- [🔧 安装指南](#-安装指南)
- [🚀 快速开始](#-快速开始)
- [💡 使用示例](#-使用示例)
- [🤝 如何贡献](#-如何贡献)
- [❤️ 赞助我们](#-赞助我们)

---

## ✨ 功能特点

* [ ] 语言国际化
* [ ] 终端用户界面(开发中)
* [ ] 网络通信
* [ ] 插件系统

---

## 🌍 国际化与本地化

本项目使用 `gettext` 工具集进行国际化 (i18n) 和本地化 (l10n)。以下是相关操作指南。

#### 1. 提取文本生成模板文件 (.pot)

此步骤会扫描源代码，将所有待翻译的文本提取到一个 `.pot` 模板文件中。

*   **方法一：手动指定文件**
    ```bash
    xgettext --language=C++ --from-code=UTF-8 -o [输出.pot文件路径] --keyword=translate [源文件1] [源文件2] ...
    ```
    *   **示例：**
        ```bash
        xgettext --language=C++ --from-code=UTF-8 -o Language/StyxTelegramBotFramework.pot --keyword=translate Src/Main.CPP Src/Core/System/SingletonInstanceControl.CPP
        ```

*   **方法二：自动查找所有源文件 (推荐)**
    此命令会自动查找 `Src` 和 `Include` 目录下的所有 `.CPP` 和 `.HPP` 文件。
    ```bash
    find Src Include -name "*.CPP" -o -name "*.HPP" | xargs xgettext --language=C++ --from-code=UTF-8 -o Language/StyxTelegramBotFramework.pot --keyword=translate
    ```

#### 2. 为新语言创建翻译文件 (.po)

基于 `.pot` 模板文件，为目标语言（例如：简体中文 `zh_CN`）创建一个新的 `.po` 文件。此文件用于存放实际的译文。

*   **命令格式：**
    ```bash
    msginit --input=[模板.pot文件] --locale=[语言代码] -o [输出.po文件路径]
    ```
*   **示例：**
    ```bash
    msginit --input=Language/StyxTelegramBotFramework.pot --locale=zh_CN -o Language/zh_CN/LC_MESSAGES/StyxTelegramBotFramework.po
    ```
    创建文件后，您需要手动编辑此 `.po` 文件，在 `msgstr` 字段中填入翻译。同时，请确保将文件头部的 `charset` 修改为 `UTF-8`：
    ```po
    "Content-Type: text/plain; charset=UTF-8\n"
    ```

#### 3. 更新现有的翻译文件

当源代码中的文本发生变化后，您需要先重新执行第 1 步生成最新的 `.pot` 文件，然后使用以下命令将变更合并到现有的 `.po` 文件中，而不会丢失已有的翻译。

*   **命令格式：**
    ```bash
    msgmerge --update [要更新的.po文件] [模板.pot文件]
    ```
*   **示例：**
    ```bash
    msgmerge --update Language/zh_CN/LC_MESSAGES/StyxTelegramBotFramework.po Language/StyxTelegramBotFramework.pot
    ```

#### 4. 编译翻译文件为二进制格式 (.mo)

将编辑好的 `.po` 文件编译成程序可直接读取的二进制 `.mo` 文件。

*   **命令格式：**
    ```bash
    msgfmt [输入的.po文件] -o [输出的.mo文件]
    ```
*   **示例：**
    ```bash
    msgfmt Language/zh_CN/LC_MESSAGES/StyxTelegramBotFramework.po -o Language/zh_CN/LC_MESSAGES/StyxTelegramBotFramework.mo
    ```

---

## 🔧 安装指南

## 🚀 快速开始

## 💡 使用示例

## 🤝 如何贡献

我们热烈欢迎任何形式的贡献！无论是报告一个 Bug、提交一个功能请求，还是直接贡献代码，都对我们意义重大。

在您开始之前，请花几分钟阅读我们的 **[贡献指南](./Docs/CONTRIBUTING.zh-CN.md)**，它将帮助您更顺畅地参与进来。

<p align="center">
  <a href="https://github.com/OasisPioneer/StyxTelegramBotFramework/issues"><img src="https://img.shields.io/github/issues/OasisPioneer/StyxTelegramBotFramework?style=flat-square" alt="GitHub issues"></a>
  <a href="https://github.com/OasisPioneer/StyxTelegramBotFramework/pulls"><img src="https://img.shields.io/github/issues-pr/OasisPioneer/StyxTelegramBotFramework?style=flat-square" alt="GitHub pull requests"></a>
  <img src="https://img.shields.io/badge/PRs-welcome-brightgreen.svg?style=flat-square" alt="PRs Welcome">
</p>

## 💖 由衷感谢

### 本项目贡献者

<a href="https://github.com/OasisPioneer/StyxTelegramBotFramework/graphs/contributors">
  <img src="https://contrib.rocks/image?repo=OasisPioneer/StyxTelegramBotFramework" />
</a>

## ❤️ 赞助我们

* [BTC] `1C9L21Y4VTbeVeTnccyhZb6ziJfdpyQswz`
* [USDT-TRC20] `TGMPjDRU92JYjidTu6tRuqZezqrNhWZcYS`

<img alt="Sponsor" align="center" src="/Docs/Sponsor.png"/>

## 💬 交流反馈
[![Telegram Channel](https://img.shields.io/badge/Telegram-加入频道-blue?style=for-the-badge&logo=telegram)](https://t.me/StyxTelegramBotFramework)

<p align="right"><a href="#README-TOP"><img src="https://img.shields.io/badge/回到顶部-555555?style=for-the-badge"></a></p>

## Star History

[![Star History Chart](https://api.star-history.com/svg?repos=OasisPioneer/StyxTelegramBotFramework&type=Date)](https://www.star-history.com/#OasisPioneer/StyxTelegramBotFramework&Date)