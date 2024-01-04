# Shell 1_Shell 简介

## 1. Shell 简介

Shell 是一个用 C 语言编写的程序，它是用户使用 Linux 的桥梁。Shell 既是一种命令语言，又是一种程序设计语言。Shell 是指一种应用程序，这个应用程序提供了一个界面，用户通过这个界面访问操作系统内核的服务。Ken Thompson 的 sh 是第一种 Unix Shell，Windows Explorer 是一个典型的图形界面 Shell。

Shell 编程跟 JavaScript、php 编程一样，只要有一个能编写代码的文本编辑器和一个能解释执行的脚本解释器就可以了。

Linux 的 Shell 种类众多，常见的有：

- Bourne Shell（`/usr/bin/sh`或`/bin/sh`）
- Bourne Again Shell（`/bin/bash`）
- C Shell（`/usr/bin/csh`）
- K Shell（`/usr/bin/ksh`）
- Shell for Root（`/sbin/sh`）

Bash 是大多数 Linux 系统默认的 Shell。

## 2. 第一个 Shell 脚本

打开文本编辑器，新建一个文件 `test.sh`，扩展名为 sh（sh代表shell）。

```shell
#!/bin/bash
echo "Hello World"
```

> - `#!` 是一个约定的标记，它告诉系统这个脚本需要什么解释器来执行，即使用哪一种 Shell。
>
> - `echo`命令用于向窗口输出文本。

Shell 可以作为可执行程序运行：

```shell
$ chmod +x ./test.sh    #使脚本具有执行权限
$ ./test.sh  			#执行脚本
Hello World
```

> 注意，一定要写成 `./test.sh`，而不是 `test.sh`，运行其它二进制的程序也一样，直接写 `test.sh`，`linux` 系统会去 `PATH` 里寻找有没有叫 `test.sh` 的，而只有 `/bin`, `/sbin`, `/usr/bin`，`/usr/sbin` 等在 `PATH` 里。

