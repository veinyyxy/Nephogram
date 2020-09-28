#include "Layer.h"
#include <osg/MatrixTransform>
#include "Map.h"
#include "Quadrilateral.h"
#include "Mark.h"


GROUND_NAMESPACE_START

Layer::Layer(DataProvider* data , CoordinateTransform* ct, int iNodeType)
	: m_layerZ(0.0f), m_coordTrans(ct),m_dataProvider(data)
	, m_pParentMap(0),b_trans(true), m_bUseLayerZ(true),m_fontSize(10),m_bVisible(true)
	, m_LineWidth(0), m_LineStripple(0)
	, m_PointSize(0), m_iUsedLegendID(-1)
	, m_pSymbolLibrary(0)//,m_fiedName("NAME")
	, m_pParentLayer(0)
	, m_pChildLayer(0)
	, m_uAlphaValue(100)
{
	switch(iNodeType)
	{
	case 0:
		m_pNode = new osg::Geode();
		break;
	case 1:
		m_pNode = new osg::Group();
		break;
	case 2:
		m_pNode = new osg::MatrixTransform;
	default:
		m_pNode = new osg::Geode();
		break;
	}

	osg::StateSet* stateset = m_pNode->getOrCreateStateSet();
	m_LineWidth = new osg::LineWidth();
	m_LineWidth->setWidth(1.0f);
	m_LineStripple = new osg::LineStipple(1, 0xFFFF);
	m_PointSize = new osg::Point(1.0f);

	stateset->setAttributeAndModes(m_LineWidth,osg::StateAttribute::ON);
	stateset->setAttributeAndModes(m_LineStripple,osg::StateAttribute::ON);
	stateset->setAttributeAndModes(m_PointSize,osg::StateAttribute::ON);
	//stateset->setMode(GL_BLEND, osg::StateAttribute::ON);
	m_pgoGeometry.reset(new MapGeometry());

	//SyncLayerAttributeTable();
}

Layer::~Layer(void)
{
	/*if (!m_dataProvider)
	{
	delete m_dataProvider;
	m_dataProvider = NULL;
	}*/
}

//void Layer::InsertLayerAttribute(boost::any _val,std::string name,std::string typeName,std::string comment,int type,int len,int prec)
//{
//	GeomField geomFiled;
//	geomFiled.setName(name);
//	geomFiled.setType(type);
//	geomFiled.setTypeName(typeName);
//	geomFiled.setLength(len);
//	geomFiled.setPrecision(prec);
//	geomFiled.setComment(comment);
//
//	int count = m_LayerAttributeDescripe.size();
//	m_LayerAttributeDescripe.insert(FIELD_MAPPair(count,geomFiled));
//	m_pLayerAttribteTable.insert(LAYER_ATTRIBUTE_MAPPair(count,_val));
//}

void Layer::LayerZ( float z )
{
	m_layerZ = z;
}

float Layer::LayerZ()
{
	return m_layerZ;
}

double Layer::MinimumScale()
{
	return m_minScale;
}

void Layer::MinimumScale( double mix )
{
	m_minScale = mix;
}

void Layer::MaximumScale( double max )
{
	m_maxScale = max;
}

double Layer::MaximumScale()
{
	return m_maxScale;
}

P_FIELD_MAP Layer::GetFieldMap()
{
	return &m_PendingFieldMap;
}

void Layer::CoordTrans(CoordinateTransform* ct)
{
	m_coordTrans = ct;
}

CoordinateTransform* Layer::CoordTrans()
{
	return m_coordTrans;
}

P_FIELD_MAP Layer::GetLayerAttributeMap()
{
	return &m_LayerAttributeDescripe;
}

#if 0
void Layer::UpdateProperty(int index, boost::any value)
{
	boost::any _any ;
	FIELD_MAP::iterator arrtiIter =m_LayerAttributeDescripe.find(index);
	_any = arrtiIter->second;
	GeomField geomField = boost::any_cast<GeomField>(_any);
	if (geomField.typeName()== "Color")
	{
		osg::Vec4 vect4 = boost::any_cast<osg::Vec4>(value);
		
		m_v4LayerColor = vect4;
		/*osg::StateSet* stateset = m_pNode->getOrCreateStateSet();
		m_LayerMaterial->setAmbient(osg::Material::FRONT_AND_BACK, vect4);

		stateset->setAttributeAndModes(m_LayerMaterial);*/
		LAYER_ATTRIBUTE_MAP::iterator findResult = m_pLayerAttribteTable.find(index);
		findResult->second = vect4;

		UpdateLayer();
	}
	else if (geomField.typeName()== "WidthInt")
	{
		double  vect4 = boost::any_cast<double>(value);
		m_LineWidth->setWidth(vect4);
		osg::StateSet* stateset = m_pNode->getOrCreateStateSet();
		stateset->setAttributeAndModes(m_LineWidth,osg::StateAttribute::ON);
		LAYER_ATTRIBUTE_MAP::iterator findResult = m_pLayerAttribteTable.find(index);
		findResult->second = vect4;
	}
	else if (geomField.typeName()== "PointInt")
	{
		double  vect4 = boost::any_cast<double>(value);
		m_PointSize->setSize(vect4);
		osg::StateSet* stateset = m_pNode->getOrCreateStateSet();
		stateset->setAttributeAndModes(m_PointSize,osg::StateAttribute::ON);
		LAYER_ATTRIBUTE_MAP::iterator findResult = m_pLayerAttribteTable.find(index);
		findResult->second = vect4;
	}
	else if (geomField.typeName()== "StrippleInt")
	{
		int vect4 = boost::any_cast<int>(value);
		if (vect4 == 0)
		{
				m_LineStripple->setFactor(1);
				m_LineStripple->setPattern(GL_LINE_STIPPLE);
		}
		else if (vect4 == 1)
		{
			m_LineStripple->setFactor(2);
			m_LineStripple->setPattern(osg::StateAttribute::LINESTIPPLE);
		}




		osg::StateSet* stateset = m_pNode->getOrCreateStateSet();
		stateset->setAttributeAndModes(m_LineStripple,osg::StateAttribute::ON);
	}
}
#endif

//bool Layer::GetLayerAtrributeFromName( const std::string& name, boost::any& pValue )
//{
//	Layer::P_LAYER_ATTRIBUTE_MAP pLayerAttributeMap = &m_pLayerAttribteTable;
//	//////////////////////////////////////////////////////////////////////////
//	P_FIELD_MAP pFiledMap = &m_LayerAttributeDescripe;
//	FIELD_MAP::iterator be = pFiledMap->begin();
//	for(; be != pFiledMap->end(); be++)
//	{
//		std::string strName = be->second.name();
//		if(strName == name)
//		{
//			Layer::LAYER_ATTRIBUTE_MAP::iterator findIt = pLayerAttributeMap->find(be->first);
//
//			if(findIt != pLayerAttributeMap->end())
//			{
//				pValue = findIt->second;
//				return true;
//			}
//		}
//	}
//	return false;
//}

osg::Node* Layer::GetLayerNode()
{
	 return m_pNode;
}

void Layer::UpdateLayer()
{
	osg::StateSet* stateset = m_pNode->getOrCreateStateSet();
	stateset->setAttributeAndModes(m_LineWidth,osg::StateAttribute::ON);
	stateset->setAttributeAndModes(m_PointSize,osg::StateAttribute::ON);
	stateset->setAttributeAndModes(m_LineStripple,osg::StateAttribute::ON);
	m_v4LayerColor.set(m_v4LayerColor.r(), m_v4LayerColor.g(), m_v4LayerColor.b(), m_uAlphaValue/100.0);
	std::map<int, std::auto_ptr<Geometry>>::iterator goGeomIter = m_pgoGeometry->begin();
	while(goGeomIter != m_pgoGeometry->end())
	{
		Geometry* goGeom = goGeomIter->second.get();
		if(goGeom)
		{
			goGeom->UpdateGeometry();
		}
		goGeomIter++;
	}

	//SyncLayerAttributeTable();
}

//void Layer::SyncLayerAttributeTable()
//{
//	m_pLayerAttribteTable.clear();
//	m_LayerAttributeDescripe.clear();
//	//////////////////////////////////////////////////////////////////////////
//	InsertLayerAttribute(m_v4LayerColor,"��ɫ","Color","ͼ����ɫ",QVariant::Color);
//	InsertLayerAttribute(m_LineWidth,"�߿�","WidthInt","�߿�",QVariant::Double);
//	InsertLayerAttribute(QStringList()<<"ʵ��"<<"����","����","StrippleInt","����",QVariant::StringList);
//	InsertLayerAttribute(m_PointSize,"���С","PointInt","���С",QVariant::Double);
//	InsertLayerAttribute(m_uAlphaValue,"͸����","FuckYou","͸��������",QVariant::Int);
//}

void Layer::operator=(const Layer& other)
{
	this->m_layerZ = other.m_layerZ;
	this->m_v4LayerColor = other.m_v4LayerColor;//ͼ����ɫ
	this->m_fontSize = other.m_fontSize;
	this->m_textColor = other.m_textColor;
	this->m_bVisible = other.m_bVisible;
	this->m_fSize = other.m_fSize;

	this->m_PendingFieldMap = other.m_PendingFieldMap;
	this->m_LayerAttributeDescripe = other.m_LayerAttributeDescripe;
	//this->m_pLayerAttribteTable = other.m_pLayerAttribteTable;
	this->m_coordTrans = other.m_coordTrans;

	int count = 0;
	std::map<int, std::auto_ptr<Geometry>>::iterator goGeomIter = other.m_pgoGeometry->begin();
	while(goGeomIter != other.m_pgoGeometry->end())
	{
		Geometry* goGeom = goGeomIter->second.get();
		Geometry* newGoGeom = goGeom->Clone();
		
		this->m_pgoGeometry->insert(Layer::MapGeometryPair(count, newGoGeom));
		count++;
		goGeomIter++;
	}
	
	if(other.m_LineWidth) this->m_LineWidth = (osg::LineWidth*)other.m_LineWidth->clone(osg::CopyOp::DEEP_COPY_ALL);
	if(other.m_LineStripple) this->m_LineStripple = (osg::LineStipple*)other.m_LineStripple->clone(osg::CopyOp::DEEP_COPY_ALL);
	if(other.m_PointSize) this->m_PointSize = (osg::Point*)other.m_PointSize->clone(osg::CopyOp::DEEP_COPY_ALL);
	if(other.m_LayerMaterial) this->m_LayerMaterial = (osg::Material*)other.m_LayerMaterial->clone(osg::CopyOp::DEEP_COPY_ALL);

	this->m_pNode = other.m_pNode;//ָ������
	this->m_pParentMap = other.m_pParentMap;//ָ������
	this->m_PendingFieldMap = other.m_PendingFieldMap;
	this->m_LayerAttributeDescripe = other.m_LayerAttributeDescripe;
	//this->m_pLayerAttribteTable = other.m_pLayerAttribteTable;
	
	this->m_minScale = other.m_minScale;
	this->m_maxScale = other.m_maxScale;
	this->m_dataProvider.reset(other.m_dataProvider.get());
	this->b_trans = other.b_trans;
	this->m_bUseLayerZ = other.m_bUseLayerZ;
	this->m_textColor = other.m_textColor;
	this->m_fiedName = other.m_fiedName;
	this->m_pSymbolLibrary = other.m_pSymbolLibrary;//ָ������
	this->m_iUsedLegendID = other.m_iUsedLegendID;
	this->m_pParentLayer = other.m_pParentLayer;//ָ������
	this->m_pChildLayer = other.m_pChildLayer;//ָ������
	this->m_uAlphaValue = other.m_uAlphaValue;
}

GROUND_NAMESPACE_END