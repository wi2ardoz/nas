###############################################################################
# 	FILENAME:	makefile    		AUTHOR: Liad Oz 		LAB: RD100	  	  #
#																			  #
#	TARGETS:	./lib/lib_framework_{DEBUG/RELEASE}.so						  #
#				./lib/lib_$(INPUT_PROXY)_{DEBUG/RELEASE}.so					  #
#				./bin/master_{DEBUG/RELEASE}.out							  #
#																			  #			
###############################################################################

# variable definitions
SDIR = ./src
IDIR = ./include
TDIR = ./test
LDIR = ./lib
ODIR = ./obj
BDIR = ./bin

#misq
EDIR = ./export
INPDIR = ./input
SODIR = ./dll
LOG_FILE = log
DEVICE_NAME = nbd6
DEVICE_PATH = /dev/$(DEVICE_NAME)
MOUNT_PATH = ~/my_nbd

# design patterns paths
DPDIR = ../design_patterns
DPINCDIR = $(DPDIR)/$(IDIR)

# thread safe queue include
TSQINCDIR = ../../cpp/$(IDIR)

# FM_SRCS = dir_monitor.cpp logger.cpp reactor.cpp thread_pool.cpp
# FM_OBJS_DEBUG =
# $(addprefix $(ODIR)/,$(patsubst %.c,%_DEBUG.o,$(notdir $(DS_SRCS))))
# FM_OBJS_DEBUG =
# $(addprefix $(ODIR)/,$(patsubst %.c,%_DEBUG.o,$(notdir $(DS_SRCS))))

# deps := $(patsubst %.o,%.d,$(OBJS))
# -include $(deps)
# DEPFLAGS = -MMD -MF $(@:.o=.d)

INCFLAGS = -I $(IDIR) -I $(DPINCDIR) -I $(TSQINCDIR) 
CC = g++ -std=c++98 -pedantic-errors -Wall -Wextra $(INCFLAGS)
LINKFLAGS = -L$(LDIR) -Wl,-rpath=$(LDIR)
ADDLIB = -lboost_system -lboost_thread -lpthread -ldl
DEBUG = -g
RELEASE = -DNDEBUG -O3

#server
QUEUE = thread_safe_que
MASTER = master
DIR_MONITOR = dir_monitor
LOGGER = logger
REACTOR = reactor
THREAD_POOL = thread_pool
INPUT_MEDIATOR = input_mediator
INPUT_PROXY = input_proxy
STARTUP = fw_starter
HANDLETON = singleton
DISPATCHER = dispatcher
TASKTP = task_tp
CMD = cmd
REGISTER = register
PACKET = packet
FACTORY = factory
DISTRIBUTOR = distributor
RAID = raid
RAID01 = raid_01
COMM_SERVER = comm_server_proxy
COMM_CLIENT = comm_client_proxy
UDP_SERVER = udp_server_proxy
UDP_CLIENT = udp_client_proxy

#input
DYNAMICHD = dynamic_hd
NBD = nbd
CMD_W = cmd_w
CMD_R = cmd_r
CMD_E = cmd_e

.PHONY: all clean dir export nbd mount log

all: clean \
	nbd \
	dir \
	$(BDIR)/$(MASTER)_DEBUG.out \
	$(LDIR)/lib_$(CMD_W)_DEBUG.so\
	$(LDIR)/lib_$(CMD_R)_DEBUG.so \
	$(LDIR)/lib_$(CMD_E)_DEBUG.so

###############################################################################
# build DEBUG
$(BDIR)/$(MASTER)_DEBUG.out: $(SDIR)/$(MASTER).cpp \
							 $(LDIR)/lib_framework_DEBUG.so \
							 $(LDIR)/lib_$(INPUT_PROXY)_DEBUG.so \
							 $(IDIR)/$(MASTER).hpp

	$(CC) $^ $(DEBUG) $(ADDLIB) $(LINKFLAGS) -o $@ 

# framework.so build 
FM_OBJ_DEBUG = $(ODIR)/$(DIR_MONITOR)_DEBUG.o \
		   		 $(ODIR)/$(LOGGER)_DEBUG.o \
		   		 $(ODIR)/$(REACTOR)_DEBUG.o \
		   		 $(ODIR)/$(THREAD_POOL)_DEBUG.o \
		   		 $(ODIR)/$(INPUT_MEDIATOR)_DEBUG.o \
		   		 $(ODIR)/$(STARTUP)_DEBUG.o \
				 $(ODIR)/$(HANDLETON)_DEBUG.o \
				 $(ODIR)/$(TASKTP)_DEBUG.o \
				 $(ODIR)/$(CMD)_DEBUG.o \
				 $(ODIR)/$(REGISTER)_DEBUG.o \
				 $(ODIR)/$(DISTRIBUTOR)_DEBUG.o \
				 $(ODIR)/$(RAID)_DEBUG.o \
				 $(ODIR)/$(RAID01)_DEBUG.o \
				 $(ODIR)/$(COMM_SERVER)_DEBUG.o \
				 $(ODIR)/$(COMM_CLIENT)_DEBUG.o \
				 $(ODIR)/$(UDP_SERVER)_DEBUG.o \
				 $(ODIR)/$(UDP_CLIENT)_DEBUG.o \
				 $(ODIR)/$(DYNAMICHD)_DEBUG.o

$(LDIR)/lib_framework_DEBUG.so: $(FM_OBJ_DEBUG) 
	$(CC) -shared $(FM_OBJ_DEBUG) -o $@

###############################################################################
# input_proxy so
$(LDIR)/lib_$(INPUT_PROXY)_DEBUG.so: $(ODIR)/$(NBD)_DEBUG.o \
								$(IDIR)/$(INPUT_PROXY).hpp 
	$(CC) -shared $< -o $@

#dir_monitor
$(ODIR)/$(DIR_MONITOR)_DEBUG.o: $(DPDIR)/src/$(DIR_MONITOR)/$(DIR_MONITOR).cpp \
								$(ODIR)/$(LOGGER)_DEBUG.o \
								$(ODIR)/$(HANDLETON)_DEBUG.o \
								$(DPINCDIR)/$(DIR_MONITOR).hpp \
								$(DPINCDIR)/$(DISPATCHER).hpp 

	$(CC) $(DEBUG) -c -fPIC $< -o $@ -I $(DPINCDIR)

# logger
$(ODIR)/$(LOGGER)_DEBUG.o: $(DPDIR)/$(SDIR)/$(LOGGER)/$(LOGGER).cpp \
						   $(DPINCDIR)/$(LOGGER).hpp \
						   $(TSQINCDIR)/$(QUEUE).hpp

	$(CC) $(DEBUG) -c -fPIC $< -o $@ -I $(DPINCDIR) -I $(TSQINCDIR)


# reactor
$(ODIR)/$(REACTOR)_DEBUG.o: $(DPDIR)/src/$(REACTOR)/$(REACTOR).cpp \
							$(ODIR)/$(LOGGER)_DEBUG.o \
							$(ODIR)/$(HANDLETON)_DEBUG.o \
							$(DPINCDIR)/$(REACTOR).hpp

	$(CC) $(DEBUG) -c -fPIC $< -o $@ -I $(DPINCDIR)

# thread_pool
$(ODIR)/$(THREAD_POOL)_DEBUG.o: $(DPDIR)/$(SDIR)/$(THREAD_POOL)/$(THREAD_POOL).cpp \
								$(ODIR)/$(LOGGER)_DEBUG.o \
								$(ODIR)/$(HANDLETON)_DEBUG.o \
								$(DPINCDIR)/$(THREAD_POOL).hpp \
								$(TSQINCDIR)/$(QUEUE).hpp

	$(CC) $(DEBUG) -c -fPIC $< -o $@ -I $(DPINCDIR) -I $(TSQINCDIR)

# input_mediator
$(ODIR)/$(INPUT_MEDIATOR)_DEBUG.o: $(SDIR)/$(INPUT_MEDIATOR).cpp \
								   $(IDIR)/$(INPUT_MEDIATOR).hpp \
								   $(IDIR)/$(INPUT_PROXY).hpp \
								   $(IDIR)/$(PACKET).hpp \
								   $(DPINCDIR)/$(REACTOR).hpp

	$(CC) $(DEBUG) -c -fPIC $< -o $@ -I $(DPINCDIR) -I $(IDIR) 

# startup
$(ODIR)/$(STARTUP)_DEBUG.o: $(SDIR)/$(STARTUP).cpp 
	$(CC) $(DEBUG) -c -fPIC $< -o $@ $(INCFLAGS) 


# handleton
$(ODIR)/$(HANDLETON)_DEBUG.o: $(DPDIR)/$(SDIR)/$(HANDLETON)/$(HANDLETON).cpp \
							  $(ODIR)/$(LOGGER)_DEBUG.o \
							  $(ODIR)/$(THREAD_POOL)_DEBUG.o \
							  $(DPINCDIR)/$(HANDLETON).hpp \
							  $(DPINCDIR)/$(FACTORY).hpp

	$(CC) -c $(DEBUG) -fPIC $< -o $@ -I $(DPINCDIR)

# task_tp
$(ODIR)/$(TASKTP)_DEBUG.o: $(SDIR)/$(TASKTP).cpp 
	$(CC) $(DEBUG) -c -fPIC $< -o $@ $(INCFLAGS)

# register
$(ODIR)/$(REGISTER)_DEBUG.o: $(SDIR)/$(REGISTER).cpp
	$(CC) $(DEBUG) -c -fPIC $< -o $@ $(INCFLAGS)

# cmd
$(ODIR)/$(CMD)_DEBUG.o: $(SDIR)/$(CMD).cpp
	$(CC) $(DEBUG) -c -fPIC $< -o $@ $(INCFLAGS)

# distributor
$(ODIR)/$(DISTRIBUTOR)_DEBUG.o : $(SDIR)/$(DISTRIBUTOR).cpp
	$(CC) $(DEBUG) -c -fPIC $< -o $@ $(INCFLAGS)

# raid
$(ODIR)/$(RAID)_DEBUG.o : $(SDIR)/$(RAID).cpp
	$(CC) $(DEBUG) -c -fPIC $< -o $@ $(INCFLAGS)

# raid 01
$(ODIR)/$(RAID01)_DEBUG.o : $(SDIR)/$(RAID01).cpp
	$(CC) $(DEBUG) -c -fPIC $< -o $@ $(INCFLAGS)

# comm_proxy
$(ODIR)/$(COMM_SERVER)_DEBUG.o : $(SDIR)/$(COMM_SERVER).cpp
	$(CC) $(DEBUG) -c -fPIC $< -o $@ $(INCFLAGS)

$(ODIR)/$(COMM_CLIENT)_DEBUG.o : $(SDIR)/$(COMM_CLIENT).cpp
	$(CC) $(DEBUG) -c -fPIC $< -o $@ $(INCFLAGS)

# udp_proxy
$(ODIR)/$(UDP_SERVER)_DEBUG.o : $(SDIR)/$(UDP_SERVER).cpp
	$(CC) $(DEBUG) -c -fPIC $< -o $@ $(INCFLAGS)

$(ODIR)/$(UDP_CLIENT)_DEBUG.o : $(SDIR)/$(UDP_CLIENT).cpp
	$(CC) $(DEBUG) -c -fPIC $< -o $@ $(INCFLAGS)

## <-------------------- ADD FRAMWORK components here -------------------> ##







## <----------------------- ADD INPUT components here ---------------------> ##

# nbd
$(ODIR)/$(NBD)_DEBUG.o: $(SDIR)/$(INPDIR)/$(NBD).cpp \
						$(IDIR)/$(NBD).hpp

	$(CC) -c $(DEBUG) -fPIC $< -o $@ -I $(IDIR)

# WRITE
$(LDIR)/lib_$(CMD_W)_DEBUG.so: $(ODIR)/$(CMD_W)_DEBUG.o

	$(CC) -shared $(ODIR)/$(CMD_W)_DEBUG.o -o $@

$(ODIR)/$(CMD_W)_DEBUG.o: $(SDIR)/$(INPDIR)/$(CMD_W).cpp
	$(CC) $(DEBUG) -c -fPIC $< -o $@ $(INCFLAGS)

# READ
$(LDIR)/lib_$(CMD_R)_DEBUG.so: $(ODIR)/$(CMD_R)_DEBUG.o
	$(CC) -shared $(ODIR)/$(CMD_R)_DEBUG.o -o $@

$(ODIR)/$(CMD_R)_DEBUG.o: $(SDIR)/$(INPDIR)/$(CMD_R).cpp
	$(CC) $(DEBUG) -c -fPIC $< -o $@ $(INCFLAGS)

# Exception
$(LDIR)/lib_$(CMD_E)_DEBUG.so: $(ODIR)/$(CMD_E)_DEBUG.o
	$(CC) -shared $(ODIR)/$(CMD_E)_DEBUG.o -o $@

$(ODIR)/$(CMD_E)_DEBUG.o: $(SDIR)/$(INPDIR)/$(CMD_E).cpp
	$(CC) $(DEBUG) -c -fPIC $< -o $@ $(INCFLAGS)
###############################################################################
# dynamic_hd

$(ODIR)/$(DYNAMICHD)_DEBUG.o: $(SDIR)/$(DYNAMICHD).cpp \
							  $(IDIR)/$(DYNAMICHD).hpp

	$(CC) -c $(DEBUG) -fPIC $< -o $@ -I $(IDIR)
###############################################################################
dir:
	@mkdir -p $(ODIR) $(LDIR) $(BDIR) $(SODIR)

export:
	@mkdir -p $(EDIR) $(EDIR)/$(BDIR) $(EDIR)/$(SODIR) $(EDIR)/$(IDIR) $(EDIR)/$(LDIR)
#master
	@cp $(BDIR)/$(MASTER)_DEBUG.out (EDIR)/$(BDIR)
#framework
	@cp $(LDIR)/lib_framework_DEBUG.so $(EDIR)/$(LDIR)
#input proxy
	@cp $(IDIR)/$(INPUT_PROXY).hpp $(EDIR)/$(IDIR)
	@cp $(LDIR)/lib_$(INPUT_PROXY)_DEBUG.so $(EDIR)/$(LDIR)
	
clean:
# silence unmount
	@sudo umount $(MOUNT_PATH) > /dev/null 2>&1 || /bin/true 
# clean dirs
	@sudo rm -rf $(MOUNT_PATH)
	@sudo rm -rf $(LDIR) $(ODIR) $(BDIR) $(EDIR) $(SODIR)
	@sudo rm -f $(TDIR)/$(LOG_FILE)

log:
	@sudo cat $(TDIR)/$(LOG_FILE)

nbd:
	@sudo modprobe nbd
	@sudo chmod 777 /sys/block/$(DEVICE_NAME)/queue/max_sectors_kb
	@sudo echo "4" >> /sys/block/$(DEVICE_NAME)/queue/max_sectors_kb
    
mount:
	@sudo mkfs.ext4 $(DEVICE_PATH)
	@sudo mkdir $(MOUNT_PATH)
	@sudo mount $(DEVICE_PATH) $(MOUNT_PATH)

run:
	@sudo rm -f $(TDIR)/$(LOG_FILE)
	@touch $(TDIR)/$(LOG_FILE)
	@sudo $(BDIR)/$(MASTER)_DEBUG.out
###############################################################################