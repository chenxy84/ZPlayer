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

#include <string>

class IJKMediaPlayerController {
public:
    IJKMediaPlayerController();
    virtual ~IJKMediaPlayerController();

    void SetSource(std::string url);
    void Prepare();
    void Stop();
    
    void Play();
    void Pause();
    
    void Seek(long ts);
    
    void SetDisplayView(void *view);

private:
    IjkMediaPlayer *mp_;
    std::string url_;

};
