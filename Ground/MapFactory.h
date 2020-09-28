#pragma once
#include "Config.h"
#include "Map.h"

GROUND_NAMESPACE_START
class MapFactory
{
public:
	virtual Map* CreateMap() = 0;
};
GROUND_NAMESPACE_END