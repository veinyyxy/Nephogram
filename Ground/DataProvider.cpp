#include "DataProvider.h"
#include "Layer.h"

GROUND_NAMESPACE_START

DataProvider::DataProvider()
{
	m_pParentLayer = 0;
}


DataProvider::~DataProvider()
{

}

void DataProvider::InsertExtendInterface( void* pIF )
{
	size_t iI = m_ExtendInterface.size();
	m_ExtendInterface.insert(INDEX_INTERFACE_PAIR(iI, pIF));
}

void* DataProvider::GetExtendInterface( int iI )
{
	INDEX_INTERFACE_MAP::iterator fr = m_ExtendInterface.find(iI);
	if(fr != m_ExtendInterface.end())
	{
		return fr->second;
	}
	else
		return 0;
}

bool DataProvider::MineData(const std::string&)
{
	return false;
}

GROUND_NAMESPACE_END