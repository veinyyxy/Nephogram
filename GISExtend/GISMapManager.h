#pragma once
#include "Map.h"

#include "GISExtendConfig.h"
#include "CoordinateTransform.h"

#include <QtCore/QObject>

class QString;
class QFont;

using namespace nephogram_ground;

typedef unsigned int UINT, *P_UINT;



extern "C"
{
	typedef DataProvider* (*pDataProviderPluginMain)();
}


class GISMapManager : public QObject
{
public:
	GISMapManager(Map* pMap);
	virtual ~GISMapManager(void);
	bool ReadMapScheme(const QString& filename, Map* pMap);
	void WriteMapScheme(const QString& schName, const QString& filename);
	Layer* NewVectorLayer(const QString& fileName, qreal qrZ);
	Layer* NewRasterLayer(const QString& fileName, qreal qrz);
	inline CoordinateTransform* CoordTans() {return m_pProj4;}
	inline void SetMap(Map* pMap){m_pMap = pMap;}
	inline Map* GetMap(){return m_pMap;}
	void LoadBasicMap(const QString& filename);
	/** @brief »æÖÆ¾­Î³Íø¸ñ */ 
	void AddFishNet(float lonstart,float latstart,float lonend,float latend,float lonCellSize,float LatCellSize, qreal qrz);
	//bool AddWorkStationLayer();
	bool AddLayer(Map* map,const QString& filename);
private:
	Map* m_pMap;
	CoordinateTransform* m_pProj4;

	float m_LonStart; 
	float m_LatStart;
	float m_LonEnd;
	float m_LatEnd;
	float m_LonCellSize;
	float m_LatCellSize;
};

