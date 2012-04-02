/*
 * JACK Backend code for Carla
 * Copyright (C) 2011-2012 Filipe Coelho <falktx@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * For a full copy of the GNU General Public License see the COPYING file
 */

#ifndef CARLA_INCLUDES_H
#define CARLA_INCLUDES_H

#ifdef __WINE__
#define __socklen_t_defined
#define __WINE_WINSOCK2__
#define HRESULT LONG
#define Q_CORE_EXPORT
#define Q_GUI_EXPORT
#define QT_NO_STL
//#define _WIN32_X11_
#endif

#include <stdint.h>
#include <Qt>

#if defined (__GXX_EXPERIMENTAL_CXX0X__) && defined (__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6))
// nullptr is available
#else
#define nullptr (0)
#endif

#ifdef Q_OS_WIN
#  include <windows.h>
#  define sleep(t)  Sleep(t * 1000)
#  define msleep(t) Sleep(t)
#  define usleep(t) Sleep(t / 1000)
#else
#  include <dlfcn.h>
#  include <unistd.h>
#  define msleep(t) usleep(t * 1000)
#  ifndef __cdecl
#    define __cdecl
#  endif
#endif

// needed for qDebug/Warning/Critical sections
#if __WORDSIZE == 64
#  define P_INTPTR "%li"
#  define P_SIZE   "%lu"
#else
#  define P_INTPTR "%i"
#  define P_SIZE   "%u"
#endif

// set native binary type
#if defined(Q_OS_LINUX) || defined(Q_OS_DARWIN)
#  if __LP64__
#    define BINARY_NATIVE BINARY_UNIX64
#  else
#    define BINARY_NATIVE BINARY_UNIX32
#  endif
#elif defined(Q_OS_WIN)
#  ifdef Q_OS_WIN64
#    define BINARY_NATIVE BINARY_WIN64
#  else
#    define BINARY_NATIVE BINARY_WIN32
#   endif
#else
#  error Invalid build type
#endif

// don't export symbols if in bridge mode
#ifdef BUILD_BRIDGE
#  define CARLA_EXPORT
#else
#  ifdef Q_OS_WIN
#    define CARLA_EXPORT extern "C" __declspec (dllexport)
#  else
#    define CARLA_EXPORT extern "C" __attribute__ ((visibility("default")))
#  endif
#endif

#endif // CARLA_INCLUDES_H
