#include "DrawCircle.h"

class DebugDraw : public osg::Drawable::DrawCallback
{
public:
	virtual void drawImplementation( osg::RenderInfo& renderInfo, const osg::Drawable* drawable) const
	{
		unsigned id = renderInfo.getContextID();
		int i = 0;
		i++;
	}

	virtual osg::Object* clone( const osg::CopyOp& ) const
	{
		return 0;
	}

};

DrawCircle::DrawCircle(void) : m_bStart(false)
{
	m_pLayer = 0;
	m_DrawNode = new osg::Geode;
	m_pVertexs = new osg::Vec3Array;
	m_pCircleVertexs = new osg::Vec3Array;
	m_Colors = new osg::Vec4Array;
	m_pLine = new osg::Geometry;
	m_DrawArrays = new osg::DrawArrays(osg::PrimitiveSet::LINES,0,0);
	osg::Geode* pGeode = m_DrawNode->asGeode();
	pGeode->addDrawable(m_pLine);

	m_Colors->push_back(m_color);
	
	m_pLine->setVertexArray(m_pCircleVertexs);
	m_pLine->setColorArray(m_Colors);

	m_pLine->addPrimitiveSet(m_DrawArrays);
	m_pLine->setColorBinding(osg::Geometry::BIND_OVERALL);
}

void DrawCircle::ToDrawCircle( osg::Vec3& pos, float fr, float fz, osg::Vec3Array& out )
{
	float X, Y;
	X = pos.x();
	Y = pos.y();

	for (int p=1; p<=360; p++)
	{
		osg::Vec3 circle;
		float angle = p-1;
		circle.set(X+fr * sin(M_PI / 180 * angle),Y+fr * cos(M_PI / 180 * angle), fz);
		out.push_back(circle);
	}
}


DrawCircle::~DrawCircle(void)
{
}

bool DrawCircle::handle( const osg::Vec3& pos, const osgGA::GUIEventAdapter& ea )
{
	float fZ = 0;

	if(m_pLayer)
		fZ = m_pLayer->LayerZ();

	osg::Vec3 locPos;
	locPos.set(pos.x(), pos.y(), fZ);

	switch( ea.getEventType() )
	{
	case osgGA::GUIEventAdapter::MOVE:
		if(m_bStart)
		{
			m_pVertexs->pop_back();
			m_pVertexs->push_back(locPos);
		}
		break;
	case osgGA::GUIEventAdapter::PUSH:
		{
			if(ea.getButton() == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON)
			{
				if(m_bStart)
				{
					m_pVertexs->push_back(locPos);
					m_pVertexs->push_back(locPos);
				}
				else
				{
					m_pVertexs->clear();
					m_pVertexs->push_back(locPos);
					m_pVertexs->push_back(locPos);
					m_bStart = true;
				}

			}
		}
		break;

	case osgGA::GUIEventAdapter::RELEASE:
		if(ea.getButton() == osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON)
		{
			m_bStart = false;

			CreateLineGeometry();
		}
		break;
	default:
		return false;
	}
	if(m_bStart)
	{
		if(m_pVertexs->size() >= 2)
		{
			m_pCircleVertexs->clear();
			osg::Vec3 pos = m_pVertexs->at(0);
			osg::Vec3 pos2 = m_pVertexs->at(1);
			float fr = sqrt((pos.x()-pos2.x())*(pos.x()-pos2.x()) + (pos.y()-pos2.y())*(pos.y()-pos2.y()));
			ToDrawCircle(pos, fr, fZ, *m_pCircleVertexs);
			(*m_Colors)[0] = m_color;
			m_DrawArrays->set(osg::PrimitiveSet::LINE_LOOP, 0, m_pCircleVertexs->size());
			m_pLine->dirtyDisplayList();
			m_pLine->dirtyBound();
		}
		return true;
	}
	return true;
}

void DrawCircle::CreateLineGeometry()
{
	osg::ref_ptr<osg::Vec3Array> lVertexs = new osg::Vec3Array;
	osg::ref_ptr<osg::Vec4Array> lColors = new osg::Vec4Array;
	osg::Geometry* lpLine  = new osg::Geometry;

	//*lVertexs = *m_pVertexs;

	for(unsigned i = 0; m_pCircleVertexs->size() > i; i++)
	{
		osg::Vec3 pos = m_pCircleVertexs->at(i);
		lVertexs->push_back(pos);
	}
	lpLine->setVertexArray(lVertexs);
	lpLine->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINE_LOOP, 0, lVertexs->size()));
	
	lColors->push_back(m_color);
	lpLine->setColorArray(lColors);
	lpLine->setColorBinding(osg::Geometry::BIND_OVERALL);
	//lpLine->setDrawCallback(new DebugDraw);
	if(m_pLayer)
	{
		osg::Group* pGroup = dynamic_cast<osg::Group*>(m_pLayer->GetLayerNode());
		if(pGroup)
		{
			osg::Geode* pGeode = new osg::Geode;
			if(pGeode)
			{
				pGeode->addDrawable(lpLine);
				pGroup->addChild(pGeode);
			}
		}
	}
}

void DrawCircle::SetColor( osg::Vec4& v4c )
{
	m_color = v4c;

	(*m_Colors)[0] = m_color;
}

void DrawCircle::SetDrawLayer(nephogram_ground::Layer* pLayer )
{
	if(!pLayer) return;

	osg::Group* pGroup = dynamic_cast<osg::Group*>(pLayer->GetLayerNode());
	if(!pGroup) return;

	pGroup->addChild(m_DrawNode);
	m_pLayer = pLayer;
}
