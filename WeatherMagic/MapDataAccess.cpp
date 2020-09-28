#include <osgGA/TrackballManipulator>
#include <osgGA/KeySwitchMatrixManipulator>

#include "Map.h"
#include "AdapterWidget.h"
#include "DefaultManipulator.h"
#include "CompositeViewerQT.h"
#include "MapDataAccess.h"
//#include "IDPdb.h"

MapDataAccess::MapDataAccess(QObject *parent)
	: QObject(parent)
{

}

MapDataAccess::~MapDataAccess()
{

}

Q_GLOBAL_STATIC(MapDataAccess, mapDataAccess)
	MapDataAccess *MapDataAccess::Instance() 
{ 
	return mapDataAccess(); 
}

void MapDataAccess::GoMapCenter(QWidget* viewerWidget , QString layerName /*=QString::fromLocal8Bit("ÖÐ¹úµØÍ¼")*/ )
{
#if 0
	if (viewerWidget)
	{
		DefaultManipulator* dm = 0;
		nephogram_ground::Map* map = 0;
		ViewerQT* viewerWindow = dynamic_cast<ViewerQT*>(viewerWidget);
		map = (nephogram_ground::Map*)viewerWindow->property("Map").toLongLong();
		int wdt = viewerWindow->property("DType").toInt();
		if (wdt == RadarData)
		{
			dm = dynamic_cast<DefaultManipulator*>(viewerWindow->getViewer()->getCameraManipulator());
		}
		else if (wdt == CZData)
		{
			osgGA::KeySwitchMatrixManipulator* keym = dynamic_cast<osgGA::KeySwitchMatrixManipulator*>(viewerWindow->getViewer()->getCameraManipulator());
			if (keym)
			{
				dm = dynamic_cast<DefaultManipulator*>(keym->getMatrixManipulatorWithKey('1'));
			}
		}
		if (dm&& map->GetMapLayers().size() > 0)
		{
			osg::Node* node = map->GetLayer(layerName.toStdString())->GetLayerNode();
			if (node)
			{
				double dr = node->getBound().radius();
				dm->GoToNodeCenter(viewerWindow->getViewer()->getCamera(),node,dr);
			}
		}
	}
#endif
}

void MapDataAccess::MapMZoomIn(QWidget* viewerWidget)
{
	DefaultManipulator* dm  = GetDM(viewerWidget);
	if (dm)
	{
		dm->MapMZoomIn();
	}
	
}

void MapDataAccess::MapMZoomOut(QWidget* viewerWidget)
{
	DefaultManipulator* dm  = GetDM(viewerWidget);
	if (dm)
	{
		dm->MapMZoomOut();
	}
}

void MapDataAccess::MapZoomIn(QWidget* viewerWidget)
{
	DefaultManipulator* dm  = GetDM(viewerWidget);
	if (dm)
	{
		dm->MapZoomIn();
	}
}

void MapDataAccess::MapZoomOut(QWidget* viewerWidget)
{
	DefaultManipulator* dm  = GetDM(viewerWidget);
	if (dm)
	{
		dm->MapZoomOut();
	}
}

void MapDataAccess::MapTop(QWidget* viewerWidget)
{
	DefaultManipulator* dm  = GetDM(viewerWidget);
	if (dm)
	{
		dm->MapTop();
	}
}
void MapDataAccess::MapBottom(QWidget* viewerWidget)
{
	DefaultManipulator* dm  = GetDM(viewerWidget);
	if (dm)
	{
		dm->MapBottom();
	}
}
void MapDataAccess::MapLeft(QWidget* viewerWidget)
{
	DefaultManipulator* dm  = GetDM(viewerWidget);
	if (dm)
	{
		dm->MapLeft();
	}
}
void MapDataAccess::MapRight(QWidget* viewerWidget)
{
	DefaultManipulator* dm  = GetDM(viewerWidget);
	if (dm)
	{
		dm->MapRight();
	}
}
void MapDataAccess::MapALLMap( QWidget* viewerWidget )
{
	ViewerQT* viewerWindow = dynamic_cast<ViewerQT*>(viewerWidget);
	DefaultManipulator* dm  = GetDM(viewerWidget);
	if (dm)
	{
		dm->MapALLMap();
	}
}
DefaultManipulator* MapDataAccess::GetDM( QWidget* viewerWidget )
{
#if 0
	DefaultManipulator* dm = 0;
	//ViewerQT* viewerWindow = dynamic_cast<ViewerQT*>(viewerWidget);
	int wdt = viewerWidget->property("DType").toInt();
	if (wdt == RadarData)
	{
		dm = dynamic_cast<DefaultManipulator*>(dynamic_cast<ViewerQT*>(viewerWidget)->getViewer()->getCameraManipulator());
	}
	else if (wdt == Win4)
	{
		QWidget* cv = dynamic_cast<CompositeViewerQT*>(viewerWidget)->CurrentWidget();
		if (cv)
		{
			osgViewer::Viewer* viewer = (osgViewer::Viewer*)cv->property("Viewer").toLongLong();
			if (viewer)
			{
				dm = dynamic_cast<DefaultManipulator*>(viewer->getCameraManipulator());
			}
		}
		
	}
	else if (wdt == NoData)
	{
		dm = dynamic_cast<DefaultManipulator*>(dynamic_cast<ViewerQT*>(viewerWidget)->getViewer()->getCameraManipulator());
	}
	else if (wdt == CZData)
	{
		osgGA::KeySwitchMatrixManipulator* keym = dynamic_cast<osgGA::KeySwitchMatrixManipulator*>(dynamic_cast<ViewerQT*>(viewerWidget)->getViewer()->getCameraManipulator());
		if (keym)
		{
			dm = dynamic_cast<DefaultManipulator*>(keym->getMatrixManipulatorWithKey('1'));
		}
	}
	return dm;
#endif
	return 0;
}
