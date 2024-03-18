# CMake 3_CMakeLists 文件编写

## 1. 基础配置

### 设置项目版本和生成`version.h`

一般来说，项目一般需要设置一个版本号，方便进行版本的发布，也可以根据版本对问题或者特性进行追溯和记录。

通过project命令配置项目信息，如下：

```cmake
project(CMakeTemplate VERSION 1.0.0 LANGUAGES C CXX)
```

第一个字段是项目名称；通过`VERSION`指定版本号，格式为`major.minor.patch.tweak`，并且CMake会将对应的值分别赋值给以下变量（如果没有设置，则为空字符串）：

```text
PROJECT_VERSION, <PROJECT-NAME>_VERSION
PROJECT_VERSION_MAJOR, <PROJECT-NAME>_VERSION_MAJOR
PROJECT_VERSION_MINOR, <PROJECT-NAME>_VERSION_MINOR
PROJECT_VERSION_PATCH, <PROJECT-NAME>_VERSION_PATCH
PROJECT_VERSION_TWEAK, <PROJECT-NAME>_VERSION_TWEAK
```

使用`configure_file`命令，可以配置自动生成版本头文件，将头文件版本号定义成对应的宏，或者定义成接口，方便在代码运行的时候了解当前的版本号。

```cmake
configure_file(src/c/cmake_template_version.h.in "${PROJECT_SOURCE_DIR}/src/c/cmake_template_version.h")
```

假如`cmake_template_version.h.in`内容如下：

```c
#define CMAKE_TEMPLATE_VERSION_MAJOR @CMakeTemplate_VERSION_MAJOR@
#define CMAKE_TEMPLATE_VERSION_MINOR @CMakeTemplate_VERSION_MINOR@
#define CMAKE_TEMPLATE_VERSION_PATCH @CMakeTemplate_VERSION_PATCH@
```

执行CMake配置构建系统后，将会自动生成文件：`cmake_template_version.h`，其中`@<var-name>@`将会被替换为对应的值：

```c
#define CMAKE_TEMPLATE_VERSION_MAJOR 1
#define CMAKE_TEMPLATE_VERSION_MINOR 0
#define CMAKE_TEMPLATE_VERSION_PATCH 0
```

### 指定编程语言版本

为了在不同机器上编译更加统一，最好指定语言的版本，比如声明C使用`c99`标准，C++使用`c++11`标准：

```cmake
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
```

这里设置的变量都是`CMAKE_`开头(包括`project`命令自动设置的变量)，这类变量都是CMake的内置变量，正是通过修改这些变量的值来配置CMake构建的行为。

> `CMAKE_`、`_CMAKE`或者以下划线开头后面加上任意CMake命令的变量名都是CMake保留的。

### **配置编译选项**

通过命令`add_compile_options`命令可以为所有编译器配置编译选项（同时对多个编译器生效）； 

通过设置变量`CMAKE_C_FLAGS`可以配置c编译器的编译选项； 

而设置变量`CMAKE_CXX_FLAGS`可配置针对c++编译器的编译选项。 

```cmake
add_compile_options(-Wall -Wextra -pedantic -Werror)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pipe -std=c99")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pipe -std=c++11")
```

### 配置编译类型

通过设置变量`CMAKE_BUILD_TYPE`来配置编译类型，可设置为：`Debug`、`Release`、`RelWithDebInfo`、`MinSizeRel`等，比如：

```cmake
set(CMAKE_BUILD_TYPE Debug)
```

当然，更好的方式应该是在执行`cmake`命令的时候通过参数`-D`指定：

```shell
cmake -B build -DCMAKE_BUILD_TYPE=Debug
```

- 如果设置编译类型为`Debug`，那么对于c编译器，CMake会检查是否有针对此编译类型的编译选项`CMAKE_C_FLAGS_DEBUG`，如果有，则将它的配置内容加到`CMAKE_C_FLAGS`中。

可以针对不同的编译类型设置不同的编译选项，比如对于`Debug`版本，开启调试信息，不进行代码优化：

```cmake
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -O0")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
```

- 对于`Release`版本，不包含调试信息，优化等级设置为2：

```cmake
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O2")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")
```

### 添加全局宏定义

通过命令`add_definitions`可以添加全局的宏定义，在源码中就可以通过判断不同的宏定义实现相应的代码逻辑。

```cmake
add_definitions(-DDEBUG -DREAL_COOL_ENGINEER)
```

### 添加include目录

通过命令`include_directories`来设置头文件的搜索目录，比如：

```cmake
include_directories(src)
```

## 2. 编译目标文件

一般来说，编译目标(`target`)的类型一般有静态库、动态库和可执行文件。 这时编写`CMakeLists.txt`主要包括两步：

1. 编译：确定编译目标所需要的源文件；
2. 链接：确定链接的时候需要依赖的额外的库。

###  编译静态库/动态库

需要获取编译此静态库需要的文件列表，可以使用`set`命令，或者`file`命令来进行设置。

```cmake
file(GLOB_RECURSE MATH_LIB_SRC
        src/math/*.c
        )
add_library(math STATIC ${MATH_LIB_SRC})
```

使用`file`命令获取`src/c/math`目录下所有的`*.c`文件，然后通过`add_library`命令编译名为`math`的静态库，库的类型是第二个参数`STATIC`指定的。

> 如果指定为`SHARED`则编译的就是动态链接库。

### 编译可执行文件

通过`add_executable`命令来往构建系统中添加一个可执行构建目标，同样需要指定编译需要的源文件。

但是对于可执行文件来说，有时候还会依赖其他的库，则需要使用`target_link_libraries`命令来声明构建此可执行文件需要链接的库。