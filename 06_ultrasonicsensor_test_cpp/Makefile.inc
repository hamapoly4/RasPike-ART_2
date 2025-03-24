USE_RASPIKE_ART=1

mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_CXXOBJS +=\
	SonarSensor.o \

SRCLANG := c++

APPL_DIRS += $(mkfile_path)SonarSensor_class

INCLUDES += \
	-I$(mkfile_path)SonarSensor_class \
