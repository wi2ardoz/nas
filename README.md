# nas
Network Attached Storage (NAS) for Linux distros

## Introduction
An NAS device is a storage device connected to a network that allows storage and retrieval of data from a central location for authorised network users and varied clients. NAS devices are flexible and scale out, meaning that as you need additional storage, you can add to what you have. NAS is like having a private cloud in the office. It’s faster, less expensive and provides all the benefits of a public cloud on site, giving you complete control.

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


TBD
