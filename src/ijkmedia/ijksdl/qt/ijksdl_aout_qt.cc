/*
 * ijksdl_aout_ios_audiounit.m
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

#include "ijksdl_aout_qt.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "ijksdl/ijksdl_inc_internal.h"
#include "ijksdl/ijksdl_thread.h"
#include "ijksdl/ijksdl_aout_internal.h"
#ifdef __cplusplus
}
#endif


#include <stdbool.h>
#include <assert.h>

// #import "IJKSDLAudioUnitController.h"
// #import "IJKSDLAudioQueueController.h"
#include <QAudioFormat>
#include <QAudioOutput>


#define SDL_QT_AUDIO_MAX_CALLBACKS_PER_SEC 20

struct SDL_Aout_Opaque {
    //IJKSDLAudioQueueController *aoutController;
    SDL_cond   *wakeup_cond;
    SDL_mutex  *wakeup_mutex;
    
    SDL_AudioSpec spec;
    //ADD QAudioOutput
    uint8_t *buffer;
    int buffer_size;
    
    
    volatile bool need_flush;
    volatile bool pause_on;
    volatile bool abort_request;

    SDL_Thread *audio_tid;
    SDL_Thread _audio_tid;
    
    volatile bool need_set_volume;
    volatile float left_volume;
    volatile float right_volume;
    
    volatile float speed;
    volatile bool speed_changed;
};

static int aout_thread(void *arg)
{
    SDL_Aout *aout = (SDL_Aout *)arg;
    SDL_Aout_Opaque *opaque = aout->opaque;
//    SDL_Android_AudioTrack *atrack = opaque->atrack;
    SDL_AudioCallback audio_cblk = opaque->spec.callback;
    void *userdata = opaque->spec.userdata;
    uint8_t *buffer = opaque->buffer;
    int copy_size = 256;

//    assert(atrack);
    assert(buffer);

    SDL_SetThreadPriority(SDL_THREAD_PRIORITY_HIGH);

    if (!opaque->abort_request && !opaque->pause_on){
//        SDL_Android_AudioTrack_play(env, atrack);
    }


    while (!opaque->abort_request) {
        SDL_LockMutex(opaque->wakeup_mutex);
        if (!opaque->abort_request && opaque->pause_on) {
//            SDL_Android_AudioTrack_pause(env, atrack);
            while (!opaque->abort_request && opaque->pause_on) {
                SDL_CondWaitTimeout(opaque->wakeup_cond, opaque->wakeup_mutex, 1000);
            }
            if (!opaque->abort_request && !opaque->pause_on) {
                if (opaque->need_flush) {
                    opaque->need_flush = 0;
//                    SDL_Android_AudioTrack_flush(env, atrack);
                }
//                SDL_Android_AudioTrack_play(env, atrack);
            }
        }
        if (opaque->need_flush) {
            opaque->need_flush = 0;
//            SDL_Android_AudioTrack_flush(env, atrack);
        }
        if (opaque->need_set_volume) {
            opaque->need_set_volume = 0;
//            SDL_Android_AudioTrack_set_volume(env, atrack, opaque->left_volume, opaque->right_volume);
        }
        if (opaque->speed_changed) {
            opaque->speed_changed = 0;
//            SDL_Android_AudioTrack_setSpeed(env, atrack, opaque->speed);
        }
        SDL_UnlockMutex(opaque->wakeup_mutex);

        audio_cblk(userdata, buffer, copy_size);
        if (opaque->need_flush) {
//            SDL_Android_AudioTrack_flush(env, atrack);
            opaque->need_flush = false;
        }

        if (opaque->need_flush) {
            opaque->need_flush = 0;
//            SDL_Android_AudioTrack_flush(env, atrack);
        } else {
//            int written = SDL_Android_AudioTrack_write(env, atrack, buffer, copy_size);
//            if (written != copy_size) {
//                ALOGW("AudioTrack: not all data copied %d/%d", (int)written, (int)copy_size);
//            }
        }

        // TODO: 1 if callback return -1 or 0
    }

//    SDL_Android_AudioTrack_free(env, atrack);
    return 0;
}

static int aout_open_audio(SDL_Aout *aout, const SDL_AudioSpec *desired, SDL_AudioSpec *obtained)
{
    assert(desired);
    SDL_Aout_Opaque *opaque = aout->opaque;

    opaque->spec = *desired;
//    opaque->atrack = SDL_Android_AudioTrack_new_from_sdl_spec(env, desired);
//    if (!opaque->atrack) {
//        ALOGE("aout_open_audio_n: failed to new AudioTrcak()");
//        return -1;
//    }

//    opaque->buffer_size = SDL_Android_AudioTrack_get_min_buffer_size(opaque->atrack);
//    if (opaque->buffer_size <= 0) {
//        ALOGE("aout_open_audio_n: failed to getMinBufferSize()");
//        SDL_Android_AudioTrack_free(env, opaque->atrack);
//        opaque->atrack = NULL;
//        return -1;
//    }

//    opaque->buffer = malloc(opaque->buffer_size);
//    if (!opaque->buffer) {
//        ALOGE("aout_open_audio_n: failed to allocate buffer");
//        SDL_Android_AudioTrack_free(env, opaque->atrack);
//        opaque->atrack = NULL;
//        return -1;
//    }

//    if (obtained) {
//        SDL_Android_AudioTrack_get_target_spec(opaque->atrack, obtained);
//        SDLTRACE("audio target format fmt:0x%x, channel:0x%x", (int)obtained->format, (int)obtained->channels);
//    }

//    opaque->audio_session_id = SDL_Android_AudioTrack_getAudioSessionId(env, opaque->atrack);
//    ALOGI("audio_session_id = %d\n", opaque->audio_session_id);

    opaque->pause_on = 1;
    opaque->abort_request = 0;
    opaque->audio_tid = SDL_CreateThreadEx(&opaque->_audio_tid, aout_thread, aout, "ff_aout_android");
//    if (!opaque->audio_tid) {
//        ALOGE("aout_open_audio_n: failed to create audio thread");
//        SDL_Android_AudioTrack_free(env, opaque->atrack);
//        opaque->atrack = NULL;
//        return -1;
//    }

    return 0;
}

static void aout_pause_audio(SDL_Aout *aout, int pause_on)
{
    SDLTRACE("aout_pause_audio(%d)\n", pause_on);
    SDL_Aout_Opaque *opaque = aout->opaque;

    // if (pause_on) {
    //     [opaque->aoutController pause];
    // } else {
    //     [opaque->aoutController play];
    // }
}

static void aout_flush_audio(SDL_Aout *aout)
{
    SDLTRACE("aout_flush_audio()\n");
    SDL_Aout_Opaque *opaque = aout->opaque;

    // [opaque->aoutController flush];
}

static void aout_close_audio(SDL_Aout *aout)
{
    SDLTRACE("aout_close_audio()\n");
    SDL_Aout_Opaque *opaque = aout->opaque;

    // [opaque->aoutController close];
}

static void aout_set_playback_rate(SDL_Aout *aout, float playbackRate)
{
    SDLTRACE("aout_close_audio()\n");
    SDL_Aout_Opaque *opaque = aout->opaque;

    // [opaque->aoutController setPlaybackRate:playbackRate];
}

static void aout_set_playback_volume(SDL_Aout *aout, float volume)
{
    SDLTRACE("aout_set_volume()\n");
    SDL_Aout_Opaque *opaque = aout->opaque;

    // [opaque->aoutController setPlaybackVolume:volume];
}

static double auout_get_latency_seconds(SDL_Aout *aout)
{
    SDL_Aout_Opaque *opaque = aout->opaque;
    return 0;//[opaque->aoutController get_latency_seconds];
}

static int aout_get_persecond_callbacks(SDL_Aout *aout)
{
    return SDL_QT_AUDIO_MAX_CALLBACKS_PER_SEC;
}

static void aout_free_l(SDL_Aout *aout)
{
    if (!aout)
        return;

    aout_close_audio(aout);

    SDL_Aout_Opaque *opaque = aout->opaque;
    if (opaque) {
        // [opaque->aoutController release];
        // opaque->aoutController = nil;
    }

    SDL_Aout_FreeInternal(aout);
}

SDL_Aout *SDL_Aout_Qt_Create()
{
    SDL_Aout *aout = SDL_Aout_CreateInternal(sizeof(SDL_Aout_Opaque));
    if (!aout)
        return NULL;

    SDL_Aout_Opaque *opaque = aout->opaque;
    opaque->wakeup_cond  = SDL_CreateCond();
    opaque->wakeup_mutex = SDL_CreateMutex();
    opaque->speed        = 1.0f;

    aout->free_l = aout_free_l;
    aout->open_audio  = aout_open_audio;
    aout->pause_audio = aout_pause_audio;
    aout->flush_audio = aout_flush_audio;
    aout->close_audio = aout_close_audio;

    aout->func_set_playback_rate = aout_set_playback_rate;
    aout->func_set_playback_volume = aout_set_playback_volume;
    aout->func_get_latency_seconds = auout_get_latency_seconds;
    aout->func_get_audio_persecond_callbacks = aout_get_persecond_callbacks;
    return aout;
}
