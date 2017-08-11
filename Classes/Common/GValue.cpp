#include "GValue.h"
#include <numeric>
#include <math.h>
#include "commontools.h"

const GValue GValue::Null;

GValue::GValue()
	:m_type(Type::NONE)
	, m_pFormat(nullptr)
{
	memset(&m_data, 0, sizeof(Data));
}

GValue::GValue(int nValue)
	: m_type(Type::INT)
	, m_pFormat(nullptr)
{
	m_data.nValue = nValue;
}

GValue::GValue(float fValue)
	: m_type(Type::FLOAT)
	, m_pFormat(nullptr)
{
	m_data.fValue = fValue;
}

GValue::GValue(double fValue)
	: m_type(Type::DOUBLE)
	, m_pFormat(nullptr)
{
	m_data.dValue = fValue;
}

GValue::GValue(bool bValue)
	: m_type(Type::BOOL)
	, m_pFormat(nullptr)
{
	m_data.bValue = bValue;
}

GValue::GValue(void* pVoidValue)
	: m_type(Type::PVOID)
	, m_pFormat(nullptr)
{
	m_data.pVoid = pVoidValue;
}

GValue::GValue(const string& szValue)
	: m_type(Type::STRING)
	, m_pFormat(nullptr)
{
	m_data.pStringValue = new string;
	*m_data.pStringValue = szValue;
}

GValue::GValue(const char* szValue)
	:m_type(Type::STRING)
	, m_pFormat(nullptr)
{
	m_data.pStringValue = new string;
	if (szValue)
	{
		*m_data.pStringValue = szValue;
	}
}

GValue::GValue(long long lValue)
	:m_type(Type::INT64)
	, m_pFormat(nullptr)
{
	m_data.lValue = lValue;
}

GValue::GValue(const GValue& value)
	:m_type(Type::NONE)
{
	*this = value;
}

GValue::GValue(GValue&& value)
	: m_type(Type::NONE)
{
	*this = std::move(value);
}

GValue::~GValue()
{
	clear();
}

void GValue::clear()
{
	switch (m_type)
	{
	case GValue::Type::INT:
		m_data.nValue = 0;
		break;
	case GValue::Type::STRING:
		{
			if (m_data.pStringValue)
			{
				delete m_data.pStringValue;
			}
			m_data.pStringValue = nullptr;
		}
		break;
	case GValue::Type::FLOAT:
		m_data.fValue = 0.0f;
		break;
	case GValue::Type::DOUBLE:
		m_data.dValue = 0.0;
		break;
	case GValue::Type::PVOID:
		m_data.pVoid = nullptr;
		break;
	case GValue::Type::BOOL:
		m_data.bValue = false;
		break;
	case GValue::Type::INT64:
		m_data.lValue = 0;
	case GValue::Type::NONE:
		memset(&m_data, 0, sizeof(Data));
	default:
		break;
	}
	if (m_pFormat && m_type != Type::NONE )
	{
		delete m_pFormat;
	}
	m_pFormat = nullptr;
	m_type = Type::NONE;
}

const int GValue::asInt() const
{
	int result = 0;
	switch (m_type)
	{
	case GValue::Type::NONE:
		break;
	case GValue::Type::INT:
		result = m_data.nValue;
		break;
	case GValue::Type::STRING:
		result = m_data.pStringValue ? atoi(m_data.pStringValue->data()) : 0;
		break;
	case GValue::Type::FLOAT:
		result = static_cast<int>(m_data.fValue);
		break;
	case GValue::Type::DOUBLE:
		result = static_cast<int>(m_data.dValue);
		break;
	case GValue::Type::PVOID:
		break;
	case GValue::Type::BOOL:
		result = m_data.bValue ? 1 : 0;
		break;
	case GValue::Type::INT64:
		result = static_cast<int>(m_data.lValue);
		break;
	default:
		break;
	}
	return result;
}

const long long GValue::asInt64() const
{
	long long result = 0;
	switch (m_type)
	{
	case GValue::Type::NONE:
		break;
	case GValue::Type::INT:
		result = static_cast<long long>(m_data.nValue);
		break;
	case GValue::Type::STRING:
#if( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
		result = m_data.pStringValue ? _atoi64(m_data.pStringValue->data()) : 0;
#else
		result = m_data.pStringValue ? atoll(m_data.pStringValue->data()) : 0;
#endif
		break;
	case GValue::Type::FLOAT:
		result = static_cast<long long>(m_data.fValue);
		break;
	case GValue::Type::DOUBLE:
		result = static_cast<long long>(m_data.dValue);
		break;
	case GValue::Type::PVOID:
		break;
	case GValue::Type::BOOL:
		result = m_data.bValue ? 1 : 0;
		break;
	case GValue::Type::INT64:
		result = m_data.lValue;
		break;
	default:
		break;
	}
	return result;
}

const float GValue::asFloat() const 
{
	float result = 0.f;
	switch (m_type)
	{
	case GValue::Type::NONE:
		break;
	case GValue::Type::INT:
		result = static_cast<float>(m_data.nValue);
		break;
	case GValue::Type::STRING:
		result = m_data.pStringValue ? atof(m_data.pStringValue->data()) : 0;
		break;
	case GValue::Type::FLOAT:
		result = m_data.fValue;
		break;
	case GValue::Type::DOUBLE:
		result = static_cast<float>(m_data.dValue);
		break;
	case GValue::Type::PVOID:
		break;
	case GValue::Type::BOOL:
		result = m_data.bValue ? 1.f : 0.f;
		break;
	case GValue::Type::INT64:
		result = static_cast<float>(m_data.lValue);
		break;
	default:
		break;
	}
	return result;
}

const double GValue::asDouble() const 
{
	double result = 0.;
	switch (m_type)
	{
	case GValue::Type::NONE:
		break;
	case GValue::Type::INT:
		result = static_cast<double>(m_data.nValue);
		break;
	case GValue::Type::STRING:
		result = m_data.pStringValue ? atof(m_data.pStringValue->data()) : 0;
		break;
	case GValue::Type::FLOAT:
		result = static_cast<double>(m_data.fValue);
		break;
	case GValue::Type::DOUBLE:
		result = m_data.dValue;
		break;
	case GValue::Type::PVOID:
		break;
	case GValue::Type::BOOL:
		result = m_data.bValue ? 1. : 0.;
		break;
	case GValue::Type::INT64:
		result = static_cast<double>(m_data.lValue);
		break;
	default:
		break;
	}
	return result;
}

const bool GValue::asBool() const
{
	bool result = false;
	switch (m_type)
	{
	case GValue::Type::NONE:
		break;
	case GValue::Type::INT:
		result = m_data.nValue == 1;
		break;
	case GValue::Type::STRING:
		result = m_data.pStringValue ? (*m_data.pStringValue == "1" || *m_data.pStringValue == "true" ) : false;
		break;
	case GValue::Type::FLOAT:
		result = !(m_data.fValue == 0.0f);
		break;
	case GValue::Type::DOUBLE:
		result = !(m_data.dValue == 0.0);
		break;
	case GValue::Type::PVOID:
		break;
	case GValue::Type::BOOL:
		result = m_data.bValue;
		break;
	case GValue::Type::INT64:
		result = m_data.lValue == 1;
		break;
	default:
		break;
	}
	return result;
}

const string GValue::asString() const
{
	string result = "";
	switch (m_type)
	{
	case GValue::Type::NONE:
		result = "null";
		break;
	case GValue::Type::INT:
		{
			if ( m_pFormat )
			{
				char buf[128] = { 0 };
				sprintf(buf, m_pFormat->data(), m_data.nValue);
				result = buf;
			}
			else
			{
				result = toString(m_data.nValue);
			}
		}
		break;
	case GValue::Type::STRING:
		result = m_data.pStringValue ? *m_data.pStringValue : "";
		break;
	case GValue::Type::FLOAT:
		{
			if ( m_pFormat )
			{
				char buf[128] = { 0 };
				sprintf(buf, m_pFormat->data(), m_data.fValue);
				result = buf;
			}
			else
			{
				result = toString(m_data.fValue);
			}
		}
		break;
	case GValue::Type::DOUBLE:
		{
			if (m_pFormat)
			{
				char buf[128] = { 0 };
				sprintf(buf, m_pFormat->data(), m_data.dValue);
				result = buf;
			}
			else
			{
				result = toString(m_data.dValue);
			}
		}
		break;
	case GValue::Type::PVOID:
		result = "0x" + toString(m_data.pVoid);
		break;
	case GValue::Type::BOOL:
		result = toString(m_data.bValue);
		break;
	case GValue::Type::INT64:
	{
		if (m_pFormat)
		{
			char buf[128] = { 0 };
			sprintf(buf, m_pFormat->data(), m_data.lValue);
			result = buf;
		}
		else
		{
			result = toString(m_data.lValue);
		}
	}
		break;
	default:
		break;
	}
	return result;
}

const char* GValue::asCString() const
{
	return asString().data();
}

const void* GValue::asPointer() const
{
	const void* pRet = nullptr;
	switch (m_type)
	{
	case GValue::Type::NONE:
		break;
	case GValue::Type::INT:
		pRet = &m_data.nValue;
		break;
	case GValue::Type::STRING:
		pRet = m_data.pStringValue;
		break;
	case GValue::Type::FLOAT:
		pRet = &m_data.fValue;
		break;
	case GValue::Type::DOUBLE:
		pRet = &m_data.dValue;
		break;
	case GValue::Type::PVOID:
		pRet = m_data.pVoid;
		break;
	case GValue::Type::BOOL:
		pRet = &m_data.bValue;
		break;
	case GValue::Type::INT64:
		pRet = &m_data.lValue;
		break;
	default:
		break;
	}
	return pRet;
}

GValue& GValue::operator=(const GValue& other)
{
	if (this != &other) {
		reset(other.m_type);
		switch (other.m_type)
		{
		case GValue::Type::INT:
			m_data.nValue = other.m_data.nValue;
			break;
		case GValue::Type::STRING:
			{
				if ( !m_data.pStringValue )
				{
					m_data.pStringValue = new string;
				}
				*m_data.pStringValue = *other.m_data.pStringValue;
			}
			break;
		case GValue::Type::FLOAT:
			m_data.fValue = other.m_data.fValue;
			break;
		case GValue::Type::DOUBLE:
			m_data.dValue = other.m_data.dValue;
			break;
		case GValue::Type::PVOID:
			m_data.pVoid = other.m_data.pVoid;
			break;
		case GValue::Type::BOOL:
			m_data.bValue = other.m_data.bValue;
			break;
		default:
			break;
		}
		if ( m_type != Type::NONE && other.m_pFormat )
		{
			if (m_pFormat) delete m_pFormat;
			m_pFormat = new (std::nothrow) std::string;
			*m_pFormat = *other.m_pFormat;
		}
		
	}
	return *this;
}

GValue& GValue::operator=(GValue&& other)
{
	if ( this != &other )
	{
		clear();
		switch (other.m_type)
		{
		case GValue::Type::INT:
			m_data.nValue = other.m_data.nValue;
			break;
		case GValue::Type::STRING:
			m_data.pStringValue = other.m_data.pStringValue;
			break;
		case GValue::Type::FLOAT:
			m_data.fValue = other.m_data.fValue;
			break;
		case GValue::Type::DOUBLE:
			m_data.dValue = other.m_data.dValue;
			break;
		case GValue::Type::PVOID:
			m_data.pVoid = other.m_data.pVoid;
			break;
		case GValue::Type::BOOL:
			m_data.bValue = other.m_data.bValue;
			break;
		default:
			break;
		}
		m_type = other.m_type;
		m_pFormat = other.m_pFormat;
		memset(&other.m_data, 0, sizeof(Data));
		other.m_pFormat = nullptr;
		other.m_type = Type::NONE;
		
	}
	return *this;
}

GValue& GValue::operator=(int nValue)
{
	reset(Type::INT);
	m_data.nValue = nValue;
	return *this;
}

GValue& GValue::operator=(float fValue)
{
	reset(Type::FLOAT);
	m_data.fValue = fValue;
	return *this;
}

GValue& GValue::operator=(double dValue)
{
	reset(Type::DOUBLE);
	m_data.dValue = dValue;
	return *this;
}

GValue& GValue::operator=(bool bValue)
{
	reset(Type::BOOL);
	m_data.bValue = bValue;
	return *this;
}

GValue& GValue::operator=(void* pVoidValue)
{
	reset(Type::PVOID);
	m_data.pVoid = pVoidValue;
	return *this;
}

GValue& GValue::operator=(const string& szValue)
{
	reset(Type::STRING);
	*m_data.pStringValue = szValue;
	return *this;
}

GValue& GValue::operator=(const char* szValue)
{
	reset(Type::STRING);
	*m_data.pStringValue = szValue ? szValue : "";
	return *this;
}

GValue& GValue::operator=(long long lValue)
{
	reset(Type::INT64);
	m_data.lValue = lValue;
	return *this;
}

void GValue::reset(Type type)
{
	if (m_type == type)
		return;

	clear();

	switch (type)
	{
	case Type::STRING:
		m_data.pStringValue = new string();
		break;
	default:
		break;
	}

	m_type = type;
}

bool GValue::operator==(const GValue& other)
{
	const auto& value = *this;
	return value == other;
}

bool GValue::operator==(const GValue& other) const
{
	if (this == &other) return true;
	if (m_type != other.m_type) return false;
	if (this->isNull()) return true;
	switch (m_type)
	{
	case GValue::Type::INT:
		return m_data.nValue == other.m_data.nValue;
		break;
	case GValue::Type::STRING:
		return *m_data.pStringValue == *other.m_data.pStringValue;
		break;
	case GValue::Type::FLOAT:
		return fabs(m_data.fValue - other.m_data.fValue) <= std::numeric_limits<float>::min();
		break;
	case GValue::Type::DOUBLE:
		return fabs(m_data.dValue - other.m_data.dValue) <= std::numeric_limits<double>::min();
		break;
	case GValue::Type::PVOID:
		return m_data.pVoid == other.m_data.pVoid;
		break;
	case GValue::Type::BOOL:
		return m_data.bValue == other.m_data.bValue;
		break;
	case GValue::Type::INT64:
		return m_data.lValue == other.m_data.lValue;
		break;
	default:
		break;
	}
	return false;
}

bool GValue::operator!=(const GValue& other)
{
	return !(*this == other);
}

bool GValue::operator!=(const GValue& other) const
{
	return !(*this == other);
}

std::string GValue::getFormatString() const
{
	string szFormat = "";
	switch (m_type)
	{
	case GValue::Type::INT:
		szFormat = m_pFormat ? *m_pFormat : "%d";
		break;
	case GValue::Type::STRING:
		szFormat = "%s";
		break;
	case GValue::Type::FLOAT:
		szFormat = m_pFormat ? *m_pFormat : "%f";
		break;
	case GValue::Type::DOUBLE:
		szFormat = m_pFormat ? *m_pFormat : "%f";
		break;
	case GValue::Type::PVOID:
		szFormat = "%p";
		break;
	case GValue::Type::BOOL:
		szFormat = "%d";
		break;
	case GValue::Type::INT64:
		szFormat = m_pFormat ? *m_pFormat : "%lld";
		break;
	case GValue::Type::NONE:
		szFormat = "%s";
		break;
	default:
		break;
	}
	return szFormat;
}

bool GValue::checkFormat(const string& szFormat)
{
	bool bRet = false;
	do 
	{
		if (m_type == Type::NONE || m_type == Type::STRING || m_type == Type::PVOID || m_type == Type::BOOL )
			break;
		if (szFormat.empty())
			break;
		if (string::npos == szFormat.find("%"))//如果找不到%，说明这个指定有问题，不更换默认格式串
			break;
		bRet = true;
	} while (0);
	return bRet;
}

GValue& GValue::setFormatString(const string& szFormat)
{
	if ( !checkFormat(szFormat) )
	{
		return *this;
	}
	//可能指定的长度不一样，这里先删除掉在申请
	if (m_pFormat)
	{
		delete m_pFormat;
	}

	m_pFormat = new (std::nothrow) string;
	*m_pFormat = szFormat;
	return *this;
}



