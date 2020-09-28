#include "SymbolContainer.h"
#include <osg/AutoTransform>
#include <osg/MatrixTransform>


#include "Layer.h"
GROUND_NAMESPACE_START

SymbolContainer::SymbolContainer(SymbolContainer::CONTAINER_MODE mod) : m_pCoordinateTransform(0), m_pParentNode(0), m_mode(mod)
{
	bAngleEnable = false, bNodeSymbol = false, bDrawableSymbol = false;
	bScaleEnable = false;
	m_posArray = new osg::Vec3Array;
	m_ColorArray = new osg::Vec4Array;
}


SymbolContainer::~SymbolContainer(void)
{
}

void SymbolContainer::CreateOsgFromGeos( osg::Node* pNode )
{
	if(!m_pCoordinateTransform) return;
	
	osg::Group* pGoup = dynamic_cast<osg::Group*>(pNode);
	m_pParentNode = pGoup;
	
	if(m_mode == MODE1)
	{
		osg::Vec3 PosTemp;
		if(m_angleArray.size() == m_posArray->size())
			bAngleEnable = true;

		if(m_scaleArray.size() == m_posArray->size())
			bScaleEnable = true;

		if(m_pGeometryArray.size() == m_posArray->size())
			bDrawableSymbol = true;

		if(!bDrawableSymbol)
		{
			if(m_pNodeArray.size() == m_posArray->size())
			{
				bNodeSymbol = true;
			}
			else
				return;
		}

		if(pGoup)
		{
			for(unsigned int i = 0; i < m_posArray->size(); i++)
			{
				osg::Vec3 v3pos = m_posArray->at(i);
				osg::ref_ptr<osg::AutoTransform> pAutoTransfrom = new osg::AutoTransform;
				pAutoTransfrom->setAutoScaleToScreen(true);
				m_pCoordinateTransform->Transform(v3pos, PosTemp);

				PosTemp.set(PosTemp.x(), GetParentLayer()->LayerZ(), PosTemp.z());
				pAutoTransfrom->setPosition(PosTemp);
				osg::ref_ptr<osg::Geode> pGeode = new osg::Geode;
				if(bAngleEnable || bScaleEnable)
				{
					osg::ref_ptr<osg::MatrixTransform> pMatrixTransform = new osg::MatrixTransform;
					osg::Matrix m4Rot, m4Scale, m4Result;


					if(bAngleEnable && bScaleEnable)
					{
						m4Scale.makeScale(osg::Vec3(m_scaleArray.at(i), m_scaleArray.at(i), 1.0));
						m4Rot.makeRotate(m_angleArray.at(i), osg::Vec3(0, 0, 1));
					}
					else
					{
						if(bScaleEnable)
						{
							m4Scale.makeScale(osg::Vec3(m_scaleArray.at(i), m_scaleArray.at(i), 1.0));
						}
						else
						{
							m4Rot.makeRotate(m_angleArray.at(i), osg::Vec3(0, 0, 1));
						}
					}

					m4Result = m4Rot * m4Scale;

					pMatrixTransform->setMatrix(m4Result);

					if(bDrawableSymbol)
					{
						osg::ref_ptr<osg::Geode> pGeode = new osg::Geode;
						pGeode->addDrawable(m_pGeometryArray.at(i));
						pMatrixTransform->addChild(pGeode);
					}
					else
						pMatrixTransform->addChild(m_pNodeArray.at(i));
					pAutoTransfrom->addChild(pMatrixTransform);
					m_pParentNode->addChild(pAutoTransfrom);

					m_AutoTransformNode.push_back(pAutoTransfrom);
				}
				else
				{
					osg::ref_ptr<osg::Geode> pGeode = new osg::Geode;
					pGeode->addDrawable(m_pGeometryArray.at(i));
					pAutoTransfrom->addChild(pGeode);
					m_pParentNode->addChild(pAutoTransfrom);
					m_AutoTransformNode.push_back(pAutoTransfrom);
				}
			}
		}
	}
	else
	{
		osg::Vec3 PosTemp;

		if(m_pNodeArray.size() > 0) bNodeSymbol = true;
		if(m_pGeometryArray.size() > 0) bDrawableSymbol = true;

		if(pGoup)
		{
			if(m_posArray->size() <= 0) return;

			osg::Vec3 v3pos = m_posArray->at(0);
			osg::ref_ptr<osg::AutoTransform> pAutoTransfrom = new osg::AutoTransform;
			pAutoTransfrom->setAutoScaleToScreen(true);
			m_pCoordinateTransform->Transform(v3pos, PosTemp);

			PosTemp.set(PosTemp.x(), GetParentLayer()->LayerZ(), PosTemp.z());
			pAutoTransfrom->setPosition(PosTemp);

			pGoup->addChild(pAutoTransfrom);

			if(bDrawableSymbol)
			{
				for(size_t i = 0; i < m_pGeometryArray.size(); i++)
				{
					osg::Geode* pGeode = new osg::Geode;
					pGeode->addDrawable(m_pGeometryArray.at(i));
					pAutoTransfrom->addChild(pGeode);
				}
			}
			else if(bNodeSymbol)
			{
				for(size_t i = 0; i < m_pNodeArray.size(); i++)
				{
					pAutoTransfrom->addChild(m_pNodeArray.at(i));
				}
			}
		}
	}
}

void SymbolContainer::SetCoordinateTransform( CoordinateTransform* pCT )
{
	m_pCoordinateTransform = pCT;
}

geom::GeometryTypeId SymbolContainer::GetGeometryType()
{
	return (geom::GeometryTypeId)-1;
}

void SymbolContainer::TransformGeometry()
{
	osg::Vec3 orgPos, PosTemp;
	for(unsigned int i = 0; i<m_posArray->size(); i++)
	{
		orgPos = m_posArray->at(i);
		m_pCoordinateTransform->Transform(orgPos, PosTemp);

		unsigned int iCC = m_AutoTransformNode.size();

		if(iCC != m_posArray->size()) return;
		//osg::Node* pNode = m_pParentNode->getChild(i);
		osg::AutoTransform* pAutoTransform = m_AutoTransformNode.at(i);

		if(pAutoTransform)
		{
			PosTemp.set(PosTemp.x(), GetParentLayer()->LayerZ(), PosTemp.z());
			pAutoTransform->setPosition(PosTemp);
		}
	}
}

void SymbolContainer::AddSymbol(osg::Drawable* pGeom )
{
	osg::ref_ptr<osg::Drawable> pDrawable = pGeom;

	m_pGeometryArray.push_back(pDrawable);
}

void SymbolContainer::AddSymbol(osg::Node* pNode )
{
	osg::ref_ptr<osg::Node> pNodeRefPoint = pNode;

	m_pNodeArray.push_back(pNodeRefPoint);
}

void SymbolContainer::SetPositionArray( osg::Vec3Array* posArray )
{
	if(posArray)
		*m_posArray = *posArray;
	//m_posArray = posArray->clone(osg::CopyOp::DEEP_COPY_ARRAYS);
}

void SymbolContainer::SetAngleArray( std::vector<float>* angArray )
{
	if(angArray)
		m_angleArray = *angArray;
}

void SymbolContainer::SetColorArray( osg::Vec4Array* colorArray )
{
	if(colorArray)
		*m_ColorArray = *colorArray;
}

void SymbolContainer::SetScaleArray( std::vector<float>* scaleArray )
{
	if(scaleArray)
		m_scaleArray = *scaleArray;
}

void SymbolContainer::AddSymbolPosition( osg::Vec3* pVec3 )
{
	m_posArray->push_back(*pVec3);
}

void SymbolContainer::AddSymbolAngle(float fa)
{
	m_angleArray.push_back(fa);
}

void SymbolContainer::AddSymbolScale( float fa )
{
	m_scaleArray.push_back(fa);
}

GROUND_NAMESPACE_END