#include "UIFactory.h"
#include "StartController.h"
#include "AboutController.h"
#include "SettingController.h"
#include "GameController.h"
#include "GameOverController.h"

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

GET_CONTROLLER_INFO(ControllerID::Start, StartController);
GET_CONTROLLER_INFO(ControllerID::About, AboutController);
GET_CONTROLLER_INFO(ControllerID::Setting, SettingController);
GET_CONTROLLER_INFO(ControllerID::Game, GameController);
GET_CONTROLLER_INFO(ControllerID::GameOver, GameOverController);
	
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