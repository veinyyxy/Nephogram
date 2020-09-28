#pragma once
#include "geometry.h"
GROUND_NAMESPACE_START
	
class GROUND_EXPORT Point :	public Geometry
{
public:
	Point(void);
	Point(geom::Geometry* geometry, CoordinateTransform* pCT = 0, Layer* pL = 0);
	virtual ~Point(void);
	virtual void CreateOsgFromGeos(osg::Node* pNode);
	virtual void SetCoordinateTransform(CoordinateTransform* pCT);
	virtual void TransformGeometry();
	inline geom::GeometryTypeId GetGeometryType(){return geom::GEOS_POINT;}

	virtual void operator=(const Point& other);

	virtual Geometry* Clone();

};

GROUND_NAMESPACE_END