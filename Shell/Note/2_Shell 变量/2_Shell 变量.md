# Shell 2_Shell 变量

## 1. Shell 变量

### 变量定义

在 Shell 编程中，变量是用于存储数据值的名称。定义变量时，变量名不加美元符号。**变量名和等号之间不能有空格。**

1. 变量命名遵循以下规则：

> - 只包含字母、数字和下划线： 变量名可以包含字母（大小写敏感）、数字和下划线 _，不能包含其他特殊字符。
> - 不能以数字开头： 变量名不能以数字开头，但可以包含数字。
> - 避免使用 Shell 关键字： 不要使用Shell的关键字（例如 `if`、`then`、`else`、`fi`、`for`、`while` 等）作为变量名，以免引起混淆。
> - 使用大写字母表示常量： 习惯上，常量的变量名通常使用大写字母，例如 `PI=3.14`。
> - 避免使用特殊符号： 尽量避免在变量名中使用特殊符号，因为它们可能与 `Shell`的语法产生冲突。
> - 避免使用空格： 变量名中不应该包含空格，因为空格通常用于分隔命令和参数。

```shell
# 有效的变量命名
RUNOOB="www.runoob.com"
LD_LIBRARY_PATH="/bin/"
_var="123"
var2="abc"

# 无效的变量命名
## 避免使用if作为变量名
if="some_value"
## 避免使用 $ 等特殊符号
variable_with_$=42
?var=123
user*name=runoob
## 避免空格
variable with space="value"
```

2. 可以用语句给变量赋值：

```shell
for file in `ls /etc`
# 或者 for file in $(ls /etc)
```

### 变量使用

使用一个定义过的变量，只要在变量名前面加美元符号即可。

```shell
your_name="qinjx"
echo $your_name
echo ${your_name}
```

变量名外面的花括号是可选的，加不加都行，**加花括号是为了帮助解释器识别变量的边界**。

### 只读变量

使用 `readonly`命令可以将变量定义为只读变量，只读变量的值不能被改变。

```shell
#!/bin/bash

myUrl="https://www.google.com"
readonly myUrl
myUrl="https://www.runoob.com"
```

其结果如下：

```shell
/bin/sh: NAME: This variable is read only.
```

### 删除变量

使用 `unset` 命令可以删除变量。

```shell
#!/bin/sh

myUrl="https://www.runoob.com"
unset myUrl
echo $myUrl
```

变量被删除后不能再次使用。`unset`命令不能删除只读变量。

## 2. Shell 变量类型

### 字符串变量

**在 Shell 中，变量通常被视为字符串。**字符串可以用单引号，也可以用双引号，也可以不用引号。

1. 单引号里的任何字符都会原样输出，单引号字符串中的变量是无效的；单引号字串中不能出现单独一个的单引号（对单引号使用转义符后也不行），但可成对出现，作为字符串拼接使用。

2. 双引号里可以有变量，双引号里可以出现转义字符。
3. 通过以下方式获取字符串长度：

```shell
string="abcd"
echo ${#string}   
echo ${#string[0]}   
```

4. 通过以下方式获得子字符串：

```shell
string="runoob is a great site"
echo ${string:1:4} 
```

5. 通过以下方式查找子字符串：

```shell
string="runoob is a great site"
echo `expr index "$string" io` 
```

### 数组变量

bash 支持一维数组（不支持多维数组），并且没有限定数组的大小。

类似于 C 语言，数组元素的下标由 0 开始编号。获取数组中的元素要利用下标，下标可以是整数或算术表达式，其值应大于或等于 0。

1. 通过以下方式定义数组：

```shell
数组名=(值1 值2 ... 值n)
```

2. 通过以下方式读取数组：

```shell
${数组名[下标]}
```

> 使用 `@` 符号可以获取数组中的所有元素

## 3. Shell 注释

以 `#`开头的行就是注释，会被解释器忽略。通过每一行加一个 `#` 号设置多行注释

使用Here文档进行多行注释：

```shell
:<<EOF
注释内容...
注释内容...
注释内容...
EOF
```

> `:` 是一个空命令，用于执行后面的 Here 文档，`<<'EOF'` 表示开启 Here 文档，`COMMENT` 是 Here 文档的标识符，在这两个标识符之间的内容都会被视为注释，不会被执行。

也可以使用`:`命令并用单引号 ' 将多行内容括起来。格式为：`: + 空格 + 单引号`。

```shell
: '
这是注释的部分。
可以有多行内容。
'
```

