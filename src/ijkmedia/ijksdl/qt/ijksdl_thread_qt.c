/*
 * ijksdl_thread_ios.m
 *
 * Copyright (c) 2013 Bilibili
 * Copyright (c) 2013 Zhang Rui <bbcallen@gmail.com>
 *
 * This file is part of ijkPlayer.
 *
 * ijkPlayer is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * ijkPlayer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with ijkPlayer; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */
#include <string.h>
#include <pthread.h>
#include "ijksdl_thread_qt.h"
#include "ijksdl/ijksdl_thread.h"

static void *SDL_RunThread(void *data)
{
    SDL_Thread *thread = data;
//Fix by chenxiangyu
#if defined(__APPLE__)
    pthread_setname_np(thread->name);
#elif defined(__FreeBSD__)
    pthread_set_name_np(pthread_self(), thread->name);
#elif defined(__GLIBC__) && !defined(__MINGW32__)
    if (strlen(thread->name) <= 15) {
        pthread_setname_np(pthread_self(), thread->name);
    } else {
        char *thread_name = bstrdup_n(thread->name, 15);
        pthread_setname_np(pthread_self(), thread_name);
        bfree(thread_name);
    }
#endif
    
    thread->retval = thread->func(thread->data);
    return NULL;
}

SDL_Thread *SDL_CreateThreadEx(SDL_Thread *thread, int (*fn)(void *), void *data, const char *name)
{
    thread->func = fn;
    thread->data = data;
    strlcpy(thread->name, name, sizeof(thread->name) - 1);
    int retval = pthread_create(&thread->id, NULL, SDL_RunThread, thread);
    if (retval)
        return NULL;

    return thread;
}
