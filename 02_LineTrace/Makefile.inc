USE_RASPIKE_ART=1

mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_CXXOBJS +=\
	Motor.o \
	ColorSensor.o \
	Camera.o \
	
SRCLANG := c++

APPL_DIRS += $(mkfile_path)Motor $(mkfile_path)ColorSensor $(mkfile_path)Camera
APPL_LIBS += -I/usr/include/opencv4
APPL_LIBS += `pkg-config --cflags --libs opencv4`

INCLUDES += \
	-I$(mkfile_path)Motor \
	-I$(mkfile_path)ColorSensor \
	-I$(mkfile_path)Camera \
	-I/usr/include/opencv4 \
