#pragma once
#include "Geometry.h"
GROUND_NAMESPACE_START
	
class GROUND_EXPORT MultiPoint :public Geometry
{
public:
	MultiPoint(void);
	MultiPoint(geom::Geometry* geometry, CoordinateTransform* pCT = 0, Layer* pL = 0);
	virtual ~MultiPoint(void);
	virtual void CreateOsgFromGeos(osg::Node* pNode);
	virtual void SetCoordinateTransform(CoordinateTransform* pCT);
	virtual void TransformGeometry();
	inline geom::GeometryTypeId GetGeometryType(){return geom::GEOS_MULTIPOINT;}

	virtual void operator=(const MultiPoint& other);

	virtual Geometry* Clone();

};

GROUND_NAMESPACE_END