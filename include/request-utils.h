//SPDX-License-Identifier: AGPL-3.0

/**
 * Copyright (C) 2024 - Ágatha Isabelle Chris Moreira Guedes
 *
 * Author: Ágatha Isabelle Chris Moreira Guedes <code@agatha.dev>
 * 
 * @file request-utils.h
 * @description: useful request-related data structures & functions
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

#ifndef __REQUEST_UTILS_H
#define __REQUEST_UTILS_H

#include <errno.h>

#include "cgi-config.h"

#define MAX_ENV_VAR_NAME_LENGTH 1024
#define MAX_ENV_VAR_VALUE_LENGTH 16386
#define MAX_ENV_VAR_LENGTH MAX_ENV_VAR_NAME_LENGTH + MAX_ENV_VAR_VALUE_LENGTH + 2

#define CHUNK_SIZE 1024

#define ENVIRONMENT_EMPTY 0x0001
#define ENVIRONMENT_INVALID 0x0002
#define ENVIRONMENT_MEMERROR 0x0004

enum environment_parse_status
{
        PARSE_SUCCESS = 0x00,
        PARSE_EINVAL = EINVAL,
        PARSE_ENOMEM = ENOMEM,
        PARSE_EUNKNOWN
};

struct environment;

struct env_var
{
        char *origin_key;
        char *variable;
        char *value;
        struct env_var *prev;
        struct env_var *next;
        struct environment *environ;
};

struct environment
{
        size_t length;
        struct env_var *first;
        struct env_var *last;
};


struct environment *environment_alloc();
void free_environment(struct environment *env);

struct environment *create_environment();
void destroy_environment(struct environment *env);

int parse_environment(struct environment *env, char **envp);

struct env_var *env_var_alloc();
void env_var_free(struct env_var *ev);

int parse_env_var(struct env_var *ev, char *s);

int environment_pop(struct environment *ev);
int environment_push(struct environment *ev, struct env_var *var);

//char *read_post_request(FILE *in_stream);

#endif//__REQUEST_UTILS_H