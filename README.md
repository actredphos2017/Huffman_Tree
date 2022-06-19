# 哈夫曼树

## 文件说明

主程序
main.cpp

哈夫曼

哈夫曼数据结构
Huffman.h

哈夫曼函数
Huffman.cpp

工具程序

二进制文件编辑
BinaryFileEdit.cpp

浮点型权重转整性权重
DoubleMapToInt.cpp

## 功能简介

```
======= System Status =======
Target Code File: NULL                                  //目标编码字典
Target Origin File: NULL                                //目标原文件
Huffman Tree Status: Unexisted                          //哈夫曼树是否存在
Huffman Code Status: Unexisted                          //哈夫曼编码是否存在

Menu:

 About Code File:
    1. Switch code file in local                        //选择本地编码字典文件
    2. Design code from char-weight file                //用 字符-权重 文件进行哈夫曼树的搭建
    3. Enter temporary code file into Terminal          //从命令行中输入临时的 字符-编码
    4. Build code file from origin file                 //利用原文件中的字符数频作为权重生成哈夫曼树

 About Origin File:
    A. Switch origin file to coding/decoding            //选择原文件
    B. Coding origin file with existed huffman code     //编码
    C. Decoding origin file with existed huffman code   //译码

 About Huffman:
    a. Visual print huffman tree                        //可视化打印输出哈夫曼树
    b. Output the huffman code                          //输出哈夫曼编码字典
    c. Save huffman code in local                       //保存哈夫曼编码字典
    d. Save huffman tree in local                       //保存哈夫曼树
    e. Load huffman tree in local                       //读取哈夫曼树

    Q. Quit                                             //结束
```

## 操作举例

### 用频率文件设计哈夫曼树

新建一个文本文件，里面写入以下内容

```
1 0.05
2 0.29
3 0.07
4 0.08
5 0.14
6 0.23
7 0.03
8 0.11
```

选择操作2

输入该文件的位置

然后程序会构建哈夫曼树

之后选择操作a

可视化查看哈夫曼树

选择操作b

打印输出哈夫曼编码

### 对文本文件进行哈夫曼编码
利用功能1~4来生成哈夫曼编码字典

```
 About Code File:
    1. Switch code file in local                        //选择本地编码字典文件
    2. Design code from char-weight file                //用 字符-权重 文件进行哈夫曼树的搭建
    3. Enter temporary code file into Terminal          //从命令行中输入临时的 字符-编码
    4. Build code file from origin file                 //利用原文件中的字符数频作为权重生成哈夫曼树
```

然后使用功能

```
    A. Switch origin file to coding/decoding            //选择原文件
```

锁定要编码的文件位置

然后选择编码

```
    B. Coding origin file with existed huffman code     //编码
```

生成的编码文件会保存在output文件夹下

如有需要则需额外

```
    c. Save huffman code in local                       //保存哈夫曼编码字典
    d. Save huffman tree in local                       //保存哈夫曼树
```

来保存编码字典或者哈夫曼树

### 对编码文件进行解码
先生成与编码文件对应的编码字典

然后使用功能

```
    A. Switch origin file to coding/decoding            //选择原文件
```

锁定要编码的文件位置

然后选择译码

```
    C. Decoding origin file with existed huffman code   //译码
```

译码文件会保存在output文件夹下