USE_RASPIKE_ART=1

mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_CXXOBJS +=\
	Motor.o \
	IMU.o \
	RollAngle.o \
	
SRCLANG := c++

APPL_DIRS += $(mkfile_path)Motor $(mkfile_path)IMU $(mkfile_path)RollAngle

INCLUDES += \
	-I$(mkfile_path)Motor \
	-I$(mkfile_path)IMU \
	-I$(mkfile_path)RollAngle \
