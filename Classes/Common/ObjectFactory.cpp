#include "ObjectFactory.h"
#include "tClass.h"

ObjectFactory::ObjectFactory()
{

}

ObjectFactory::~ObjectFactory()
{

}

void ObjectFactory::registerClass(tClass* pClass)
{
	if ( pClass )
	{
		auto it = m_classes.find(pClass->m_szClassName);
		if ( it == m_classes.end() )
		{
			m_classes[pClass->m_szClassName] = pClass;
		}
	}
}

Ref* ObjectFactory::create( const std::string& szClassName )
{
	auto it = m_classes.find(szClassName);
	if ( it != m_classes.end() )
	{
		auto pClass = it->second;
		if ( pClass && pClass->m_createFunc )
		{
			return pClass->m_createFunc();
		}
	}
	return nullptr;
}

