#------------------------------------------------------------------------------#
# This makefile was generated by 'cbp2make' tool rev.147                       #
#                                                                              #
#                                                                              #
# Using cmdline:                                                               #
# ./cbp2make.linux-x86_64 -in LedCtrl.cbp --with-deps -unix -out Makefile      #
#------------------------------------------------------------------------------#


WORKDIR = `pwd`

CC = gcc
CXX = g++
AR = ar
LD = g++
WINDRES = windres

INC = 
CFLAGS = -Wall -fexceptions
RESINC = 
LIBDIR = 
LIB = 
LDFLAGS = 

INC_DEBUG = $(INC) -Iinclude
CFLAGS_DEBUG = $(CFLAGS) -std=c++11 -g
RESINC_DEBUG = $(RESINC)
RCFLAGS_DEBUG = $(RCFLAGS)
LIBDIR_DEBUG = $(LIBDIR)
LIB_DEBUG = $(LIB)
LDFLAGS_DEBUG = $(LDFLAGS)
OBJDIR_DEBUG = obj/Debug
DEP_DEBUG = 
OUT_DEBUG = bin/Debug/LedCtrl

INC_RELEASE = $(INC) -Iinclude
CFLAGS_RELEASE = $(CFLAGS) -O2 -std=c++11
RESINC_RELEASE = $(RESINC)
RCFLAGS_RELEASE = $(RCFLAGS)
LIBDIR_RELEASE = $(LIBDIR)
LIB_RELEASE = $(LIB)
LDFLAGS_RELEASE = $(LDFLAGS) -s
OBJDIR_RELEASE = obj/Release
DEP_RELEASE = 
OUT_RELEASE = bin/Release/LedCtrl

OBJ_DEBUG = $(OBJDIR_DEBUG)/main.o $(OBJDIR_DEBUG)/src/cmdresult.o $(OBJDIR_DEBUG)/src/led.o $(OBJDIR_DEBUG)/src/led_hal.o $(OBJDIR_DEBUG)/src/led_int_param.o $(OBJDIR_DEBUG)/src/led_str_param.o

OBJ_RELEASE = $(OBJDIR_RELEASE)/main.o $(OBJDIR_RELEASE)/src/cmdresult.o $(OBJDIR_RELEASE)/src/led.o $(OBJDIR_RELEASE)/src/led_hal.o $(OBJDIR_RELEASE)/src/led_int_param.o $(OBJDIR_RELEASE)/src/led_str_param.o

all: debug release

clean: clean_debug clean_release

before_debug: 
	test -d bin/Debug || mkdir -p bin/Debug
	test -d $(OBJDIR_DEBUG) || mkdir -p $(OBJDIR_DEBUG)
	test -d $(OBJDIR_DEBUG)/src || mkdir -p $(OBJDIR_DEBUG)/src

after_debug: 

debug: before_debug out_debug after_debug

out_debug: before_debug $(OBJ_DEBUG) $(DEP_DEBUG)
	$(LD) $(LIBDIR_DEBUG) -o $(OUT_DEBUG) $(OBJ_DEBUG)  $(LDFLAGS_DEBUG) $(LIB_DEBUG)

$(OBJDIR_DEBUG)/main.o: main.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c main.cpp -o $(OBJDIR_DEBUG)/main.o

$(OBJDIR_DEBUG)/src/cmdresult.o: src/cmdresult.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/cmdresult.cpp -o $(OBJDIR_DEBUG)/src/cmdresult.o

$(OBJDIR_DEBUG)/src/led.o: src/led.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/led.cpp -o $(OBJDIR_DEBUG)/src/led.o

$(OBJDIR_DEBUG)/src/led_hal.o: src/led_hal.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/led_hal.cpp -o $(OBJDIR_DEBUG)/src/led_hal.o

$(OBJDIR_DEBUG)/src/led_int_param.o: src/led_int_param.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/led_int_param.cpp -o $(OBJDIR_DEBUG)/src/led_int_param.o

$(OBJDIR_DEBUG)/src/led_str_param.o: src/led_str_param.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/led_str_param.cpp -o $(OBJDIR_DEBUG)/src/led_str_param.o

clean_debug: 
	rm -f $(OBJ_DEBUG) $(OUT_DEBUG)
	rm -rf bin/Debug
	rm -rf $(OBJDIR_DEBUG)
	rm -rf $(OBJDIR_DEBUG)/src

before_release: 
	test -d bin/Release || mkdir -p bin/Release
	test -d $(OBJDIR_RELEASE) || mkdir -p $(OBJDIR_RELEASE)
	test -d $(OBJDIR_RELEASE)/src || mkdir -p $(OBJDIR_RELEASE)/src

after_release: 

release: before_release out_release after_release

out_release: before_release $(OBJ_RELEASE) $(DEP_RELEASE)
	$(LD) $(LIBDIR_RELEASE) -o $(OUT_RELEASE) $(OBJ_RELEASE)  $(LDFLAGS_RELEASE) $(LIB_RELEASE)

$(OBJDIR_RELEASE)/main.o: main.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c main.cpp -o $(OBJDIR_RELEASE)/main.o

$(OBJDIR_RELEASE)/src/cmdresult.o: src/cmdresult.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/cmdresult.cpp -o $(OBJDIR_RELEASE)/src/cmdresult.o

$(OBJDIR_RELEASE)/src/led.o: src/led.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/led.cpp -o $(OBJDIR_RELEASE)/src/led.o

$(OBJDIR_RELEASE)/src/led_hal.o: src/led_hal.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/led_hal.cpp -o $(OBJDIR_RELEASE)/src/led_hal.o

$(OBJDIR_RELEASE)/src/led_int_param.o: src/led_int_param.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/led_int_param.cpp -o $(OBJDIR_RELEASE)/src/led_int_param.o

$(OBJDIR_RELEASE)/src/led_str_param.o: src/led_str_param.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/led_str_param.cpp -o $(OBJDIR_RELEASE)/src/led_str_param.o

clean_release: 
	rm -f $(OBJ_RELEASE) $(OUT_RELEASE)
	rm -rf bin/Release
	rm -rf $(OBJDIR_RELEASE)
	rm -rf $(OBJDIR_RELEASE)/src

main.cpp: include/led.h

include/led.h: include/led_hal.h include/led_str_param.h include/led_int_param.h include/led_types.h include/cmdresult.h

src/cmdresult.cpp: include/cmdresult.h

src/led.cpp: include/led.h

src/led_hal.cpp: include/led_hal.h

src/led_int_param.cpp: include/led_int_param.h

src/led_str_param.cpp: include/led_str_param.h

.PHONY: before_debug after_debug clean_debug before_release after_release clean_release

