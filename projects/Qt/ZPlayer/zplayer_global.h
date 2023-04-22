#ifndef ZPLAYER_GLOBAL_H
#define ZPLAYER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ZPLAYER_LIBRARY)
#  define ZPLAYER_EXPORT Q_DECL_EXPORT
#else
#  define ZPLAYER_EXPORT Q_DECL_IMPORT
#endif

#endif // ZPLAYER_GLOBAL_H
