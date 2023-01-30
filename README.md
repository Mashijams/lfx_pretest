# Implementation of #2227 pretest for LFX-Mentorship with WasmEdge

## Introduction

This repository contains a standalone tool that uses wasmedge C sdk to execute a given wasm application.

The implementation is done with object oriented programming so any new wasm application can be added elegantly without much hassle to change existing source code.

This tool (named shell) handles all sorts of arguments user can pass, so access wasmedge C api calls are made after analyzing command written by user and indicating errors if any rule is violated.

Currently this tool supports add.wasm, fibonacci.wasm, factorial.wasm applications.

More support for different wasm application can be added on top of it.


## Building shell tool

Clone this repository and run **make** command on source code directory.

This will create executable named shell and available command info will be displayed in terminal.

<img width="568" alt="Screenshot 2023-01-31 at 1 33 40 AM" src="https://user-images.githubusercontent.com/90818578/215585544-b908aaff-d3f3-4267-97b9-a947f7e23384.png">
