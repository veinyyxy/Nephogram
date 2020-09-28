#pragma once
/** @file		Mark.h
* @brief		
* @author		杨晓宇
* @date			2013.4
* @version		1.0
  @note			
*/

#include "geometry.h"

GROUND_NAMESPACE_START

/** @class  MultiLineString
    @brief  多线的实现，就是线条的集合
    @author 杨晓宇
    @note   成员功能参见接口类。
*/
class GROUND_EXPORT MultiLineString : public Geometry
{
public:
	MultiLineString(void);
	MultiLineString(geom::Geometry* geometry, CoordinateTransform* pCT = 0, Layer* pL = 0);
	virtual ~MultiLineString(void);
	virtual void CreateOsgFromGeos(osg::Node* pNode);
	virtual void SetCoordinateTransform(CoordinateTransform* pCT);
	virtual void TransformGeometry();
	inline geom::GeometryTypeId GetGeometryType(){return geom::GEOS_MULTILINESTRING;}

	virtual void operator=(const MultiLineString& other);

	virtual Geometry* Clone();

};

GROUND_NAMESPACE_END