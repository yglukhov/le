#if !defined SL_LE_glut_slGlut_h
#define SL_LE_glut_slGlut_h

#ifdef _WIN32
#	ifdef _WIN32_WCE
#		include "es/inc/glutes.h"
#	else
#		include "win32/glut.h"
#	endif
#else
#	include <GLUT/glut.h>
#endif

#endif // not defined SL_LE_glut_slGlut_h
