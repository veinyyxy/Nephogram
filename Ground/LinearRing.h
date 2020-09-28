#pragma once
/** @file		LinearRing.h
* @brief		
* @author		������
* @date			2013.4
* @version		1.0
  @note			
*/

#include "Geometry.h"

GROUND_NAMESPACE_START

/** @class  LinearRing
    @brief  GIS�ж�Ӧ���߻���
    @author ������
    @note   ��Ա���ܲμ��ӿ��ࡣ�������ĸ��ǽӿ��࣬��ؼ�������
*/
class GROUND_EXPORT LinearRing :public Geometry
{
public:
	LinearRing(void);
	LinearRing(geom::Geometry* geometry, CoordinateTransform* pCT = 0, Layer* pL = 0);
	virtual ~LinearRing(void);
	virtual void CreateOsgFromGeos(osg::Node* pNode);
	virtual void SetCoordinateTransform(CoordinateTransform* pCT);
	virtual void TransformGeometry();
	inline geom::GeometryTypeId GetGeometryType(){return geom::GEOS_LINEARRING;}

	virtual void operator=(const LinearRing& other);

	virtual Geometry* Clone();

};

GROUND_NAMESPACE_END