#pragma once
#include "Config.h"
#include "ClipBoard.h"
#include "Map.h"
#include "Layer.h"

class ClipCallback : public ClipBoard::ClipBoardMoveCallback
{
public:
	ClipCallback(nephogram_ground::Map* map);
	QVariant GetAttributeValue(int index ,nephogram_ground::Layer* layer)
	{
		QVariant _value;
		/*Layer::P_LAYER_ATTRIBUTE_MAP pLayerAttribteTable = layer->GetLayerAttribteTable();
		Layer::LAYER_ATTRIBUTE_MAP::iterator findResult = pLayerAttribteTable->find(index);
		_value = findResult->second;*/
		return _value;
	}

	double Get_Length( double dx, double dy )
	{
		return( sqrt(dx*dx + dy*dy) );
	}

	virtual void MoveCompleted( osg::Vec3& p1, osg::Vec3& p2, osg::Vec3& p3, osg::Vec3& p4, osg::Node* pClipNode, osg::Image** ppImage);
	void DrawPlotGraph( nephogram_ground::Map* srcMap, osg::Vec3& p1, osg::Vec3& p2, osg::Vec3& p3, osg::Vec3& p4, osg::Node* pClipNode );
	void DrawPlotGraph(nephogram_ground::Map* srcMap, QImage* pImage, osg::Vec3& p1, osg::Vec3& p2, osg::Vec3& p3, osg::Vec3& p4);
private:
	nephogram_ground::Map* _map;
};