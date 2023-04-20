/*
 * ffpipeline_ios.c
 *
 * Copyright (c) 2014 Zhou Quan <zhouqicy@gmail.com>
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

#include "ffpipeline_qt.h"
//#include "ffpipenode_ios_videotoolbox_vdec.h"
#include "ijkplayer/pipeline/ffpipenode_ffplay_vdec.h"
#include "ff_ffplay.h"
#include "ijksdl/qt/ijksdl_aout_qt.h"

static SDL_Class g_pipeline_class = {
    .name = "ffpipeline_qt_media",
};

struct IJKFF_Pipeline_Opaque {
    FFPlayer    *ffp;
    SDL_mutex   *surface_mutex;
    
    SDL_Vout    *weak_vout;
};

static void func_destroy(IJKFF_Pipeline *pipeline)
{
    
}

inline static bool check_ffpipeline(IJKFF_Pipeline* pipeline, const char *func_name)
{
    if (!pipeline || !pipeline->opaque || !pipeline->opaque_class) {
        ALOGE("%s.%s: invalid pipeline\n", pipeline->opaque_class->name, func_name);
        return false;
    }

    if (pipeline->opaque_class != &g_pipeline_class) {
        ALOGE("%s.%s: unsupported method\n", pipeline->opaque_class->name, func_name);
        return false;
    }

    return true;
}

//TODO
static IJKFF_Pipenode *func_open_video_decoder(IJKFF_Pipeline *pipeline, FFPlayer *ffp)
{
    IJKFF_Pipenode* node = NULL;
    IJKFF_Pipeline_Opaque *opaque = pipeline->opaque;
    if (ffp->videotoolbox) {
//        node = ffpipenode_create_video_decoder_from_ios_videotoolbox(ffp);
        if (!node)
            ALOGE("vtb fail!!! switch to ffmpeg decode!!!! \n");
    }
    if (node == NULL) {
        node = ffpipenode_create_video_decoder_from_ffplay(ffp);
        ffp->stat.vdec_type = FFP_PROPV_DECODER_AVCODEC;
//        opaque->is_videotoolbox_open = false;
    } else {
        ffp->stat.vdec_type = FFP_PROPV_DECODER_VIDEOTOOLBOX;
//        opaque->is_videotoolbox_open = true;
    }
//    ffp_notify_msg2(ffp, FFP_MSG_VIDEO_DECODER_OPEN, opaque->is_videotoolbox_open);
    return node;
}

static SDL_Aout *func_open_audio_output(IJKFF_Pipeline *pipeline, FFPlayer *ffp)
{
    return SDL_Aout_Qt_Create();
}

IJKFF_Pipeline *ffpipeline_create_from_qt(FFPlayer *ffp)
{
    IJKFF_Pipeline *pipeline = ffpipeline_alloc(&g_pipeline_class, sizeof(IJKFF_Pipeline_Opaque));
    if (!pipeline)
        return pipeline;

    IJKFF_Pipeline_Opaque *opaque     = pipeline->opaque;
    opaque->ffp                       = ffp;
    pipeline->func_destroy            = func_destroy;
    pipeline->func_open_video_decoder = func_open_video_decoder;
    pipeline->func_open_audio_output  = func_open_audio_output;

    return pipeline;
}

void ffpipeline_set_vout(IJKFF_Pipeline* pipeline, SDL_Vout *vout)
{
    if (!check_ffpipeline(pipeline, __func__))
        return;

    IJKFF_Pipeline_Opaque *opaque = pipeline->opaque;
    opaque->weak_vout = vout;
}
