# Markdown table of content generator

<!--MARKDOWN_INDEX_BEGIN-->
# Table of content

**[Markdown table of content generator](#markdown-table-of-content-generator)**<br/>
&emsp;*[Get started](#get-started)*<br/>
&emsp;*[How to ?](#how-to-)*<br/>
&emsp;&emsp;[Get started](#get-started-1)<br/>
&emsp;&emsp;&emsp;[Test   !](#test---)<br/>
&emsp;&emsp;&emsp;[TEST 2   ](#test-2)<br/>
<!--MARKDOWN_INDEX_END-->

<br/><br/>
## Get started

Cloning the repo and compiling the program

Note that a compiler supporting C++20 is mandatory
```bash
git clone --recurse-submodules https://github.com/mathieu0c/MarkdownTable.git && cd MarkdownTable
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

#### Test   !

#### TEST 2   
