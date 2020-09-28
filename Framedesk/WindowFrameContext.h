#pragma once
#include "AdapterWidget.h"
#include <QtWidgets/QMdiSubWindow>

class WindowFrameContext
{
public:
	virtual ViewerQT* GetCurrentQGLWidget() = 0;
	virtual QMdiSubWindow* GetCurrentSubWindow() = 0;
};

