#include "ProviderPluginsManager.h"
#include "GisExtendPluginsManager.h"
#include "Ground.h"
#include "DefaultMapFactory.h"

GROUND_NAMESPACE_START

Ground* Ground::m_sGeosOnTheOsg = 0;

Ground::~Ground(void)
{
}

Ground* Ground::Instantiate()
{
	if(m_sGeosOnTheOsg == 0)
	{
		m_sGeosOnTheOsg = new Ground;
		return m_sGeosOnTheOsg;
	}
	else
		return m_sGeosOnTheOsg;
}

void Ground::Uninstantiate()
{
	if(m_sGeosOnTheOsg) delete m_sGeosOnTheOsg;
}


void Ground::OpenDataAsLayer(const std::string& strDataName , Layer* pNewLayer)
{
	//VectorLayer* pNewLayer = 0;
	
	int iCount = m_pPluginManager->GetDataProviderPluginCount();
	for(int i = 0; i < iCount; i++)
	{
		ProviderPluginsManager::MineData pMineData = (ProviderPluginsManager::MineData)(m_pPluginManager->GetMineFunctionFromID(i));
		if(pMineData == 0) continue;

		if(pMineData(strDataName))
		{
			ProviderPluginsManager::DataProviderPluginMain pCreatorMain = (ProviderPluginsManager::DataProviderPluginMain)(m_pPluginManager->GetDataProviderPluginFromID(i));
			if(!pCreatorMain) return;
			DataProvider* pDataProvider = pCreatorMain();
			if(!pDataProvider) return;

			char drive[_MAX_DRIVE] = {0};
			char dir[_MAX_DIR] = {0};
			char fname[_MAX_FNAME] = {0}; 
			char ext[_MAX_EXT] = {0};

			_splitpath( strDataName.c_str(), drive, dir, fname, ext );

			//pNewLayer = new VectorLayer;
			pNewLayer->SetDataProvider(pDataProvider);
			pDataProvider->ParentLayer(pNewLayer);
			int iRandRGB[3] = {0};
			for(int i = 0; i < 3; i++)
			{
				//(unsigned)time(NULL)
				//srand(255);
				int iCC = rand() % 255;
				iRandRGB[i] = iCC;
			}
			osg::Vec4 osgColor(iRandRGB[0] / 255.0, iRandRGB[1]/255.0, iRandRGB[2]/255.0, 1.0);
			pNewLayer->SetLayerColor(osgColor);
			pNewLayer->CreateLayer(strDataName);

			if(pNewLayer->LayerName().size() == 0)
			{
				pNewLayer->SetLayerName(fname);
			}
		}
	}
}


/*
Layer* GeosOnTheOsg::OpenRadarDataAsLayer(const std::string& strDataName , Map* map / *= 0* /, CoordinateTransform* coords / *= 0 * /)
{
	RadarVectorLayer* pNewLayer = 0;

	int iCount = m_pPluginManager->GetDataProviderPluginCount();
	for(int i = 0; i < iCount; i++)
	{
		ProviderPluginsManager::MineData pMineData = (ProviderPluginsManager::MineData)m_pPluginManager->GetMineFunctionFromID(i);
		if(pMineData == 0) continue;

		if(pMineData(strDataName))
		{
			ProviderPluginsManager::DataProviderPluginMain pCreatorMain = (ProviderPluginsManager::DataProviderPluginMain)m_pPluginManager->GetDataProviderPluginFromID(i);
			DataProvider* pDataProvider = pCreatorMain();
			pNewLayer = new RadarVectorLayer;
			pNewLayer->SetParentMap(map);
			pNewLayer->CoordTrans(coords);
			pNewLayer->SetDataProvider(pDataProvider);
			pDataProvider->ParentLayer(pNewLayer);


			pNewLayer->CreateLayer(strDataName);
		}
	}

	return pNewLayer;
}*/

Ground::Ground( void ) : m_pPluginManager(0)
{
	m_pPluginManager = new ProviderPluginsManager;
	m_pGisExtendPluginsManager = new GisExtendPluginsManager;
}

int Ground::DynamicLoadPugin(const std::string& strPlName)
{
	return m_pPluginManager->LoadPlugin(strPlName);
}

int Ground::LoadProviderPlugins( const std::string& strConfigName )
{
	return m_pPluginManager->LoadPluginsFromConfigFile(strConfigName);
}

int Ground::LoadGisExtendPlugins( const std::string& strConfigName )
{
	return m_pGisExtendPluginsManager->LoadPluginsFromConfigFile(strConfigName);
}

MapFactory* Ground::GetMapFactory()
{
	if(m_pGisExtendPluginsManager->GetDataProviderPluginFromID(0) != 0)
	{
		return (MapFactory*)m_pGisExtendPluginsManager->GetDataProviderPluginFromID(0);
	}
	else
	{
		return DefaultMapFactory::Instantiate();
	}
}

GROUND_NAMESPACE_END