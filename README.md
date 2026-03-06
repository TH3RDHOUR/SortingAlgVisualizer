I am using CMake to import & use different libraries for this project.

When you switch computers it is probably a good idea to clean the build file by deleting it:
**rm -rf build**

Each time you make a change please use the following commands to run the program:

### To Configure the project:

**cmake -S . -B build**

### To Build the project:

**cmake --build build**

### To Run in Windows:

**.\build\Debug\SortingAlgVisualizer.exe**

### To run in MacOS or Linux:

**./build/SortingAlgVisualizer**
