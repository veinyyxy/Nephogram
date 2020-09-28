#pragma once
#include "Config.h"
#include "mapfactory.h"
#include "Map.h"

GROUND_NAMESPACE_START

class DefaultMapFactory :
	public MapFactory
{
public:
	virtual ~DefaultMapFactory(void);

	virtual Map* CreateMap();
	static MapFactory* Instantiate();
private:
	DefaultMapFactory(void);
	DefaultMapFactory(DefaultMapFactory&);
	void operator=(DefaultMapFactory&);
	static MapFactory* m_pMe;
};

GROUND_NAMESPACE_END