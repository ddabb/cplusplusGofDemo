C++ Design Patterns Demo

说明

- 这是一个用于教学的 C++ 控制台项目，展示 23 个经典的 GoF 设计模式（C++20 实现）。
- 每个模式在 src/ 下以头文件形式实现并包含一个 demo 调用函数，用于在控制台演示行为。

快速开始（使用 CMake）：

1. 克隆仓库

   git clone <repo-url>
   cd <repo-dir>

2. 创建构建目录并构建

   mkdir build && cd build
   cmake ..
   cmake --build .

3. 运行

   # 交互式运行
   ./DesignPatternDemo

   # 非交互式：运行所有 demo
   ./DesignPatternDemo --all

   # 非交互式：运行指定模式，例如 1
   ./DesignPatternDemo --pattern 1

说明与建议

- 目前 demo 的实现都放在头文件中，便于教学，但会导致编译耦合。建议将实现拆分到对应的 .cpp 文件以优化编译时间并便于单元测试。
- 建议添加 README 的示例输出、LICENSE、贡献指南和单元测试（如 GoogleTest）。
- 如果使用 Git，请将构建产物、IDE 特定文件加入 .gitignore（项目已包含 .gitignore）。

联系方式

- 本仓库为教学演示，欢迎提交 issue/PR 以改进内容。