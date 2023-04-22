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
#include "ff_fferror.h"
#include "ff_ffplay.h"
#include "ijkplayer_internal.h"
 #include "pipeline/ffpipeline_qt.h"
#include "ijksdl/qt/ijksdl_vout_qt.h"

IjkMediaPlayer *ijkmp_qt_create(int(*msg_loop)(void*))
{
    IjkMediaPlayer *mp = ijkmp_create(msg_loop);
    if (!mp)
        goto fail;

     mp->ffplayer->vout = SDL_Vout_Qt_ForOpenGL();
     if (!mp->ffplayer->vout)
         goto fail;

     mp->ffplayer->pipeline = ffpipeline_create_from_qt(mp->ffplayer);
     if (!mp->ffplayer->pipeline)
         goto fail;

     ffpipeline_set_vout(mp->ffplayer->pipeline, mp->ffplayer->vout);

    return mp;

fail:
    ijkmp_dec_ref_p(&mp);
    return NULL;
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

void ijkmp_qt_set_glview_l(IjkMediaPlayer *mp, void *glView)
{
    assert(mp);
    assert(mp->ffplayer);
    assert(mp->ffplayer->vout);

    SDL_Vout_Qt_SetGLView(mp->ffplayer->vout, glView);
}

void ijkmp_qt_set_glview(IjkMediaPlayer *mp, void *glView)
{
    assert(mp);
    MPTRACE("ijkmp_qt_set_view(glView=%p)\n", (void*)glView);
    pthread_mutex_lock(&mp->mutex);
    ijkmp_qt_set_glview_l(mp, glView);
    pthread_mutex_unlock(&mp->mutex);
    MPTRACE("ijkmp_qt_set_view(glView=%p)=void\n", (void*)glView);
}
