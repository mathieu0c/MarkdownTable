# Markdown table of content generator

<!--MARKDOWN_INDEX_BEGIN--># Table of content

**[Markdown table of content generator](#markdown-table-of-content-generator)**<br/>
 .. *[Get started](#get-started)*<br/>
 .. *[How to ?](#how-to-)*<br/>
 ..  .. [Get started](#get-started-1)<br/>
**[Creating installation package](#creating-installation-package)**<br/>
**[Compiling for windows under linux](#compiling-for-windows-under-linux)**<br/>
<!--MARKDOWN_INDEX_END-->

<br/><br/>
## Get started

Cloning the repo and compiling the program

Note that a compiler supporting C++20 is mandatory


If the lib [LittleArgsParser](https://github.com/mathieu0c/LittleArgsParser) is not installed on your system (most probable case) you will need to install it first.


Then
```bash
git clone https://github.com/mathieu0c/MarkdownTable.git && cd MarkdownTable
mkdir release && cd release
cmake --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=Release ..
make
```

Installing the program
```bash
sudo make install
```

Display help
```bash
MarkdownTable -h
```

## How to ?

### Get started

Just add the following tags where you want to insert the TOC

```
<!--MARKDOWN_INDEX_BEGIN-->
<!--MARKDOWN_INDEX_END-->
```

And you will be good to go

<br/><br/><br/><br/><br/><br/>

# Creating installation package

1. Build the project
1. Run cpack :
    ```
    cpack -G DEB
    ```

# Compiling for windows under linux

>***Note :*** MinGw for linux toolchain has to be installed

```
mkdir build_win64 && cd build_win64
cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/Toolchain_win64.cmake ..
make
```