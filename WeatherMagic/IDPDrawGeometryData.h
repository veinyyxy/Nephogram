#pragma once
#include "idp_control_global.h"
#include "drawgeometrydata.h"
#include "Ground.h"
#include "Layer.h"

class IDP_CONTROL_EXPORT IDPDrawGeometryData :
	public DrawGeometryData
{
public:
	IDPDrawGeometryData(void);
	virtual ~IDPDrawGeometryData(void);
	inline void SetDrawLayer(nephogram_ground::Layer* pLayer){m_pLayer = pLayer;}
	void SetResultHandle(RectResult* pHandler){m_RectResult = pHandler;}
protected:
	RectResult* m_RectResult;
	nephogram_ground::Layer* m_pLayer;
};

