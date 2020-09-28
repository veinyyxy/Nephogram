#pragma once
/** @file		Contour.h
* @brief		
* @author		������
* @date			2013.7
* @version		1.0
  @note			
*/
#include "Config.h"
#include "Geometry.h"
GROUND_NAMESPACE_START

/** @class  DataProvider
    @brief  ��ֵ��������
    @author ������
    @note   ��ʱûʲô����
*/ 
class Contour :
	public Geometry
{
public:
	Contour(void);
	virtual ~Contour(void);

	virtual void CreateOsgFromGeos( osg::Node* pNode );

	virtual void SetCoordinateTransform( CoordinateTransform* pCT );

	virtual geom::GeometryTypeId GetGeometryType();

	virtual void TransformGeometry();

public:
	void PushBackPoint(float x, float y, float z);
	void SetColor(float r, float g, float b, float a);
private:
	osg::ref_ptr<osg::Vec3Array> m_coodArray;
	osg::ref_ptr<osg::Vec3Array> m_VertexArray;
	osg::ref_ptr<osg::Vec4Array> m_ColorArray;
};

GROUND_NAMESPACE_END