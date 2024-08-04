//SPDX-License-Identifier: AGPL-3.0

/**
 * Copyright (C) 2024 - Ágatha Isabelle Chris Moreira Guedes
 *
 * Author: Ágatha Isabelle Chris Moreira Guedes <code@agatha.dev>
 * 
 * @file request-utils.c
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "request-utils.h"

// create_environment
//ret = parse_environment(env, envp);
//destroy_environment(env);

struct environment *create_environment()
{
        return environment_alloc();
}

struct environment *environment_alloc()
{
        struct environment *ret = NULL;

        ret = malloc(sizeof(struct environment));

        if (ret == NULL) {
                perror("Error allocating environment");
                goto env_alloc_ret;
        }

        bzero(ret, sizeof(struct environment));

env_alloc_ret:
        return ret;
}

int environment_push(struct environment *ev, struct env_var *var)
{
        if (ev == NULL || var == NULL) {
                return ENVIRONMENT_INVALID;
        }

        var->next = NULL;
        var->environ = ev;

        if (ev->length == 0) {
                var->prev = NULL;
                ev->first = var;
                ev->last = var;
        }
        else {
                ev->last->next = var;
                var->prev = ev->last;
                ev->last = var;
        }

        return (int) ev->length++;
}

int environment_pop(struct environment *ev)
{
        struct env_var *destroy = NULL;

        if (ev == NULL) {
                return ENVIRONMENT_INVALID;
        }

        destroy = ev->last;

        if (destroy != NULL) {
                if (destroy->prev != NULL) {
                        destroy->prev->next = NULL;
                }
                
                ev->last = destroy->prev;
                env_var_free(destroy);
                ev->length--;
        }

        return ev->length;
}

int parse_environment(struct environment *env, char **envp)
{
        struct env_var *new_item = NULL;
        char **env_ptr = envp;
        int ret = 0;
        //size_t cur_len = 0;

        if (env == NULL || envp == NULL || *envp == NULL) {
                return ENVIRONMENT_INVALID;
        }

        while (*env_ptr) {
                new_item = env_var_alloc();
                //cur_len = env->length;
                if (new_item == NULL) {
                        perror("Env allocation error");
                        return ENVIRONMENT_MEMERROR;
                }

                if (parse_env_var(new_item, *env_ptr++) < 0) {
                        perror("Error parsing env var");
                        fprintf(stderr, "Value: %s\n", *(env_ptr-1));
                        env_var_free(new_item);
                        new_item = NULL;
                        continue;
                }

                environment_push(env, new_item);
                /*if (environment_push(env, new_item) <= cur_len) {
                        fprintf(stderr,
                                "Something went wrong popping "
                                "item %s\n", *(env_ptr-1));
                        continue;
                }*/

                ret++;
        }

        return ret;
}

void destroy_environment(struct environment *env)
{
        if (env == NULL) {
                return;
        }

        while(env->length) {
                environment_pop(env);
        }

        free_environment(env);

}

void free_environment (struct environment *env)
{
        if (env != NULL) {
                free(env);
        }
}

struct env_var *env_var_alloc()
{
        struct env_var *ret = NULL;

        ret = malloc(sizeof(struct env_var));
        if (ret == NULL) {
                perror("Env var allocation error");
                return NULL;
        }

        bzero(ret, sizeof(struct env_var));

        return ret;
}

int parse_env_var(struct env_var *ev, char *s)
{
        char *raw_var = NULL;
        char *ptr = NULL;

        if (ev == NULL || s == NULL) {
                return ENVIRONMENT_INVALID;
        }

        raw_var = strndup(s, MAX_ENV_VAR_LENGTH);
        if (raw_var == NULL) {
                perror("Error duplicating string");
                return ENVIRONMENT_MEMERROR;
        }

        ev->origin_key = s;
        ev->variable = raw_var;

        ptr = raw_var;
        while (*ptr != '=')
                ptr++;
        
        *ptr++ = '\0';

        ev->value = ptr;

        while(*ptr++);
        
        return ptr - raw_var;
}

void env_var_free(struct env_var *ev)
{
        if (ev == NULL) {
                return;
        }

        if (ev->variable != NULL) {
                free(ev->variable);
        }

        free(ev);
}