#include "Contour.h"
#include <osg/Array>
#include "geometry.h"

GROUND_NAMESPACE_START

Contour::Contour(void)
{
}


Contour::~Contour(void)
{
}

void Contour::CreateOsgFromGeos( osg::Node* pNode )
{
	osg::Vec3 srcVec3, destVec3;
	if(m_coodArray->empty()) return;
	osg::Geode* geode = pNode->asGeode();
	if(geode == 0) return;

	std::size_t csSize = m_coodArray->size();
	
	for(std::size_t scs = 0; scs < csSize; scs++)
	{
		srcVec3.set(m_coodArray->at(scs).x(),m_coodArray->at(scs).y(),m_coodArray->at(scs).z());

		if (GetBTransform())
		{
			m_pCoordinateTransform->Transform(srcVec3, destVec3);
		}
		else
		{
			destVec3 = srcVec3;
		}
		
		m_VertexArray->push_back(destVec3);
	}
	m_pOsgGeometry->setVertexArray(m_VertexArray);
	m_pOsgGeometry->setColorArray(m_ColorArray);
	m_pOsgGeometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINE_STRIP,0,csSize)); 
	m_pOsgGeometry->setColorBinding(osg::Geometry::BIND_PER_PRIMITIVE_SET);
	geode->addDrawable(m_pOsgGeometry);
}

void Contour::SetCoordinateTransform( CoordinateTransform* pCT )
{
	m_pCoordinateTransform = pCT;m_pCoordinateTransform = pCT;
}

geom::GeometryTypeId Contour::GetGeometryType()
{
	return (geom::GeometryTypeId)8;
}

void Contour::TransformGeometry()
{
	osg::Vec3 srcVec3, destVec3;
	if(m_coodArray->empty()) return;

	m_VertexArray->clear();

	std::size_t csSize = m_coodArray->size();

	for(std::size_t scs = 0; scs < csSize; scs++)
	{
		srcVec3.set(m_coodArray->at(scs).x(),m_coodArray->at(scs).y(),m_coodArray->at(scs).z());

		if (GetBTransform())
		{
			m_pCoordinateTransform->Transform(srcVec3, destVec3);
		}
		else
		{
			destVec3 = srcVec3;
		}

		m_VertexArray->push_back(destVec3);
	}

	m_pOsgGeometry->dirtyDisplayList();
	m_pOsgGeometry->dirtyBound();
}

void Contour::PushBackPoint( float x, float y, float z )
{
	m_coodArray->push_back(osg::Vec3(x, y, z));
}

void Contour::SetColor( float r, float g, float b, float a )
{
	m_ColorArray->push_back(osg::Vec4(r, g, b, a));
}

GROUND_NAMESPACE_END