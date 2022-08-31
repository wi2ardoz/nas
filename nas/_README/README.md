# NAS Project

## Overview

## How to Use

config nbd & mount:

* sudo modprobe nbd
* run master.out
* sudo mkfs.ext4 /dev/nbd0
* sudo mount /dev/nbd0 <_path_>/<_dir_name_>

change max_sectors_kb:

* sudo chmod 777 /sys/block/nbd0/queue/max_sectors_kb.
* gedit /sys/block/nbd0/queue/max_sectors_kb.
* change to 4 (KB) and save.

## Phase 1 - Master

## Phase 2 - Minion
