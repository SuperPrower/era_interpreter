## Building

In the directory with `CMakeLists.txt` file, run following commands:

```
cmake -H. -Bbuild
cmake --build build
```

(Note to S): Adding `-DCMAKE_EXPORT_COMPILE_COMMANDS=ON` to the first command will generate `compile_commands.json`

### Tests
To build tests, you will need to set `CMAKE_BUILD_TYPE` to `Debug`:
```
cmake -H. -Bbuild -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

Currently, tests build as separate binary. To run them, execute `runUnitTests`, located in `./bin/runUnitTests`
