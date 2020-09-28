#include "GraticuleCoordinates.h"
#include "geos/geom/CoordinateSequenceFactory.h"
#include "geos/geom/CoordinateArraySequence.h"
#include "geos/geom/Coordinate.h"
#include "geos/geom/LineString.h"
#include "Quadrilateral.h"
#include "Mark.h"
#include "osg/Hint"

GROUND_NAMESPACE_START

QGraticuleCoordinates::QGraticuleCoordinates(DataProvider* data, CoordinateTransform* ct) : Layer(data, ct)
	, m_constantInterval(false)
	, pLongLineData(0)
	, pLatLineData(0)
	, pAllAnntation(0)
{
	//m_LongLatRect.left_top.first = (-70.0);
	//m_LongLatRect.left_top.second = (89.9);
	//m_LongLatRect.right_top.first = (-70.0004);
	//m_LongLatRect.right_top.second = (89.9);
	//m_LongLatRect.left_bottom.first = (-70.0);
	//m_LongLatRect.left_bottom.second = (-89.9);
	//m_LongLatRect.right_bottom.first = (-70.0004);
	//m_LongLatRect.right_bottom.second = (-89.9);
	//m_LongLatLineData.latitude_line_interval = 10.0;
	//m_LongLatLineData.longitude_line_interval = 10.0;
	m_LongLatRect.left_top.first = (70);
	m_LongLatRect.left_top.second = (55);
	m_LongLatRect.right_top.first = (145);
	m_LongLatRect.right_top.second = (55);
	m_LongLatRect.left_bottom.first = (70);
	m_LongLatRect.left_bottom.second = (0);
	m_LongLatRect.right_bottom.first = (145);
	m_LongLatRect.right_bottom.second = (0);
	m_LongLatLineData.latitude_line_interval = 5.0;
	m_LongLatLineData.longitude_line_interval = 5.0;
}

QGraticuleCoordinates::~QGraticuleCoordinates(void)
{
	
}

void QGraticuleCoordinates::DrawGrid()
{
	//计算绘制纬线的数量
	int  LonCount= abs(m_LongLatRect.left_top.first - m_LongLatRect.right_top.first) / m_LongLatLineData.latitude_line_interval;		//计算纬线数量
	int  latCount= abs(m_LongLatRect.left_top.second -m_LongLatRect.left_bottom.second) /m_LongLatLineData.longitude_line_interval;		//计算经线数量
	LonCount++;latCount++;
	//绘制经线
	float StartValue = m_LongLatRect.left_top.first;
	Layer::MapGeometry* pMG = GetMgoGeometry();

	for(int i = 0 ; i < LonCount ; i++)
	{

		Quadrilateral *ln1 = new Quadrilateral;
		osg::ref_ptr <osg::Vec3Array> temp_array = new osg::Vec3Array  ;//数据数组
		osg::ref_ptr <osg::Vec4Array> temp_color_array = new osg::Vec4Array;//颜色数组
		ln1->setGlenum(osg::PrimitiveSet::LINE_STRIP);
		if (i == 0 )
		{
			StartValue = StartValue + m_LongLatLineData.longitude_line_interval;
			continue;
		}
		if (i == LonCount-1 )
		{
			StartValue = StartValue + m_LongLatLineData.longitude_line_interval;
			continue;
		}
		//加上第一个点
		temp_array->push_back(osg::Vec3(StartValue,m_LongLatRect.left_top.second,m_layerZ));
		temp_color_array->push_back(osg::Vec4(0, 0, 0, 1));
		for( float j = m_LongLatRect.left_bottom.second ; j <m_LongLatRect.left_top.second ; j+=m_LongLatLineData.latitude_line_interval)
		{
			temp_array->push_back(osg::Vec3(StartValue,j,m_layerZ));
			temp_color_array->push_back(osg::Vec4(0, 0, 0, 1));
		}
		//增加最后一个点
		temp_array->push_back(osg::Vec3(StartValue,m_LongLatRect.left_top.second,m_layerZ));
		temp_color_array->push_back(osg::Vec4(0, 0, 0, 1));
		ln1->SetCoordinateTransform(CoordTrans());
		ln1->SetOsgArray(temp_array);
		ln1->SetOsgColorArray(*temp_color_array);
		ln1->SetParentLayer(this);

		pMG->insert(Layer::MapGeometryPair(pMG->size(),ln1));

		StartValue = StartValue + m_LongLatLineData.longitude_line_interval;
	}

	//绘制纬度
	float StartLatValue = m_LongLatRect.left_bottom.second;
	//北纬
	for(int i = 0 ; i < latCount; i++)
	{
		Quadrilateral *ln1 = new Quadrilateral;
		osg::ref_ptr <osg::Vec3Array> temp_array = new osg::Vec3Array  ;//数据数组
		osg::ref_ptr <osg::Vec4Array> temp_color_array = new osg::Vec4Array;//颜色数组
		ln1->setGlenum(osg::PrimitiveSet::LINE_STRIP);
		if (i == 0 )
		{
			StartLatValue = StartLatValue + m_LongLatLineData.latitude_line_interval;
			continue;
		}
		if (i == latCount-1 )
		{
			StartLatValue = StartLatValue + m_LongLatLineData.latitude_line_interval;
			continue;
		}
		for( float j = m_LongLatRect.left_top.first ; j <= m_LongLatRect.right_top.first ; j++)
		{
			temp_array->push_back(osg::Vec3(j,StartLatValue,m_layerZ));
			temp_color_array->push_back(osg::Vec4(0, 0, 0, 1));
		}
		temp_array->push_back(osg::Vec3(m_LongLatRect.right_top.first,StartLatValue,m_layerZ));
		temp_color_array->push_back(osg::Vec4(0, 0, 0, 1));
		ln1->SetCoordinateTransform(CoordTrans());
		ln1->SetOsgArray(temp_array);
		ln1->SetOsgColorArray(*temp_color_array);
		ln1->SetParentLayer(this);
		pMG->insert(Layer::MapGeometryPair(pMG->size(),ln1));	
		StartLatValue = StartLatValue + m_LongLatLineData.latitude_line_interval;
	}
}

void QGraticuleCoordinates::SetGridLineColor( const LONG_LAT_LINE& line, osg::Vec4 color )
{
}

void QGraticuleCoordinates::SetGridColor( osg::Vec4 color )
{
	osg::Vec4 fdColor;
	fdColor = color;
}

void QGraticuleCoordinates::TransformLayer()
{
	std::map<int, std::auto_ptr<Geometry>>::iterator goGeomIter = m_pgoGeometry->begin();
	while(goGeomIter != m_pgoGeometry->end())
	{
		Geometry* goGeom = goGeomIter->second.get();
		if(goGeom)
		{
			goGeom->SetCoordinateTransform(m_coordTrans);
			goGeom->TransformGeometry();
		}
		goGeomIter++;
	}
}

void QGraticuleCoordinates::CreateLayerData()
{
	std::map<int, std::auto_ptr<Geometry>>::iterator goGeomIter = m_pgoGeometry->begin();
	while(goGeomIter != m_pgoGeometry->end())
	{
		Geometry* goGeom = goGeomIter->second.get();
		if(goGeom)
		{
			goGeom->SetCoordinateTransform(m_coordTrans);
			goGeom->CreateOsgFromGeos(m_pNode);
		}
		goGeomIter++;
	}
}

int QGraticuleCoordinates::CreateLayer( const std::string& filename )
{	
	//if (filename ==std::string("FishNet"))
	//{
		DrawGrid();
	//}
	//else if (filename ==std::string("Frame1"))
	//{
		DrawFrame1();
	//}
	//else if (filename ==std::string("Frame2"))
	//{
		DrawFrame2();
	//}
	
	return 1;
}

void QGraticuleCoordinates::SetGrid( float lonstart,float latstart,float lonend,float latend,float lonCellSize,float LatCellSize )
{
	m_LongLatRect.left_top.first = lonstart;
	m_LongLatRect.left_top.second = latstart;
	m_LongLatRect.right_top.first = lonend;
	m_LongLatRect.right_top.second = latstart;
	m_LongLatRect.left_bottom.first = lonstart;
	m_LongLatRect.left_bottom.second = latend;
	m_LongLatRect.right_bottom.first = lonend;
	m_LongLatRect.right_bottom.second = latend;
	m_LongLatLineData.latitude_line_interval = lonCellSize;
	m_LongLatLineData.longitude_line_interval = LatCellSize;
}

void QGraticuleCoordinates::DrawFrame1()
{
	//计算绘制纬线的数量
	int  LonCount= abs(m_LongLatRect.left_top.first - m_LongLatRect.right_top.first) / m_LongLatLineData.latitude_line_interval;		//计算纬线数量
	int  latCount= abs(m_LongLatRect.left_top.second -m_LongLatRect.left_bottom.second) /m_LongLatLineData.longitude_line_interval;		//计算经线数量
	LonCount++;latCount++;

#if 1
	//绘制经线
	float StartValue = m_LongLatRect.left_top.first;
	Layer::MapGeometry* pMG = GetMgoGeometry();
	Quadrilateral *ln1 = new Quadrilateral;
	osg::ref_ptr <osg::Vec3Array> temp_array = new osg::Vec3Array  ;//数据数组
	osg::ref_ptr <osg::Vec4Array> temp_color_array = new osg::Vec4Array;//颜色数组
	ln1->setGlenum(osg::PrimitiveSet::LINE_LOOP);
	for( float j1 = m_LongLatRect.left_bottom.second ; j1 <m_LongLatRect.left_top.second ; j1+=m_LongLatLineData.latitude_line_interval)
	{
		temp_array->push_back(osg::Vec3(StartValue,j1,m_layerZ));
		temp_color_array->push_back(osg::Vec4(0, 0, 0, 1));
		std::string text = std::to_string(j1) + "°" +"N";
		std::string m_text = text;
		Mark* gm = new Mark(m_text,osg::Vec3(StartValue-1.0,j1,m_layerZ),this);
		gm->SetTextColor(0, 0, 0, 1.0);
		gm->SetTextDirection(M_PI / 2);
		gm->UsedLayerSet(false);
		gm->MarkSize(16);
		gm->SetAlignment( osgText::Text::RIGHT_BOTTOM );
		pMG->insert(Layer::MapGeometryPair(pMG->size(),gm));
	}
	temp_array->push_back(osg::Vec3(StartValue,m_LongLatRect.left_top.second,m_layerZ));
	temp_color_array->push_back(osg::Vec4(0, 0, 0, 1));

	std::string text = std::to_string(m_LongLatRect.left_top.second) + "°" +"N";
	std::string m_text = text;
	Mark* gm1 = new Mark(m_text,osg::Vec3(m_LongLatRect.left_top.first-1.0,m_LongLatRect.left_top.second,m_layerZ),this);
	gm1->SetTextColor(0, 0, 0, 1.0);
	gm1->SetTextDirection(M_PI / 2);
	gm1->UsedLayerSet(false);
	gm1->MarkSize(16);
	gm1->SetAlignment( osgText::Text::RIGHT_BOTTOM );
	pMG->insert(Layer::MapGeometryPair(pMG->size(),gm1));

	for( float j2 = m_LongLatRect.left_top.first ; j2 <= m_LongLatRect.right_top.first ; j2+=m_LongLatLineData.longitude_line_interval)
	{
		temp_array->push_back(osg::Vec3(j2,m_LongLatRect.left_top.second,m_layerZ));
		temp_color_array->push_back(osg::Vec4(0, 0, 0, 1));
	}

	for( float j3 = m_LongLatRect.right_top.second ; j3 >= m_LongLatRect.right_bottom.second ; j3-=m_LongLatLineData.latitude_line_interval)
	{
		temp_array->push_back(osg::Vec3(m_LongLatRect.right_top.first,j3,m_layerZ));
		temp_color_array->push_back(osg::Vec4(0, 0, 0, 1));
	}
	temp_array->push_back(osg::Vec3(m_LongLatRect.right_bottom.first,m_LongLatRect.right_bottom.second,m_layerZ));
	temp_color_array->push_back(osg::Vec4(0, 0, 0, 1));

	for( float j4 = m_LongLatRect.right_bottom.first; j4 >=m_LongLatRect.left_bottom.first ; j4-=m_LongLatLineData.longitude_line_interval)
	{
		temp_array->push_back(osg::Vec3(j4,m_LongLatRect.right_bottom.second,m_layerZ));
		temp_color_array->push_back(osg::Vec4(0, 0, 0, 1));
		std::string text = std::to_string(j4) + "°" +"E";
		std::string m_text = text;
		Mark* gm = new Mark(m_text,osg::Vec3(j4,m_LongLatRect.right_bottom.second-1.5,m_layerZ),this);
		gm->SetTextColor(0, 0, 0, 1.0);
		gm->SetTextDirection(M_PI / 2);
		gm->UsedLayerSet(false);
		gm->MarkSize(16);
		gm->SetAlignment( osgText::Text::CENTER_TOP );
		pMG->insert(Layer::MapGeometryPair(pMG->size(),gm));
	}

	ln1->SetCoordinateTransform(CoordTrans());
	ln1->SetOsgArray(temp_array);
	ln1->SetOsgColorArray(*temp_color_array);
	ln1->SetParentLayer(this);

	osg::StateSet* stateSet = ln1->GetOsgGeometry()->getOrCreateStateSet();
	osg::ref_ptr <osg::LineWidth>liwidth = new osg::LineWidth;
	osg::ref_ptr<osg::Hint> linehint = new osg::Hint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	liwidth->setWidth(10.0);     
	stateSet->setAttributeAndModes(liwidth, osg::StateAttribute::ON);
	stateSet->setMode(GL_LINE_SMOOTH, osg::StateAttribute::ON);
	stateSet->setAttribute(linehint);
	pMG->insert(Layer::MapGeometryPair(pMG->size(),ln1));

	
#endif
}

void QGraticuleCoordinates::DrawFrame2()
{
	//计算绘制纬线的数量
	int  LonCount= abs(m_LongLatRect.left_top.first - m_LongLatRect.right_top.first) / m_LongLatLineData.longitude_line_interval;		//计算纬线数量
	int  latCount= abs(m_LongLatRect.left_top.second -m_LongLatRect.left_bottom.second) /m_LongLatLineData.latitude_line_interval;		//计算经线数量
	LonCount++;latCount++;
	//绘制经线
	float StartValue = m_LongLatRect.left_top.first;
	Layer::MapGeometry* pMG = GetMgoGeometry();
	geos::geom::GeometryFactory * linestrigFactory = new geos::geom::GeometryFactory;

	for(int i = 0 ; i < LonCount ; i++)
	{

		Quadrilateral *ln2 = new Quadrilateral;
		osg::ref_ptr <osg::Vec3Array> temp_array = new osg::Vec3Array  ;//数据数组
		osg::ref_ptr <osg::Vec4Array> temp_color_array = new osg::Vec4Array;//颜色数组
		ln2->setGlenum(osg::PrimitiveSet::LINES);
#if 1
		if (i ==0)
		{
			for( float j = m_LongLatRect.left_bottom.second ; j <m_LongLatRect.right_top.second ; j+=m_LongLatLineData.longitude_line_interval)
			{
				temp_array->push_back(osg::Vec3(StartValue,j,m_layerZ+2));
				temp_color_array->push_back(osg::Vec4(255, 255, 255, 1));
			}
			temp_array->push_back(osg::Vec3(StartValue,m_LongLatRect.right_top.second,m_layerZ+2));
			temp_color_array->push_back(osg::Vec4(255, 255, 255, 1));
			ln2->SetCoordinateTransform(CoordTrans());
			ln2->SetOsgArray(temp_array);
			ln2->SetOsgColorArray(*temp_color_array);
			ln2->SetParentLayer(this);

			osg::StateSet* stateSet = ln2->GetOsgGeometry()->getOrCreateStateSet();
			osg::ref_ptr <osg::LineWidth>liwidth = new osg::LineWidth;
			liwidth->setWidth(6.0);     
			stateSet->setAttributeAndModes(liwidth, osg::StateAttribute::ON);

			pMG->insert(Layer::MapGeometryPair(pMG->size(),ln2));

			StartValue = StartValue + m_LongLatLineData.longitude_line_interval;
			continue;
		}
		if (i == LonCount -1)
		{
			for( float j = m_LongLatRect.left_bottom.second ; j <m_LongLatRect.right_top.second ; j+=m_LongLatLineData.latitude_line_interval)
			{
				temp_array->push_back(osg::Vec3(m_LongLatRect.right_top.first,j,m_layerZ + 2));
				temp_color_array->push_back(osg::Vec4(255, 255, 255, 1));
			}
			temp_array->push_back(osg::Vec3(m_LongLatRect.right_top.first,m_LongLatRect.right_top.second ,m_layerZ+2));
			temp_color_array->push_back(osg::Vec4(255, 255, 255, 1));
			//添加白线
			ln2->SetCoordinateTransform(CoordTrans());
			ln2->SetOsgArray(temp_array);
			ln2->SetOsgColorArray(*temp_color_array);
			ln2->SetParentLayer(this);

			osg::StateSet* stateSet = ln2->GetOsgGeometry()->getOrCreateStateSet();
			osg::ref_ptr <osg::LineWidth>liwidth = new osg::LineWidth;
			liwidth->setWidth(6.0);     
			stateSet->setAttributeAndModes(liwidth, osg::StateAttribute::ON);

			pMG->insert(Layer::MapGeometryPair(pMG->size(),ln2));
			StartValue = StartValue + m_LongLatLineData.longitude_line_interval;
			continue;
		}
#endif


		StartValue = StartValue + m_LongLatLineData.longitude_line_interval;

	}

	//绘制纬度
	float StartLatValue = m_LongLatRect.left_bottom.second;
	//北纬
	for(int i = 0 ; i < latCount; i++)
	{
		Quadrilateral *ln1 = new Quadrilateral;
		osg::ref_ptr <osg::Vec3Array> temp_array = new osg::Vec3Array  ;//数据数组
		osg::ref_ptr <osg::Vec4Array> temp_color_array = new osg::Vec4Array;//颜色数组
		ln1->setGlenum(osg::PrimitiveSet::LINES);
#if 1


		if (i == 0)
		{
			for( float j = m_LongLatRect.left_top.first ; j <= m_LongLatRect.right_top.first ; j+=m_LongLatLineData.longitude_line_interval)
			{
				temp_array->push_back(osg::Vec3(j,StartLatValue,m_layerZ+2));
				temp_color_array->push_back(osg::Vec4(255, 255, 255, 1));
			}
			temp_array->push_back(osg::Vec3(m_LongLatRect.right_top.first ,StartLatValue,m_layerZ+2));
			temp_color_array->push_back(osg::Vec4(255, 255, 255, 1));
			//添加白线
			ln1->SetCoordinateTransform(CoordTrans());
			ln1->SetOsgArray(temp_array);
			ln1->SetOsgColorArray(*temp_color_array);
			ln1->SetParentLayer(this);

			osg::StateSet* stateSet = ln1->GetOsgGeometry()->getOrCreateStateSet();
			osg::ref_ptr <osg::LineWidth>liwidth = new osg::LineWidth;
			liwidth->setWidth(6.0);     
			stateSet->setAttributeAndModes(liwidth, osg::StateAttribute::ON);

			pMG->insert(Layer::MapGeometryPair(pMG->size(),ln1));	
			StartLatValue = StartLatValue + m_LongLatLineData.latitude_line_interval;
			continue;
		}
		if (i == latCount-1)
		{
			StartLatValue = m_LongLatRect.left_top.second;
			for( float j = m_LongLatRect.left_top.first ; j <= m_LongLatRect.right_top.first ; j+=m_LongLatLineData.longitude_line_interval)
			{
				temp_array->push_back(osg::Vec3(j,m_LongLatRect.right_top.second,m_layerZ+2));
				temp_color_array->push_back(osg::Vec4(255, 255, 255, 1));
			}
			temp_array->push_back(osg::Vec3(m_LongLatRect.right_top.first,m_LongLatRect.right_top.second,m_layerZ+2));
			temp_color_array->push_back(osg::Vec4(255, 255, 255, 1));
			//添加白线
			ln1->SetCoordinateTransform(CoordTrans());
			ln1->SetOsgArray(temp_array);
			ln1->SetOsgColorArray(*temp_color_array);
			ln1->SetParentLayer(this);

			osg::StateSet* stateSet = ln1->GetOsgGeometry()->getOrCreateStateSet();
			osg::ref_ptr <osg::LineWidth>liwidth = new osg::LineWidth;
			liwidth->setWidth(6.0);     
			stateSet->setAttributeAndModes(liwidth, osg::StateAttribute::ON);

			pMG->insert(Layer::MapGeometryPair(pMG->size(),ln1));	
			//StartLatValue = StartLatValue + m_LongLatLineData.latitude_line_interval;
			continue;
		}

#endif
		StartLatValue = StartLatValue + m_LongLatLineData.latitude_line_interval;

	}
}

GROUND_NAMESPACE_END