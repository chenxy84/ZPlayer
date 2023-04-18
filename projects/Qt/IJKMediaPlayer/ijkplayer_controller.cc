#include "ijkplayer_controller.h"

#ifdef __cplusplus
extern "C" {
#endif   

// #include "ijksdl/android/ijksdl_android.h"
#include "ijkplayer/ff_fferror.h"
#include "ijkplayer/ff_ffplay.h"
#include "ijkplayer/ijkplayer_internal.h"
// #include "../pipeline/ffpipeline_ffplay.h"
// #include "pipeline/ffpipeline_android.h"

#ifdef __cplusplus
}
#endif

static int msg_loop(void *) {

    return 0;
}

IJKMediaPlayerController::IJKMediaPlayerController() {
    mp = ijkmp_create(msg_loop);
}

IJKMediaPlayerController::~IJKMediaPlayerController() {
    ijkmp_stop(mp);
    ijkmp_shutdown(mp);
}
