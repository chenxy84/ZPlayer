cmake_minimum_required(VERSION 3.5)

project(zplayer VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ROOT_PATH ../..)
message("Project root path = ${ROOT_PATH}")

set(SRC_PATH ${ROOT_PATH}/src)
set(PRJ_PATH ${ROOT_PATH}/projects)
set(LIB_PATH ${ROOT_PATH}/../third-party-libs/dist/Darwin/macOS_x86_64)

include_directories(
        ${SRC_PATH}
        ${SRC_PATH}/ijkmedia
        ${SRC_PATH}/ijkmedia/ijkplayer
        ${SRC_PATH}/ijkmedia/ijksdl
        ${SRC_PATH}/ijkmedia/ijkyuv/include
        ${SRC_PATH}/ijkmedia/ijksoundtouch
        ${SRC_PATH}/ijkmedia/ijksoundtouch/include
        ${LIB_PATH}/include
        )
        
include_directories(
        ${SRC_PATH}/ijkmedia/ijkplayer/qt
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
        ${SRC_PATH}/ijkmedia/ijkplayer/qt/pipeline/ffpipeline_qt.c
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

set(SOURCE_IJK_SDL_QT
        ${SRC_PATH}/ijkmedia/ijksdl/qt/ijksdl_thread_qt.h
        ${SRC_PATH}/ijkmedia/ijksdl/qt/ijksdl_thread_qt.c
        ${SRC_PATH}/ijkmedia/ijksdl/qt/ijksdl_aout_qt.h
        ${SRC_PATH}/ijkmedia/ijksdl/qt/ijksdl_aout_qt.cc
        ${SRC_PATH}/ijkmedia/ijksdl/qt/ijksdl_vout_qt.h
        ${SRC_PATH}/ijkmedia/ijksdl/qt/ijksdl_vout_qt.cc
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

set(ffmpeg_static_libs
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

# add_library(player_sdl_static
#         STATIC
# 
#         )
# 
# add_library(player_core_static
#         STATIC
#         ${SOURCE_IJK_MEDIA}
#         ${SOURCE_IJK_MEDIA_QT}
#         )

# add_library(player_core
#         SHARED
#         ${SOURCE_IJK_MEDIA}
#         ${SOURCE_IJK_MEDIA_QT}
#         )

# target_link_libraries(player_core
#         ${ffmpeg_static_libs}
#         yuv_static
#         player_sdl_static
#         )


set(ZPLAYER_SOURCE
    ZPlayer/zplayer_global.h
    ZPlayer/player_controller.cpp
    ZPlayer/player_controller.h
    ZPlayer/video_gl_widget.cpp
    ZPlayer/video_gl_widget.h
    IJKMediaPlayer/ijkplayer_controller.cc
    IJKMediaPlayer/ijkplayer_controller.h
)

add_library(zplayer SHARED
    ${ZPLAYER_SOURCE}
    ${SOURCE_IJK_MEDIA}
    ${SOURCE_IJK_MEDIA_QT}
    ${SOURCE_IJK_SDL}
    ${SOURCE_IJK_SDL_QT}
)

set(PROJECT_SOURCES
    PlayerDemo/main.cpp
    PlayerDemo/mainwindow.cpp
    PlayerDemo/mainwindow.h
    PlayerDemo/mainwindow.ui
)

include_directories(${CMAKE_SOURCE_DIR})

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets OpenGLWidgets Multimedia)

qt_add_executable(zplayer_demo
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)

## macOS deps libs

set(ZPLAYER_DEPS_LIBS
    iconv 
    m 
    dl 
    pthread
    z
    bz2
    "-framework AVFoundation"
    "-framework VideoToolbox" 
    "-framework CoreFoundation" 
    "-framework CoreMedia"
    "-framework CoreVideo"
    "-framework CoreServices"
)

target_link_libraries(zplayer PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::OpenGLWidgets
    Qt${QT_VERSION_MAJOR}::Multimedia
    ${ffmpeg_static_libs}
    yuv_static
    ${ZPLAYER_DEPS_LIBS}
)

target_link_libraries(zplayer_demo PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::OpenGLWidgets
    Qt${QT_VERSION_MAJOR}::Multimedia
    zplayer
)


set(MACOSX_BUNDLE_GUI_IDENTIFIER zplayer_demo.sdk.someone.vip)
set(MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION})
set(MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR})
set(MACOSX_BUNDLE_NAME ZPlayerDemo)

set_target_properties(zplayer_demo PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER ${MACOSX_BUNDLE_GUI_IDENTIFIER}
    MACOSX_BUNDLE_BUNDLE_VERSION ${MACOSX_BUNDLE_BUNDLE_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${MACOSX_BUNDLE_SHORT_VERSION_STRING}
    MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/PlayerDemo/Info.plist.in
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE FALSE
)

install(TARGETS zplayer_demo
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(zplayer_demo)
endif()
