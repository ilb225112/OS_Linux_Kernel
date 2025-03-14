# Process Tree Viewer with Memory Map (Linux Kernel Module)

## 📑 Contents
1. [Overview](#overview)  
2. [Description](#description)  
3. [How To Run](#how-to-run)  
4. [Future Fixes](#future-fixes)  
5. [Author & License](#author--license)  
6. [References](#references)    

---

## Overview 
This project consists of a **Linux Kernel Module (LKM)** and a **User-space Program** that together visualize a **process tree with dynamically allocated memory**.  
- The kernel module prints **process hierarchy**, including **parent, child, and grandchild** processes.  
- The user-space program creates **multiple child and grandchild processes**, allocating memory dynamically.  

---

## Description 
This project helps users visualize the **process tree** in Linux along with **memory allocation details**.  
- The **kernel module** recursively fetches child processes using `task_struct`.  
- The **user program** spawns multiple child & grandchild processes with dynamic memory allocation.  
- Uses `dmesg` for **debugging & monitoring**.  

---

## How To Run 

### **Step 1:**
**_Pre-requisites_**:
- **Operating System**: Ubuntu 24.04.2 LTS (used for this)  <br/>
  **_Note_**: The Code varies from one to another version
- **Run the Command** :
  ```bash
  sudo apt update && sudo apt upgrade -y
  ```
- **GCC Compiler**: To install run 
  ```bash
  sudo apt install gcc
  ```
- **Make Utility**: To install run
  ```bash
  sudo apt install make
  ```
- **Kernel Headers**: To install run
  ```bash
  sudo apt install linux-headers-$(uname -r)
  ```
- Vim (optional): To install run
  ```bash
    sudo apt install vim -y
  ```
  
### **Step 2:**
  - Create a Folder
  - Create three files `user.c`,`my_kernel_module.c` and `Makefile`
  - <u> Note: </u>**_Make sure `Makefile` has no extension it's not .txt just save it as `Makefile` with no extension_** 
  - Open the files using Text editor and paste the codes
    

### **Step 3:**
  - In the folder _Left Click_ -> Open in Terminal
  - Click on the `+` tab at top and make sure u have two terminals side by side
  - Now let the Terminals be Terminal 1 and Terminal 2
  - **_Note:_** Both terminal must me in same dir where the fies are saved

    
### **Step 4:** _Execute these commands in order_
  - Terminal 2:
      ```bash
      make # Compile the kernel module
      ```
  - Terminal 1:
      ```bash
      gcc user.c -o user
      ./user
      ```
      -> **_Note Down the Parent process ID for example, `ABC`_**
  - Terminal 2:
    ```bash
    sudo insmod my_kernel_module.ko parent_pid=ABC
    ```
    ```bash
    sudo dmesg | tail -n 23
    ```
     -> **_NOTE: Adjust 23 based on the number of relevant log lines for your system._**
    ```bash
    make clean
    sudo rmmod my_kernel_module
    ```

## Sample Output  
After running the module and executing `dmesg | tail -n 23`, you should see an output similar to this:

```bash
[10695.413276] Kernel Module Loaded: Process Tree Viewer
[10695.413327] Displaying process tree for 👴 Parent -> PID 14671
[10695.413329] |-- 👴 Process: user [PID: 14671] [PPID: 13679] (Heap: 132 KB, Stack: 137437455117 KB)
[10695.413332] [Memory Map]
[10695.413333]        Region: Start=0x7fffa48a5000, End=0x7fffa48c6000, Size=132 KB
[10695.413335]     |-- 🧑 Process: user [PID: 14672] [PPID: 14671] (Heap: 132 KB, Stack: 137437455117 KB)
[10695.413337]     [Memory Map]
[10695.413338]            Region: Start=0x7fffa48a5000, End=0x7fffa48c6000, Size=132 KB
[10695.413361]         |-- 👶 Process: user [PID: 14675] [PPID: 14672] (Heap: 132 KB, Stack: 137437455117 KB)
[10695.413363]         [Memory Map]
[10695.413364]                Region: Start=0x7fffa48a5000, End=0x7fffa48c6000, Size=132 KB
[10695.413366]     |-- 🧑 Process: user [PID: 14673] [PPID: 14671] (Heap: 132 KB, Stack: 137437455117 KB)
[10695.413367]     [Memory Map]
[10695.413368]            Region: Start=0x7fffa48a5000, End=0x7fffa48c6000, Size=132 KB
[10695.413369]         |-- 👶 Process: user [PID: 14676] [PPID: 14673] (Heap: 132 KB, Stack: 137437455117 KB)
[10695.413370]         [Memory Map]
[10695.413372]                Region: Start=0x7fffa48a5000, End=0x7fffa48c6000, Size=132 KB
[10695.413373]     |-- 🧑 Process: user [PID: 14674] [PPID: 14671] (Heap: 132 KB, Stack: 137437455117 KB)
[10695.413374]     [Memory Map]
[10695.413375]            Region: Start=0x7fffa48a5000, End=0x7fffa48c6000, Size=132 KB
[10695.413376]         |-- 👶 Process: user [PID: 14677] [PPID: 14674] (Heap: 132 KB, Stack: 137437455117 KB)
[10695.413377]         [Memory Map]
[10695.413378]                Region: Start=0x7fffa48a5000, End=0x7fffa48c6000, Size=132 KB
```
### Note: The actual PIDs and memory addresses will be different each time you run the program
---

## Future Fixes  
- [ ] Improve error handling in `user.c`
- [ ] Support dynamic parent selection without manual PID input
- [ ] Add command-line arguments for user flexibility

---

## Author & License
**Author:** PES1UG23CS167  
**License:** MIT

---

## References  
- [Linux Kernel Module Programming Guide](https://www.tldp.org/LDP/lkmpg/2.6/html/)  

## Contributing 🤝 
Contributions are welcome! Feel free to **fork** this repo, make changes, and submit a **pull request**.  
