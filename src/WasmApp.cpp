/*
	Copyright 2022, Raghav Sharma, raghavself28@gmail.com
	Distributed under the terms of the MIT License.

	This file is implementation for pretest 2227
	https://github.com/WasmEdge/WasmEdge/discussions/2227
*/


#include "WasmApp.h"


// Map for storing shell app hash
std::map<std::string, Apps> app_hash;


void
_setup_app_hash_map()
{
	app_hash["add"]         =   ADD;
	app_hash["fibonacci"]   =   fIBONACI;
	app_hash["factorial"]   =   FACTORIAL;
}


bool
_numeric_check(char* s)
{
	int len = strlen(s);
	for (int i = 0; i < len; i++) {
		if (!isdigit(s[i]))
			return false;
	}
	return true;
}


WasmApp::~WasmApp()
{
}


WasmApp*
WasmApp::Create(char* argv)
{
	uint32_t len = strlen(argv);
	std::string str = ""; // empty string
	int i;

	// check if file ends with .wasm
	for (i = len - 1; i >= len - 5; i--) {
		str += argv[i];
	}
	std::reverse(str.begin(), str.end());
	if (str != ".wasm")
		return NULL;

	str.clear();

	// find matching wasm app
	while (i >=0 && argv[i] != '/') {
    	str += argv[i];
    	i--;
	}
	std::reverse(str.begin(), str.end());

	Apps c;

	if (app_hash.find(str) != app_hash.end())
		c = app_hash[str];
	else
		c = UNKNOWN;

	switch(c) {

		case ADD:
			return new Add();
			break;

		case FACTORIAL:
			return new Factorial();
			break;

		case fIBONACI:
			return new Fibonaci();
			break;

		case UNKNOWN:
			return NULL;
			break;

		default:
			break;
	}

	return NULL;
}


Add::Add()
{
	fParamlen	=	2;
	fReturnlen	=	1;
}


Add::~Add()
{
}


status_t
Add::Run(int argc, char* argv[])
{
	if (argc - 1 < fParamlen || argc - 1 > fParamlen) {
		fprintf(stderr, "Invalid add application arguments\n");
		fprintf(stderr, "Example command : ./shell run add.wasm 5 7\n");
		return APP_FAIL;
	}

	// Extract the arguements.
	char app_path[strlen(argv[0])];
	strcpy(app_path, argv[0]);

	// first check if argv[1] & argv[2] is numeric or not
	if (!_numeric_check(argv[1])) {
		fprintf(stderr, "Invalid add application arguments\n");
		fprintf(stderr, "Example command : ./shell run add.wasm 5 7\n");
		return APP_FAIL;
	}
	if (!_numeric_check(argv[2])) {
		fprintf(stderr, "Invalid add application arguments\n");
		fprintf(stderr, "Example command : ./shell run add.wasm 5 7\n");
		return APP_FAIL;
	}

	// we can now safely use stoi function
	int param1;
	int param2;

	try
	{
		std::string s = argv[1];
		param1 = stoi(s);
		s = argv[2];
		param2 = stoi(s);
	}
	catch (const std::out_of_range& oor) {
		fprintf(stderr, "Out of Range error: %s\n", oor.what());
		fprintf(stderr, "Arguments and return value greater than INT32 is not supported\n");
		return APP_FAIL;
  	}

	// Create the configure context and add the WASI support.
	// This step is not necessary unless you need WASI support.
	WasmEdge_ConfigureContext *ConfCxt = WasmEdge_ConfigureCreate();
	WasmEdge_ConfigureAddHostRegistration(ConfCxt, WasmEdge_HostRegistration_Wasi);

	// The configure and store context to the VM creation can be NULL.
	WasmEdge_VMContext *VMCxt = WasmEdge_VMCreate(ConfCxt, NULL);

	WasmEdge_Value Params[2] = { WasmEdge_ValueGenI32(param1), WasmEdge_ValueGenI32(param2) };
	WasmEdge_Value Returns[1];
	// Function name.
	WasmEdge_String FuncName = WasmEdge_StringCreateByCString("add");
	// Run the WASM function from file.
	WasmEdge_Result Res = WasmEdge_VMRunWasmFromFile(VMCxt, app_path, FuncName, Params,
		fParamlen, Returns, fReturnlen);

	if (WasmEdge_ResultOK(Res)) {
		printf("Addition of %d and %d is: %d\n", param1, param2, WasmEdge_ValueGetI32(Returns[0]));
    } else {
		fprintf(stderr, "Error message: %s\n", WasmEdge_ResultGetMessage(Res));
	}

	// Resources deallocations.
	WasmEdge_VMDelete(VMCxt);
	WasmEdge_ConfigureDelete(ConfCxt);
	WasmEdge_StringDelete(FuncName);

	return APP_SUCCESS;
}


Factorial::Factorial()
{
	fParamlen	=	1;
	fReturnlen	=	1;
}


Factorial::~Factorial()
{
}


status_t
Factorial::Run(int argc, char* argv[])
{
	if (argc - 1 < fParamlen || argc - 1 > fParamlen) {
		fprintf(stderr, "Invalid factorial application arguments\n");
		fprintf(stderr, "Example command : ./shell run factorial.wasm 5\n");
		return APP_FAIL;
	}

	// Extract the arguements.
	char app_path[strlen(argv[0])];
	strcpy(app_path, argv[0]);

	// first check if argv[1] is numeric or not
	if (!_numeric_check(argv[1])) {
		fprintf(stderr, "Invalid factorial application arguments\n");
		fprintf(stderr, "Example command : ./shell run factorial.wasm 5\n");
		return APP_FAIL;
	}
	int param1 = atoi(argv[1]);

	if (param1 > 12) {
		fprintf(stderr, "Arguments and return value greater than INT32 is not supported\n");
		return APP_FAIL;
	}

	// Create the configure context and add the WASI support.
	// This step is not necessary unless you need WASI support.
	WasmEdge_ConfigureContext *ConfCxt = WasmEdge_ConfigureCreate();
	WasmEdge_ConfigureAddHostRegistration(ConfCxt, WasmEdge_HostRegistration_Wasi);

	// The configure and store context to the VM creation can be NULL.
	WasmEdge_VMContext *VMCxt = WasmEdge_VMCreate(ConfCxt, NULL);

	WasmEdge_Value Params[1] = { WasmEdge_ValueGenI32(param1) };
	WasmEdge_Value Returns[1];
	// Function name.
	WasmEdge_String FuncName = WasmEdge_StringCreateByCString("fac");
	// Run the WASM function from file.
	WasmEdge_Result Res = WasmEdge_VMRunWasmFromFile(VMCxt, app_path, FuncName,
		Params, fParamlen, Returns, fReturnlen);

	if (WasmEdge_ResultOK(Res)) {
		printf("Factorial of %d is: %d\n", param1, WasmEdge_ValueGetI32(Returns[0]));
    } else {
		fprintf(stderr, "Error message: %s\n", WasmEdge_ResultGetMessage(Res));
	}

	// Resources deallocations.
	WasmEdge_VMDelete(VMCxt);
	WasmEdge_ConfigureDelete(ConfCxt);
	WasmEdge_StringDelete(FuncName);

	return APP_SUCCESS;
}


Fibonaci::Fibonaci()
{
	fParamlen	=	1;
	fReturnlen	=	1;
}


Fibonaci::~Fibonaci()
{
}


status_t
Fibonaci::Run(int argc, char* argv[])
{
	if (argc - 1 < fParamlen || argc - 1 > fParamlen) {
		fprintf(stderr, "Invalid fibonaci application arguments\n");
		fprintf(stderr, "Example command : ./shell run fibonacci.wasm 5\n");
		return APP_FAIL;
	}

	// Extract the arguements.
	char app_path[strlen(argv[0])];
	strcpy(app_path, argv[0]);

	// first check if argv[1] is numeric or not
	if (!_numeric_check(argv[1])) {
		fprintf(stderr, "Invalid fibonaci application arguments\n");
		fprintf(stderr, "Example command : ./shell run fibonacci.wasm 5\n");
		return APP_FAIL;
	}
	int param1 = atoi(argv[1]);

	if (param1 > 46) {
		fprintf(stderr, "Arguments and return value greater than INT32 is not supported\n");
		return APP_FAIL;
	}

	// Create the configure context and add the WASI support.
	// This step is not necessary unless you need WASI support.
	WasmEdge_ConfigureContext *ConfCxt = WasmEdge_ConfigureCreate();
	WasmEdge_ConfigureAddHostRegistration(ConfCxt, WasmEdge_HostRegistration_Wasi);

	// The configure and store context to the VM creation can be NULL.
	WasmEdge_VMContext *VMCxt = WasmEdge_VMCreate(ConfCxt, NULL);

	WasmEdge_Value Params[1] = { WasmEdge_ValueGenI32(param1) };
	WasmEdge_Value Returns[1];
	// Function name.
	WasmEdge_String FuncName = WasmEdge_StringCreateByCString("fib");
	// Run the WASM function from file.
	WasmEdge_Result Res = WasmEdge_VMRunWasmFromFile(VMCxt, app_path, FuncName,
		Params, fParamlen, Returns, fReturnlen);

	if (WasmEdge_ResultOK(Res)) {
		printf("%dth fibonacci number is: %d\n", param1, WasmEdge_ValueGetI32(Returns[0]));
    } else {
		fprintf(stderr, "Error message: %s\n", WasmEdge_ResultGetMessage(Res));
	}

	// Resources deallocations.
	WasmEdge_VMDelete(VMCxt);
	WasmEdge_ConfigureDelete(ConfCxt);
	WasmEdge_StringDelete(FuncName);

	return APP_SUCCESS;
}