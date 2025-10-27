# Makefile
#
# (C) Copyright 2025 @NachtsternBuild
#
# Main makefile for the UI base

# include the language makefile
include Dependencies.mk
include language.mk

.DEFAULT_GOAL := all

CC = ccache gcc

INCLUDES = -I. -Iinclude -I$(BUILD_DIR)
PKG_CFLAGS = $(shell pkg-config --cflags glib-2.0 gtk4 libadwaita-1 libsecret-1 vte-2.91-gtk4)
PKG_LIBS = $(shell pkg-config --libs glib-2.0 gtk4 libadwaita-1 libsecret-1 vte-2.91-gtk4)

CFLAGS = -Wall $(PKG_CFLAGS) $(INCLUDES)
LIBS = $(PKG_LIBS)

HEADERS = $(shell find . -name '*.h')
OBJ_CLEAN = $(shell find . -name '*.o')

# Zielnamen
TARGET_CLI = hamilton_cli
TARGET_GUI = hamilton_gui
TARGETS = $(TARGET_CLI) $(TARGET_GUI)

# source definition
SRC_ALL = $(shell find . -name '*.c')

SRC_GUI_ONLY = $(filter %GUI.c, $(SRC_ALL))
SRC_CORE = $(filter-out $(SRC_GUI_ONLY), $(SRC_ALL))

# filter fil4es
SRC_CLI_MAIN = $(filter %main.c, $(SRC_CORE))
SRC_GUI_LINK = $(filter-out $(SRC_CLI_MAIN), $(SRC_ALL))

# objectfiles
OBJS_GUI = $(SRC_GUI_ONLY:.c=.o)
OBJS_CORE = $(SRC_CORE:.c=.o)
OBJS_GUI_LINK = $(SRC_GUI_LINK:.c=.o)


.PHONY: all objects clean po depends prepare cli gui

all: prepare $(TARGETS)

# create no UI
$(TARGET_CLI): $(OBJS_CORE)
	$(CC) $^ -o $@ $(LIBS) 

# create UI target
$(TARGET_GUI): $(OBJS_GUI_LINK)
	$(CC) $^ -o $@ $(LIBS)

# create the object files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# running language makefile
po: lang

# cleanup
clean:
	rm -f $(OBJS_CORE) $(OBJS_GUI) $(TARGETS) 
	rm -rf locale
	rm -f $(POTFILE)
	@for lang in $(LINGUAS); do \
		rm -f $(LOCALEDIR)/$$lang/LC_MESSAGES/$(PACKAGE).mo; \
		rm -rf $(LOCALEDIR)/$$lang; \
	done
	rm -rf $(TMP_DIR)
	#rm -rf $(BUILD_DIR)
	#rm -rf $(DEBBUILD_TARGET) 
