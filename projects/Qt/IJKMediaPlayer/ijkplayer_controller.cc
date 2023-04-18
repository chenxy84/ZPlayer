#include "ijkplayer_controller.h"

#ifdef __cplusplus
extern "C" {
#endif   

// #include "ijksdl/android/ijksdl_android.h"
//#include "ijkplayer/ff_fferror.h"
//#include "ijkplayer/ff_ffplay.h"
//#include "ijkplayer/ijkplayer_internal.h"
#include "ijkplayer_qt.h"
// #include "../pipeline/ffpipeline_ffplay.h"
// #include "pipeline/ffpipeline_android.h"

#ifdef __cplusplus
}
#endif

static int msg_loop(void *) {

    return 0;
}

IJKMediaPlayerController::IJKMediaPlayerController() {
    ijkmp_global_init();
    mp_ = ijkmp_qt_create(msg_loop);
}

IJKMediaPlayerController::~IJKMediaPlayerController() {
    ijkmp_stop(mp_);
    ijkmp_shutdown(mp_);
}


void IJKMediaPlayerController::SetSource(std::string url) {
    url_ = url;
}
void IJKMediaPlayerController::Prepare() {
    ijkmp_set_data_source((mp_), url_.c_str());
    ijkmp_prepare_async(mp_);
    
}
void IJKMediaPlayerController::Play() {

}
void IJKMediaPlayerController::Stop() {

}
void IJKMediaPlayerController::Pause() {

}
void IJKMediaPlayerController::Seek(long ts) {
    
}
