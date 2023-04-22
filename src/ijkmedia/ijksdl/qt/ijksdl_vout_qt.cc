#import "ijksdl_vout_qt.h"

#ifdef __cplusplus
extern "C" {
#endif
#include <assert.h>
#include "ijksdl/ijksdl_vout.h"
#include "ijksdl/ijksdl_vout_internal.h"
#include "ijksdl/ffmpeg/ijksdl_vout_overlay_ffmpeg.h"

#ifdef __cplusplus
}
#endif

#include <QDebug>
#include "video_gl_widget.h"

typedef struct SDL_VoutSurface_Opaque {
    SDL_Vout *vout;
} SDL_VoutSurface_Opaque;

struct SDL_Vout_Opaque {
    OpenGLDisplay *gl_display;
};

static SDL_VoutOverlay *vout_create_overlay_l(int width, int height, int frame_format, SDL_Vout *vout)
{
//    switch (frame_format) {
//        case IJK_AV_PIX_FMT__VIDEO_TOOLBOX:
//            return SDL_VoutVideoToolBox_CreateOverlay(width, height, vout);
//        default:
//            return SDL_VoutFFmpeg_CreateOverlay(width, height, frame_format, vout);
//    }
    return SDL_VoutFFmpeg_CreateOverlay(width, height, frame_format, vout);
}

static SDL_VoutOverlay *vout_create_overlay(int width, int height, int frame_format, SDL_Vout *vout)
{
    SDL_LockMutex(vout->mutex);
    vout->overlay_format = SDL_FCC__GLES2;
    SDL_VoutOverlay *overlay = vout_create_overlay_l(width, height, frame_format, vout);
    SDL_UnlockMutex(vout->mutex);
    return overlay;
}

static void vout_free_l(SDL_Vout *vout)
{
    if (!vout)
        return;

    SDL_Vout_Opaque *opaque = vout->opaque;
    if (opaque) {
        if (opaque->gl_display) {
//            // TODO: post to MainThread?
//            [opaque->gl_view release];
//            opaque->gl_view = nil;
        }
    }

    SDL_Vout_FreeInternal(vout);
}

static int vout_display_overlay_l(SDL_Vout *vout, SDL_VoutOverlay *overlay)
{
    SDL_Vout_Opaque *opaque = vout->opaque;
    OpenGLDisplay *gl_view = opaque->gl_display;

    if (!gl_view) {
        ALOGE("vout_display_overlay_l: NULL gl_view\n");
        return -1;
    }

    if (!overlay) {
        ALOGE("vout_display_overlay_l: NULL overlay\n");
        return -1;
    }

    if (overlay->w <= 0 || overlay->h <= 0) {
        ALOGE("vout_display_overlay_l: invalid overlay dimensions(%d, %d)\n", overlay->w, overlay->h);
        return -1;
    }
    int size = overlay->w * overlay->h * 3 / 2;
    gl_view->InitDrawBuffer(size);
    gl_view->DisplayVideoFrame(overlay->pixels, overlay->pitches, overlay->w, overlay->h);
    /*
    if (gl_view.isThirdGLView) {
        IJKOverlay ijk_overlay;

        ijk_overlay.w = overlay->w;
        ijk_overlay.h = overlay->h;
        ijk_overlay.format = overlay->format;
        ijk_overlay.planes = overlay->planes;
        ijk_overlay.pitches = overlay->pitches;
        ijk_overlay.pixels = overlay->pixels;
        ijk_overlay.sar_num = overlay->sar_num;
        ijk_overlay.sar_den = overlay->sar_den;
#ifdef __APPLE__
        if (ijk_overlay.format == SDL_FCC__VTB) {
            ijk_overlay.pixel_buffer = SDL_VoutOverlayVideoToolBox_GetCVPixelBufferRef(overlay);
        }
#endif
        if ([gl_view respondsToSelector:@selector(display_pixels:)]) {
             [gl_view display_pixels:&ijk_overlay];
        }
    } else {
        [gl_view display:overlay];
    }
     */
    return 0;
}

static int vout_display_overlay(SDL_Vout *vout, SDL_VoutOverlay *overlay)
{
    
    SDL_LockMutex(vout->mutex);
    int retval = vout_display_overlay_l(vout, overlay);
    SDL_UnlockMutex(vout->mutex);
    return retval;
    
}

SDL_Vout *SDL_Vout_Qt_ForOpenGL()
{
    SDL_Vout *vout = SDL_Vout_CreateInternal(sizeof(SDL_Vout_Opaque));
    if (!vout)
        return NULL;

    SDL_Vout_Opaque *opaque = vout->opaque;
    opaque->gl_display = NULL;
    vout->create_overlay = vout_create_overlay;
    vout->free_l = vout_free_l;
    vout->display_overlay = vout_display_overlay;

    return vout;
}

static void SDL_Vout_Qt_SetGLView_l(SDL_Vout *vout, OpenGLDisplay *view)
{
    SDL_Vout_Opaque *opaque = vout->opaque;

    if (opaque->gl_display == view)
        return;

//    if (!opaque->gl_display) {
//        [opaque->gl_view release];
//        opaque->gl_view = nil;
        opaque->gl_display = view;
//    }

    if (view) {
        //opaque->gl_view = [view retain];
        //TODO chenxiangyu
    }
        
}

void SDL_Vout_Qt_SetGLView(SDL_Vout *vout, void *view)
{
    OpenGLDisplay *dispaly = (OpenGLDisplay *)view;
    SDL_LockMutex(vout->mutex);
    SDL_Vout_Qt_SetGLView_l(vout, dispaly);
    SDL_UnlockMutex(vout->mutex);
}
