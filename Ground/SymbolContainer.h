#pragma once
#include "Geometry.h"

GROUND_NAMESPACE_START

class GROUND_EXPORT SymbolContainer : public Geometry
{
public:
	enum CONTAINER_MODE{MODE1 = 1, MODE2 = 2};

	SymbolContainer(SymbolContainer::CONTAINER_MODE mod = SymbolContainer::MODE1);
	virtual ~SymbolContainer(void);
	virtual void CreateOsgFromGeos( osg::Node* pNode );
	virtual void SetCoordinateTransform( CoordinateTransform* pCT );
	virtual geom::GeometryTypeId GetGeometryType();
	virtual void TransformGeometry();
	void AddSymbol(osg::Drawable* pGeom);
	void AddSymbol(osg::Node* pNode);
	void AddSymbolPosition(osg::Vec3* pVec3);
	void AddSymbolAngle(float fa);
	void AddSymbolScale(float fa);

	void SetPositionArray(osg::Vec3Array* posArray);
	void SetAngleArray(std::vector<float>* angArray);
	void SetColorArray(osg::Vec4Array* colorArray);
	void SetScaleArray(std::vector<float>* scaleArray);

private:
	osg::Group* m_pParentNode;
	osg::ref_ptr<osg::Vec3Array> m_posArray;
	std::vector<float> m_angleArray;
	std::vector<float> m_scaleArray;
	osg::ref_ptr<osg::Vec4Array> m_ColorArray;

	std::vector<osg::ref_ptr<osg::Drawable>> m_pGeometryArray;
	std::vector<osg::ref_ptr<osg::Node>> m_pNodeArray;

	CoordinateTransform* m_pCoordinateTransform;

	std::vector<osg::AutoTransform*> m_AutoTransformNode;
	bool bAngleEnable, bNodeSymbol, bDrawableSymbol, bScaleEnable;

	SymbolContainer::CONTAINER_MODE m_mode;
};

GROUND_NAMESPACE_END