#pragma once
/** @file		DataProvider.h
* @brief		
* @author		������
* @date			2012.10
* @version		1.0
  @note			
*/
#include "Config.h"
#include "Geometry.h"
#include "Layer.h"

GROUND_NAMESPACE_START

using namespace std;

/** @class  DataProvider
    @brief  ͼ�������ṩ���ӿ���
    @author ������
    @note   
*/ 
class GROUND_EXPORT DataProvider
{
public:
	typedef std::pair<int, void*> INDEX_INTERFACE_PAIR, *P_INDEX_INTERFACE_PAIR;
	typedef std::map<int, void*> INDEX_INTERFACE_MAP, *P_INDEX_INTERFACE_MAP;
	DataProvider();
	virtual ~DataProvider();
public:
	/** 
	  * @brief			��������ṩ��������ġ��㡱    
	  * @author			������
	  * @param [in]		null
	  * @param [out]	null
	  * @return			Layer*
	  * @note			
	  * @date			2010.10                                
	  * @exception		null  
	  * @remarks remark null             
	  * @deprecated		null          
	  * @since			1.0           
	  * @see references         
	*/
	inline Layer* ParentLayer() {return m_pParentLayer;};

	/** 
	  * @brief			���������ṩ��������ġ��㡱     
	  * @author			������
	  * @param [in]		Layer*
	  * @param [out]	null
	  * @return			null
	  * @note			
	  * @date			2010.10                                
	  * @exception		null  
	  * @remarks remark null             
	  * @deprecated		null          
	  * @since			1.0           
	  * @see references         
	*/
	inline void ParentLayer(Layer* pl) {m_pParentLayer = pl;};

	/** 
	  * @brief			�����ļ�    
	  * @author			������
	  * @param [in]		std::string
	  * @param [out]	null
	  * @return			bool
	  * @note			
	  * @date			2010.10
	  * @exception		null
	  * @remarks remark null
	  * @deprecated		null
	  * @since			1.0 
	  * @see references         
	*/
	virtual bool LoadFile(const std::string& filename) = 0;
//	virtual inline bool LoadFile(const std::list<std::string>&filenameList ){return true;};
	/** 
	  * @brief			δ֪    
	  * @author			������
	  * @param [in]		std::string
	  * @param [out]	null
	  * @return			bool
	  * @note			
	  * @date			2010.10
	  * @exception		null
	  * @remarks remark null
	  * @deprecated		null
	  * @since			1.0 
	  * @see references         
	*/
	virtual inline bool LoadRefFile(const std::string&filename) {return false;};
	
	/** 
	  * @brief			���һ�������ṩ����չ�ӿ�    
	  * @author			������
	  * @param [in]		void*
	  * @param [out]	null
	  * @return			null
	  * @note			
	  * @date			2010.10                                
	  * @exception		null  
	  * @remarks remark null             
	  * @deprecated		null          
	  * @since			1.0           
	  * @see references         
	*/
	void InsertExtendInterface(void* pIF);
	
	/** 
	  * @brief			    
	  * @author			�õ�һ�������ṩ����չ�ӿ�
	  * @param [in]		null
	  * @param [out]	null
	  * @return			void*
	  * @note			
	  * @date			2010.10
	  * @exception		null
	  * @remarks remark null
	  * @deprecated		null
	  * @since			1.0
	  * @see references
	*/
	void* GetExtendInterface(int iI);
	virtual void AreaAdd(bool tArea,bool tPie,float tMin,float tMax,osg::Vec3Array* p)= 0;
	virtual bool MineData(const std::string& strIns = "");
	
	virtual float GetPositionValue(double lon,double lat,double height){return 0.0;};//��ȡ���λ�õ�������ֵ
	inline std::string GetFileName(){return m_fileName;}//�����������
protected:
	Layer* m_pParentLayer;
	INDEX_INTERFACE_MAP m_ExtendInterface;
	std::string     m_fileName;
};

GROUND_NAMESPACE_END