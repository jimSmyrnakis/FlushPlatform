#=========================	Basic Directories Definitions ================================
#=========================================================================================
#=========================================================================================

#Object Directories Variables 
OBJ_DIR_X86DEB  	= ./Objects/Linux-x86/Debug
OBJ_DIR_X86REL		= ./Objects/Linux-x86/Release
OBJ_DIR_X86DIST		= ./Objects/Linux-x86/Dist

OBJ_DIR_X64DEB		= ./Objects/Linux-x64/Debug
OBJ_DIR_X64REL		= ./Objects/Linux-x64/Release
OBJ_DIR_X64DIST		= ./Objects/Linux-x64/Dist

OBJ_DIR_ARM32DEB	= ./Objects/Linux-ARM32/Debug
OBJ_DIR_ARM32REL	= ./Objects/Linux-ARM32/Release
OBJ_DIR_ARM32DIST	= ./Objects/Linux-ARM32/Dist

OBJ_DIR_ARM64DEB	= ./Objects/Linux-ARM64/Debug
OBJ_DIR_ARM64REL	= ./Objects/Linux-ARM64/Release
OBJ_DIR_ARM64DIST	= ./Objects/Linux-ARM64/Dist


#Library Directories Variables
LIB_DIR_X86DEB  	= ./Library/Linux-x86/Debug
LIB_DIR_X86REL		= ./Library/Linux-x86/Release
LIB_DIR_X86DIST		= ./Library/Linux-x86/Dist

LIB_DIR_X64DEB		= ./Library/Linux-x64/Debug
LIB_DIR_X64REL		= ./Library/Linux-x64/Release
LIB_DIR_X64DIST		= ./Library/Linux-x64/Dist

LIB_DIR_ARM32DEB	= ./Library/Linux-ARM32/Debug
LIB_DIR_ARM32REL	= ./Library/Linux-ARM32/Release
LIB_DIR_ARM32DIST	= ./Library/Linux-ARM32/Dist

LIB_DIR_ARM64DEB	= ./Library/Linux-ARM64/Debug
LIB_DIR_ARM64REL	= ./Library/Linux-ARM64/Release
LIB_DIR_ARM64DIST	= ./Library/Linux-ARM64/Dist


#Base Directories for source code and include's
SRC_DIR				= ./Source/OS/Linux
INC_DIR				= ./Include


#==================	PreCompiler Definitions ======================================
#=================================================================================
#=================================================================================
DEFS_X86DEB			=	-DFLUSH_DEBUG		-DFLUSH_PROC_X86
DEFS_X86REL			=	-DFLUSH_RELEASE		-DFLUSH_PROC_X86
DEFS_X86DIST		=	-DFLUSH_DIST		-DFLUSH_PROC_X86

DEFS_X64DEB			=	-DFLUSH_DEBUG		-DFLUSH_PROC_X64
DEFS_X64REL			=	-DFLUSH_RELEASE		-DFLUSH_PROC_X64
DEFS_X64DIST		=	-DFLUSH_DIST		-DFLUSH_PROC_X64

DEFS_ARM32DEB		=	-DFLUSH_DEBUG		-DFLUSH_PROC_ARM32
DEFS_ARM32REL		=	-DFLUSH_RELEASE		-DFLUSH_PROC_ARM32
DEFS_ARM32DIST		=	-DFLUSH_DIST		-DFLUSH_PROC_ARM32

DEFS_ARM64DEB		=	-DFLUSH_DEBUG		-DFLUSH_PROC_ARM64
DEFS_ARM64REL		=	-DFLUSH_RELEASE		-DFLUSH_PROC_ARM64
DEFS_ARM64DIST		=	-DFLUSH_DIST		-DFLUSH_PROC_ARM64


#==================	Common Flags for GCC =========================================
#=================================================================================
#=================================================================================
COMMON_OS_FLAGS= -I$(INC_DIR) -DFLUSH_OS_LINUX -std=c++11
COMMON_DEBUG_FLAGS= -g $(COMMON_OS_FLAGS) 
COMMON_RELEASE_FLAGS=  $(COMMON_OS_FLAGS) 
COMMON_DIST_FLAGS= $(COMMON_OS_FLAGS) 

#==================== Parameters default state ===================================
#=================================================================================
#=================================================================================

MODE_PLATFORM ?= debug-x64
CURRENT_PLATFORM ?= x64

#===================== Basic Compilers , flags , dirs and other's ================
#=================================================================================
#=================================================================================

DEFS= $(DEFS_X64DEB)
OBJ_DIR= $(OBJ_DIR_X64DEB)
LIB_DIR= $(LIB_DIR_X64DEB)
COMPILE_TARGET_PLATFORM=x64
CC= g++
CCFLAGS= $(COMMON_DEBUG_FLAGS) $(DEFS)
#====================`Set Up Basic Compilers , flags  , dirs ... =================
#=================================================================================
#=================================================================================

ifeq 	($(MODE_PLATFORM) , debug-x86)

DEFS= $(DEFS_X86DEB)
OBJ_DIR= $(OBJ_DIR_X86DEB)
LIB_DIR= $(LIB_DIR_X86DEB)
COMPILE_TARGET_PLATFORM=x86
CCFLAGS= $(COMMON_DEBUG_FLAGS) $(DEFS)

else ifeq 	($(MODE_PLATFORM) , debug-x64)

DEFS= $(DEFS_X64DEB)
OBJ_DIR= $(OBJ_DIR_X64DEB)
LIB_DIR= $(LIB_DIR_X64DEB)
COMPILE_TARGET_PLATFORM=x64
CCFLAGS= $(COMMON_DEBUG_FLAGS) $(DEFS)

else ifeq 	($(MODE_PLATFORM) , debug-arm32)

DEFS= $(DEFS_ARM32DEB)
OBJ_DIR= $(OBJ_DIR_ARM32DEB)
LIB_DIR= $(LIB_DIR_ARM32DEB)
COMPILE_TARGET_PLATFORM=arm32
CCFLAGS= $(COMMON_DEBUG_FLAGS) $(DEFS)

else ifeq 	($(MODE_PLATFORM) , debug-arm64)

DEFS= $(DEFS_ARM64DEB)
OBJ_DIR= $(OBJ_DIR_ARM64DEB)
LIB_DIR= $(LIB_DIR_ARM64DEB)
COMPILE_TARGET_PLATFORM=arm64
CCFLAGS= $(COMMON_DEBUG_FLAGS) $(DEFS)

else ifeq 	($(MODE_PLATFORM) , release-x86)

DEFS= $(DEFS_X86REL)
OBJ_DIR= $(OBJ_DIR_X86REL)
LIB_DIR= $(LIB_DIR_X86REL)
COMPILE_TARGET_PLATFORM=x86
CCFLAGS= $(COMMON_RELEASE_FLAGS) $(DEFS)

else ifeq 	($(MODE_PLATFORM) , release-x64)

DEFS= $(DEFS_X64REL)
OBJ_DIR= $(OBJ_DIR_X64REL)
LIB_DIR= $(LIB_DIR_X64REL)
COMPILE_TARGET_PLATFORM=x64
CCFLAGS= $(COMMON_RELEASE_FLAGS) $(DEFS)

else ifeq 	($(MODE_PLATFORM) , release-arm32)

DEFS= $(DEFS_ARM32REL)
OBJ_DIR= $(OBJ_DIR_ARM32REL)
LIB_DIR= $(LIB_DIR_ARM32REL)
COMPILE_TARGET_PLATFORM=arm32
CCFLAGS= $(COMMON_RELEASE_FLAGS) $(DEFS)

else ifeq 	($(MODE_PLATFORM) , release-arm64)

DEFS= $(DEFS_ARM64REL)
OBJ_DIR= $(OBJ_DIR_ARM64REL)
LIB_DIR= $(LIB_DIR_ARM64REL)
COMPILE_TARGET_PLATFORM=arm64
CCFLAGS= $(COMMON_RELEASE_FLAGS) $(DEFS)

else ifeq 	($(MODE_PLATFORM) , dist-x86)

DEFS= $(DEFS_X86DIST)
OBJ_DIR= $(OBJ_DIR_X86DIST)
LIB_DIR= $(LIB_DIR_X86DIST)
COMPILE_TARGET_PLATFORM=x86
CCFLAGS= $(COMMON_DIST_FLAGS) $(DEFS)

else ifeq 	($(MODE_PLATFORM) , dist-x64)

DEFS= $(DEFS_X64DIST)
OBJ_DIR= $(OBJ_DIR_X64DIST)
LIB_DIR= $(LIB_DIR_X64DIST)
COMPILE_TARGET_PLATFORM=x64
CCFLAGS= $(COMMON_DIST_FLAGS) $(DEFS)

else ifeq 	($(MODE_PLATFORM) , dist-arm32)

DEFS= $(DEFS_ARM32DIST)
OBJ_DIR= $(OBJ_DIR_ARM32DIST)
LIB_DIR= $(LIB_DIR_ARM32DIST)
COMPILE_TARGET_PLATFORM=arm32
CCFLAGS= $(COMMON_DIST_FLAGS) $(DEFS)

else ifeq 	($(MODE_PLATFORM) , dist-arm64)

DEFS= $(DEFS_ARM64DIST)
OBJ_DIR= $(OBJ_DIR_ARM64DIST)
LIB_DIR= $(LIB_DIR_ARM64DIST)
COMPILE_TARGET_PLATFORM=arm64
CCFLAGS= $(COMMON_DIST_FLAGS) $(DEFS)

endif



ifeq 		($(CURRENT_PLATFORM) , x86) 
	ifeq 		($(COMPILE_TARGET_PLATFORM) , x86) 
		CC= g++
	else ifeq 	($(COMPILE_TARGET_PLATFORM) , x64)
		CC= g++-x86-64-linux-gnu
	else ifeq 	($(COMPILE_TARGET_PLATFORM) , arm32)
		CC= arm-linux-gnueabihf-g++
	else ifeq 	($(COMPILE_TARGET_PLATFORM) , arm64)
		CC= aarch64-linux-gnu-g++ 
	endif
else ifeq 	($(CURRENT_PLATFORM) , x64)
	ifeq 		($(COMPILE_TARGET_PLATFORM) , x86) 
		CC= g++ -m32
	else ifeq 	($(COMPILE_TARGET_PLATFORM) , x64)
		CC= g++ -m64
	else ifeq 	($(COMPILE_TARGET_PLATFORM) , arm32)
		CC= arm-linux-gnueabihf-g++
	else ifeq 	($(COMPILE_TARGET_PLATFORM) , arm64)
		CC= aarch64-linux-gnu-g++ 
	endif
else ifeq 	($(CURRENT_PLATFORM) , arm32)
	ifeq 		($(COMPILE_TARGET_PLATFORM) , x86) 
		CC= g++-i686-linux-gnu
	else ifeq 	($(COMPILE_TARGET_PLATFORM) , x64)
		CC= g++-x86-64-linux-gnu
	else ifeq 	($(COMPILE_TARGET_PLATFORM) , arm32)
		CC= g++
	else ifeq 	($(COMPILE_TARGET_PLATFORM) , arm64)
		CC= aarch64-linux-gnu-g++ 
	endif
else ifeq 	($(CURRENT_PLATFORM) , arm64)
	ifeq 		($(COMPILE_TARGET_PLATFORM) , x86) 
		CC= g++-i686-linux-gnu
	else ifeq 	($(COMPILE_TARGET_PLATFORM) , x64)
		CC= g++-x86-64-linux-gnu
	else ifeq 	($(COMPILE_TARGET_PLATFORM) , arm32)
		CC= arm-linux-gnueabihf-g++
	else ifeq 	($(COMPILE_TARGET_PLATFORM) , arm64)
		CC= g++
	endif
endif


#=============================================================================================================================
#=============================================================================================================================
#=============================================================================================================================
#=============================================================================================================================
#=============================================================================================================================
#=============================================================================================================================
#=============================================================================================================================
#=============================================================================================================================
#=============================================================================================================================
#=============================================================================================================================
#=============================================================================================================================
#=============================================================================================================================
#=============================================================================================================================
#=============================================================================================================================
#=============================================================================================================================
#=============================================================================================================================
#=============================================================================================================================
#=============================================================================================================================
#=============================================================================================================================
#=============================================================================================================================
#=============================================================================================================================
#=============================================================================================================================
#=============================================================================================================================
#=============================================================================================================================
#=============================================================================================================================
#=============================================================================================================================
#=============================================================================================================================
#=============================================================================================================================




OBJECTS= $(OBJ_DIR)/PThread.o $(OBJ_DIR)/PMutex.o $(OBJ_DIR)/PCondition.o $(OBJ_DIR)/Linux_Defs.o

$(LIB_DIR)/libFlushPlatform.a: $(OBJECTS)
	ar rcs $(LIB_DIR)/libFlushPlatform.a $(OBJECTS)

#=======================================	Threads	==========================================================================
#=============================================================================================================================
#=============================================================================================================================

$(OBJ_DIR)/PThread.o: $(SRC_DIR)/PThread/PThread.cpp
	$(CC) -c $(SRC_DIR)/PThread/PThread.cpp -o $(OBJ_DIR)/PThread.o $(CCFLAGS) -lpthread

$(OBJ_DIR)/PMutex.o: $(SRC_DIR)/PThread/PMutex.cpp
	$(CC) -c $(SRC_DIR)/PThread/PMutex.cpp -o $(OBJ_DIR)/PMutex.o $(CCFLAGS) -lpthread

$(OBJ_DIR)/PCondition.o: $(SRC_DIR)/PThread/PCondition.cpp
	$(CC) -c $(SRC_DIR)/PThread/PCondition.cpp -o $(OBJ_DIR)/PCondition.o $(CCFLAGS) -lpthread

#=======================================	Files	==========================================================================
#=============================================================================================================================
#=============================================================================================================================

#=======================================	Memory	==========================================================================
#=============================================================================================================================
#=============================================================================================================================


#=======================================	LINUX    ==========================================================================
#=============================================================================================================================
#=============================================================================================================================

$(OBJ_DIR)/Linux_Defs.o: $(SRC_DIR)/Defs.cpp
	$(CC) -c $(SRC_DIR)/Defs.cpp -o $(OBJ_DIR)/Linux_Defs.o $(CCFLAGS) -lpthread


clean: 
	rm -rf $(OBJ_DIR)/*.o $(LIB_DIR)/libFlushPlatform.a

