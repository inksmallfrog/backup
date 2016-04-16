.PHONY: all release_mode test_mode make_each clean clean_build clean_test clean_release

MKDIR = mkdir
RM = rm
RMFLAGS = -fr

DIRS = $(wildcard src/*)
MODULS = $(notdir $(DIRS))
BASE_DIR = build test
BUILD_DIR = $(addprefix build/, $(MODULS))
TEST_DIR = $(addprefix test/, $(MODULS))
RELEASE_DIR = release

all: $(BASE_DIR) $(TEST_DIR) $(RELEASE_DIR) make_each

release_mode: $(BASE_DIR) $(RELEASE_DIR) make_each

test_mode: $(BASE_DIR) $(TEST_DIR) make_each

make_each: $(BUILD_DIR)
	@echo "$(ROOT)"
	@set -e;\
	for dir in $(DIRS);\
	do\
		cd $$dir && $(MAKE) $(MAKECMDGOALS);\
	done
	@echo ""
	@echo ":-) Completed!"
	@echo ""

$(BUILD_DIR):
	$(MKDIR) $@
	$(MKDIR) $@/objs
	$(MKDIR) $@/deps

$(TEST_DIR):
	$(MKDIR) $@

$(BASE_DIR) $(RELEASE_DIR):
	$(MKDIR) $@

clean: clean_build clean_test clean_release

clean_build:
	$(RM) $(RMFLAGS) $(BUILD_DIR)/*/*

clean_test:
	$(RM) $(RMFLAGS) $(TEST_DIR)/*

clean_release:
	$(RM) $(RMFLAGS) $(RELEASE_DIR)/*
