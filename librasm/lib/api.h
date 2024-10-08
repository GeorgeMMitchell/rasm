#ifndef RASM_API_H
#define RASM_API_H

#if defined(RASM_LIB_SHARED) && defined(_WIN32)
#ifdef RASM_LIB
#define RASM_API __declspec(dllexport)
#else
#define RASM_API __declspec(dllimport)
#endif
#else
#define RASM_API extern
#endif

#endif
