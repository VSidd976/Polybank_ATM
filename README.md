# Polybank_ATM

# 🧩 React + Vite Frontend & C++ Backend (Crow, CPR, Catch2)

A modern full-stack project combining a **React + Vite** frontend with a **C++ backend** powered by [Crow](https://github.com/CrowCpp/Crow), [CPR](https://github.com/libcpr/cpr), and [Catch2](https://github.com/catchorg/Catch2) for testing.  
The backend is built using **Meson** and **Ninja**, with **Asio** for networking support.


---

## ⚙️ Backend Setup (C++ Crow Server)

### 🧰 Dependencies

You’ll need:

- **C++17 or later** compiler (e.g. `g++`, `clang++`, or MSVC)
- **Meson** and **Ninja**
- **Asio** (if not using Boost.Asio)
- **Ninja**

### 📦 Install Dependencies

#### Front end
```bash
sudo apt update
sudo apt install g++ cmake meson ninja-build libboost-all-dev libasio-dev libssl-dev

cd frontend
npm install
npm run dev
