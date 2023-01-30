# Implementation of #2227 pretest for LFX-Mentorship with WasmEdge

## Introduction

This repository contains a standalone tool that uses wasmedge C sdk to execute a given wasm application.

The implementation is done with object oriented programming so any new wasm application can be added elegantly without much hassle to change existing source code.

This tool (named shell) handles all sorts of arguments user can pass, so access to wasmedge C api calls are made after analyzing command written by user and indicating errors if any rule is violated.

Currently this tool supports add.wasm, fibonacci.wasm, factorial.wasm applications.

More support for different wasm application can be added on top of it.


## Building shell tool

Clone this repository and run **make** command on source code directory.

This will create executable named shell and available command info will be displayed in terminal.

<img width="568" alt="Screenshot 2023-01-31 at 1 33 40 AM" src="https://user-images.githubusercontent.com/90818578/215585544-b908aaff-d3f3-4267-97b9-a947f7e23384.png">


## Test examples

### version Tests

#### commands
```
./shell version
./shell version run 
./shell version a b 
./shell version a b c
```

#### output

<img width="570" alt="Screenshot 2023-01-31 at 1 57 00 AM" src="https://user-images.githubusercontent.com/90818578/215587656-38122348-acaa-4f5e-bd5d-be69abf3b235.png">

### add.wasm Tests

#### commands
```
./shell run add.wasm 5 7
./shell run add.wasm 5
./shell run add.wasm 5 7 3
./shell run add.wasm a 7
./shell run add.wasm a b
./shell add.wasm 5 7
./shell add.wasm 5
./shell add.wasm 5 7 3
./shell add.wasm a 7
./shell add.wasm a b

```

#### output

<img width="569" alt="Screenshot 2023-01-31 at 2 01 57 AM" src="https://user-images.githubusercontent.com/90818578/215588705-54d9d243-a361-40b2-8f97-0fd3b67062ec.png">

### fibonacci Tests

Similar tests like add.wasm could be run for fibonacci.wasm application

#### command
```
./shell fibonacci.wasm 32
./shell /Users/raghavsharma/lfx_pretest/fibonacci.wasm 32

```

#### output 

<img width="572" alt="Screenshot 2023-01-31 at 2 09 59 AM" src="https://user-images.githubusercontent.com/90818578/215590247-87d9d94b-5c42-4cbb-b8d7-6af648e4581a.png">

### More Tests

If you want to test this tool more just build and compile this tool and test it using any available wasm application.

## Implementation details

The tool is implemented in two parts :

* shell.cpp

* WasmApp.cpp

### shell.cpp

As the name suggests this file contains implementation for shell tools, it interacts with wasm applications and works as a driving function for entire tool.

First it handles all **version** edge cases in commands and then add support for optional **run** argument.

After testing for above arguments it passes command to **WasmApp abstract class** which handles all wasm applications.

### WasmApp.h

This header file contains all class declarations for shell tool.

**WasmApp** is an abstract class which is instance of any wasm application class at runtime. It contains a static function **Create** which returns instance of wasm application class as per arguments passed by user.

Classes like **Add**, **fibonaci** etc... are derived from **WasmApp** class which then implements **Run()** function which answers user query.

Lets suppose command entered by user is `./shell add.wasm 5 7` **Create** function will return instance of **Add** class and then **Run** method of **Add** class will be used.

### WasmApp.cpp

This file contains all method implementations of functions defined in WasmApp.h header file

### Adding new wasm application

Suppose we need to add new wasm application support for our tool.

With the way shell tool is implemented we can just create a new derived class for new application and implement its **Run** method, after that we will be ready to use that wasm application.
