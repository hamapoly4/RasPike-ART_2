USE_RASPIKE_ART=1

mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_CXXOBJS +=\
	LineTracer.o\
	
SRCLANG := c++

APPL_DIRS += $(mkfile_path)LineTracer

APPL_LIBS += -I/usr/include/opencv4
APPL_LIBS += -I/usr/include
APPL_LIBS += `pkg-config --cflags --libs opencv4`
APPL_LIBS += -lpthread

INCLUDES += \
	-I$(mkfile_path)LineTracer\
	-I/usr/include/opencv4 \
	-I/usr/include \
