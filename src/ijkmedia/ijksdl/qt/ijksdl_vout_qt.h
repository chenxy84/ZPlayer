#pragma once

#ifdef __cplusplus
extern "C" {
#endif
#include "ijksdl/ijksdl_stdinc.h"
#include "ijksdl/ijksdl_vout.h"
SDL_Vout *SDL_Vout_Qt_ForOpenGL();
void SDL_Vout_Qt_SetGLView(SDL_Vout *vout, void *view);
#ifdef __cplusplus
}
#endif



