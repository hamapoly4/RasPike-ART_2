USE_RASPIKE_ART=1

mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_CXXOBJS +=\
	Motor.o \
	Button.o \
	
SRCLANG := c++

APPL_DIRS += $(mkfile_path)Motor \
			 $(mkfile_path)Button \

INCLUDES += \
	-I$(mkfile_path)Motor \
	-I$(mkfile_path)Button \
