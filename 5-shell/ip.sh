# Author: Mingzhe Wang
# Date: Jul 5, 2026
# Description: get current ip address of this machine

#!/bin/bash
ifconfig enp0s8 | grep 'inet ' | awk '{print $2}' | cut -d/ -f1
