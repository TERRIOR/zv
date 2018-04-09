#ifndef ZVDATABASE_GLOBAL_H
#define ZVDATABASE_GLOBAL_H

#if defined(ZVDATABASE_LIBRARY)
#  define ZVDATABASESHARED_EXPORT __declspec(dllexport)
#else
#  define ZVDATABASESHARED_EXPORT __declspec(dllimport)
#endif

#endif // ZVDATABASE_GLOBAL_H
