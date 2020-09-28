#pragma once
#include <string>
#include <osg/Vec4>
#include <osg/Geometry>
#include "Config.h"
#include "Ground_Global.h"
#include "LegendInterface.h"
GROUND_NAMESPACE_START


class GROUND_EXPORT SymbolLibraryInterface
{
public:
	inline LegendInterface* GetLegend(int i = 0){return m_pLegendVector.at(i);}
	inline void AddLegend(LegendInterface* pLF){m_pLegendVector.push_back(pLF);}
	virtual int InitSymbolLibrary(std::string strLibName) = 0;

protected:
	
	std::vector<LegendInterface*> m_pLegendVector;
};

GROUND_NAMESPACE_END