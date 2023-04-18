/*
 * ijkplayer_android.c
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

#include "ijkplayer_qt.h"

#include <assert.h>
// #include "ijksdl/android/ijksdl_android.h"
#include "ff_fferror.h"
#include "ff_ffplay.h"
#include "ijkplayer_internal.h"
// #include "../pipeline/ffpipeline_ffplay.h"
 #include "pipeline/ffpipeline_qt.h"

IjkMediaPlayer *ijkmp_qt_create(int(*msg_loop)(void*))
{
    IjkMediaPlayer *mp = ijkmp_create(msg_loop);
    if (!mp)
        goto fail;

//     mp->ffplayer->vout = SDL_VoutAndroid_CreateForAndroidSurface();
//     if (!mp->ffplayer->vout)
//         goto fail;

     mp->ffplayer->pipeline = ffpipeline_create_from_qt(mp->ffplayer);
     if (!mp->ffplayer->pipeline)
         goto fail;

    // ffpipeline_set_vout(mp->ffplayer->pipeline, mp->ffplayer->vout);

    return mp;

fail:
    ijkmp_dec_ref_p(&mp);
    return NULL;
}

void ijkmp_qt_set_surface_l(IjkMediaPlayer *mp, void* surface)
{
    if (!mp || !mp->ffplayer || !mp->ffplayer->vout)
        return;

    //TODO 
    //SDL_VoutAndroid_SetAndroidSurface(mp->ffplayer->vout, surface);
    //ffpipeline_set_surface(mp->ffplayer->pipeline, surface);

}

void ijkmp_qt_set_surface(IjkMediaPlayer *mp, void* surface)
{
    if (!mp)
        return;

    MPTRACE("ijkmp_set_android_surface(surface=%p)", (void*)surface);
    pthread_mutex_lock(&mp->mutex);
    ijkmp_qt_set_surface_l(mp, surface);
    pthread_mutex_unlock(&mp->mutex);
    MPTRACE("ijkmp_set_android_surface(surface=%p)=void", (void*)surface);
}

void ijkmp_qt_set_volume(IjkMediaPlayer *mp, float left, float right)
{
    if (!mp)
        return;

    MPTRACE("ijkmp_android_set_volume(%f, %f)", left, right);
    pthread_mutex_lock(&mp->mutex);

    if (mp && mp->ffplayer && mp->ffplayer->pipeline) {
        //TODO 
        //ffpipeline_set_volume(mp->ffplayer->pipeline, left, right);
    }

    pthread_mutex_unlock(&mp->mutex);
    MPTRACE("ijkmp_android_set_volume(%f, %f)=void", left, right);
}

// int ijkmp_android_get_audio_session_id(JNIEnv *env, IjkMediaPlayer *mp)
// {
//     int audio_session_id = 0;
//     if (!mp)
//         return audio_session_id;

//     MPTRACE("%s()", __func__);
//     pthread_mutex_lock(&mp->mutex);

//     if (mp && mp->ffplayer && mp->ffplayer->aout) {
//         audio_session_id = SDL_AoutGetAudioSessionId(mp->ffplayer->aout);
//     }

//     pthread_mutex_unlock(&mp->mutex);
//     MPTRACE("%s()=%d", __func__, audio_session_id);

//     return audio_session_id;
// }

// void ijkmp_android_set_mediacodec_select_callback(IjkMediaPlayer *mp, bool (*callback)(void *opaque, ijkmp_mediacodecinfo_context *mcc), void *opaque)
// {
//     if (!mp)
//         return;

//     MPTRACE("ijkmp_android_set_mediacodec_select_callback()");
//     pthread_mutex_lock(&mp->mutex);

//     if (mp && mp->ffplayer && mp->ffplayer->pipeline) {
//         ffpipeline_set_mediacodec_select_callback(mp->ffplayer->pipeline, callback, opaque);
//     }

//     pthread_mutex_unlock(&mp->mutex);
//     MPTRACE("ijkmp_android_set_mediacodec_select_callback()=void");
// }
