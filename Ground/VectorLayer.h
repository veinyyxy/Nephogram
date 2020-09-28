#pragma once

#include "Config.h"
#include "Layer.h"
#include "CoordinateTransform.h"

using namespace std;

GROUND_NAMESPACE_START

class  GROUND_EXPORT VectorLayer: public Layer
{
public:
	VectorLayer(DataProvider* data = 0, CoordinateTransform* ct = 0, int iNT = 0);
	virtual ~VectorLayer(void);

public:
	virtual void TransformLayer();
	virtual int CreateLayer(const std::string& filename);
	virtual void CreateLayerData();
	virtual void operator=(const VectorLayer& other);
};

GROUND_NAMESPACE_END
