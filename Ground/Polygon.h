#pragma once
#include "geometry.h"

GROUND_NAMESPACE_START

class GROUND_EXPORT Polygon :	public Geometry
{
public:
	Polygon(void);
	Polygon(geom::Geometry* geometry, CoordinateTransform* pCT = 0, Layer* pL = 0);
	virtual ~Polygon(void);
	virtual void CreateOsgFromGeos(osg::Node* pNode);
	virtual void SetCoordinateTransform(CoordinateTransform* pCT);
	virtual void TransformGeometry();
	inline geom::GeometryTypeId GetGeometryType(){return geom::GEOS_POLYGON;}

	virtual void operator=(const Polygon& other);
	osg::Vec3Array* triangulizeGeometry(osg::Geometry* src);

	virtual Geometry* Clone();

private:
	geom::CoordinateSequence* pCoordinateSequence;
};

GROUND_NAMESPACE_END