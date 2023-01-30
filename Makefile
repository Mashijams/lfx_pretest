shell: shell.o wasmapp.o
	g++ shell.o wasmapp.o -o shell
	$(info Successfully compiled tool)
	$(info To use it run : ./shell [version] [run] [wasm path] [arguments])

shell.o: WasmApp.h
	g++ -c shell.cpp -lwasmedge

wasmapp.o: WasmApp.h
	g++ -c WasmApp.cpp -lwasmedge

clean:
	rm *.o shell