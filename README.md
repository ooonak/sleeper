# Kind of a template for new projects, and an application

## Sleeper
Linux client that waits for multicast messages written in C++.

## Build and test

### Build
```bash
$ mkdir build && cd build
$ cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER=clang++ \
    -DCMAKE_INSTALL_PREFIX=$HOME/usr/local ..
$ cmake --build .
$ ctest
$ cmake --install .
```

### Valgrind memcheck
```bash
$ mkdir build && cd build
$ cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug ..
$ cmake --build .
$ ctest -T memcheck
```

### Coverage
```bash
$ mkdir build && cd build
$ cmake -G Ninja -DCMAKE_BUILD_TYPE=Coverage ..
$ cmake --build .
$ ctest -T coverage
```

### Sanitizers
```bash
$ export ASAN_SYMBOLIZER_PATH=`which llvm-symbolizer`
$ export UBSAN_OPTIONS=print_stacktrace=1
$ mkdir build && cd build
$ cmake -G Ninja -DCMAKE_BUILD_TYPE=<Asan, Tsan, Memsan, Ubsan> -DCMAKE_CXX_COMPILER=clang++ ..
$ cmake --build .
$ ctest
$ app/sleeperapp
```

## TODO
* Place all dependency stuff in seperat CMake file.
  + Add option to only use FetchContent if package is not already installed.
* Ctest setup that runs and test all types of builds in one.
  + Play with cdash to upload test results.
* Dockerfile(s)
  + Container that builds and tests everything with distro X version Y.
    - Exactly what dev tools are needed.
  + Container that is identical, without all dev tools and libraries, bare minimum to run the build binary.
* Conan.
+ Write configuration files for Jenkins, Travis, ...
