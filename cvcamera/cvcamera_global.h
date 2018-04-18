#ifndef CVCAMERA_GLOBAL_H
#define CVCAMERA_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CVCAMERA_LIBRARY)
#  define CVCAMERASHARED_EXPORT Q_DECL_EXPORT
#else

#  define CVCAMERASHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // VCAMERA_GLOBAL_H
