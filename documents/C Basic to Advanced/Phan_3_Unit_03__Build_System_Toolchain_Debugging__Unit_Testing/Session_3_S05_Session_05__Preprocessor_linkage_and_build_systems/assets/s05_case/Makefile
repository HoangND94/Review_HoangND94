CC ?= gcc
AR ?= ar
CPPFLAGS := -Iinclude
CFLAGS := -std=c17 -O0 -g -Wall -Wextra -Wpedantic -Werror -MMD -MP
BUILD := build-make
OBJECT := $(BUILD)/gateway.o
DEPS := $(OBJECT:.o=.d)

.PHONY: all clean test

all: $(BUILD)/libgateway_core.a $(BUILD)/gateway_demo

$(BUILD):
	mkdir -p $@

$(OBJECT): src/gateway.c include/gateway.h include/gateway_events.def | $(BUILD)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD)/libgateway_core.a: $(OBJECT)
	$(AR) rcs $@ $^

$(BUILD)/gateway_demo: apps/demo.c $(BUILD)/libgateway_core.a
	$(CC) $(CPPFLAGS) $(CFLAGS) $< $(BUILD)/libgateway_core.a -o $@

test: all
	$(BUILD)/gateway_demo

clean:
	rm -rf -- $(BUILD)

-include $(DEPS)
