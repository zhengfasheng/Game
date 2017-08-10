#include "UIFactory.h"
#include "LoginDialog.h"
#include "HallMainDialog.h"
#include "HallBottomDialog.h"
#include "HallActivityDialog.h"
#include "HallUserInfoDialog.h"


#define GET_DIALOG_INFO_BEGIN \
void UIFactory::getDialogInfo( DialogID id,std::string& szName, std::function<Dialog*()>& createFun )\
{\
	switch (id)\
	{\

#define GET_DIALOG_INFO( id , StateClass )\
	case id :\
	{\
		szName = "state_" + std::string(#StateClass) + "_view";\
		createFun = [](){ return new StateClass;};\
	}\
	break

#define GET_DIALOG_INFO_END \
	default:\
		break;\
	}\
}

GET_DIALOG_INFO_BEGIN

GET_DIALOG_INFO(DialogID::Login, LoginDialog);
GET_DIALOG_INFO(DialogID::HallMain, HallMainDialog);
GET_DIALOG_INFO(DialogID::HallBottom, HallBottomDialog);
GET_DIALOG_INFO(DialogID::HallActivity, HallActivityDialog);
GET_DIALOG_INFO(DialogID::HallUserInfo, HallUserInfoDialog);
	
GET_DIALOG_INFO_END



UIFactory::UIFactory()
{

}

UIFactory::~UIFactory()
{

}

Dialog* UIFactory::Create(DialogID id)
{
	std::string szName = "";
	std::function<Dialog*()> createFunc = nullptr;
	getDialogInfo(id, szName, createFunc);
	if (createFunc)
	{
		return createFunc();
	}
	return nullptr;
}

const std::string UIFactory::getDialogViewName(DialogID id)
{
	std::string szName = "";
	std::function<Dialog*()> createFunc = nullptr;
	getDialogInfo(id, szName, createFunc);
	return szName;
}