#########################################
#                top dir                #
#########################################
PROJBASE=$(CURDIR)
#COMPILE_SHARED=1
FPIC_FLAG=1

#########################################
#                target                 #
#########################################
SUBDIR=src

#########################################
#      header and lib dependancy        #
#########################################
INC_DIR= -I. -I./include 		
STATIC_LIB=  
SHARED_LIB_DIR=
SHARED_LIB=-ldl -lpthread -lrt  

include $(PROJBASE)/base/build/makefile.staticlib.base.linux
include $(PROJBASE)/base/build/makefile.staticlib.mysql.linux
include $(PROJBASE)/base/build/makefile.staticlib.libxml2.linux
include $(PROJBASE)/base/build/makefile.staticlib.libpcap.linux

#########################################
#              compiler                 #
#########################################
include $(PROJBASE)/base/build/makefile.compiler

#########################################
#              rules                    #
#########################################
include $(PROJBASE)/base/build/makefile.compile.rules

