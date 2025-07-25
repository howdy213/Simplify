# Simplify

## 项目简介

简易数学公式化简器，支持含未知数的四则运算，可以带入未知数的值并计算

## 目录结构

    │  .gitattributes
    │  .gitignore
    │  ConsoleOp.cpp
    │  ConsoleOp.h
    │  Formula.cpp
    │  Formula.h
    │  Frame.cpp
    │  Frame.h
    │  Functions.cpp
    │  Functions.h
    │  LICENSE
    │  main.cpp
    │  Print.cpp
    │  Print.h
    │  README.md
    │  Simplify.sln
    │  Simplify.vcxproj
    │  Simplify.vcxproj.filters
    │  Test.h
    │  Types.h

## 编译环境

Visual Studio 2022

Boost库

## 编译配置

将Boost库目录包含至项目中即可(默认为C:/local/boost_1_88_0/)

## 使用

公式输入示例：
$$
(x+2)*(x+2)/7+5/x
$$
将化简为:
$$
\frac{x^3+4x^2+4x+35}{7x}
$$

## 许可证

Mozilla Public License 2.0，详见LICENSE文件