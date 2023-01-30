shell: shell.o wasmapp.o
	g++ shell.o wasmapp.o -o shell -lwasmedge
	$(info Successfully compiled tool)
	$(info To use it run : ./shell [version] [run] [wasm path] [arguments])

shell.o: WasmApp.h
	g++ -c shell.cpp

wasmapp.o: WasmApp.h
	g++ -c WasmApp.cpp

clean:
	rm *.o shell