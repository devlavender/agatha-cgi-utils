#SPDX-License-Identifier: AGPL-3.0

# Copyright (C) 2024 - Ágatha Isabelle Chris Moreira Guedes

# Author: Ágatha Isabelle Chris Moreira Guedes <code@agatha.dev>

# file: src/dumper/Makefile
# description: build for agatha-cgi-utils' dumper tool

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

# Source files
SRC = dumper.c
OBJ = $(SRC:.c=.o)
TARGET = dumper.cgi

# Compiler and flags
CC ?= gcc
CFLAGS ?= -Wall -O2

# Installation directories
PREFIX ?= /srv/cgi
PKGDIR ?= $(PREFIX)/agatha-cgi-utils
BINDIR ?= $(PKGDIR)/bin

.PHONY: all clean install uninstall

# Default target
all: $(TARGET)

# Link the object files into the final executable
$(TARGET): $(OBJ)
	$(CC) "$(CFLAGS)" -o $@ $^ -L$(COMMON_DIR) -lagathacgi

# Compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target
clean:
	rm -f $(OBJ) $(TARGET)

# Install the binary
install: $(TARGET)
	install -d $(DESTDIR)$(BINDIR)
	install -m 0755 $(TARGET) $(DESTDIR)$(BINDIR)

# Uninstall the binary
uninstall:
	rm -f $(DESTDIR)$(BINDIR)/$(TARGET)
