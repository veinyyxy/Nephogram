#include "geometry.h"
#include "ColorLump.h"

GROUND_NAMESPACE_START

ColorLump::ColorLump(void)
{
}


ColorLump::~ColorLump(void)
{
}

void ColorLump::CreateOsgFromGeos( osg::Node* pNode  )
{
	throw std::exception("The method or operation is not implemented.");
}

void ColorLump::SetCoordinateTransform( CoordinateTransform* pCT )
{
	throw std::exception("The method or operation is not implemented.");
}

geom::GeometryTypeId ColorLump::GetGeometryType()
{
	throw std::exception("The method or operation is not implemented.");
}

void ColorLump::TransformGeometry()
{
	throw std::exception("The method or operation is not implemented.");
}

GROUND_NAMESPACE_END