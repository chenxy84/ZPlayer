#ifndef FFPLAY__FF_FFPIPELINE_QT_H
#define FFPLAY__FF_FFPIPELINE_QT_H

#include "ijkplayer/ff_ffpipeline.h"

struct FFPlayer;

IJKFF_Pipeline *ffpipeline_create_from_qt(struct FFPlayer *ffp);

void ffpipeline_set_vout(IJKFF_Pipeline* pipeline, SDL_Vout *vout);

#endif
