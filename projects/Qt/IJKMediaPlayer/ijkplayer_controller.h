#pragma once

#ifdef __cplusplus
extern "C" {
#endif   

#include "ijkplayer/ijkplayer.h"
// #include "ijksdl/android/ijksdl_android.h"
#include "ijkplayer/ff_fferror.h"
#include "ijkplayer/ff_ffplay.h"
#include "ijkplayer/ijkplayer_internal.h"
// #include "../pipeline/ffpipeline_ffplay.h"
// #include "pipeline/ffpipeline_android.h"

#ifdef __cplusplus
}
#endif

class IJKMediaPlayerController {
public:
    IJKMediaPlayerController();
    virtual ~IJKMediaPlayerController();


private:
    IjkMediaPlayer *mp;

};