#SPDX-License-Identifier: AGPL-3.0

# Copyright (C) 2024 - Ágatha Isabelle Chris Moreira Guedes

# Author: Ágatha Isabelle Chris Moreira Guedes <code@agatha.dev>

# file: src/Makefile
# description: general sources build for agatha-cgi-utils

########################################################################
#
#                            L  I  C  E  N  S  E
#
########################################################################

# This code is licensed under the GNU Affero General Public License
# version 3 <https://www.gnu.org/licenses/agpl-3.0.html>.

# This file is part of agatha-cgi-utils.

# agatha-cgi-utils is free software: you can redistribute it and/or
# modify it under the terms of the GNU Affero General Public License
# as published by the Free Software Foundation, in the version 3 of the
# License.
 
# agatha-cgi-utils is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# Affero General Public License for more details.

# You should have received a copy of the GNU Affero General Public
# License along with agatha-cgi-utils. If not, see
# <https://www.gnu.org/licenses/> and
# <https://www.gnu.org/licenses/agpl-3.0.html>.

# List of subdirectories to build
SUBDIRS = dumper

# Common sources
COMMON_SRC = request-utils.c
COMMON_OBJ = $(COMMON_SRC:.c=.o)
COMMON_LIB = libagathacgi.a
COMMON_DIR = $(PWD)/src

# Compiler and flags
CC ?= gcc
AR ?= ar
CFLAGS += -Werror -Wall

.PHONY: all clean install uninstall $(SUBDIRS)

# Default target builds the common library and all subdirectories
all: $(COMMON_LIB) $(SUBDIRS)

# Build the common library
$(COMMON_LIB): $(COMMON_OBJ)
	$(AR) rcs $@ $^

# Build each subdirectory
$(SUBDIRS): $(COMMON_LIB)
	$(MAKE) -C $@ CFLAGS='$(CFLAGS)' COMMON_DIR='$(COMMON_DIR)'

# Compile common source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -I../include -c $< -o $@

# Clean target
clean:
	rm -f $(COMMON_OBJ) $(COMMON_LIB)
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done

# Install target
install: $(COMMON_LIB)
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir install PREFIX=$(PREFIX); \
	done

# Uninstall target
uninstall:
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir uninstall PREFIX=$(PREFIX); \
	done
