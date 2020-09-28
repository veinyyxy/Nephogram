#pragma once
#include "Config.h"
#include "VectorLayer.h"
#include "Layer.h"
#include "CoordinateTransform.h"
#include "PluginsManager.h"
#include "MapFactory.h"

class RectResult
{
public:
	virtual void FinishDraw(const osg::Vec3Array* pVec3Array) = 0;
};

GROUND_NAMESPACE_START

class GROUND_EXPORT Ground
{
public:
	virtual ~Ground(void);
	static Ground* Instantiate();
	static void Uninstantiate();

	int LoadProviderPlugins(const std::string& strConfigName);
	int LoadGisExtendPlugins(const std::string& strConfigName);
	void OpenDataAsLayer(const std::string& strDataName , Layer* layer);
	int DynamicLoadPugin(const std::string& strPlName);
	/*É¾³ýµÄº¯Êý*///Layer* OpenRadarDataAsLayer(const std::string& strDataName , Map* map = 0, CoordinateTransform* coords = 0);
	MapFactory* GetMapFactory();

private:
	Ground(void);
	Ground(Ground&){};
	void operator=(Ground&){};
	

private:
	static Ground* m_sGeosOnTheOsg;
	PluginsManager* m_pPluginManager;
	PluginsManager* m_pGisExtendPluginsManager;
};

GROUND_NAMESPACE_END