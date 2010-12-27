#if !defined SL_LE_gui_slOpenGL_h
#define SL_LE_gui_slOpenGL_h

#include <le/core/config/slCompiler.h>

#if LE_TARGET_PLATFORM_FAMILY == LE_PLATFORM_FAMILY_WINDOWS
#	include <windows.h>
#	if LE_TARGET_PLATFORM == LE_PLATFORM_WINDOWS_CE
#		include "es/inc/glutes.h"
#	else
#		include <gl/gl.h>
#	endif
#elif LE_TARGET_PLATFORM == LE_PLATFORM_MACOSX
#	include <OpenGL/OpenGL.h>
#	include <OpenGL/glu.h>
#elif LE_TARGET_PLATFORM == LE_PLATFORM_IOS
#	include <OpenGLES/ES1/gl.h>
#	include <OpenGLES/ES2/gl.h>

// glOrtho function is defined as glOrthof in OpenGL ES
#define glOrtho glOrthof

#endif

#endif // not defined SL_LE_gui_slOpenGL_h
