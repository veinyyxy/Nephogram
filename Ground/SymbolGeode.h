#pragma once
#include "Config.h"
#include "Ground_Global.h"

GROUND_NAMESPACE_START

class GROUND_EXPORT SymbolGeode :
	public osg::Billboard
{
public:
	SymbolGeode(void);
	virtual ~SymbolGeode(void);
	bool computeMatrix(osg::Matrix& modelview, const osg::Vec3& eye_local, const osg::Vec3& pos_local) const;
};

GROUND_NAMESPACE_END