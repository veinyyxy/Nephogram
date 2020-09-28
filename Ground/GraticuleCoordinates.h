#pragma once
#include "Config.h"
#include "Ground_Global.h"
#include "Layer.h"
//#include "Map.h"
#include "LineString.h"
#include "Proj4Transform.h"


GROUND_NAMESPACE_START

typedef std::pair< double, double > LONG_LAT_POINT;
typedef std::pair< LONG_LAT_POINT, LONG_LAT_POINT > LONG_LAT_LINE;
typedef std::map< LONG_LAT_LINE, LineString* > LONG_LAT_LINE_MAP;
typedef std::map< LONG_LAT_POINT, osgText::Text* > LONG_LAT_MARK_MAP;
typedef std::vector<LineString*> LONG_LAT_LINE_VECTOR;
typedef std::map< LONG_LAT_POINT, osgText::Text* > ANNOTATION;
typedef struct longlatrect
{
	LONG_LAT_POINT left_top, right_top;
	LONG_LAT_POINT left_bottom, right_bottom;
} LONG_LAT_RECT;

typedef struct LongLatLineData
{
	 LONG_LAT_LINE_MAP longitude_line;
	 double longitude_line_interval;
	 LONG_LAT_LINE_MAP latitude_line;
	 double latitude_line_interval;
	 ANNOTATION line_make;
	 int mark_font;
	 void clear(){
		 longitude_line.clear(); 
		 line_make.clear();
		 latitude_line.clear();
	 }
} LONGLAT_LINE_DATA;

class GROUND_EXPORT QGraticuleCoordinates : public Layer
{
	

public:
	QGraticuleCoordinates(DataProvider* data = 0, CoordinateTransform* ct = 0);
	~QGraticuleCoordinates(void);

	void SetGridLineColor(const LONG_LAT_LINE& line, osg::Vec4 color);
	void SetGridColor(osg::Vec4 color);
	
	virtual void TransformLayer();
	virtual void CreateLayerData();
	virtual int CreateLayer(const std::string& filename);
	void SetGrid(float lonstart,float latstart,float lonend,float latend,float lonCellSize,float LatCellSize);
private:
	void DrawGrid();//添加经纬网格
	void DrawFrame1();//添加经纬网格边界黑线
	void DrawFrame2();//添加经纬网格边界白线
	

private:
	LONGLAT_LINE_DATA m_LongLatLineData;
	osg::Group* renderVol;

	bool m_constantInterval;
	LONG_LAT_LINE_VECTOR m_LongLine;
	LONG_LAT_LINE_VECTOR m_LatLine;
	LONG_LAT_MARK_MAP m_LongLatMark;
	LONG_LAT_RECT m_LongLatRect;
	osg::Vec4 m_GridColor;
	//QAttributeSet m_gridAttribute;
	std::vector<LineString*> m_deleteLine;
	LineString* pLongLineData;
	LineString* pLatLineData;
	osgText::Text* pAllAnntation;
	//QPointer<QLeaf> node;
	//Proj4Transform trans;
};

GROUND_NAMESPACE_END