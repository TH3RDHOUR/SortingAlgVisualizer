I am using CMake to import & use different libraries for this project.

When you switch computers it is probably a good idea to clean the build file by deleting it:

```
rm -rf build
```

Each time you make a change please use the following commands from the source directory to run the program:

# Sorting Algorithm Visualizer

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
