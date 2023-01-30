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
	app_hash["fibonaci"]    =   fIBONACI;
	app_hash["factorial"]   =   FACTORIAL;
}


WasmApp::~WasmApp()
{
}


WasmApp*
WasmApp::Create(char* argv)
{
	uint32_t len = sizeof(argv);
	std::string str = ""; // empty string
	int i;

	// check if file ends with .wasm
	for (i = len - 1; i >= len - 5; i--) {
		str += argv[i];
	}
	reverse(str.begin(), str.end());
	if (str != ".wasm")
		return NULL;

	str.clear();

	// find matching wasm app
	while (i >=0 && argv[i] != '/') {
    	str += argv[i];
    	i--;
	}
	reverse(str.begin(), str.end());

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
}


Add::~Add()
{
}


status_t
Add::Run(int argc, char* argv[])
{
	if (argc < 3 || argc > 3) {
		fprintf(stderr, "Invalid add application arguments\n");
		fprintf(stderr, "Example command : ./shell run add.wasm 5 7");
		return APP_FAIL;
	}

	// Extract the arguements.
	char app_path[strlen(argv[0])];
	strcpy(app_path, argv[0]);
	int param1 = atoi(argv[1]);
	int param2 = atoi(argv[2]);

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
	WasmEdge_Result Res = WasmEdge_VMRunWasmFromFile(VMCxt, app_path, FuncName, Params, 2, Returns, 1);

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
}


Factorial::~Factorial()
{
}


status_t
Factorial::Run(int argc, char* argv[])
{
	if (argc < 2 || argc > 2) {
		fprintf(stderr, "Invalid factorial application arguments\n");
		fprintf(stderr, "Example command : ./shell run factorial.wasm 5");
		return APP_FAIL;
	}

	// Extract the arguements.
	char app_path[strlen(argv[0])];
	strcpy(app_path, argv[0]);
	int param1 = atoi(argv[1]);

	// Create the configure context and add the WASI support.
	// This step is not necessary unless you need WASI support.
	WasmEdge_ConfigureContext *ConfCxt = WasmEdge_ConfigureCreate();
	WasmEdge_ConfigureAddHostRegistration(ConfCxt, WasmEdge_HostRegistration_Wasi);

	// The configure and store context to the VM creation can be NULL.
	WasmEdge_VMContext *VMCxt = WasmEdge_VMCreate(ConfCxt, NULL);

	WasmEdge_Value Params[1] = { WasmEdge_ValueGenI32(param1) };
	WasmEdge_Value Returns[1];
	// Function name.
	WasmEdge_String FuncName = WasmEdge_StringCreateByCString("factorial");
	// Run the WASM function from file.
	WasmEdge_Result Res = WasmEdge_VMRunWasmFromFile(VMCxt, app_path, FuncName, Params, 1, Returns, 1);

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
}


Fibonaci::~Fibonaci()
{
}


status_t
Fibonaci::Run(int argc, char* argv[])
{
	if (argc < 2 || argc > 2) {
		fprintf(stderr, "Invalid fibonaci application arguments\n");
		fprintf(stderr, "Example command : ./shell run fibonaci.wasm 5");
		return APP_FAIL;
	}

	// Extract the arguements.
	char app_path[strlen(argv[0])];
	strcpy(app_path, argv[0]);
	int param1 = atoi(argv[1]);

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
	WasmEdge_Result Res = WasmEdge_VMRunWasmFromFile(VMCxt, app_path, FuncName, Params, 1, Returns, 1);

	if (WasmEdge_ResultOK(Res)) {
		printf("%dth fiboncai number is: %d\n", param1, WasmEdge_ValueGetI32(Returns[0]));
    } else {
		fprintf(stderr, "Error message: %s\n", WasmEdge_ResultGetMessage(Res));
	}

	// Resources deallocations.
	WasmEdge_VMDelete(VMCxt);
	WasmEdge_ConfigureDelete(ConfCxt);
	WasmEdge_StringDelete(FuncName);

	return APP_SUCCESS;
}