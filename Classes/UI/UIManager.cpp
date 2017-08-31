#include "UIManager.h"
#include "cocos2d.h"
#include "UIFactory.h"
#include "UIView.h"
#include "IScene.h"
#include "Tips.h"

USING_NS_CC;
UIManager::UIManager()
{

}

UIManager::~UIManager()
{
	Destory();
}

void UIManager::Show(ControllerID id)
{
	UIViewController* pController = nullptr;
	auto it = m_controllers.find(id);
	if ( it == m_controllers.end() )
	{
		pController = Create(id);
	}
	else
	{
		pController = it->second;
	}
	if (!pController) return;
	pController->ShowView();
}

void UIManager::Hide(ControllerID id)
{
	auto it = m_controllers.find(id);
	if ( it == m_controllers.end() || !it->second)
	{
		return;
	}
	auto pController = it->second;
	pController->HideView();
}

void UIManager::ShowOrHide(ControllerID id)
{
	auto it = m_controllers.find(id);
	if ( it == m_controllers.end() || !it->second )
	{
		Show(id);
	}
	else
	{
		auto pController = it->second;
		if ( pController->IsViewShow() )
		{
			pController->HideView();
		}
		else
		{
			pController->ShowView();
		}
	}
}

UIViewController* UIManager::GetController(ControllerID id , bool bIsCreate /* = true */ )
{
	UIViewController* pController = nullptr;
	auto it = m_controllers.find(id);
	if ( it != m_controllers.end() )
	{
		pController = it->second;
	}
	else
	{
		//找不到
		if ( bIsCreate )
		{
			pController = Create(id);
		}
	}

	if ( !pController )
	{
		CCLOGERROR("state id error , the id : %d", (int)id);
	}

	return pController;
}

const std::string UIManager::GetControllerViewName(ControllerID id)
{
	return UIFactory::getInstance()->getViewName(id);
}

void UIManager::ShowTips(const std::string& szContent)
{
	auto pTips = Tips::create(szContent);
	pTips->Show();
}

void UIManager::ShowMessageBox()
{

}

UIViewController* UIManager::Create(ControllerID id)
{
	auto pController = UIFactory::getInstance()->Create(id);
	if ( !pController )
	{
		CCLOGERROR("create state %d failure", (int)id);
		return nullptr;
	}
	if ( pController && pController->Init(this,id) )
	{
		m_controllers[id] = pController;
	}
	else
	{
		CC_SAFE_DELETE(pController);
	}
	return pController;
}

void UIManager::WillShow(UIViewController* pController)
{
	if ( pController && pController->getView() )
	{
		//这里做下处理，如果当前场景已经有了，就不做添加了
		auto pRunningScene = dynamic_cast<IScene*>(Director::getInstance()->getRunningScene());
		if ( !pRunningScene)
		{
			CCLOGERROR("all sence must be inherit IScene");
			return;
		}
		auto szStateName = GetControllerViewName(pController->getStateID());
		if (pRunningScene && !pRunningScene->getChildByName(szStateName) )
		{
			CCLOGERROR("current scene %d, add state viwe name is %s , zoder : %d", (int)pRunningScene->getSceneType(), szStateName.data(),pController->getSceneZOrder());
			pRunningScene->addChild(pController->getView(),pController->getSceneZOrder(),szStateName);
		}
		else
		{
			CCLOGERROR("current scene exist in scene %d, the state viwe name is %s",(int)pRunningScene->getSceneType(),szStateName.data());
		}
	}
	else
	{
		CCLOGERROR("state or state view is null");
	}
}

void UIManager::DidShow(UIViewController* pController)
{

}

void UIManager::WillHide(UIViewController* pController)
{

}

void UIManager::DidHide(UIViewController* pController)
{
	if ( pController  )
	{
		if ( pController->IsDestroyOnHideView() )
		{
			auto it = m_controllers.find(pController->getStateID());
			//从场景中移除
			pController->RemoveFromParent();

			//删除整个State
			if (it != m_controllers.end())
			{
				auto& pTemp = it->second;
				if (pTemp)
				{
					delete pTemp;
					pTemp = nullptr;
				}
				m_controllers.erase(it);
			}
		}
		else
		{
			//从场景中移除
			pController->RemoveFromParent();
		}
	}
}

void UIManager::Destory(ControllerID id)
{
	auto it = m_controllers.find(id);
	if ( it != m_controllers.end() )
	{
		auto& pController = it->second;
		if ( pController )
		{
			delete pController;
		}
		pController = nullptr;
		m_controllers.erase(it);
	}
}

void UIManager::Destory()
{
	for (auto it = m_controllers.begin(); it != m_controllers.end(); ++it )
	{
		auto& pController = it->second;
		if ( pController )
		{
			delete pController;
		}
		pController = nullptr;
	}
	m_controllers.clear();
}

void UIManager::Init(IScene* pScene)
{

}

void UIManager::OnEnter(IScene* pScene)
{

}

void UIManager::OnEnterTransitionDidFinish(IScene* pScene)
{

}

void UIManager::OnExit(IScene* pScene)
{
	//场景退出时，把场景上的界面给全部移除
	for (auto it = m_controllers.begin(); it != m_controllers.end(); ++it )
	{
		auto pController = it->second;
		if ( pController )
		{
			pController->RemoveFromParent();
		}
	}
}

void UIManager::OnExitTransitionDidStart(IScene* pScene)
{

}

GValue UIManager::GetValue(ControllerID id, const std::string& szValueName)
{
	if (id > ControllerID::Min && id < ControllerID::Max)
	{
		auto it = m_controllers.find(id);
		if (it == m_controllers.end())
		{
			return GValue::Null;
		}
		auto pDlg = it->second;
		if (!pDlg)
			return GValue::Null;
		return pDlg->GetValue(szValueName);
	}
	return GValue::Null;
}

