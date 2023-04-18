```text
 _____ ______ _     _   _ ___________ _     _   _ _____
/  __ \| ___ \ |   | | | /  ___| ___ \ |   | | | /  ___|
| /  \/| |_/ / |   | | | \ `--.| |_/ / |   | | | \ `--.
| |    |  __/| |   | | | |`--. \  __/| |   | | | |`--. \
| \__/\| |   | |___| |_| /\__/ / |   | |___| |_| /\__/ /
 \____/\_|   \_____/\___/\____/\_|   \_____/\___/\____/
```

[![Build Status](https://github.com/Robin329/CPlusPlusThings/actions/workflows/cmake.yml/badge.svg)](https://github.com/Robin329/CPlusPlusThings/actions/workflows/cmake.yml)

- [C++](#c)
    - [项目运行](#项目运行)
    - [0. 项目概要](#0-项目概要)
    - [1. 基础进阶](#1-基础进阶)
    - [2. 实战系列](#2-实战系列)
      - [2.1 10日狂练](#21-10日狂练)
      - [2.2 重点实战练习](#22-重点实战练习)
      - [2.3 实践练习](#23-实践练习)
        - [2.3.1 回调功能实践](#231-回调功能实践)
        - [2.3.2 简单的定时器功能](#232-简单的定时器功能)
        - [2.3.3 c++原理与实践练习题](#233-c原理与实践练习题)
        - [2.3.4 epoll实践](#234-epoll实践)
        - [2.3.5 looper/handler实践](#235-looperhandler实践)
        - [2.3.6 共享内存实践](#236-共享内存实践)
        - [2.3.7 socket实践](#237-socket实践)
        - [2.3.8 面试题实践](#238-面试题实践)
        - [2.3.9 openCV练习](#239-opencv练习)
        - [2.3.10 Primer C++ 5](#2310-primer-c-5)
        - [2.3.11 Primer C++ 6](#2311-primer-c-6)
        - [2.3.12 一些实用的小例子](#2312-一些实用的小例子)
    - [3. C++2.0 新特性](#3-c20-新特性)
      - [3.0 概况](#30-概况)
      - [3.1 C++11 新特性](#31-c11-新特性)
      - [3.2 C++14/17/20](#32-c141720)
    - [4. 设计模式](#4-设计模式)
    - [5. STL 源码剖析](#5-stl-源码剖析)
    - [6. 并发编程](#6-并发编程)
      - [6.1 C++ Concurrency in Action](#61-c-concurrency-in-action)
      - [6.2 多线程与多进程](#62-多线程与多进程)
        - [6.2.1 Threading In C++](#621-threading-in-c)
        - [6.2.2 多进程实践](#622-多进程实践)
        - [6.2.3 多线程实践](#623-多线程实践)
        - [6.2.4 多线程竞争](#624-多线程竞争)
        - [6.2.5 多线程在C++中的应用](#625-多线程在c中的应用)
    - [7. C++ 惯用法](#7-c-惯用法)
        - [你最喜欢的 c++ 编程风格惯用法是什么?](#你最喜欢的-c-编程风格惯用法是什么)
    - [8. 学习课程](#8-学习课程)
      - [8.1 极客时间《现代 C++ 实战 30 讲》](#81-极客时间现代-c-实战-30-讲)
    - [9. 工具篇](#9-工具篇)
      - [9.1 容器快捷输出工具](#91-容器快捷输出工具)
      - [9.2 像 Python 一样简单输出（Jupyter Notebook）](#92-像-python-一样简单输出jupyter-notebook)
      - [9.3 观察编译过程变化](#93-观察编译过程变化)
      - [9.4 C++ 的 Debug 工具 dbg-macro](#94-c-的-debug-工具-dbg-macro)
      - [9.5 在 Linux 上的 Debug 工具 rr - 拥有回到过去的能力](#95-在-linux-上的-debug-工具-rr---拥有回到过去的能力)
    - [10. lib介绍](#10-lib介绍)
      - [10.1 ini解析](#101-ini解析)
      - [10.2 xml解析](#102-xml解析)
      - [10.3 ltp linux test工具](#103-ltp-linux-test工具)
      - [10.4 json生成和解析](#104-json生成和解析)
      - [10.5 enum转换](#105-enum转换)
    - [11. 拓展部分](#11-拓展部分)
      - [11.1 一些问题](#111-一些问题)
      - [11.2 clangd配置](#112-clangd配置)

# C++

### 项目运行

- **代码环境**

> Macosx : Darwin Kernel Version 21.3.0;
>
> root : xnu-8019.80.24~20/RELEASE_ARM64_T6000 arm64

- **编辑工具**

> CLion/VScode

- **编译器**

> gcc/g++

----

### 0. 项目概要

这是一个适合初学者从<u>**入门到进阶**</u>的仓库，解决了<u>**面试者与学习者**</u>想要<u>**深入 C++**</u>及如何<u>**入坑 C++**</u>的问题。除此之外，本仓库拓展了更加深入的源码分析，多线程并发等的知识，是一个比较全面的 C++ 学习从入门到进阶提升的仓库。

----

### 1. 基础进阶

- [const](./basic_content/const)
- [static](./basic_content/static)
- [this](./basic_content/this)
- [inline](./basic_content/inline)
- [sizeof](./basic_content/sizeof)
- [函数指针那些事](./basic_content/func_pointer)
- [纯虚函数和抽象类那些事](./basic_content/abstract)
- [vptr_vtable](./basic_content/vptr_vtable)
- [virtual](./basic_content/virtual)
- [volatile](./basic_content/volatile)
- [assert](./basic_content/assert)
- [位域那些事](./basic_content/bit)
- [extern](./basic_content/extern)
- [struct](./basic_content/struct)
- [struct 与 class](./basic_content/struct_class)
- [union](./basic_content/union)
- [c 实现 c++ 多态那些事](./basic_content/c_poly)
- [explicit](./basic_content/explicit)
- [friend](./basic_content/friend)
- [using](./basic_content/using)
- [::](./basic_content/maohao)
- [enum](./basic_content/enum)
- [decltype](./basic_content/decltype)
- [引用与指针那些事](./basic_content/pointer_refer)
- [宏那些事](./basic_content/macro)

----

### 2. 实战系列

#### 2.1 [10日狂练](./practical_exercises/10_day_practice)

- [x] [day1](practical_exercises/10_day_practice/day1)

基本c++语法

- [x] [day2](practical_exercises/10_day_practice/day2)

递归、结构体、枚举、静态变量等

- [x] [day3](practical_exercises/10_day_practice/day3)

函数

- [x] [day4](practical_exercises/10_day_practice/day4)

函数深入

- [x] [day5](practical_exercises/10_day_practice/day5)

继承多态

- [x] [day6](practical_exercises/10_day_practice/day6)

虚函数、抽象类

- [x] [day7](practical_exercises/10_day_practice/day7)

运算符重载

- [x] [day8](practical_exercises/10_day_practice/day8)

模板与STL

- [x] [day9](practical_exercises/10_day_practice/day9)

异常

- [x] [day10](practical_exercises/10_day_practice/day10)

文件与流

#### 2.2 [重点实战练习](./practical_exercises/key_exercises/)

├── [中括号重载.cpp](practical_exercises/key_exercises/2.bracket_overload.cpp)

├── [时钟++运算符重载.cpp](./practical_exercises/key_exercises/时钟++运算符重载.cpp)

├── [运算符重载之强制转换.cpp](./practical_exercises/key_exercises/运算符重载之强制转换.cpp)

└── [重载圆括号的时钟.cpp](./practical_exercises/key_exercises/重载圆括号的时钟.cpp)

├── [函数模板.cpp](practical_exercises/key_exercises/3.function_template.cpp)

├── [动态数组.cpp](practical_exercises/key_exercises/4.dynamic_array.cpp)

├── [字典插入与查找.cpp](practical_exercises/key_exercises/5.Dictionary_insertion_and_lookup.cpp)

├── [异常捕获.cpp](practical_exercises/key_exercises/12.Exception_catch.cpp)

├── [类模板之栈.cpp](./practical_exercises/key_exercises/类模板之栈.cpp)

├── [类模板特化之数组.cpp](./practical_exercises/key_exercises/类模板特化之数组.cpp)

├── [继承与封装.cpp](./practical_exercises/key_exercises/继承与封装.cpp)

├── [读写文件综合题.cpp](./practical_exercises/key_exercises/读写文件综合题.cpp)

├── [输入输出运算符重载.cpp](./practical_exercises/key_exercises/输入输出运算符重载.cpp)

├── [输入输出重载.cpp](./practical_exercises/key_exercises/输入输出重载.cpp)

├── [输出格式.cpp](./practical_exercises/key_exercises/输出格式.cpp)

#### 2.3 [实践练习](./practical_exercises/)

##### 2.3.1 [回调功能实践](./practical_exercises/callback/)

##### 2.3.2 [简单的定时器功能](./practical_exercises/timerfunc)

##### 2.3.3 [c++原理与实践练习题](./practical_exercises/cpp_principles_practice/)

##### 2.3.4 [epoll实践](./practical_exercises/epoll/)

##### 2.3.5 [looper/handler实践](./practical_exercises/looper_handler/)

##### 2.3.6 [共享内存实践](./practical_exercises/share_memory/)

##### 2.3.7 [socket实践](./practical_exercises/socket/)

##### 2.3.8 [面试题实践](./practical_exercises/interview_test/)

##### 2.3.9 [openCV练习](./practical_exercises/opencv/)

##### 2.3.10 [Primer C++ 5](./practical_exercises/primer_cpp_5/)

##### 2.3.11 [Primer C++ 6](./practical_exercises/primer_cpp_6/)

##### 2.3.12 [一些实用的小例子](./practical_exercises/key_exercises/)

----
### 3. [C++2.0 新特性](./c++2.0)

#### 3.0 概况

C++2.0 是一个简称，意为「现代 C++」，包括 C++11/14/17/20。

#### 3.1 [C++11 新特性](./c++2.0/c++11)

- [Variadic Templates](./c++2.0/c++11/variadic)

- Spaces in Template Expressions

  ```cpp
  vector<list<int> > //ok in each C++ version
  vector<list<int>> // before c++ 11 error error: ‘>>’ should be ‘> >’ within a nested template argument list,c++11后可以正常通过
  ```

- [nullptr and nullptr_t](./c++2.0/c++11/nullptr.cpp)

- [Automatic Type Deduction with auto](./c++2.0/c++11/auto.cpp)

- [Uniform Initialization ](./c++2.0/c++11/uniform_initialization.cpp)

- [initializer_list](./c++2.0/c++11/initializer.cpp)

- [explicit for ctors taking more than one argument](./c++2.0/c++11/explicit.cpp)

- [range-based for statement](./c++2.0/c++11/auto.cpp)

  ```cpp
  for(decl:col) {
      statement
  }
  ```

- [=default,=delete](./c++2.0/c++11/default_delete.cpp)

  如果你自行定义了一个 ctor,那么编译器就不会给你一个 default ctor
  如果强制加上 =default,就可以重新获得并使用 default ctor.

- Alias(化名)Template(template typedef)

  - [alias.cpp](./c++2.0/c++11/alias.cpp)
  - [template_template.cpp](./c++2.0/c++11/template_template.cpp)

- [template template parameter](./c++2.0/template_template.cpp)

- [type alias](./c++2.0/c++11/type_alias.cpp)

- [noexcept](./c++2.0/c++11/noexcept.cpp)

- [override](./c++2.0/c++11/override.cpp)

- [final](./c++2.0/c++11/final.cpp)

- [decltype](./c++2.0/c++11/decltype.cpp)

- [lambda](./c++2.0/c++11/lambda.cpp)

- [Rvalue reference](./c++2.0/c++11/rvalue.cpp)

- [move aware class](./c++2.0/c++11/move.cpp)

- 容器-结构与分类

  - (1) 序列式容器包括：`array`(C++2.0 新引入),`vector`,`deque`,`list`,`forward_list`(C++2.0 新引入)
  - (2) 关联式容器包括：`set/multiset`,`map/multimap`
  - (3) 无序容器(C++2.0 新引入,更换原先 `hash_xxx` 为 `unordered_xxx`)包括：`unordered_map/unordered_multimap,unordered_set/unordered_multiset`

- [Hash Function](./c++2.0/c++11/hash.cpp)

- [tuple](./c++2.0/c++11/tuple.cpp)

  学习资料：https://www.bilibili.com/video/av51863195?from=search&seid=3610634846288253061

#### 3.2 C++14/17/20

待更新...

---

### 4. [设计模式](./design_patterns/)

- [单例模式](./design-patterns/design-patterns-cpp/singleton)
- [生产消费者模式](./design-patterns/design-patterns-cpp/producer_consumer)

---

### 5. [STL 源码剖析](./src_analysis/stl)

- [array](src_analysis/stl/stl_src/Doc/array.md)
- [deque](src_analysis/stl/stl_src/Doc/deque.md)
- [queue and stack](src_analysis/stl/stl_src/Doc/queue_stack.md)
- [list](src_analysis/stl/stl_src/Doc/list.md)
- [vector](src_analysis/stl/stl_src/Doc/vector.md)
- [typename](src_analysis/stl/stl_src/Doc/typename.md)
- [traits](src_analysis/stl/stl_src/Doc/traits.md)
- [iterator](src_analysis/stl/stl_src/Doc/iterator.md)
- [谈谈 STL 设计之 EBO 优化](src_analysis/stl/stl_src/Doc/谈谈STL设计之EBO优化.md)
- [rb_tree](src_analysis/stl/stl_src/Doc/rb_tree.md)
- [set and multiset](set_multiset.md)
- [map and multimap](src_analysis/stl/stl_src/Doc/map_multimap.md)
- [hashtable](src_analysis/stl/stl_src/Doc/hashtable.md)
- [myhashtable](src_analysis/stl/stl_src/Doc/myhashtable.md)
- [unordered_map](src_analysis/stl/stl_src/Doc/unordered_map.md)

----

### 6. [并发编程](./concurrency)

#### 6.1 C++ Concurrency in Action

- [第一章](./concurrency/concurrency_v1/chapter1)
- [第二章](./concurrency/concurrency_v1/chapter2)

学习资料：https://downdemo.gitbook.io/cpp-concurrency-in-action-2ed/

#### 6.2 多线程与多进程

##### 6.2.1 Threading In C++

- [介绍](./concurrency/Threading_In_CPlusPlus/1.thread)
- [创建线程的五种类型](./concurrency/Threading_In_CPlusPlus/2.create_type)
- [Join 与 Detachs](./concurrency/Threading_In_CPlusPlus/3.join_detach)
- [mutex in C++ Threading](./concurrency/Threading_In_CPlusPlus/4.mutex)

> 学习自：
> https://www.youtube.com/watch?v=eZ8yKZo-PGw&list=PLk6CEY9XxSIAeK-EAh3hB4fgNvYkYmghp&index=4

##### 6.2.2 [多进程实践](./concurrency/process/)

##### 6.2.3 [多线程实践](./concurrency/pthread/)

##### 6.2.4 [多线程竞争](./concurrency/thread_example/)

##### 6.2.5 [多线程在C++中的应用](./concurrency/Threading_In_CPlusPlus/)

----

### 7. [C++ 惯用法](./codingStyleIdioms)

##### 你最喜欢的 c++ 编程风格惯用法是什么?

- [1.类初始化列表](./codingStyleIdioms/1_classInitializers)
- [2.枚举类替换命名空间](./codingStyleIdioms/2_enumclass_namespace)
- [3.RAII(资源获取即初始化)](./codingStyleIdioms/3_RAII)
- [4.copy and swap](./codingStyleIdioms/4_copy-swap)
- [5.pImpl(指针指向具体实现)](./codingStyleIdioms/5_pImpl)

----

### 8. 学习课程

#### 8.1 [极客时间《现代 C++ 实战 30 讲》](https://time.geekbang.org/channel/home)

- [堆、栈、RAII：C++ 里该如何管理资源？](./learn_class/modern_C++_30/RAII)
  - [堆](./modern_++_30/RAII/heap.cpp)
  - [栈](./learn_class/modern_C++_30/RAII/stack.cpp)
  - [RAII](./learn_class/modern_C++_30/RAII/RAII.cpp)
- [自己动手，实现 C++ 的智能指针](./learn_class/modern_C++_30/smart_ptr)
  - [auto_ptr、scope_ptr](./learn_class/modern_C++_30/smart_ptr/auto_scope.cpp)
  - [unique_ptr](./learn_class/modern_C++_30/smart_ptr/unique_ptr.cpp)
  - [shared_ptr](./learn_class/modern_C++_30/smart_ptr/shared_ptr.cpp)
- [右值和移动究竟解决了什么问题？](./learn_class/modern_C++_30/reference)
  - [左值与右值](./learn_class/modern_C++_30/reference/reference.cpp)
  - [延长声明周期](./learn_class/modern_C++_30/reference/lifetime.cpp)
  - [引用折叠](./learn_class/modern_C++_30/reference/collapses.cpp)
  - [完美转发](./learn_class/modern_C++_30/reference/forward.cpp)
  - [不要返回本地变量的引用](./learn_class/modern_C++_30/reference/don'treturnReference.cpp)
- [容器 1](./learn_class/modern_C++_30/container1)
- [容器 2](./learn_class/modern_C++_30/container2)
- [异常](./learn_class/modern_C++_30/exception)
- [字面量、静态断言和成员函数说明符](./learn_class/modern_C++_30/literalAssert)
- [是不是应该返回对象？](./learn_class/modern_C++_30/returnObj)
- [编译期多态：泛型编程和模板入门](./learn_class/modern_C++_30/compilerpoly)
- [译期能做些什么？一个完整的计算世界](./learn_class/modern_C++_30/compilercompute)
- [SFINAE：不是错误的替换失败是怎么回事?](./learn_class/modern_C++_30/SFINAE)
- [constexpr：一个常态的世界](./learn_class/modern_C++_30/constexpr)
- [函数对象和 lambda：进入函数式编程](./learn_class/modern_C++_30/functionLambda)
- [内存模型和 atomic：理解并发的复杂性](./learn_class/modern_C++_30/memorymodel_atomic)

----

### 9. 工具篇

#### 9.1 [容器快捷输出工具](./tool/output)

对吴老师的代码进行了修改，[点击此处直通代码](./tool/output/output_container.h)

输入：

```cpp
map<int, int> mp{
            {1, 1},
            {2, 4},
            {3, 9}};
    cout << mp << endl;
```

输出结果显示：

```cpp
{ 1 => 1, 2 => 4, 3 => 9 }
```

#### 9.2 像 Python 一样简单输出（Jupyter Notebook）

- [像 Python 一样玩 C/C++](./tool/像Python一样玩CC++.md)

#### 9.3 观察编译过程变化

-  [https://cppinsights.io](https://cppinsights.io/)

#### 9.4 C++ 的 Debug 工具 dbg-macro

- [C++ 的 Debug 工具 dbg-macro](./tool/C++的Debug工具dbg-macro.md)

#### 9.5 在 Linux 上的 Debug 工具 rr - 拥有回到过去的能力
- [用rr来进行debug](./tool/用rr来进行debug.md)

----

### 10. [lib介绍](./lib/)

#### 10.1 [ini解析](./lib/iniparser/)
#### 10.2 [xml解析](./lib/tinyxml/)
#### 10.3 [ltp linux test工具](./lib/ltp/)
#### 10.4 [json生成和解析](./lib/json-develop/)
#### 10.5 [enum转换](./lib/magic_enum/)

------

### 11. 拓展部分

#### 11.1 一些问题

- [C++ 中如何将 string 类型转换为 int 类型？](./extension/some_problem/string_int.md)



#### 11.2 clangd配置
`cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON .`

