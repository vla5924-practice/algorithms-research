# Анализ и разработка алгоритмов

Практические работы по курсу "Анализ и разработка алгоритмов" (ПМИ 1 курс)


## Настройка окружения

* Компилятор и инструменты:
  ```sh
  sudo apt install cmake build-essential clang-12 clang-format-12 clang-tidy-12
  ```

* Расширения в Visual Studio Code:
  ```
  ms-vscode.cpptools
  ms-vscode.cmake-tools
  twxs.cmake
  xaver.clang-format
  notskm.clang-tidy
  ```

* Настройки рабочей области в `settings.json`:
  ```json
  {
      "clang-format.executable": "/usr/bin/clang-format-12",
      "clang-tidy.executable": "/usr/bin/clang-tidy-12",
      "clang-tidy.lintOnSave": false,
      "clang-tidy.compilerArgs": [
          "-std=c++17"
      ],
      "files.insertFinalNewline": true,
      "files.trimFinalNewlines": true
  }
  ```
