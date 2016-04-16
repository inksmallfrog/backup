.PHONY: all test_mode

RM = rm
RMFLAGS = -fr

CC = gcc
CCFLAGS = -Wall

OBJS_DIR = $(ROOT)/build/$(MODULE)/objs
DEPS_DIR = $(ROOT)/build/$(MODULE)/deps
RELEASE_DIR = $(ROOT)/release
TEST_DIR = $(ROOT)/test/$(MODULE)

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
OBJS := $(addprefix $(OBJS_DIR)/, $(OBJS))
DEPS = $(SRCS:.c=.dep)
DEPS := $(addprefix $(DEPS_DIR)/, $(DEPS))

ifneq ($(TEST), "")
TEST := $(addprefix $(TEST_DIR)/, $(TEST))
all: test_mode
-include $(DEPS)
release_mode:
test_mode: $(TEST)
else
all:
release_mode:
test_mode:
endif

$(TEST): $(OBJS)
	$(CC) $(CCFLAGS) -o $@ $^

$(OBJS_DIR)/%.o: %.c
	$(CC) $(CCFLAGS) -o $@ -c $^

$(DEPS_DIR)/%.dep: %.c
	@echo "Making $@ ..."
	@set -e;\
	$(RM) $(RMFLAGS) $@.tmp ;\
	$(CC) -E -MM $^ > $@.tmp ;\
	sed 's,\(.*\)\.o[:]*,objs/\1.o $@:,g' < $@.tmp > $@ ;\
	$(RM) $(RMFLAGS) $@.tmp
