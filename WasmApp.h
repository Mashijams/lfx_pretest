/*
	Copyright 2022, Raghav Sharma, raghavself28@gmail.com
	Distributed under the terms of the MIT License.

	This file is implementation for pretest 2227
	https://github.com/WasmEdge/WasmEdge/discussions/2227
*/


#ifndef WASM_APP_H
#define WASM_APP_H


#include <wasmedge/wasmedge.h>
#include <iostream>
#include <string>
#include <map>


// an enum for success or failure of methods in shell
enum status_t {
	APP_SUCCESS,
	APP_FAIL,
};


// This enum will store supported apps
enum Apps {
	ADD,
	fIBONACI,
	FACTORIAL,
	UNKNOWN,
};


void
_setup_app_hash_map();


// An abstract class which will refer to instance of any supported wasm application
class WasmApp {
public:
		virtual				~WasmApp()					=	0;
		virtual	status_t	Run(int argc, char* argv[])	=	0;
		static	WasmApp*	Create(char* argv);
};


// Add wasm application class
class Add : public WasmApp {
public:
							Add();
							~Add();
		status_t			Run(int argc, char* argv[]);
};


// fibonaci wasm application class
class Fibonaci : public WasmApp {
public:
							Fibonaci();
							~Fibonaci();
		status_t			Run(int argc, char* argv[]);
};


// factorial wasm application class
class Factorial : public WasmApp {
public:
							Factorial();
							~Factorial();
		status_t			Run(int argc, char* argv[]);
};

#endif