cmake_minimum_required(VERSION 3.18)
project("player_core")

set(ROOT_PATH ../..)
message("Project root path = ${ROOT_PATH}")

set(SRC_PATH ${ROOT_PATH}/src)
set(LIB_PATH ${ROOT_PATH}/../third-party-libs/dist/Darwin/macOS_x86_64)

include_directories(
        ${SRC_PATH}
        ${SRC_PATH}/ijkmedia
        ${SRC_PATH}/ijkmedia/ijkj4a
        ${SRC_PATH}/ijkmedia/ijkplayer
        ${SRC_PATH}/ijkmedia/ijksdl
        ${SRC_PATH}/ijkmedia/ijkyuv/include
        ${SRC_PATH}/ijkmedia/ijksoundtouch
        ${SRC_PATH}/ijkmedia/ijksoundtouch/include
        ${LIB_PATH}/include
        )


set(SOURCE_IJK_MEDIA
        ${SRC_PATH}/ijkmedia/ijkplayer/ff_cmdutils.c
        ${SRC_PATH}/ijkmedia/ijkplayer/ff_ffplay.c
        ${SRC_PATH}/ijkmedia/ijkplayer/ff_ffpipeline.c
        ${SRC_PATH}/ijkmedia/ijkplayer/ff_ffpipenode.c
        ${SRC_PATH}/ijkmedia/ijkplayer/ijkmeta.c
        ${SRC_PATH}/ijkmedia/ijkplayer/ijkplayer.c

        ${SRC_PATH}/ijkmedia/ijkplayer/pipeline/ffpipeline_ffplay.c
        ${SRC_PATH}/ijkmedia/ijkplayer/pipeline/ffpipenode_ffplay_vdec.c

        ${SRC_PATH}/ijkmedia/ijkplayer/ijkavformat/allformats.c
        ${SRC_PATH}/ijkmedia/ijkplayer/ijkavformat/cJSON.c

        ${SRC_PATH}/ijkmedia/ijkplayer/ijkavutil/ijkdict.c
        ${SRC_PATH}/ijkmedia/ijkplayer/ijkavutil/ijkutils.c
        ${SRC_PATH}/ijkmedia/ijkplayer/ijkavutil/ijkthreadpool.c
        ${SRC_PATH}/ijkmedia/ijkplayer/ijkavutil/ijktree.c
        ${SRC_PATH}/ijkmedia/ijkplayer/ijkavutil/ijkfifo.c
        ${SRC_PATH}/ijkmedia/ijkplayer/ijkavutil/ijkstl.cpp
        )

set(SOURCE_IJK_MEDIA_QT
        ${SRC_PATH}/ijkmedia/ijkplayer/qt/ijkplayer_qt.c

#        ${SRC_PATH}/ijkmedia/ijkplayer/qt/pipeline/ffpipeline_qt.c
#        ${SRC_PATH}/ijkmedia/ijkplayer/qt/pipeline/ffpipenode_qt_mediacodec_vdec.c
        )

set(SOURCE_IJK_SDL
        ${SRC_PATH}/ijkmedia/ijksdl/ijksdl_aout.c
        ${SRC_PATH}/ijkmedia/ijksdl/ijksdl_audio.c
        ${SRC_PATH}/ijkmedia/ijksdl/ijksdl_egl.c
        ${SRC_PATH}/ijkmedia/ijksdl/ijksdl_error.c
        ${SRC_PATH}/ijkmedia/ijksdl/ijksdl_mutex.c
        ${SRC_PATH}/ijkmedia/ijksdl/ijksdl_stdinc.c
        ${SRC_PATH}/ijkmedia/ijksdl/ijksdl_thread.c
        ${SRC_PATH}/ijkmedia/ijksdl/ijksdl_timer.c
        ${SRC_PATH}/ijkmedia/ijksdl/ijksdl_vout.c

        ${SRC_PATH}/ijkmedia/ijksdl/dummy/ijksdl_vout_dummy.c

        ${SRC_PATH}/ijkmedia/ijksdl/ffmpeg/ijksdl_vout_overlay_ffmpeg.c
        ${SRC_PATH}/ijkmedia/ijksdl/ffmpeg/abi_all/image_convert.c
        )

set(SOURCE_IJK_YUV
        ${SRC_PATH}/ijkmedia/ijkyuv/source/compare.cc
        ${SRC_PATH}/ijkmedia/ijkyuv/source/compare_common.cc
        ${SRC_PATH}/ijkmedia/ijkyuv/source/compare_posix.cc
        ${SRC_PATH}/ijkmedia/ijkyuv/source/convert.cc
        ${SRC_PATH}/ijkmedia/ijkyuv/source/convert_argb.cc
        ${SRC_PATH}/ijkmedia/ijkyuv/source/convert_from.cc
        ${SRC_PATH}/ijkmedia/ijkyuv/source/convert_from_argb.cc
        ${SRC_PATH}/ijkmedia/ijkyuv/source/convert_to_argb.cc
        ${SRC_PATH}/ijkmedia/ijkyuv/source/convert_to_i420.cc
        ${SRC_PATH}/ijkmedia/ijkyuv/source/cpu_id.cc
        ${SRC_PATH}/ijkmedia/ijkyuv/source/format_conversion.cc
        ${SRC_PATH}/ijkmedia/ijkyuv/source/planar_functions.cc
        ${SRC_PATH}/ijkmedia/ijkyuv/source/rotate.cc
        ${SRC_PATH}/ijkmedia/ijkyuv/source/rotate_argb.cc
        ${SRC_PATH}/ijkmedia/ijkyuv/source/rotate_mips.cc
        ${SRC_PATH}/ijkmedia/ijkyuv/source/row_any.cc
        ${SRC_PATH}/ijkmedia/ijkyuv/source/row_common.cc
        ${SRC_PATH}/ijkmedia/ijkyuv/source/row_mips.cc
        ${SRC_PATH}/ijkmedia/ijkyuv/source/row_posix.cc
        ${SRC_PATH}/ijkmedia/ijkyuv/source/scale.cc
        ${SRC_PATH}/ijkmedia/ijkyuv/source/scale_argb.cc
        ${SRC_PATH}/ijkmedia/ijkyuv/source/scale_common.cc
        ${SRC_PATH}/ijkmedia/ijkyuv/source/scale_mips.cc
        ${SRC_PATH}/ijkmedia/ijkyuv/source/scale_posix.cc
        ${SRC_PATH}/ijkmedia/ijkyuv/source/video_common.cc
)


set(SOURCE_IJK_SOUNDTOUCH
        ${SRC_PATH}/ijkmedia/ijksoundtouch/source/SoundTouch/AAFilter.cpp
        ${SRC_PATH}/ijkmedia/ijksoundtouch/source/SoundTouch/FIFOSampleBuffer.cpp
        ${SRC_PATH}/ijkmedia/ijksoundtouch/source/SoundTouch/FIRFilter.cpp
        ${SRC_PATH}/ijkmedia/ijksoundtouch/source/SoundTouch/cpu_detect_x86.cpp
        ${SRC_PATH}/ijkmedia/ijksoundtouch/source/SoundTouch/sse_optimized.cpp
        ${SRC_PATH}/ijkmedia/ijksoundtouch/source/SoundTouch/RateTransposer.cpp
        ${SRC_PATH}/ijkmedia/ijksoundtouch/source/SoundTouch/InterpolateCubic.cpp
        ${SRC_PATH}/ijkmedia/ijksoundtouch/source/SoundTouch/InterpolateLinear.cpp
        ${SRC_PATH}/ijkmedia/ijksoundtouch/source/SoundTouch/InterpolateShannon.cpp
        ${SRC_PATH}/ijkmedia/ijksoundtouch/source/SoundTouch/TDStretch.cpp
        ${SRC_PATH}/ijkmedia/ijksoundtouch/source/SoundTouch/BPMDetect.cpp
        ${SRC_PATH}/ijkmedia/ijksoundtouch/source/SoundTouch/PeakFinder.cpp
        ${SRC_PATH}/ijkmedia/ijksoundtouch/source/SoundTouch/SoundTouch.cpp
        ${SRC_PATH}/ijkmedia/ijksoundtouch/source/SoundTouch/mmx_optimized.cpp
        ${SRC_PATH}/ijkmedia/ijksoundtouch/ijksoundtouch_wrap.cpp
)

link_directories(${LIB_PATH}/lib)
set(ffmpeg_libs
        avcodec
        avfilter
        avformat
        avutil
        swresample
        swscale
        crypto
        ssl
        x264
        )

add_library(yuv_static
        STATIC
        ${SOURCE_IJK_YUV}
)

add_library(player_sdl
        STATIC
        ${SOURCE_IJK_SDL}
        )

target_link_libraries(player_sdl
        yuv_static
        )

# add_library(player_core
#         STATIC
#         ${SOURCE_IJK_MEDIA}
#         )

add_library(player_core
        SHARED
        ${SOURCE_IJK_MEDIA}
        ${SOURCE_IJK_MEDIA_QT}
        )

target_link_libraries(player_core
        ${ffmpeg_libs}
        yuv_static
        player_sdl
        )