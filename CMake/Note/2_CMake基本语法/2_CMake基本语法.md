# CMake 2_CMake 基本语法

## 1. 基本语法

### 1. 注释

行注释使用`#`；

块注释使用`#[[Some comments can be multi lines or in side the command]]`

### 2. 变量

CMake中使用`set`和`unset`命令设置或者取消设置变量。CMake中有以下常用变量类型。

#### 一般变量

设置的变量可以是字符串，数字或者列表（直接设置多个值，或者使用分号隔开的字符串格式为`v1;v2;v3`）

```cmake
# Set variable
set(AUTHOR_NAME Farmer)
set(AUTHOR "Farmer Li")
set(AUTHOR Farmer\ Li)

# Set list
set(SLOGAN_ARR To be)   # Saved as "To;be"
set(SLOGAN_ARR To;be)
set(SLOGAN_ARR "To;be")

set(NUM 30)   # Saved as string, but can compare with other number string
set(FLAG ON)  # Bool value
```

> 1. 如果要设置的变量值包含空格，则需要使用双引号或者使用`\`转义，否则可以省略双引号；如果包含空格，且不遵守以上规则，视为列表。
> 2. 如果设置多个值或者字符串值的中间有`;`，则保存成列表。
> 3. 变量可以被`list`命令操作，单个值的变量相当于只有一个元素的列表。
> 4. 引用变量：`${<variable>}`，在`if()`条件判断中可以简化为只用变量名`<variable>`。

#### Cache变量

Cache变量（缓存条目，cache entries）的作用主要是为了**提供用户配置选项**，如果用户没有指定，则使用默认值。

```cmake
# set(<variable> <value>... CACHE <type> <docstring> [FORCE])
set(CACHE_VAR "Default cache value" CACHE STRING "A sample for cache variable")
```

> 1. 主要为了提供可配置变量，比如编译开关；
> 2. 引用CACHE变量：`$CACHE{<varialbe>}`。
> 3. Cache变量会被保存在构建目录下的`CMakeCache.txt`中，缓存起来之后是不变的，除非重新配置更新。

#### 环境变量

修改当前处理进程的环境变量，设置和引用格式为：

```cmake
# set(ENV{<variable>} [<value>])
set(ENV{ENV_VAR} "$ENV{PATH}")
message("Value of ENV_VAR: $ENV{ENV_VAR}")
```

### 3. 条件语句

支持的语法有：

1. 字符串比较，比如：`STREQUAL`、`STRLESS`、`STRGREATER`等；
2. 数值比较，比如：`EQUAL`、`LESS`、`GREATER`等；
3. 布尔运算，`AND`、`OR`、`NOT`；
4. 路径判断，比如：`EXISTS`、`IS_DIRECTORY`、`IS_ABSOLUTE`等；
5. 版本号判断；等等；
6. 使用小括号可以组合多个条件语句，比如：`(cond1) AND (cond2 OR (cond3))`。

对于**常量**：

1. `ON`、`YES`、`TRUE`、`Y`和非0值均被视为`True`；
2. `0`、`OFF`、`NO`、`FALSE`、`N`、`IGNORE`、空字符串、`NOTFOUND`、及以"-`NOTFOUND`"结尾的字符串均视为`False`。

对于**变量**，只要**其值不是常量中为`False`的情形，则均视为`True`**。

## 2. 基本语句

### 1. 消息打印

```cmake
message([<mode>] "message text" ...)
```

> 其中`mode`就相当于打印的等级，常用的有这几个选项：
>
> 1. 空或者`NOTICE`：比较重要的信息，如前面演示中的格式
> 2. `DEBUG`：调试信息，主要针对开发者
> 3. `STATUS`：项目使用者可能比较关心的信息，比如提示当前使用的编译器
> 4. `WARNING`：CMake警告，不会打断进程
> 5. `SEND_ERROR`：CMake错误，会继续执行，但是会跳过生成构建系统
> 6. `FATAL_ERROR`：CMake致命错误，会终止进程

### 2.  条件分支

这里以`if()/elseif()/else()/endif()`举个例子，for/while循环也是类似的：

```cmake
set(EMPTY_STR "")
if (NOT EMPTY_STR AND FLAG AND NUM LESS 50 AND NOT NOT_DEFINE_VAR)
    message("The first if branch...")
elseif (EMPTY_STR)
    message("EMPTY_STR is not empty")
else ()
    message("All other case")
endif()
```

### 3.  列表操作

`list`也是CMake的一个命令，有很多有用的子命令，比较常用的有：

1. `APPEND`，往列表中添加元素；
2. `LENGTH`，获取列表元素个数；
3. `JOIN`，将列表元素用指定的分隔符连接起来；

```cmake
set(SLOGAN_ARR To be)   # Saved as "To;be"
set(SLOGAN_ARR To;be)
set(SLOGAN_ARR "To;be")
set(WECHAT_ID_ARR Real Cool Eengineer)
list(APPEND SLOGAN_ARR a)                # APPEND sub command
list(APPEND SLOGAN_ARR ${WECHAT_ID_ARR}) # Can append another list
list(LENGTH SLOGAN_ARR SLOGAN_ARR_LEN)   # LENGTH sub command
# Convert list "To;be;a;Real;Cool;Engineer"
# To string "To be a Real Cool Engineer"
list(JOIN SLOGAN_ARR " " SLOGEN_STR)
message("Slogen list length: ${SLOGAN_ARR_LEN}")
message("Slogen list: ${SLOGAN_ARR}")
message("Slogen list to string: ${SLOGEN_STR}\n")
```

### 4. 文件操作

CMake的`file`命令支持的操作比较多，可以**读写、创建或复制文件和目录、计算文件hash、下载文件、压缩文件**等等。

### 5. 配置文件生成

使用`configure_file`命令可以将配置文件模板中的特定内容替换，生成目标文件。 输入文件中的内容`@VAR@`或者`${VAR}`在输出文件中将被对应的变量值替换。 使用方式为：

```cmake
set(VERSION 1.0.0)
configure_file(version.h.in "${PROJECT_SOURCE_DIR}/version.h")
```

假设`version.h.in`的内容为：

```c
#define VERSION "@VERSION@"
```

那么生成的`version.h`的内容为：

```c
#define VERSION "1.0.0"
```

### 6. 执行系统命令

使用`execute_process`命令可以执行一条或者顺序执行多条系统命令，对于需要使用系统命令获取一些变量值是有用的。比如获取当前仓库最新提交的commit的commit id：

```cmake
execute_process(COMMAND bash "-c" "git rev-parse --short HEAD" OUTPUT_VARIABLE COMMIT_ID)
```

### 7. 查找库文件

通过`find_library`在指定的路径和相关默认路径下查找指定名字的库，常用的格式如下：

```cmake
find_library(<VAR> name1 [path1 path2 ...])
```

找到的库就可以被其他`target`使用，表明依赖关系。

### 8. include其他模块

`include`命令将CMake文件或者模块加载并执行。比如：

```cmake
include(CPack) # 开启打包功能
include(CTest) # 开启测试相关功能
```

