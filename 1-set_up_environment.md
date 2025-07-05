# Set up Linux/C++ developement environment 
1. install VirtualBox
2. install Linux.iso (based on architecture) on VM
3. configure `shared_foleder`
   ```bash
   sudo usermod -aG vboxsf myr
   cd /media/[shared_folder]
   ```
5. intall g++
   ```bash
   sudo apt-get update
   sudo apt-get install build-essential
   ```
6. ssh VM
   ```bash
   ip a
   ssh [username]@[ip]
   cd /media/[shared_folder]/[project_name]
   ```
7. temporarily close GUI
   ```bash
   sudo systemctl isolate multi-user.target
   ```

DONE.
