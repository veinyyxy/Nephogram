#pragma once
#include "ControllerFrameContext.h"

class ControllerFrameContextImps :
	public ControllerFrameContext
{
public:
	ControllerFrameContextImps(void);
	~ControllerFrameContextImps(void);

	virtual osgViewer::Viewer* GetCurrentViewer();

	virtual nephogram_ground::Map* GetCurrentMap();

	inline void SetCurrentViewer(osgViewer::Viewer* pV){m_pViewer = pV;}
	inline void SetCurrentMap(nephogram_ground::Map* pMap){m_pMap = pMap;}
private:

	osgViewer::Viewer* m_pViewer;
	nephogram_ground::Map* m_pMap;
};

