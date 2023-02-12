shell: shell.o WasmApp.o
	g++ shell.o WasmApp.o -o shell -lwasmedge
	$(info Successfully compiled tool)
	$(info To use it run : ./shell [version] [run] [wasm path] [arguments])

shell.o: src/WasmApp.h src/shell.cpp
	g++ -c src/shell.cpp

WasmApp.o: src/WasmApp.h src/WasmApp.cpp
	g++ -c src/WasmApp.cpp

clean:
	rm *.o shell