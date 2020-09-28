#ifndef COMPOSITEVIEWERQT_H
#define COMPOSITEVIEWERQT_H

#include <osgViewer/Viewer>
#include <osgViewer/CompositeViewer>
#include <osgViewer/ViewerEventHandlers>
#include <QtGui/QtGui>
#include <QtCore/QString>
#include <QtCore/QTimer>
#include <QtGui/QKeyEvent>
#include <QtWidgets/QApplication>
#include <QtOpenGL/QGLWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMdiSubWindow>
#include <QtWidgets/QMdiArea>
#include "DefaultManipulator.h"
using Qt::WindowFlags;

#include <iostream>
#include "GraphicsControler_global.h"
#include "RenderThread.h"

class GRAPHICSCONTROLER_EXPORT CompositeViewerQT : public QWidget
{
	Q_OBJECT

public:
	CompositeViewerQT(int index = 0 ,QWidget* parent = 0);
	~CompositeViewerQT();
	inline void SetCompositeViewer(osgViewer::CompositeViewer* pCV){m_pCompositeViewer = pCV;}
	void AddMenuItem();
	void CurrentWidget(QWidget* cw);
	QWidget* CurrentWidget();
	//QWidget* AddViewWidget( osg::Camera* camera, osg::Node* scene );
	//osg::Camera* CreateCamera( int x, int y, int w, int h, const std::string& name="", bool windowDecoration=false );
private:
	virtual void paintEvent( QPaintEvent* event );
	virtual void closeEvent( QCloseEvent *event );
	virtual bool winEvent(MSG *m, long *result);
Q_SIGNALS:
	void SetCurrentWidget(QWidget* currentWidget);
public Q_SLOTS:
	virtual void setVisible(bool visible);
		void Slot_Notify();
protected:
	DefaultManipulator* _dm;
	RenderThread mThreadHandle;
	QWidget* m_CurrentWidget;
private:
	osg::ref_ptr<osgViewer::CompositeViewer> m_pCompositeViewer;
};


#endif // COMPOSITEVIEWERQT_H