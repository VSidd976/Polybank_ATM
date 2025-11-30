# Polybank_ATM

PolyBank_ATM is a part of modern full-stack project PolyBank combining a **React + Vite** frontend with a **C++ backend** powered by [Crow](https://github.com/CrowCpp/Crow), [CPR](https://github.com/libcpr/cpr), [nlohmann json](https://github.com/nlohmann/json) and [Catch2](https://github.com/catchorg/Catch2) for testing using **CMake**.  

## Instalation

Use git to install PolyBank_ATM.

```git
git clone https://github.com/VSidd976/Polybank_ATM.git
```

### Dependencies

- **C++17 or later** compiler (e.g. GCC, Clang or MSVC)
- **CMake**
- **Meson**
- **Ninja**
- **Asio**
- **Node.js**

#### macOs instalation

```bash
brew install cmake meson asio node
```

#### Linux (Ubuntu/Debian) instalation

```bash
sudo apt install build-essential cmake meson asio node
```

#### Windows instalation

```cmd
winget install Microsoft.VisualStudio.2022.Community

winget install Kitware.CMake MesonBuild.Meson OpenJS.NodeJS

git clone https://github.com/microsoft/vcpkg
.\vcpkg\bootstrap-vcpkg.bat

.\vcpkg\vcpkg integrate install

.\vcpkg\vcpkg install asio
```

## Preparation

Before you run this project, create **env.json** file in root directory and enter your server address.

```json
{
    "SERVER_ADDRESS": "<your_address>"
}
```

### Important note

In order to use this project you need to deploy [PolyBank_Bank](https://github.com/VSidd976/Polybank_Bank) localy or on linux server.

## Executing

### Backend

Execute first commands to build project and second to run it.

#### Unix

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

```bash
cd app
./Executable
```

#### Windows

```cmd
cmake -S . -B build -G "Visual Studio 17 2022" -DCMAKE_TOOLCHAIN_FILE="C:/Users/admin/vcpkg/scripts/buildsystems/vcpkg.cmake"
```

```cmd
cd build/Debug/Executable.exe
```

### Frontend

To run frontend open new terminal in root directory and execute following commands.

```bash
cd ui
npm install
npm run dev
```

Ctrl/command + left click on the local address to open ui in browser.
