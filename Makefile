##
# Sorts
#
# @file
# @version 0.1

CC      := gcc
CCFLAGS := -Wall
LDFLAGS :=

TARGETS := sort
RUN     := $(addsuffix .run, $(TARGETS))
MAINS   := $(addsuffix .o, $(TARGETS))
_OBJ    := common bubble selection insertion shell merge quick heap radix
OBJ     := $(addprefix sorts/, $(addsuffix .o, $(_OBJ))) $(MAINS)
DEPS    := $(addprefix sorts/, $(addsuffix .h, $(_OBJ)))

.PHONY: all clean run

all: $(TARGETS)

clean:
	rm -f $(TARGETS) $(OBJ)

run: $(RUN)

$(RUN): %.run : %
	./$< $(ARGS)

$(OBJ): %.o : %.c $(DEPS)
	$(CC) -c -o $@ $< $(CCFLAGS)

$(TARGETS): % : $(filter-out $(MAINS), $(OBJ)) %.o
	$(CC) -o $@ $^ $(CCFLAGS) $(LDFLAGS)

# end
