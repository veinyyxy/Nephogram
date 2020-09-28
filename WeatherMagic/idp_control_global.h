#ifndef IDP_CONTROL_GLOBAL_H
#define IDP_CONTROL_GLOBAL_H

#include <QtCore/qglobal.h>

#ifndef IDP_CONTROL_LIB
# define IDP_CONTROL_EXPORT Q_DECL_EXPORT
#else
# define IDP_CONTROL_EXPORT Q_DECL_IMPORT
#endif

typedef struct
{
	double fStart;
	double fEnd;
	int   nRed;
	int   nGreen;
	int   nBlue;
}COLORNODE_PRODUCT, *P_COLORNODE_PRODUCT;

typedef QVector<P_COLORNODE_PRODUCT>  COLORTABLE_VECTOR, *P_COLORTABLE_VECTOR;

#endif // IDP_CONTROL_GLOBAL_H

