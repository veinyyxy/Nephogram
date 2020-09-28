#pragma once
#include "Map.h"
#include <osgViewer/Viewer>

class ControllerFrameContext
{
public:
	virtual osgViewer::Viewer* GetCurrentViewer() = 0;
	virtual nephogram_ground::Map* GetCurrentMap() = 0;
};

