USE_RASPIKE_ART=1

mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))
	
SRCLANG := c++

APPL_DIRS += -I/usr/include/opencv4

APPL_LIBS += `pkg-config --cflags --libs opencv4`

INCLUDES += \
	-I/usr/include/opencv4 \
