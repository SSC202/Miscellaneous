# Git 1_Git的安装配置

## 1. Git 的安装

### Ubuntu

```shell
$ sudo apt install libcurl4-gnutls-dev libexpat1-dev gettext \
  libz-dev libssl-dev

$ sudo apt install git

$ git --version
```

## 2. Git 的配置

Git 提供了一个叫做 git config 的工具，专门用来配置或读取相应的工作环境变量。

在Ubuntu中，这些变量可以存放在以下三个不同的地方：

- `/etc/gitconfig` 文件：系统中对所有用户都普遍适用的配置。若使用 `git config` 时用 `--system` 选项，读写的就是这个文件。
- `~/.gitconfig` 文件：用户目录下的配置文件只适用于该用户。若使用 `git config` 时用 `--global` 选项，读写的就是这个文件。
- 当前项目的 Git 目录中的配置文件（也就是工作目录中的 `.git/config` 文件）：这里的配置仅仅针对当前项目有效。每一个级别的配置都会覆盖上层的相同配置，所以 `.git/config` 里的配置会覆盖 `/etc/gitconfig` 中的同名变量。

在Windows中，Git 会找寻用户主目录下的 `.gitconfig` 文件。主目录即 `$HOME` 变量指定的目录，一般都是 `C:\Documents and Settings\$USER`。

### 用户信息设置

```shell
$ git config --global user.name "runoob"
$ git config --global user.email test@runoob.com
```

如果要在某个特定的项目中使用其他名字或者电邮，只要去掉 `--global` 选项重新配置即可，新的设定保存在当前项目的 `.git/config` 文件里。

### 文本编辑器设置

设置Git默认使用的文本编辑器, 一般可能会是 Vi 或者 Vim。

```shell
$ git config --global core.editor emacs
```

### 查看配置信息

```shell
$ git config --list
```

也可以在 `~/.gitconfig` 或 `/etc/gitconfig` 看到。

