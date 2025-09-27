# Contributing Guidelines

First off, thank you for considering contributing to StyxTelegramBotFramework! Your effort is what makes this project
great.

This guide provides a clear workflow for contributions.

## Code of Conduct

We are committed to providing a friendly, respectful, and harassment-free community. All contributors are expected to
uphold our [Code of Conduct](CODE_OF_CONDUCT.md).

## How Can I Contribute?

We welcome contributions in many forms, including but not limited to:

- Reporting Bugs
- Submitting Feature Requests
- Writing or Improving Documentation
- Submitting Code Fixes or New Features

### Reporting Bugs

If you find a bug, please report it
via [GitHub Issues](https://github.com/OasisPioneer/StyxTelegramBotFramework/issues ). To help us resolve it quickly,
please include the following information:

- **A clear title**: Briefly describe the issue.
- **Steps to reproduce**: Detail how to reproduce the bug step-by-step.
- **Expected behavior**: Describe what should have happened.
- **Actual behavior**: Describe what actually happened, including error messages or screenshots.
- **Your environment**: OS, C++ compiler version, FTXUI version, etc.

### Suggesting Enhancements

If you have a great idea, feel free to submit it
via [GitHub Issues](https://github.com/OasisPioneer/StyxTelegramBotFramework/issues ). Please use the "Feature request"
template and describe your idea and the problem it solves.

### Code Contributions

This is our recommended workflow for code contributions:

1. **Fork the Repository**: Click the "Fork" button at the top right of the project page to create a copy of the project
   in your own GitHub account.

2. **Clone Your Fork**: Clone your forked repository to your local machine.
   ```bash
   git clone https://github.com/YOUR_USERNAME/StyxTelegramBotFramework.git
   cd StyxTelegramBotFramework
   ```

3. **Create a New Branch**: Create a new feature branch from the `main` branch. Please use a descriptive name.
   ```bash
   # For a bug fix
   git checkout -b fix/some-bug-name
   
   # For a new feature
   git checkout -b feat/new-feature-name
   ```

4. **Make Changes**: Make your code changes, add new features, or fix bugs on your local branch.

5. **Commit Your Changes**: Commit your changes with a clear and conventional commit message. We recommend following
   the [Angular Commit Message Guidelines](https://github.com/angular/angular/blob/main/CONTRIBUTING.md#commit ).
   ```bash
   git add .
   git commit -m "feat: Add XYZ feature"
   # or
   git commit -m "fix: Resolve ABC issue"
   ```

6. **Push to Your Fork**: Push your local branch to your forked repository on GitHub.
   ```bash
   git push origin feat/new-feature-name
   ```

7. **Create a Pull Request (PR)**: Go to your forked repository page on GitHub and click the "Compare & pull request"
   button. Fill out the PR title and description, then submit it.

We will review your PR as soon as possible. Thank you for your contribution!

## Coding Style

To maintain absolute consistency across the codebase, this project adopts a single, unified naming convention. All
contributors are required to strictly adhere to it.

1. **Core Naming Convention**:
    * **All names**, including but not limited to **Classes, Structs, Functions, Variables, and Constants**, **must**
      use **PascalCase**.
    * **Examples**:
        * Class names: `MyPlugin`, `BotManager`
        * Function names: `SendMessage`, `ProcessEvent`
        * Variable names: `CurrentUser`, `MessageText`
        * Constant names: `MaxConnections`, `DefaultTimeout`

2. **Formatting**:
    * We use a `.clang-format` file to define and enforce code formatting. Before committing, please ensure your code
      has been formatted with `clang-format`.
    * Installing a `clang-format` plugin for your IDE can automate this process on file save.

3. **Comments**:
    * For all public classes and functions, please add clear documentation comments explaining their purpose,
      parameters, and return values.