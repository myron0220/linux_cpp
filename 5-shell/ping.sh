# Author: Mingzhe Wang
# Date: Jul 5, 2026
# Description: 
#   Bash Shell for checking if a ip address is up or down

#!/bin/bash

for i in {1..254}; do
  ping -c 2 -i 0.5 -W 192.168.198.$i &> /dev/null
  
  if [ $? -eq 0 ]; then
    echo "192.168.199.$i is up"
  else
    echo "192.168.199.$i is down"
  fi

done