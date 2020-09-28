#include "VectorLayer.h"
#include "Field.h"
#include "Geometry.h"
#include "Point.h"
#include "LinearRing.h"
#include "LineString.h"
#include "Polygon.h"
#include "MultiPoint.h"
#include "Mark.h"
#include "MultiLineString.h"
#include "MultiPolygon.h"

#include "DataProvider.h"

GROUND_NAMESPACE_START

VectorLayer::VectorLayer(DataProvider* data, CoordinateTransform* ct, int iNT) : Layer(data, ct, iNT)
{
	LayerType("VectorLayer");
	//m_coordTrans = new Proj4Transform;
}


VectorLayer::~VectorLayer(void)
{
}

int VectorLayer::CreateLayer( const std::string& filename )
{
	if(!m_dataProvider.get()) 
	{
		return false;
	}
	m_dataProvider->LoadFile(filename);
	return true;
}

void VectorLayer::TransformLayer()
{
	std::map<int, std::auto_ptr<Geometry>>::iterator goGeomIter = m_pgoGeometry->begin();
	while(goGeomIter != m_pgoGeometry->end())
	{
		Geometry* goGeom = goGeomIter->second.get();
		if(goGeom)
		{
			goGeom->SetCoordinateTransform(m_coordTrans);
			goGeom->TransformGeometry();
		}
		goGeomIter++;
	}
}

void VectorLayer::CreateLayerData()
{
	std::map<int, std::auto_ptr<Geometry>>::iterator goGeomIter = m_pgoGeometry->begin();
	while(goGeomIter != m_pgoGeometry->end())
	{
		Geometry* goGeom = goGeomIter->second.get();
		if(goGeom)
		{
			goGeom->SetCoordinateTransform(m_coordTrans);
			goGeom->SetParentLayer(this);
			goGeom->CreateOsgFromGeos(m_pNode);
		}
		goGeomIter++;
	}
}

void VectorLayer::operator=( const VectorLayer& other )
{
	*this = other;
}

GROUND_NAMESPACE_END