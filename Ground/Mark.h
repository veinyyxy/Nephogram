#pragma once
/** @file		Mark.h
* @brief		
* @author		杨晓宇
* @date			2013.4
* @version		1.0
  @note			
*/
#include "Config.h"

#include <osg/LineWidth>
#include <osg/LineStipple>
#include <osg/Point>
#include <osgText/Text>
#include <osgText/TextBase>


#include "CoordinateTransform.h"
#include "Geometry.h"

GROUND_NAMESPACE_START
class Layer;

/** @class  Mark
    @brief  字库标注类
    @author 杨晓宇
    @note   成员功能参见接口类。
*/
class GROUND_EXPORT Mark : public Geometry
{
public:
	Mark(void);
	Mark(std::string markLabel, osg::Vec3 markPostion,Layer* pL);
	virtual ~Mark(void);

	virtual void CreateOsgFromGeos(osg::Node* pNode);
	virtual void SetCoordinateTransform(CoordinateTransform* pCT);
	virtual geom::GeometryTypeId GetGeometryType();
	virtual void TransformGeometry();

	inline void MarkPostion(osg::Vec3& pos){m_markPostion = pos;}
	inline osg::Vec3 MarkPostion(){return m_markPostion;}

	inline float MarkSize(){return m_markSize;}
	inline void MarkSize(float markSize){m_markSize = markSize;}
	inline void SetFont(std::string& strFontPath){m_strFontPath = strFontPath;}
	inline void SetTextDirection(float fa){m_fTextDirection = fa;}
	inline void UsedLayerSet(bool bs){m_bUsedSet = bs;}
	inline void SetTextColor(float r, float g, float b, float a){m_markColor.set(r, g,b,a);}
	inline void SetAlignment(osgText::Text::AlignmentType al){m_alignment = al;};
	inline osgText::Text* GetMarkText(){return m_markText;}
	inline void SetText(const std::string& strText){m_markLabel = strText;}
	inline void SetText(const std::wstring& wstrText){m_markText->setText(wstrText.data());}

	inline std::string GetLabel() { return m_markLabel;}
	inline osg::Vec3 GetPostion() { return m_markPostion;}

	virtual void operator=(const Mark& other);

	virtual Geometry* Clone();

private:
	std::string m_strFontPath;
	osgText::Text* m_markText;
	std::string m_markLabel;
	osg::Vec4 m_markColor;
	osg::Vec3 m_markPostion;
	float m_markSize;
	float m_fTextDirection;
	osgText::Text::AlignmentType m_alignment;
	bool m_bUsedSet;

};

GROUND_NAMESPACE_END