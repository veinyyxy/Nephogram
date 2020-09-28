#pragma once
#include <Windows.h>
/////////////////////////////////STL Header/////////////////////////////////////////
#include <string>
#include <map>
#include <sstream>
/////////////////////////////////OSG Header/////////////////////////////////////////
#include <osg/Vec3d>
#include <osg/Vec3>
#include <osg/Array>
#include <osg/Geometry>
#include <osgViewer/Viewer>
#include <osg/Node>
#include <osgDB/ReadFile>
#include <osgUtil/Optimizer>

#include <osgGA/StateSetManipulator>
/////////////////////////////////GEOS Header/////////////////////////////////////////
#include <geos/geom/Geometry.h>
#include <geos/geom/GeometryFactory.h>
#include <geos/geom/CoordinateSequence.h>
using namespace geos;

#include "Ground_Global.h"

#define GROUND_NAMESPACE_START namespace nephogram_ground{
#define GROUND_NAMESPACE_END }