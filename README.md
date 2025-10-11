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
Styx Telegram Bot Framework
</h1>

<p align="center">
  <b>A modular Telegram bot framework for C++ developers.</b>
</p>

## Describe

> This project is a Telegram bot framework designed for C++ developers, aimed at simplifying the complexities of bot
> development. By leveraging a highly modular plugin system, you no longer need to worry about low-level network
> communication or API interactions. Simply focus on developing plugins for your desired features, and you can quickly
> build powerful and extensible Telegram bots.

## Table of Contents

- [✨ Features](#-features)
- [🔧 Installation](#-installation)
- [🚀 Quick Start](#-quick-start)
- [💡 Usage](#-usage)
- [🤝 Contributing](#-contributing)
- [❤️ Sponsoring](#️-sponsoring)

---

## ✨ Features

* [ ] Language Internationalization
* [ ] Terminal User Interface (under development)
* [ ] Network Communication
* [ ] Plugin system

---

## 🌍 Internationalization & Localization

This project uses the `gettext` toolchain for internationalization (i18n) and localization (l10n).

#### 1. Extract Strings to a Template File (.pot)

This step scans the source code and extracts all translatable strings into a `.pot` (Portable Object Template) file.

*   **Option 1: Specify files manually**
    ```bash
    xgettext --language=C++ --from-code=UTF-8 -o [path/to/output.pot] --keyword=translate [source_file_1] [source_file_2] ...
    ```
    *   **Example:**
        ```bash
        xgettext --language=C++ --from-code=UTF-8 -o Language/StyxTelegramBotFramework.pot --keyword=translate Src/Main.CPP Src/Core/System/SingletonInstanceControl.CPP
        ```

*   **Option 2: Find all source files automatically (Recommended)**
    This command automatically finds all `.CPP` and `.HPP` files within the `Src` and `Include` directories.
    ```bash
    find Src Include -name "*.CPP" -o -name "*.HPP" | xargs xgettext --language=C++ --from-code=UTF-8 -o Language/StyxTelegramBotFramework.pot --keyword=translate
    ```

#### 2. Create a Translation File (.po) for a New Language

Based on the `.pot` template, create a new `.po` file for a target language (e.g., Simplified Chinese `zh_CN`). This file will contain the actual translations.

*   **Command:**
    ```bash
    msginit --input=[path/to/template.pot] --locale=[language_code] -o [path/to/output.po]
    ```
*   **Example:**
    ```bash
    msginit --input=Language/StyxTelegramBotFramework.pot --locale=zh_CN -o Language/zh_CN/LC_MESSAGES/StyxTelegramBotFramework.po
    ```
    After creating the file, you need to edit this `.po` file and fill in the translations in the `msgstr` fields. Also, ensure the `charset` in the file's header is set to `UTF-8`:
    ```po
    "Content-Type: text/plain; charset=UTF-8\n"
    ```

#### 3. Update an Existing Translation File

When the source code strings change, you first need to regenerate the `.pot` file (Step 1), and then use the following command to merge the changes into your existing `.po` files without losing previous translations.

*   **Command:**
    ```bash
    msgmerge --update [path/to/existing.po] [path/to/template.pot]
    ```
*   **Example:**
    ```bash
    msgmerge --update Language/zh_CN/LC_MESSAGES/StyxTelegramBotFramework.po Language/StyxTelegramBotFramework.pot
    ```

#### 4. Compile the Translation File to Binary Format (.mo)

Compile the edited `.po` file into a binary `.mo` file, which is optimized for the program to read at runtime.

*   **Command:**
    ```bash
    msgfmt [path/to/input.po] -o [path/to/output.mo]
    ```
*   **Example:**
    ```bash
    msgfmt Language/zh_CN/LC_MESSAGES/StyxTelegramBotFramework.po -o Language/zh_CN/LC_MESSAGES/StyxTelegramBotFramework.mo
    ```

---

## 🔧 Installation

## 🚀 Quick Start

## 💡 Usage

## 🤝 Contributing

We warmly welcome any form of contribution! Whether it's reporting a bug, submitting a feature request, or contributing
code directly, your help is invaluable.

Before you start, please take a few minutes to read our **[Contributing Guidelines](./Docs/CONTRIBUTING.md)** to ensure
a smooth process.

<p align="center">
  <a href="https://github.com/OasisPioneer/StyxTelegramBotFramework/issues"><img src="https://img.shields.io/github/issues/OasisPioneer/StyxTelegramBotFramework?style=flat-square" alt="GitHub issues"></a>
  <a href="https://github.com/OasisPioneer/StyxTelegramBotFramework/pulls"><img src="https://img.shields.io/github/issues-pr/OasisPioneer/StyxTelegramBotFramework?style=flat-square" alt="GitHub pull requests"></a>
  <img src="https://img.shields.io/badge/PRs-welcome-brightgreen.svg?style=flat-square" alt="PRs Welcome">
</p>

## 💖 Sincere thanks

### Contributors to this project

<a href="https://github.com/OasisPioneer/StyxTelegramBotFramework/graphs/contributors">
  <img src="https://contrib.rocks/image?repo=OasisPioneer/StyxTelegramBotFramework" />
</a>

## ❤️ Sponsoring

* [BTC] `1C9L21Y4VTbeVeTnccyhZb6ziJfdpyQswz`
* [USDT-TRC20] `TGMPjDRU92JYjidTu6tRuqZezqrNhWZcYS`

<img alt="Sponsor" align="center" src="/Docs/Sponsor.png"/>

## 💬 Communication and Feedback
[![Telegram Channel](https://img.shields.io/badge/Telegram-JoinChannel-blue?style=for-the-badge&logo=telegram)](https://t.me/StyxTelegramBotFramework)

<p align="right"><a href="#README-TOP"><img src="https://img.shields.io/badge/Back to top-555555?style=for-the-badge"></a></p>

## Star History

[![Star History Chart](https://api.star-history.com/svg?repos=OasisPioneer/StyxTelegramBotFramework&type=Date)](https://www.star-history.com/#OasisPioneer/StyxTelegramBotFramework&Date)