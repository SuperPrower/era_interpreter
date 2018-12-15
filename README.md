# Machine Code Interpreter for ERRIC (prev. ERA) architecture

## Running
`./era [--filename filename] [--memory_size words] [--help]`

Read more about options at `./era --help`

Program will load a file, provided or default, and attempt to execute the code. Regardless of the result, machine information, registers and memory will be dumped to `memdump` file.

Test files available in `test_binaries` directory.

## Building

### Dependencies
Project uses CMake building system, and, if needed CMocka testing framework and LCOV utility. Please refer to your distribution documentation to find out how to install them.

### Building process
In the directory with `CMakeLists.txt` file, run following command:

```
cmake -H. -Bbuild
```

You can add following options to this command:
- `-DCMAKE_BUILD_TYPE=Debug` - will enable debug symbols and tests
- `-DCoverage` - will enable coverage report with LCOV. Note that this requires LCOV installed and supported compiler (i.e. GCC, Clang, or AppleClang)
- `-DCMAKE_EXPORT_COMPILE_COMMANDS=ON` - will generate `compile_commands.json` (This is standard CMake practice. It may be useful to anyone who uses cquery language server or vim autocomplete plugin from wide variety of choices)

Finally, build binaries:
```
cmake --build build
```

Under Windows, you will still need to move the dll into executable's path if you want to use the library in some other project.

### Tests
If you have enabled tests (as described above), you can run set of tests by changing directory to `build` and running `ctest`. You can add `-V` flag for verbose output.
Under Windows, you will also need to move the `libera_interpreter.dll` to the binary directory.
