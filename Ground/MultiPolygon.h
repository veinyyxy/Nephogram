#pragma once
#include "Geometry.h"

GROUND_NAMESPACE_START
	
class GROUND_EXPORT MultiPolygon :public Geometry
{
public:
	MultiPolygon(void);
	MultiPolygon(geom::Geometry* geometry, CoordinateTransform* pCT = 0, Layer* pL = 0);
	virtual ~MultiPolygon(void);
	virtual void CreateOsgFromGeos(osg::Node* pNode);
	virtual void SetCoordinateTransform(CoordinateTransform* pCT);
	virtual void TransformGeometry();
	inline geom::GeometryTypeId GetGeometryType(){return geom::GEOS_MULTIPOLYGON;}

	virtual void operator=(const MultiPolygon& other);

	virtual Geometry* Clone();

};

GROUND_NAMESPACE_END