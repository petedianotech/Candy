# Building Fruit Burst

This guide provides comprehensive instructions for building the Fruit Burst game on various platforms.

## Quick Start

### Linux/Ubuntu/WSL2

```bash
cd /workspaces/Candy
mkdir build
cd build
cmake ..
cmake --build . --config Release -j4
./FruitBurst
```

### macOS

```bash
# Install dependencies (if using Homebrew)
brew install cmake

cd /workspaces/Candy
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . -j4
./FruitBurst
```

### Windows (Visual Studio)

```bash
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022"
cmake --build . --config Release
Release\FruitBurst.exe
```

### Windows (MinGW)

```bash
mkdir build
cd build
cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build . -j4
FruitBurst.exe
```

## Dependencies

### Required
- CMake 3.22 or later
- C++17 compatible compiler

### Graphics (Optional - for full visual support)
- **Raylib 4.5+** (Primary graphics library)
- **SDL2** (Alternative graphics library)

### Build Tools
- GCC/G++ (Linux, MinGW)
- Clang/LLVM (macOS, Linux)
- MSVC (Visual Studio - Windows)

## Detailed Build Instructions

### Installing Dependencies

#### Ubuntu/Debian
```bash
# Build tools
sudo apt-get install -y cmake build-essential

# For Raylib support (optional, requires several packages - see note)
sudo apt-get install -y libx11-dev libxrandr-dev libxinerama-dev \
    libxi-dev libxext-dev libxcursor-dev
```

#### Fedora/RHEL
```bash
sudo yum install -y cmake gcc g++
```

#### macOS
```bash
# Install Homebrew if not already installed
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Install dependencies
brew install cmake
```

#### Windows
- Download CMake from https://cmake.org/download/
- Download and install a compiler:
  - Visual Studio Community (includes MSVC)
  - MinGW-w64
  - Or use the pre-built Raylib Windows binaries

### Build Configurations

#### Release Build (Optimized)
```bash
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release -j$(nproc)
```

#### Debug Build (For debugging)
```bash
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
cmake --build . -j$(nproc)
./FruitBurst
```

#### Build Variants

**Headless Mode** (No graphics, game logic only):
```bash
cmake ..
cmake --build .
```

**With Raylib Graphics**:
First ensure Raylib is installed on your system, then:
```bash
cmake ..
cmake --build .
```

## Build System Explained

### CMakeLists.txt
Our build system uses CMake for cross-platform compilation. Key features:

```cmake
# Attempts to find graphics libraries in order:
# 1. System-installed Raylib (via CONFIG)
# 2. System-installed SDL2 (via CONFIG)
# 3. Headless mode (no graphics)

# This allows maximum flexibility:
# - Works on restricted environments
# - Can use system libraries if available
# - Falls back gracefully if graphics unavailable
```

### Build Outputs
- `-DUSE_RAYLIB=1` - Compiled with Raylib
- `-DUSE_SDL2=1` - Compiled with SDL2
- `-DHEADLESS_MODE=1` - Core game logic only (no graphics)

## Troubleshooting

### "raylib not found"
The game will automatically build in headless  mode. To enable graphics:

**Option 1: Install Raylib**
```bash
# Clone Raylib
git clone https://github.com/raysan5/raylib.git
cd raylib/src
make
sudo make install
```

**Option 2: Install SDL2**
```bash
# Ubuntu
sudo apt-get install libsdl2-dev

# macOS
brew install sdl2

# Windows - Download from https://www.libsdl.org/
```

### CMake cache issues
```bash
# Clean cmake cache
rm -rf build
mkdir build
cd build
cmake ..
```

### Compilation errors with GCC
Ensure you have C++17 support:
```bash
g++ --version  # Should be 7.0 or later
cmake .. -DCMAKE_CXX_COMPILER=g++-11  # Explicitly specify compiler
```

### "Permission denied" during build
```bash
# Fix permissions
chmod +x FruitBurst

# Or rebuild
make clean
make
```

## Performance Tips

### Speed up builds
```bash
# Use multiple cores
cmake --build . -j$(nproc)  # Linux/macOS
cmake --build . -j8         # Windows with 8 cores
```

### Optimize binary size
```bash
cmake .. -DCMAKE_BUILD_TYPE=Release
strip FruitBurst  # Reduce executable size
```

### Enable Link Time Optimization (LTO)
```bash
cmake .. -DCMAKE_INTERPROCEDURAL_OPTIMIZATION=ON
```

## Cross-Compilation

### Building for Linux from macOS/Windows
```bash
cmake .. -DCMAKE_SYSTEM_NAME=Linux \
    -DCMAKE_SYSTEM_PROCESSOR=x86_64 \
    -DCMAKE_C_COMPILER=x86_64-linux-gnu-gcc \
    -DCMAKE_CXX_COMPILER=x86_64-linux-gnu-g++
```

### Building for Windows from Linux (MinGW)
```bash
cmake .. -DCMAKE_SYSTEM_NAME=Windows \
    -DCMAKE_C_COMPILER=x86_64-w64-mingw32-gcc \
    -DCMAKE_CXX_COMPILER=x86_64-w64-mingw32-g++
```

## Installation

### Install to system
```bash
cd build
sudo cmake --install . --prefix /usr/local
# Now run with: FruitBurst
```

### Create package
```bash
cpack  # Creates DEB/RPM/ZIP depending on system
```

## Version Information

### Required Versions
- CMake: 3.22+
- C++ Standard: 17
- Compiler: GCC 9+, Clang 10+, MSVC 2019+

### Tested Configurations
- Ubuntu 20.04, 22.04, 24.04
- macOS 12, 13, 14
- Windows 10, 11
- Fedora 38, 39
- Debian 11, 12

## Environment Variables

### Build Control
```bash
# Use specific compiler
CXX=g++-11 CC=gcc-11 cmake ..

# Add custom flags
CXXFLAGS="-O3 -march=native" cmake ..

# Parallel jobs
cmake --build . -j $JOBS
```

## Docker Build

```dockerfile
FROM ubuntu:24.04
RUN apt-get update && apt-get install -y cmake build-essential git
WORKDIR /app
COPY . .
RUN mkdir build && cd build && cmake .. && cmake --build .
CMD ["./FruitBurst"]
```

Build and run:
```bash
docker build -t fruit-burst .
docker run -it fruit-burst
```

## CI/CD Integration

### GitHub Actions
```yaml
name: Build
on: [push]
jobs:
  build:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v2
      - name: Build
        run: |
          mkdir build && cd build
          cmake .. && cmake --build .
```

## FAQs

**Q: Can I build without graphics?**
A: Yes! The game builds in headless mode by default if no graphics library is found.

**Q: How do I use a specific compiler?**
A: Set CXX and CC environment variables before running cmake.

**Q: What's the minimum disk space needed?**
A: About 50-100MB for the build directory with all dependencies.

**Q: Can I build on a Raspberry Pi?**
A: Yes, ARM compilation is supported. See cross-compilation section.

**Q: How do I enable hardware acceleration?**
A: Raylib automatically uses GPU acceleration if available.

## Support

For build issues:
1. Check compiler version: `g++ --version`
2. Verify CMake: `cmake --version`
3. Check system libraries:  `pkg-config --list-all | grep -E "(raylib|SDL2)"`
4. Review build log: `cmake --build . --verbose`

## License
Build system is part of the Fruit Burst project.
