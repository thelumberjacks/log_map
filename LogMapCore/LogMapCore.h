#ifndef __LOGMAPCORE_H_
#define __LOGMAPCORE_H_

#pragma once

#ifdef _LOGMAPCORE_DLL_EXPORT
#define LOGMAPCORE_ImpExp _declspec(dllexport)
#else
#define LOGMAPCORE_ImpExp _declspec(dllimport)
#endif

#include "LogMap.h"
#include "Reader.h"

#endif //__LOGMAPCORE_H_