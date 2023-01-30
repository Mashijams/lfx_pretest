/*
	Copyright 2022, Raghav Sharma, raghavself28@gmail.com
	Distributed under the terms of the MIT License.

	This file is implementation for pretest 2227
	https://github.com/WasmEdge/WasmEdge/discussions/2227
*/


#include <wasmedge/wasmedge.h>
#include <iostream>
#include <string>
#include "WasmApp.h"


#define	StringEquals(a, b)	(strcmp((a), (b)) == 0)


void _ArgumentFormat() {
	printf("./shell [version] [run] [wasm path] [arguments]\n");
	printf("Supported wasm applications are : add.wasm | factorial.wasm
		| fibonaci.wasm | hello.wasm\n");
}


// driving function
int main (int argc, char* argv[]) {

	// if there are no arguments return failure
	if (argc == 0) {
		fprintf(stderr, "No arguments are provided\n");
		_ArgumentFormat();
    	return EXIT_FAILURE;
	}

	// if there is only one argument that must be "version"
	// else return failure
	if (argc == 2) {
		if (StringEquals(argv[1], "version") || StringEquals(argv[1], "Version")) {
			printf("WasmEdge version: %s\n", WasmEdge_VersionGet());
			return EXIT_SUCCESS;
		} else {
			fprintf(stderr, "Invalid argument");
			_ArgumentFormat();
			return EXIT_FAILURE;
		}
	}

	// if first argument is "version" then we can ignore other arguments
	if (StringEquals(argv[1], "version") || StringEquals(argv[1], "Version")) {
		printf("WasmEdge version: %s\n", WasmEdge_VersionGet());
		return EXIT_SUCCESS;
	}

	// index in arguments where wasmapp path exits
	uint8_t index = 1;

	// if first argument is "run" index for wasm app path is increased by one
	if (StringEquals(argv[1], "run")) {
		index++;
	}

	// Create a WasmApp instance which could be any supported Wasm Application
	WasmApp* app = WasmApp::Create(argv[index]);

	// Something wrong happend instance is not created
	if (app == NULL) {
		fprintf(stderr, "Invalid or Unsupported Wasm Application");
		_ArgumentFormat();
		return EXIT_FAILURE;
	}

	status_t status = app->Run(argc - index, &argv[index]);

	delete app;

	if (status != APP_SUCCESS) {
		fprintf(stderr, "Invalid arguments");
		_ArgumentFormat();
		return EXIT_FAILURE;
	}

	// Everything has gone fine return Success
	return EXIT_SUCCESS;
}