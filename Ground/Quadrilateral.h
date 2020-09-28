#pragma once
#include "geometry.h"

GROUND_NAMESPACE_START

class GROUND_EXPORT Quadrilateral :  public Geometry
{
public:
	Quadrilateral(void);
	~Quadrilateral(void);
	virtual void CreateOsgFromGeos(osg::Node* pNode);
	virtual void SetCoordinateTransform(CoordinateTransform* pCT);
	void SetOsgArray(osg::Vec3Array* coodinateArray);
	void SetOsgColorArray(osg::Vec4Array &colorArray );
	virtual void TransformGeometry();
	inline geom::GeometryTypeId GetGeometryType(){return geom::GEOS_POLYGON;}
	inline void setGlenum(GLenum mode){m_mode = mode;};
	inline void setTess(bool tess){b_tess = tess;}

	virtual void operator=(const Quadrilateral& other);

	virtual Geometry* Clone();

private:
	bool b_tess;
	osg::ref_ptr<osg::Vec3Array> m_coodArray;
	osg::ref_ptr<osg::Vec4Array> m_colorArray;
	GLenum m_mode;
};

GROUND_NAMESPACE_END