#pragma once
#include "Layer.h"

GROUND_NAMESPACE_START
class GROUND_EXPORT ManualDrawLayer :
	public Layer
{
public:
	ManualDrawLayer(DataProvider* data = 0, CoordinateTransform* ct = 0, int iNodeType = 1);
	virtual ~ManualDrawLayer(void);

	virtual void TransformLayer();

	virtual void CreateLayerData();

	virtual int CreateLayer( const std::string& filename );
};

GROUND_NAMESPACE_END
