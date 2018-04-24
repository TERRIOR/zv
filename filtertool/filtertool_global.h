#ifndef FILTERTOOL_GLOBAL_H
#define FILTERTOOL_GLOBAL_H

#if defined(FILTERTOOL_LIBRARY)
#  define FILTERTOOLSHARED_EXPORT __declspec(dllexport)
#else
#  define FILTERTOOLSHARED_EXPORT __declspec(dllimport)
#endif

#endif // FILTERTOOL_GLOBAL_H
