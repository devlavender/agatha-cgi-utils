//SPDX-License-Identifier: AGPL-3.0

/**
 * Copyright (C) 2024 - Ágatha Isabelle Chris Moreira Guedes
 *
 * Author: Ágatha Isabelle Chris Moreira Guedes <code@agatha.dev>
 * 
 * @file dumper.c
 * @description: dumps request data into a file
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
#include <strings.h>
#include <time.h>
#include <stdlib.h>
#include <inttypes.h>
#include <assert.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

#include "request-utils.h"
#include "dumper/dumper.h"

char *generate_uuid();
struct dump_file *get_random_dumpfile();
void free_dump_file(struct dump_file *outf);
void copy_stream(FILE *in, FILE *out);

int main(int argc, char **argv, char **envp)
{
        struct environment *env = NULL;
        struct env_var *ev = NULL;
        int ret = DUMPER_EXIT_OKAY;
        //char *post_data = NULL;
        struct dump_file *out_file = NULL;

        printf("Content-type: text/plain\r\n\r\n");

        env = create_environment();

        if (env == NULL) {
                perror("Error creating environment");
                ret = DUMPER_ENV_ALLOC_ERROR;
                goto return_ret;
        }

        ret = parse_environment(env, envp);

        if (ret < PARSE_SUCCESS) {
                perror("Error creating environment");
                goto destroy_env_bef_return;
        }

        /*post_data = read_post_request(stdin);
        if (post_data == NULL) {
                perror("Error reading POST data");
                ret = DUMPER_IO_ERROR;
                goto destroy_env_bef_return;
        }*/

        out_file = get_random_dumpfile();

        if (out_file == NULL) {
                perror("Error getting random dumpfile");
                ret = DUMPER_OUTPUT_ERROR;
                goto destroy_env_bef_return;
        }

        ev = env->first;
        while (ev != NULL) {
                fprintf(out_file->handler,
                        "%s=%s\n",
                        ev->variable,
                        ev->value);
                ev = ev->next;
        }

        fprintf(out_file->handler, "\n\nPOST DATA:\n");
        copy_stream(stdin, out_file->handler);

        free_dump_file(out_file);

        ret = DUMPER_EXIT_OKAY;

destroy_env_bef_return:
        destroy_environment(env);

return_ret:
        return ret;

}

char *generate_uuid()
{
        char *ret = NULL;
        uint16_t rand_word = 0x0000;
        char *curptr = NULL;
        int count = 0;

        ret = malloc(UUID_BUFFER_SIZE);
        if (ret == NULL) {
                perror("Error allocating uuid memory:");
                return ret;
        }

        bzero(ret, UUID_BUFFER_SIZE);

        srandom(time(NULL));

        curptr = ret;

        while (curptr-ret < UUID_MAX_CURPTR) {
                rand_word = (uint16_t) random() & UUID_RAND_MASK;
                count = snprintf(curptr, UUID_STEP_BUFFER_SIZE,
                                "%04" PRIx16, rand_word);

                if (count != UUID_STEP_SIZE) {
                        fprintf(stderr,
                                "snprintf printed %d characters "
                                "instead of %zu!\n", count,
                                UUID_STEP_SIZE);
                }
                if (count < 0) {
                        perror("Error generating random sequence");
                        break;
                }

                assert(count == UUID_STEP_SIZE);

                curptr += count;

        }

        return ret;

}

struct dump_file *get_random_dumpfile()
{
        struct dump_file *ret = NULL;
        int status = 0;
        ret = malloc(sizeof(struct dump_file));

        if (ret == NULL) {
                perror("Error allocating dump file mem");
                return ret;
        }

        bzero(ret, sizeof(struct dump_file));

        ret->uuid = generate_uuid();
        ret->path = malloc(PATH_MAX);

        fprintf(stdout, "UUID: %s\n", ret->uuid);

        if (ret->path == NULL) {
                perror("Error allocating path string");
                goto get_random_dumpfile_err_dealloc;
        }

        status = snprintf(ret->path,
                PATH_MAX,
                DUMP_FILE_OUTPUT_FMT,
                ret->uuid);
        
        if (status < 0) {
                perror("Error producing path");
                goto get_random_dumpfile_err_dealloc;
        }

        ret->handler = fopen(ret->path, "w+");
        if (ret->handler == NULL) {
                perror("Error opening file");
                goto get_random_dumpfile_err_dealloc;
        }

        return ret; //Success!

get_random_dumpfile_err_dealloc:
        free_dump_file(ret);
        return NULL;
}

void free_dump_file(struct dump_file *outf)
{
        if (outf == NULL) {
                return;
        }

        if (outf->handler != NULL) {
                fclose(outf->handler);
        }

        if (outf->path != NULL) {
                free(outf->path);
        }

        if (outf->uuid != NULL) {
                free(outf->uuid);
        }

        free(outf);
}

void copy_stream(FILE *in, FILE *out)
{
        char buffer[CHUNK_SIZE];
        size_t count_in = 0;
        size_t count_out = 0;

        if (in == NULL || out == NULL) {
                fprintf(stderr,
                        "Invalid input or output stream "
                        "(in=%p, out=%p)\n",
                        in, out);
                return;
        }

        while (!feof(in)) {
                count_in = fread(buffer, 1, CHUNK_SIZE, in);
                count_out = fwrite(buffer, 1, count_in, out);

                if (count_out < count_in) {
                        perror("Couldn't write everything in buffer");
                        fprintf(stderr, "Retrying...\n");
                        count_out += fwrite(buffer+count_out,
                                        1, count_out-count_in, out);
                        if (count_out < count_in) {
                                perror("Can't write everything again");
                                fprintf(stderr, "Aborted!\n");
                                return;
                        }
                }

        }
}