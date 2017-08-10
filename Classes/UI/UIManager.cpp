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

void UIManager::ShowDialog(DialogID id)
{
	Dialog* pDialog = nullptr;
	auto it = m_dialogs.find(id);
	if ( it == m_dialogs.end() )
	{
		pDialog = Create(id);
	}
	else
	{
		pDialog = it->second;
	}
	if (!pDialog) return;
	pDialog->ShowView();
}

void UIManager::HideDialog(DialogID id)
{
	auto it = m_dialogs.find(id);
	if ( it == m_dialogs.end() || !it->second)
	{
		return;
	}
	auto pDialog = it->second;
	pDialog->HideView();
}

void UIManager::ShowOrHideDialog(DialogID id)
{
	auto it = m_dialogs.find(id);
	if ( it == m_dialogs.end() || !it->second )
	{
		ShowDialog(id);
	}
	else
	{
		auto pDialog = it->second;
		if ( pDialog->IsViewShow() )
		{
			pDialog->HideView();
		}
		else
		{
			pDialog->ShowView();
		}
	}
}

Dialog* UIManager::GetDialog(DialogID id , bool bIsCreate /* = true */ )
{
	Dialog* pDialog = nullptr;
	auto it = m_dialogs.find(id);
	if ( it != m_dialogs.end() )
	{
		pDialog = it->second;
	}
	else
	{
		//找不到
		if ( bIsCreate )
		{
			pDialog = Create(id);
		}
	}

	if ( !pDialog )
	{
		CCLOGERROR("state id error , the id : %d", (int)id);
	}

	return pDialog;
}

const std::string UIManager::getDialogViewName(DialogID id)
{
	return UIFactory::getInstance()->getDialogViewName(id);
}

void UIManager::ShowTips(const std::string& szContent)
{
	auto pTips = Tips::create(szContent);
	pTips->Show();
}

void UIManager::ShowMessageBox()
{

}

Dialog* UIManager::Create(DialogID id)
{
	auto pDialog = UIFactory::getInstance()->Create(id);
	if ( !pDialog )
	{
		CCLOGERROR("create state %d failure", (int)id);
		return nullptr;
	}
	if ( pDialog && pDialog->Init(this,id) )
	{
		m_dialogs[id] = pDialog;
	}
	return pDialog;
}

void UIManager::WillShow(Dialog* pDialog)
{
	if ( pDialog && pDialog->getView() )
	{
		//这里做下处理，如果当前场景已经有了，就不做添加了
		auto pRunningScene = dynamic_cast<IScene*>(Director::getInstance()->getRunningScene());
		if ( !pRunningScene)
		{
			CCLOGERROR("all sence must be inherit IScene");
			return;
		}
		auto szStateName = getDialogViewName(pDialog->getStateID());
		if (pRunningScene && !pRunningScene->getChildByName(szStateName) )
		{
			CCLOGERROR("current scene %d, add state viwe name is %s , zoder : %d", (int)pRunningScene->getSceneType(), szStateName.data(),pDialog->getSceneZOrder());
			pRunningScene->addChild(pDialog->getView(),pDialog->getSceneZOrder(),szStateName);
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

void UIManager::DidShow(Dialog* pDialog)
{

}

void UIManager::WillHide(Dialog* pDialog)
{

}

void UIManager::DidHide(Dialog* pDialog)
{
	if ( pDialog  )
	{
		if ( pDialog->IsDestroyOnHideView() )
		{
			auto it = m_dialogs.find(pDialog->getStateID());
			//从场景中移除
			pDialog->RemoveFromParent();

			//删除整个State
			if (it != m_dialogs.end())
			{
				auto& pTemp = it->second;
				if (pTemp)
				{
					delete pTemp;
					pTemp = nullptr;
				}
				m_dialogs.erase(it);
			}
		}
		else
		{
			//从场景中移除
			pDialog->RemoveFromParent();
		}
	}
}

void UIManager::Destory(DialogID id)
{
	auto it = m_dialogs.find(id);
	if ( it != m_dialogs.end() )
	{
		auto& pDialog = it->second;
		if ( pDialog )
		{
			delete pDialog;
		}
		pDialog = nullptr;
		m_dialogs.erase(it);
	}
}

void UIManager::Destory()
{
	for (auto it = m_dialogs.begin(); it != m_dialogs.end(); ++it )
	{
		auto& pDialog = it->second;
		if ( pDialog )
		{
			delete pDialog;
		}
		pDialog = nullptr;
	}
	m_dialogs.clear();
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
	for (auto it = m_dialogs.begin(); it != m_dialogs.end(); ++it )
	{
		auto pDialog = it->second;
		if ( pDialog )
		{
			pDialog->RemoveFromParent();
		}
	}
}

void UIManager::OnExitTransitionDidStart(IScene* pScene)
{

}

