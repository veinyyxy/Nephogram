#pragma once
#include <osg/View>
#include <Map.h>
#include <string>
#include <map>
#include "idp_control_global.h"

class IDP_CONTROL_EXPORT ViewMapAdatper
{
public:
	//ViewMapAdatper();
	ViewMapAdatper(osg::View* pV, nephogram_ground::Map* pMap);
	~ViewMapAdatper(void);
	const std::string& AdapterName();
	void AdapterName(std::string strName);

	inline osg::View* AdapterView(){return m_pView.get();}
	inline void AdapterView(osg::View* pV){
		m_pView = pV;
		UnitedViewAndMap();
	}

	inline nephogram_ground::Map* AdapterMap(){return m_pGisMap;}
	inline void AdapterMap(nephogram_ground::Map* pMap){
		m_pGisMap = pMap;
		UnitedViewAndMap();
	}

	void* GetUserData(std::string& strName);
	void SetUserData(std::string& strName, void* pData);
	void DelUserData(std::string& strName);

	virtual nephogram_ground::Layer* LoadDataToLayer(std::string& strFileName);
private:
	void UnitedViewAndMap();
	osg::ref_ptr<osg::View> m_pView;
	nephogram_ground::Map* m_pGisMap;
	std::map<std::string, void*> m_UserData;
};

