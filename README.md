# Sorting Algorithm Visualizer

This project utilizes C++ with the libraries [SFML](https://www.sfml-dev.org/) and [ImGui](https://github.com/ocornut/imgui) to visualize the following sorting algorithms:

- [Bubble Sort](https://www.geeksforgeeks.org/cpp/bubble-sort-in-cpp/)
- [Insertion Sort](https://www.geeksforgeeks.org/dsa/insertion-sort-algorithm/)
- [Selection Sort](https://www.geeksforgeeks.org/dsa/selection-sort-algorithm-2/)
- [Merge Sort](https://www.geeksforgeeks.org/dsa/merge-sort/)
- [Quick Sort](https://www.geeksforgeeks.org/cpp/cpp-program-for-quicksort/)

I am using CMake to import & use different libraries for this project.

When/if you switch computers it can be a good idea sometimes to clean the build file by deleting it then rebuilding it:

```
rm -rf build
```

Each time you make a change please use the following commands from the source directory to run the program:

## To Configure the project:

```
cmake -S . -B build
```

_-S (source directory) and -B (binary directory) make for a cleaner workflow_

## To Build the project:

```
cmake --build build
```

## To Run in Windows:

```
.\build\Debug\SortingAlgVisualizer.exe
```

## To run in MacOS or Linux:

```
./build/SortingAlgVisualizer
```
