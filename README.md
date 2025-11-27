# Polybank_ATM

PolyBank_ATM is a part of modern full-stack project PolyBank combining a **React + Vite** frontend with a **C++ backend** powered by [Crow](https://github.com/CrowCpp/Crow), [CPR](https://github.com/libcpr/cpr), [nlohmann json](https://github.com/nlohmann/json) and [Catch2](https://github.com/catchorg/Catch2) for testing using **CMake**.  
<!-- The backend is built using **Meson** and **Ninja**, with **Asio** for networking support. -->

## Instalation

Use git to install PolyBank_ATM.

```git
git clone https://github.com/VSidd976/Polybank_ATM.git
```

### Backend Dependencies

- **C++17 or later** compiler (e.g. GCC, Clang or MSVC)
- **CMake**
- **Meson**
- **Ninja**
- **Asio**

#### macOs instalation

```bash
brew install cmake meson asio
```

#### Linux (Ubuntu/Debian) instalation

```bash
sudo apt install build-essential cmake meson asio
```

#### Windows instalation

```cmd
winget install Microsoft.VisualStudio.2022.Community

winget install Kitware.CMake MesonBuild.Meson

git clone https://github.com/microsoft/vcpkg
.\vcpkg\bootstrap-vcpkg.bat

.\vcpkg\vcpkg integrate install

.\vcpkg\vcpkg install asio
```

### Frontend dependencies instalation

To install frontend dependencies open terminal in root directory and execute following comamnds.

```bash
cd ui
npm install
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

To execute this project execute following commands using terminal in root directory.

```bash
mkdir build
cd build
cmake --build
cmake ..
```
