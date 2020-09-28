#include "CoordinateTransform.h"
GROUND_NAMESPACE_START

CoordinateTransform::CoordinateTransform(void):m_lat(0.0),m_lon(0.0)
{
	m_TransType = CoordinateTransform::UNKNOW;
}

CoordinateTransform::~CoordinateTransform(void)
{
	
}
GROUND_NAMESPACE_END