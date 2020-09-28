#pragma once
#include "idp_control_global.h"


using namespace nephogram_ground;
class QGLWidget;

class IDP_CONTROL_EXPORT EarthquakeFileDisplay : public QObjectUserData
{
public:
	EarthquakeFileDisplay(ViewerQT* pvewer);
	virtual ~EarthquakeFileDisplay(void);

	QWidget* CreateView();
	Layer* ReadEarthquakeFileToLayer(const QString& fileName, nephogram_ground::CoordinateTransform* ct);
	Layer* ReadTIFFFileToLayer(const QString& fileName, nephogram_ground::CoordinateTransform* ct);
	void LoadBasicGeogInfo(const QString& configName);
	void OpenEarthquakeFile(const QString& mapConfig, const QString& fileName);
	void OpenTIFFFile(const QString& fileName,const QString& mapConfig = QString());
	void OpenEarthquakeFile(const QString& fileName);
	inline nephogram_ground::Map * Getmap(){return m_pMap;};
	//inline GISMapManager * GetMapManager(){return &m_MapManager;};
private:
	nephogram_ground::Map* m_pMap;
	//GISMapManager m_MapManager;
	ViewerQT* m_pViewer;
};

