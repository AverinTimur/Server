# Project
It's server is practice of linux C++ programming in interesting project.

It's most important ideas is ease of understanding, modularity and self-writing.

# Structure
## Files
This folder contains some static files. For example it's html, http templates, images and others. 
* RESPONSE.txt is server's http response


## server.cpp
This file is project's core with server's function

# Start
## C++
Compile server.cpp. For example if you use g++ use in folder of server.cpp:
```c++
g++ server.cpp -o server
```
After that you can use run this program in same folder:
```
./server
```

## CMake


```cmake
cmake_minimum_required(VERSION 3.24.2)
set (CMAKE_CXX_STANDARD 23)
project(server)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

add_executable(server server.cpp)
add_custom_target(files
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_BINARY_DIR}/Files/ ${CMAKE_BINARY_DIR}/build/Files/
)
add_dependencies(server files)
```