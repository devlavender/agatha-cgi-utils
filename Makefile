#SPDX-License-Identifier: AGPL-3.0

# Copyright (C) 2024 - Ágatha Isabelle Chris Moreira Guedes

# Author: Ágatha Isabelle Chris Moreira Guedes <code@agatha.dev>

# file: Makefile
# description: general build for agatha-cgi-utils

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

PREFIX ?= /srv/cgi
PKGDIR ?= $(PREFIX)/agatha-cgi-utils
CFGDIR ?= $(PKGDIR)/etc
DATADIR ?= $(PKGDIR)/data
TMPDIR ?= $(DATADIR)/tmp

DEBUG ?= 0

# Set DEBUG flags and define macros based on the DEBUG level
ifeq ($(DEBUG),1)
	CFLAGS += -D__DEBUG=1 -g1
else ifeq ($(DEBUG),2)
	CFLAGS += -D__DEBUG=2 -g2
else ifeq ($(DEBUG),3)
	CFLAGS += -D__DEBUG=3 -g3
endif

# Include directory
INCLUDEDIR = $(PWD)/include

# Compiler flags
CFLAGS += -I$(INCLUDEDIR) \
	-D__PREFIX=\"$(PREFIX)\" \
	-D__PKGDIR=\"$(PKGDIR)\" \
	-D__CFGDIR=\"$(CFGDIR)\" \
	-Werror -Wall 

.PHONY: all clean install uninstall

# Default target that builds in src/
all:
	$(MAKE) -C src CFLAGS='$(CFLAGS)'

# Clean target
clean:
	$(MAKE) -C src clean

# Install target
install:
	$(MAKE) -C src install PREFIX=$(PREFIX)
	mkdir -p $(TMPDIR)
	chmod 777 $(TMPDIR)

# Uninstall target
uninstall:
	$(MAKE) -C src uninstall PREFIX=$(PREFIX)
