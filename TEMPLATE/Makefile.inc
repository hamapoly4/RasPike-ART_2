USE_RASPIKE_ART=1

mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_CXXOBJS +=\
	＜オブジェクトファイル名＞ \
	
SRCLANG := c++

APPL_DIRS += $(mkfile_path)＜ディレクトリ名＞

INCLUDES += \
	-I$(mkfile_path)＜ディレクトリ名＞ \
