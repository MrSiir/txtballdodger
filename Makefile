###########################################
### MACROS
###########################################

# $(1) : Compiler
# $(2) : Object file to generate
# $(3) : Source file
# $(4) : Additional dependencies
# $(5) : Compiler flags
define COMPILE
$(2) : $(3) $(4)
	$(1) $(5) -c -o $(2) $(3)

endef

# $(1) : Source file
define C2O
$(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(patsubst $(SRC)%,$(OBJ)%,$(1))))
endef

# $(1) : Source file
define C2H
$(patsubst %.c,%.h,$(patsubst %.cpp,%.hpp,$(1)))
endef

###########################################
### CONFIG
###########################################
APP     := tbdodger
CFLAGS  := -Wall -pedantic
CCFLAGS := $(CFLAGS) -std=c++2a
CC      := g++
C       := gcc
MKDIR   := mkdir -p
SRC     := src
OBJ     := obj
INCDIRS := -I$(SRC)

ifdef DEBUG
   CCFLAGS += -g
else ifdef SANITIZE
   CCFLAGS += -fsanitize=address -fno-omit-frame-pointer -O1 -g
else
   CCFLAGS += -O3
endif

ALLCPPS_M  := $(shell find src/ -type f  -iname *.cpp)
ALLCPPS    := $(filter-out %main.cpp,$(ALLCPPS_M)) $(filter %main.cpp,$(ALLCPPS_M))
ALLCS      := $(shell find src/ -type f  -iname *.c)
ALLOBJ     := $(foreach F,$(ALLCPPS) $(ALLCS),$(call C2O,$(F)))
SUBDIRS    := $(shell find $(SRC) -type d)
OBJSUBDIRS := $(patsubst $(SRC)%,$(OBJ)%,$(SUBDIRS))

.PHONY: info

# comentario
$(APP) : $(OBJSUBDIRS) $(ALLOBJ)
	$(CC) $(CCFLAGS) -o $(APP) $(ALLOBJ)

# Generate rules for all objects
$(foreach F,$(ALLCPPS),$(eval $(call COMPILE,$(CC),$(call C2O,$(F)),$(F),$(call C2H,$(F)),$(CCFLAGS) $(INCDIRS))))
$(foreach F,$(ALLCS),$(eval $(call COMPILE,$(C),$(call C2O,$(F)),$(F),$(call C2H,$(F)),$(CFLAGS) $(INCDIRS))))

info:
	$(info $(SUBDIRS))
	$(info $(OBJSUBDIRS))
	$(info $(ALLCPPS))
	$(info $(ALLCS))
	$(info $(ALLCSOBJ))

$(OBJSUBDIRS) :
	$(MKDIR) $(OBJSUBDIRS)

## CLEAN rules
clean:
	$(RM) -r "./$(OBJ)"

cleanall: clean
	$(RM) "./$(APP)"
