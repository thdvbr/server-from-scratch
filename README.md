# Server from scratch in C++

## Setup

Install cmake to build the project.

```
brew install cmake
```

Install googletest in the root.

```
git clone https://github.com/google/googletest/
```

## Run

To build, run:

```
mkdir build
cd build
cmake ..
cmake --build .
```

To run server, in the build directory run

```
cd src/server
./server
```

To run client, in the build directory run

```
cd src/client
./client
```

To test echo server, run in a different terminal

```
telnet localhost 54000
```
