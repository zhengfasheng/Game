#include "UIFactory.h"
#include "LoginDialog.h"
#include "HallMainDialog.h"
#include "HallBottomDialog.h"
#include "HallActivityDialog.h"
#include "HallUserInfoDialog.h"


#define GET_CONTROLLER_INFO_BEGIN \
void UIFactory::getInfo( ControllerID id,std::string& szName, std::function<UIViewController*()>& createFun )\
{\
	switch (id)\
	{\

#define GET_CONTROLLER_INFO( id , StateClass )\
	case id :\
	{\
		szName = "state_" + std::string(#StateClass) + "_view";\
		createFun = [](){ return new StateClass;};\
	}\
	break

#define GET_CONTROLLER_INFO_END \
	default:\
		break;\
	}\
}

GET_CONTROLLER_INFO_BEGIN

GET_CONTROLLER_INFO(ControllerID::Login, LoginDialog);
GET_CONTROLLER_INFO(ControllerID::HallMain, HallMainDialog);
GET_CONTROLLER_INFO(ControllerID::HallBottom, HallBottomDialog);
GET_CONTROLLER_INFO(ControllerID::HallActivity, HallActivityDialog);
GET_CONTROLLER_INFO(ControllerID::HallUserInfo, HallUserInfoDialog);
	
GET_CONTROLLER_INFO_END



UIFactory::UIFactory()
{

}

UIFactory::~UIFactory()
{

}

UIViewController* UIFactory::Create(ControllerID id)
{
	std::string szName = "";
	std::function<UIViewController*()> createFunc = nullptr;
	getInfo(id, szName, createFunc);
	if (createFunc)
	{
		return createFunc();
	}
	return nullptr;
}

const std::string UIFactory::getViewName(ControllerID id)
{
	std::string szName = "";
	std::function<UIViewController*()> createFunc = nullptr;
	getInfo(id, szName, createFunc);
	return szName;
}