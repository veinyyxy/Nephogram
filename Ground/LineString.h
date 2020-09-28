#pragma once
/** @file		LinearRing.h
* @brief		
* @author		杨晓宇
* @date			2013.4
* @version		1.0
  @note			
*/

#include "Geometry.h"
GROUND_NAMESPACE_START

/** @class  LineString
    @brief  GIS中对应的线段类
    @author 杨晓宇
    @note   成员功能参见接口类。不明白哪个是接口类，请回家卖红薯
*/
class GROUND_EXPORT LineString : public Geometry
{
public:
	LineString(void);
	LineString(geom::Geometry* geometry, CoordinateTransform* pCT = 0, Layer* pL = 0);
	//LineString(geom::CoordinateSequence* pCoordinateSequence, CoordinateTransform* pCT = 0, Layer* pL = 0);
	virtual ~LineString(void);
	virtual void CreateOsgFromGeos(osg::Node* pNode);
	virtual void SetCoordinateTransform(CoordinateTransform* pCT);
	virtual void TransformGeometry();
	inline geom::GeometryTypeId GetGeometryType(){return geom::GEOS_LINESTRING;}

	virtual void operator=(const LineString& other);

	virtual Geometry* Clone();

};

GROUND_NAMESPACE_END