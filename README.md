# INVENTORY SYSTEM
This is the game's inventory system module.

## Characteristics:
- written in C++,
- is tested using unit tests and static analysis,
- written as universally as possible,
- module doesn't support a specific graphical interface, but has an interface for it.

## Feature
- flexible inventory size,
- selecting an item in the toolbar,
- multi toolbar,
- additional fields (armor, accessories, ...),
- optional arrangement of items.

## Technologies
- CMake
- C++20
- cppcheck
- clang-tidy
- clang-format
- valgrind
- docker
- GitHub Actions
- pre-commit

## Development
#### 1. Run cmake
- For Unix
```
cmake -S <PROJECT DIR> -B <BUILD DIR> ...
```
- For Windows
```
cmake -S <PROJECT DIR> -B <BUILD DIR> ...
```
Example:
```
cmake -S . -B build -G Ninja
```
Or
```
mkdir build
cd build
cmake ..
```
#### 2. Build
```
cmake --build <PROJECT DIR>
```
For ninja:
```
ninja -C <BUILD DIR>
```
Examples:
```
cmake --build build
ninja -C build
```
#### 3. Unit tests
````
ctest --test-dir <BUILD DIR>
````
For ninja:
```
ninja -C <BUILD DIR> test
```

### Code analysis
#### CMake targets
CMake provided following targets for code analysis:
- `clang-format-check` - check formating without chagned code
- `clang-format-fix` - formating code
- `cppcheck-check` - run cppcheck
- `clang-tidy-check` - run clang-tidy without chagned code
- `clang-tidy-fix` - run clang-tidy and fix code

Run cmake target:
```
cmake --build <BUILD DIR> --target <TARGET NAME>
```
For ninja
```
ninja -C build <TARGET NAME>
```

#### clang-format
CMake targets:
- clang-format-check
- clang-format-fix

#### cppcheck
CMake targets:
- cppcheck-check

#### clang-tidy
CMake targets:
- clang-tidy-check
- clang-tidy-fix

#### valgrind
```
valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         ./<BUILD DIR>/CarDashboardApp
```

### Docker
#### Build
```
docker build -t inventory-system .
```
#### Run
```
docker run -it --rm -v "$PWD":/home/project -w /home/project inventory-system
```

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE.txt) file for details
