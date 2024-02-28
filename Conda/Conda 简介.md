# Conda 简介

conda 是一个开源的软件包管理系统和环境管理软件，用于安装多个版本的软件包及其依赖关系，并在它们之间轻松切换。conda 是为Python程序创建的，类似于 Linux、MacOS、Windows，也可以打包和分发其他软件。

## 1. Conda 安装

conda 分为 anaconda 和 miniconda，anaconda 是一个包含了许多常用库的集合版本，miniconda 是精简版本（只包含conda、pip、zlib、python 以及它们所需的包），剩余的通过 `conda install command` 命令自行安装即可；

> - [miniconda 官网](https://conda.io/miniconda.html)
> - [anaconda 官网](https://www.anaconda.com/download)

注意，安装时需要将conda添加到系统环境变量中（无论是Windows还是Ubuntu Bash/Zsh）。

使用以下命令验证安装：

```shell
$ conda --version
```

> - conda 更新
>
> ```shell
> $ conda update conda
> ```

## 2. Conda 换源

```shell
conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/free/
conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/main/
conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/cloud/conda-forge/
conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/cloud/bioconda/
conda config --add channels https://mirrors.bfsu.edu.cn/anaconda/cloud/bioconda/
conda config --add channels https://mirrors.bfsu.edu.cn/anaconda/cloud/conda-forge/
conda config --add channels https://mirrors.bfsu.edu.cn/anaconda/pkgs/free/
conda config --add channels https://mirrors.bfsu.edu.cn/anaconda/pkgs/main/
```

查看已经添加的源：

```shell
$ conda config --get channels
```

## 3. 环境管理

### 创建/删除环境

命令创建python版本为X.X、名字为 env_name 的虚拟环境。env_name文件可以在Anaconda安装目录 envs文件下找到。

```shell
$ conda create -n [env_name] python=X.X
```

输入以下命令查看当前存在的环境：

```shell
$ conda env list
```

删除环境：

```shell
$ conda remove -n [env_name] --all
$ conda env remove -n [env_name]
```

重命名环境：

```shell
$ conda create -n [new_name] --clone [old_name]
```

进入/退出环境：

```shell
$ conda activate env_name  		# 进入环境
$ conda deactivate				# 退出环境
```

