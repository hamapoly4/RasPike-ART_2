USE_RASPIKE_ART=1

mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_CXXOBJS +=\
	Route.o \
	AreaMove.o \
	DebriRemove.o \
	Circle.o \
	Step.o \
	RotateRun.o \
	StraightRun.o \
	InitMotor.o \
	GyroPControl.o \
	EncoderPDControl.o \
	RotateAngleDetect.o \
	Motor.o \
	GyroSensor.o \
	Button.o \
	
SRCLANG := c++

APPL_LIBS += -I/usr/include/opencv4
APPL_LIBS += `pkg-config --cflags --libs opencv4`

APPL_DIRS += $(mkfile_path)DebriRemoval \
			 $(mkfile_path)SubRun \
			 $(mkfile_path)Judge \
			 $(mkfile_path)Control \
			 $(mkfile_path)Detect \
			 $(mkfile_path)Initialize \
			 $(mkfile_path)SensorMonitor \
			 $(mkfile_path)ImageProcess \
			 $(mkfile_path)Device \

INCLUDES += \
	-I$(mkfile_path)DebriRemoval \
	-I$(mkfile_path)SubRun \
	-I$(mkfile_path)Judge \
	-I$(mkfile_path)Control \
	-I$(mkfile_path)Detect \
	-I$(mkfile_path)Initialize \
	-I$(mkfile_path)SensorMonitor \
	-I$(mkfile_path)ImageProcess \
	-I$(mkfile_path)Device \
