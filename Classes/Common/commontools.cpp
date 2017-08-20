#include "commontools.h"

void split(std::string src, const char* token, std::vector<std::string>& vect)
{
	vect.clear();
	if (token == nullptr || strlen(token) == 0)
	{
		return;
	}
	size_t nend = 0;
	size_t nbegin = 0;
	std::string strTemp = "";
	while (nend != std::string::npos  && nend != src.size())
	{
		nend = src.find(token, nbegin);
		if (nend == std::string::npos)
		{
			strTemp = src.substr(nbegin, src.length() - nbegin);
			if (!strTemp.empty())
			{
				vect.push_back(strTemp);
			}
		}
		else
		{
			strTemp = src.substr(nbegin, nend - nbegin);
			if (!strTemp.empty())
			{
				vect.push_back(strTemp);
			}
		}
		nbegin = nend + strlen(token);
	}
}

cocos2d::Texture2D* getTextureForKey(const std::string& key)
{
	USING_NS_CC;
	auto pTexture = Director::getInstance()->getTextureCache()->getTextureForKey(key);
	CCASSERT(pTexture, StringUtils::format("not find this texture , name is %s", key.data()).data());
	return pTexture;
}