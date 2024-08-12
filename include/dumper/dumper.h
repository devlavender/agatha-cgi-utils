//SPDX-License-Identifier: AGPL-3.0

/**
 * Copyright (C) 2024 - Ágatha Isabelle Chris Moreira Guedes
 *
 * Author: Ágatha Isabelle Chris Moreira Guedes <code@agatha.dev>
 * 
 * @file dumper.h
 * @description: dumper utility main header file
 * 
 * *********************************************************************
 *
 *                          L  I  C  E  N  S  E
 *
 * *********************************************************************
 * This code is licensed under the GNU Affero General Public License
 * version 3 <https://www.gnu.org/licenses/agpl-3.0.html>.
 *
 * This file is part of agatha-cgi-utils.
 *
 * agatha-cgi-utils is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License
 * as published by the Free Software Foundation, in the version 3 of the
 * License.
 * 
 * agatha-cgi-utils is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Affero General Public License for more details.

 * You should have received a copy of the GNU Affero General Public
 * License along with agatha-cgi-utils. If not, see
 * <https://www.gnu.org/licenses/> and
 * <https://www.gnu.org/licenses/agpl-3.0.html>.
 * 
 **/

 #ifndef __DUMPER_H
 #define __DUMPER_H

 #include "cgi-config.h"

#define DUMPER_EXIT_OKAY 0x0000
#define DUMPER_ENV_ALLOC_ERROR 0x0001
#define DUMPER_ENV_PARSING_ERROR 0x0002
#define DUMPER_IO_ERROR 0x0004
#define DUMPER_OUTPUT_ERROR 0x0008

#define NULL_TERM_SIZE 1

#define UUID_LENGTH 16
#define UUID_BUFFER_SIZE UUID_LENGTH+NULL_TERM_SIZE
#define UUID_STEP_SIZE (sizeof(uint16_t) * 2)
#define UUID_STEP_BUFFER_SIZE UUID_STEP_SIZE+NULL_TERM_SIZE
#define UUID_MAX_CURPTR UUID_BUFFER_SIZE-UUID_STEP_SIZE
#define UUID_RAND_MASK 0xFFFF

#define DUMP_FILE_OUTPUT_BASE __TMPDIR "/dumper"
#define DUMP_FILE_OUTPUT_SUFFIX ".dump"
#define DUMP_FILE_OUTPUT_FMT DUMP_FILE_OUTPUT_BASE "/%s" DUMP_FILE_OUTPUT_SUFFIX

struct dump_file
{
        char *uuid;
        char *path;
        FILE *handler;
};

 #endif//__DUMPER_H