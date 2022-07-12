# sleeper
Linux client that waits for multicast messages.

## Build
```bash
$ mkdir build && cd build
$ cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_INSTALL_PREFIX=$HOME/usr/local ..
$ cmake --build .
$ ctest
$ cmake --install .
```

