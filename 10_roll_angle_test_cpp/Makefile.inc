USE_RASPIKE_ART=1

mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_CXXOBJS +=\
	IMU.o \
	
SRCLANG := c++

APPL_DIRS += $(mkfile_path)IMU_class

INCLUDES += \
	-I$(mkfile_path)IMU_class \
