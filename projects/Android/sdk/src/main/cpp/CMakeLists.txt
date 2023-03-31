cmake_minimum_required(VERSION 3.18)
project("player_sdk")

message("Build player_sdk for ${CMAKE_ANDROID_ARCH_ABI}")

set(ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../..)
message("Project root path = ${ROOT_PATH}")

set(SRC_PATH ${ROOT_PATH}/src)
set(LIB_PATH ${ROOT_PATH}/../third-party-libs/dist/Android)

include_directories(
        ${SRC_PATH}
        ${SRC_PATH}/ijkmedia
        ${SRC_PATH}/ijkmedia/ijkj4a
        ${SRC_PATH}/ijkmedia/ijkplayer
        ${SRC_PATH}/ijkmedia/ijksdl
        ${SRC_PATH}/ijkmedia/ijkyuv/include
        ${SRC_PATH}/ijkmedia/ijksoundtouch
        ${SRC_PATH}/ijkmedia/ijksoundtouch/include
        ${SRC_PATH}/ijkprof/android-ndk-profiler-dummy/jni
        ${LIB_PATH}/${CMAKE_ANDROID_ARCH_ABI}/include
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
#        ${SRC_PATH}/ijkmedia/ijkplayer/ijkavformat/ijklas.c
#        ${SRC_PATH}/ijkmedia/ijkplayer/ijkavformat/ijklivehook.c
#        ${SRC_PATH}/ijkmedia/ijkplayer/ijkavformat/ijkmediadatasource.c
#        ${SRC_PATH}/ijkmedia/ijkplayer/ijkavformat/ijkio.c
#        ${SRC_PATH}/ijkmedia/ijkplayer/ijkavformat/ijkiomanager.c
#        ${SRC_PATH}/ijkmedia/ijkplayer/ijkavformat/ijkiocache.c
#        ${SRC_PATH}/ijkmedia/ijkplayer/ijkavformat/ijkioffio.c
#        ${SRC_PATH}/ijkmedia/ijkplayer/ijkavformat/ijkioandroidio.c
#        ${SRC_PATH}/ijkmedia/ijkplayer/ijkavformat/ijkioprotocol.c
#        ${SRC_PATH}/ijkmedia/ijkplayer/ijkavformat/ijkioapplication.c
#        ${SRC_PATH}/ijkmedia/ijkplayer/ijkavformat/ijkiourlhook.c
#        ${SRC_PATH}/ijkmedia/ijkplayer/ijkavformat/hls_multi_bitrate.c

#        ${SRC_PATH}/ijkmedia/ijkplayer/ijkavformat/ijkasync.c
#        ${SRC_PATH}/ijkmedia/ijkplayer/ijkavformat/ijkurlhook.c
#        ${SRC_PATH}/ijkmedia/ijkplayer/ijkavformat/ijklongurl.c
#        ${SRC_PATH}/ijkmedia/ijkplayer/ijkavformat/ijksegment.c

        ${SRC_PATH}/ijkmedia/ijkplayer/ijkavutil/ijkdict.c
        ${SRC_PATH}/ijkmedia/ijkplayer/ijkavutil/ijkutils.c
        ${SRC_PATH}/ijkmedia/ijkplayer/ijkavutil/ijkthreadpool.c
        ${SRC_PATH}/ijkmedia/ijkplayer/ijkavutil/ijktree.c
        ${SRC_PATH}/ijkmedia/ijkplayer/ijkavutil/ijkfifo.c
        ${SRC_PATH}/ijkmedia/ijkplayer/ijkavutil/ijkstl.cpp
        )

set(SOURCE_IJK_MEDIA_ANDROID
        ${SRC_PATH}/ijkmedia/ijkplayer/android/ffmpeg_api_jni.c
        ${SRC_PATH}/ijkmedia/ijkplayer/android/ijkplayer_android.c
        ${SRC_PATH}/ijkmedia/ijkplayer/android/ijkplayer_jni.c

        ${SRC_PATH}/ijkmedia/ijkplayer/android/pipeline/ffpipeline_android.c
        ${SRC_PATH}/ijkmedia/ijkplayer/android/pipeline/ffpipenode_android_mediacodec_vdec.c
        )

set(SOURCE_IJK_J4A
        ${SRC_PATH}/ijkmedia/ijkj4a/j4a/j4a_allclasses.c
        ${SRC_PATH}/ijkmedia/ijkj4a/j4a/j4a_base.c
        ${SRC_PATH}/ijkmedia/ijkj4a/j4a/class/android/media/AudioTrack.c
        ${SRC_PATH}/ijkmedia/ijkj4a/j4a/class/android/media/MediaCodec.c
        ${SRC_PATH}/ijkmedia/ijkj4a/j4a/class/android/media/MediaFormat.c
        ${SRC_PATH}/ijkmedia/ijkj4a/j4a/class/android/media/PlaybackParams.c
        ${SRC_PATH}/ijkmedia/ijkj4a/j4a/class/android/os/Build.c
        ${SRC_PATH}/ijkmedia/ijkj4a/j4a/class/android/os/Bundle.c
        ${SRC_PATH}/ijkmedia/ijkj4a/j4a/class/java/nio/Buffer.c
        ${SRC_PATH}/ijkmedia/ijkj4a/j4a/class/java/nio/ByteBuffer.c
        ${SRC_PATH}/ijkmedia/ijkj4a/j4a/class/java/util/ArrayList.c
        ${SRC_PATH}/ijkmedia/ijkj4a/j4a/class/tv/danmaku/ijk/media/player/misc/IMediaDataSource.c
        ${SRC_PATH}/ijkmedia/ijkj4a/j4a/class/tv/danmaku/ijk/media/player/misc/IAndroidIO.c
        ${SRC_PATH}/ijkmedia/ijkj4a/j4a/class/tv/danmaku/ijk/media/player/IjkMediaPlayer.c

        ${SRC_PATH}/ijkmedia/ijkj4a/j4au/class/android/media/AudioTrack.util.c
        ${SRC_PATH}/ijkmedia/ijkj4a/j4au/class/java/nio/ByteBuffer.util.c
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
        ${SRC_PATH}/ijkmedia/ijksdl/ijksdl_extra_log.c
        ${SRC_PATH}/ijkmedia/ijksdl/gles2/color.c
        ${SRC_PATH}/ijkmedia/ijksdl/gles2/common.c
        ${SRC_PATH}/ijkmedia/ijksdl/gles2/renderer.c
        ${SRC_PATH}/ijkmedia/ijksdl/gles2/renderer_rgb.c
        ${SRC_PATH}/ijkmedia/ijksdl/gles2/renderer_yuv420p.c
        ${SRC_PATH}/ijkmedia/ijksdl/gles2/renderer_yuv444p10le.c
        ${SRC_PATH}/ijkmedia/ijksdl/gles2/shader.c
        ${SRC_PATH}/ijkmedia/ijksdl/gles2/fsh/rgb.fsh.c
        ${SRC_PATH}/ijkmedia/ijksdl/gles2/fsh/yuv420p.fsh.c
        ${SRC_PATH}/ijkmedia/ijksdl/gles2/fsh/yuv444p10le.fsh.c
        ${SRC_PATH}/ijkmedia/ijksdl/gles2/vsh/mvp.vsh.c

        ${SRC_PATH}/ijkmedia/ijksdl/dummy/ijksdl_vout_dummy.c

        ${SRC_PATH}/ijkmedia/ijksdl/ffmpeg/ijksdl_vout_overlay_ffmpeg.c
        ${SRC_PATH}/ijkmedia/ijksdl/ffmpeg/abi_all/image_convert.c
        )

set(SOURCE_IJK_SDL_ANDROID
        ${SRC_PATH}/ijkmedia/ijksdl/android/android_audiotrack.c
        ${SRC_PATH}/ijkmedia/ijksdl/android/android_nativewindow.c
        ${SRC_PATH}/ijkmedia/ijksdl/android/ijksdl_android_jni.c
        ${SRC_PATH}/ijkmedia/ijksdl/android/ijksdl_aout_android_audiotrack.c
        ${SRC_PATH}/ijkmedia/ijksdl/android/ijksdl_aout_android_opensles.c
        ${SRC_PATH}/ijkmedia/ijksdl/android/ijksdl_codec_android_mediacodec_dummy.c
        ${SRC_PATH}/ijkmedia/ijksdl/android/ijksdl_codec_android_mediacodec_internal.c
        ${SRC_PATH}/ijkmedia/ijksdl/android/ijksdl_codec_android_mediacodec_java.c
        ${SRC_PATH}/ijkmedia/ijksdl/android/ijksdl_codec_android_mediacodec.c
        ${SRC_PATH}/ijkmedia/ijksdl/android/ijksdl_codec_android_mediadef.c
        ${SRC_PATH}/ijkmedia/ijksdl/android/ijksdl_codec_android_mediaformat_java.c
        ${SRC_PATH}/ijkmedia/ijksdl/android/ijksdl_codec_android_mediaformat.c
        ${SRC_PATH}/ijkmedia/ijksdl/android/ijksdl_vout_android_nativewindow.c
        ${SRC_PATH}/ijkmedia/ijksdl/android/ijksdl_vout_android_surface.c
        ${SRC_PATH}/ijkmedia/ijksdl/android/ijksdl_vout_overlay_android_mediacodec.c
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

if("${CMAKE_ANDROID_ARCH_ABI}" STREQUAL "armeabi-v7a")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DLIBYUV_NEON")
        set(SOURCE_IJK_YUV
                ${SOURCE_IJK_YUV}
                ${SRC_PATH}/ijkmedia/ijkyuv/source/compare_neon.cc
                ${SRC_PATH}/ijkmedia/ijkyuv/source/rotate_neon.cc
                ${SRC_PATH}/ijkmedia/ijkyuv/source/row_neon.cc
                ${SRC_PATH}/ijkmedia/ijkyuv/source/scale_neon.cc
                )
elseif("${CMAKE_ANDROID_ARCH_ABI}" STREQUAL "arm64-v8a")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DLIBYUV_NEON")
        set(SOURCE_IJK_YUV
                ${SOURCE_IJK_YUV}
                ${SRC_PATH}/ijkmedia/ijkyuv/source/compare_neon64.cc
                ${SRC_PATH}/ijkmedia/ijkyuv/source/rotate_neon64.cc
                ${SRC_PATH}/ijkmedia/ijkyuv/source/row_neon64.cc
                ${SRC_PATH}/ijkmedia/ijkyuv/source/scale_neon64.cc
                )
endif()

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

set(SOURCE_IJK_PROF
        ${SRC_PATH}/ijkprof/android-ndk-profiler-dummy/jni/prof.c)

add_library(yuv_static
        STATIC
        ${SOURCE_IJK_YUV}
)

add_library(ijkj4a_static
        STATIC
        ${SOURCE_IJK_J4A}
        )

#find_package(${LIB_PATH}/lib/pkgconfig)
#pkg_search_module(avutil REQUIRED avutil)
#pkg_search_module(swscale REQUIRED swscale)
#pkg_search_module(swresample REQUIRED swresample)
#pkg_search_module(avcodec REQUIRED avcodec)
#pkg_search_module(avformat REQUIRED avformat)
#pkg_search_module(avfilter REQUIRED avfilter)
#
#pkg_search_module(ssl REQUIRED ssl)
#pkg_search_module(crypto REQUIRED crypto)

#add_library(ffmpeg SHARED IMPORTED)
#set_target_properties(
#        ffmpeg_shared
#        PROPERTIES IMPORTED_LOCATION
#        ${LIB_PATH}/${CMAKE_ANDROID_ARCH_ABI}/lib/libffmpeg.so
#)

link_directories(${LIB_PATH}/${CMAKE_ANDROID_ARCH_ABI}/lib)

add_library(player_sdl
        SHARED
        ${SOURCE_IJK_SDL}
        ${SOURCE_IJK_SDL_ANDROID}
        )

target_link_libraries(player_sdl
        ffmpeg
        ijkj4a_static
        yuv_static
        log
        android
        OpenSLES
        EGL
        GLESv2
        mediandk
        OpenMAXAL
#        avutil
#        swscale
#        swresample
#        avcodec
#        avformat
#        avfilter
#        ssl
#        crypto
        )

add_library(player_sdk
        SHARED
        player_sdk.cpp
        ${SOURCE_IJK_MEDIA}
        ${SOURCE_IJK_MEDIA_ANDROID}
        ${SOURCE_IJK_PROF}
        ${SOURCE_IJK_SOUNDTOUCH}
        )

target_link_libraries(player_sdk
        ffmpeg
        player_sdl
        log )
