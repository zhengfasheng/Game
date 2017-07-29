#include "UIFactory.h"
#include "LoginState.h"
#include "Hall\HallMainSate.h"
#include "Hall\HallBottomState.h"
#include "Hall\HallActivityState.h"
#include "Hall\HallUserInfoState.h"


#define GET_STATE_INFO_BEGIN \
void UIFactory::getStateInfo( StateID id,std::string& szName, std::function<State*()>& createFun )\
{\
	switch (id)\
	{\

#define GET_STATE_INFO( id , StateClass )\
	case id :\
	{\
		szName = "state_" + std::string(#StateClass) + "_view";\
		createFun = [](){ return new StateClass;};\
	}\
	break

#define GET_STATE_INFO_END \
	default:\
		break;\
	}\
}

GET_STATE_INFO_BEGIN

GET_STATE_INFO(StateID::Login, LoginState);
GET_STATE_INFO(StateID::HallMain, HallMainSate);
GET_STATE_INFO(StateID::HallBottom, HallBottomState);
GET_STATE_INFO(StateID::HallActivity, HallActivityState);
GET_STATE_INFO(StateID::HallUserInfo, HallUserInfoState);

GET_STATE_INFO_END



UIFactory::UIFactory()
{

}

UIFactory::~UIFactory()
{

}

State* UIFactory::CreateState(StateID id)
{
	std::string szName = "";
	std::function<State*()> createFunc = nullptr;
	getStateInfo(id, szName, createFunc);
	if (createFunc)
	{
		return createFunc();
	}
	return nullptr;
}

const std::string UIFactory::getStateViewName(StateID id)
{
	std::string szName = "";
	std::function<State*()> createFunc = nullptr;
	getStateInfo(id, szName, createFunc);
	return szName;
}