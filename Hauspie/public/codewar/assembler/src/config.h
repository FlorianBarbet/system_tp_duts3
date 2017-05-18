#ifndef __CONFIG_H__
#define __CONFIG_H__


#ifndef QT_NO_DEBUG_OUTPUT
#ifdef CWASM_NO_DEBUG_OUTPUT
#define qDebug if (1); else qDebug
#endif
#endif


#endif
