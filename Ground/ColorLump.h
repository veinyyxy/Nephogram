#pragma once
/** @file		glColorLump.h
* @brief		
* @author		������
* @date			2013.7
* @version		1.0
  @note			
*/

GROUND_NAMESPACE_START

/** @class  goColorLump
    @brief  ɫ��ͼͼԪ������
    @author ������
    @note   ��ʱûʲô����
*/ 
class ColorLump :
	public Geometry
{
public:
	ColorLump(void);
	virtual ~ColorLump(void);

	virtual void CreateOsgFromGeos( osg::Node* pNode  );

	virtual void SetCoordinateTransform( CoordinateTransform* pCT );

	virtual geom::GeometryTypeId GetGeometryType();

	virtual void TransformGeometry();

};

GROUND_NAMESPACE_END