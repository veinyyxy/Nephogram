#include "Point.h"
#include <osg/Point>
#include "Layer.h"
GROUND_NAMESPACE_START
	
Point::Point(void)
{
}

Point::Point( geom::Geometry* geometry, CoordinateTransform* pCT /*= 0*/, Layer* pL /*= 0*/ )
	: Geometry(geometry, pCT, pL)
{
	m_pCoordinateSequence = m_pGeosGeomtry->getCoordinates();
}

Point::~Point(void)
{
}

void Point::CreateOsgFromGeos(osg::Node* pNode)
{
	osg::Vec3 srcVec3, destVec3;
	if(!m_pCoordinateTransform) return;
	osg::Geode* geode = pNode->asGeode();
	if(geode == 0) return;

	//geom::CoordinateSequence* pCoordinateSequence = m_pGeosGeomtry->getCoordinates();
	std::size_t csSize = m_pCoordinateSequence->getSize();
	osg::Vec3Array* pyramidVertices = new osg::Vec3Array;
	for(std::size_t scs = 0; scs < csSize; scs++)
	{
		srcVec3.set((*m_pCoordinateSequence)[scs].x,
		(*m_pCoordinateSequence)[scs].y, (*m_pCoordinateSequence)[scs].z);

		TransormPoint(srcVec3, destVec3);
		pyramidVertices->push_back(destVec3);
	}
	m_pOsgGeometry->setVertexArray(pyramidVertices);
	if(m_bUserLayerColor)
	{
		m_pColors->clear();
		m_pColors->push_back(m_pParentLayer->GetLayerColor());
		m_pOsgGeometry->setColorArray(m_pColors);
		m_pOsgGeometry->setColorBinding(osg::Geometry::BIND_OVERALL);
	}
	else
	{
		m_pOsgGeometry->setColorArray(m_pColors);
		m_pOsgGeometry->setColorBinding(osg::Geometry::BIND_OVERALL);
	}
	m_pOsgGeometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::POINTS,0,csSize)); 
	geode->addDrawable(m_pOsgGeometry);

	osg::StateSet* stateSet = m_pParentLayer->GetLayerNode()->getOrCreateStateSet();
	osg::ref_ptr <osg::Point> ptSize = new osg::Point;
	ptSize->setSize(m_pParentLayer->GeometrySize());      
	stateSet->setAttributeAndModes(ptSize, osg::StateAttribute::ON);
}

void Point::SetCoordinateTransform( CoordinateTransform* pCT )
{
	m_pCoordinateTransform = pCT;
}

void Point::TransformGeometry()
{
	osg::Vec3 srcVec3, destVec3;
	geom::CoordinateSequence* pCoordinateSequence = m_pGeosGeomtry->getCoordinates();
	std::size_t csSize = pCoordinateSequence->getSize();
	osg::Vec3Array* pyramidVertices  = dynamic_cast<osg::Vec3Array*>(m_pOsgGeometry->getVertexArray());
	pyramidVertices->clear();
	for (size_t scs = 0; scs<csSize; scs++)
	{
		srcVec3.set((*pCoordinateSequence)[scs].x,(*pCoordinateSequence)[scs].y, (*pCoordinateSequence)[scs].z);
		TransormPoint(srcVec3, destVec3);
		pyramidVertices->push_back(destVec3);
	}
	m_pOsgGeometry->dirtyDisplayList();
	m_pOsgGeometry->dirtyBound();
}

void Point::operator=( const Point& other )
{
	this->m_pGeosGeomtry.reset(other.m_pGeosGeomtry->clone());
	m_pCoordinateSequence = m_pGeosGeomtry->getCoordinates();
}

Geometry* Point::Clone()
{
	Point* pNewGeom = new Point();
	*pNewGeom = *this;
	return pNewGeom;
}

GROUND_NAMESPACE_END