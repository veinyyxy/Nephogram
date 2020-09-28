#include <osgViewer/Viewer>
#include <osgEarth/EarthManipulator>
#include <osgEarth/Viewpoint>
#include "RadarCameraControler.h"


RadarCameraControler::RadarCameraControler(void) : m_pViewer(0)
{
}


RadarCameraControler::~RadarCameraControler(void)
{
}

void RadarCameraControler::ToRadarViewPort( double x, double y, double z, double heading_deg, double pitch_deg, double range )
{
	osgEarth::Util::EarthManipulator* pEM = new osgEarth::Util::EarthManipulator;
	m_pViewer->setCameraManipulator(pEM);

	osgEarth::Util::Viewpoint vp("vpname", x, y, z, heading_deg, pitch_deg, range);
	pEM->setViewpoint(vp);
}
