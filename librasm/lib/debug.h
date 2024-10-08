#ifndef RASM_DEBUG_H
#define RASM_DEBUG_H

#ifdef RASM_DEBUG
#ifdef NDEBUG
#undef NDEBUG
#endif
#include <assert.h>
#define RASM_DEBUG_ASSERT(expr) assert(expr)
#else
#define RASM_DEBUG_ASSERT(expr) ((void)0)
#endif

#endif
