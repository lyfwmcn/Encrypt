# 项目简介
## 项目功能
* 文件加解密命令行程序
## 使用说明
```
--help: get help
-en [filePath] [key]: encrypt filePath by key
-de [filePath] [key]: decrypt filePath by key
```
## 更新日志
1. **v1.0.0 2026/5/30**: 
- **Add**: 实现 -en 加密、-de 解密、--help 帮助三个命令
- **Mod**: 文件读写采用二进制 IO，适配所有类型文件
# 文件说明
## 文件树结构
```
Encrypt
├── .vscode
├── bin
│   └── Encrypt.exe
├── build
├── src
│   ├── Config.hpp
│   ├── FileOperator.cpp
│   ├── FileOperator.hpp
│   ├── main.cpp
│   ├── ToolFunction.cpp
│   └── ToolFunction.hpp
├── .gitignore
├── CmakeLists.txt
└── README.md
```
## 主要文件功能
* **Config.hpp**: 配置文件
* **FileOperator.cpp/hpp**: 文件读取、写入、加密的核心文件
* **main.cpp**: 处理命令行逻辑
* **ToolFunction.cpp/hpp**: 工具函数
