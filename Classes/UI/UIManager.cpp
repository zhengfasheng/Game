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

void UIManager::ShowState(StateID id)
{
	State* pState = nullptr;
	auto it = m_states.find(id);
	if ( it == m_states.end() )
	{
		pState = CreateState(id);
	}
	else
	{
		pState = it->second;
	}
	if (!pState) return;
	pState->ShowView();
}

void UIManager::HideState(StateID id)
{
	auto it = m_states.find(id);
	if ( it == m_states.end() || !it->second)
	{
		return;
	}
	auto pState = it->second;
	pState->HideView();
}

void UIManager::ShowOrHideState(StateID id)
{
	auto it = m_states.find(id);
	if ( it == m_states.end() || !it->second )
	{
		ShowState(id);
	}
	else
	{
		auto pState = it->second;
		if ( pState->IsViewShow() )
		{
			pState->HideView();
		}
		else
		{
			pState->ShowView();
		}
	}
}

State* UIManager::GetState(StateID id , bool bIsCreate /* = true */ )
{
	State* pState = nullptr;
	auto it = m_states.find(id);
	if ( it != m_states.end() )
	{
		pState = it->second;
	}
	else
	{
		//找不到
		if ( bIsCreate )
		{
			pState = CreateState(id);
		}
	}

	if ( !pState )
	{
		CCLOGERROR("state id error , the id : %d", (int)id);
	}

	return pState;
}

const std::string UIManager::getStateViewName(StateID id)
{
	return UIFactory::getInstance()->getStateViewName(id);
}

void UIManager::ShowTips(const std::string& szContent)
{
	auto pTips = Tips::create(szContent);
	pTips->Show();
}

void UIManager::ShowMessageBox()
{

}

State* UIManager::CreateState(StateID id)
{
	auto pState = UIFactory::getInstance()->CreateState(id);
	if ( !pState )
	{
		CCLOGERROR("create state %d failure", (int)id);
		return nullptr;
	}
	if ( pState && pState->Init(this,id) )
	{
		m_states[id] = pState;
	}
	return pState;
}

void UIManager::WillShow(State* pState)
{
	if ( pState && pState->getView() )
	{
		//这里做下处理，如果当前场景已经有了，就不做添加了
		auto pRunningScene = dynamic_cast<IScene*>(Director::getInstance()->getRunningScene());
		if ( !pRunningScene)
		{
			CCLOGERROR("all sence must be inherit IScene");
			return;
		}
		auto szStateName = getStateViewName(pState->getStateID());
		if (pRunningScene && !pRunningScene->getChildByName(szStateName) )
		{
			CCLOGERROR("current scene %d, add state viwe name is %s , zoder : %d", (int)pRunningScene->getSceneType(), szStateName.data(),pState->getSceneZOrder());
			pRunningScene->addChild(pState->getView(),pState->getSceneZOrder(),szStateName);
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

void UIManager::DidShow(State* pState)
{

}

void UIManager::WillHide(State* pState)
{

}

void UIManager::DidHide(State* pState)
{
	if ( pState  )
	{
		if ( pState->IsDestroyOnHideView() )
		{
			auto it = m_states.find(pState->getStateID());
			//从场景中移除
			pState->RemoveFromParent();

			//删除整个State
			if (it != m_states.end())
			{
				auto& pTemp = it->second;
				if (pTemp)
				{
					delete pTemp;
					pTemp = nullptr;
				}
				m_states.erase(it);
			}
		}
		else
		{
			//从场景中移除
			pState->RemoveFromParent();
		}
	}
}

void UIManager::Destory(StateID id)
{
	auto it = m_states.find(id);
	if ( it != m_states.end() )
	{
		auto& pState = it->second;
		if ( pState )
		{
			delete pState;
		}
		pState = nullptr;
		m_states.erase(it);
	}
}

void UIManager::Destory()
{
	for (auto it = m_states.begin(); it != m_states.end(); ++it )
	{
		auto& pState = it->second;
		if ( pState )
		{
			delete pState;
		}
		pState = nullptr;
	}
	m_states.clear();
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
	for (auto it = m_states.begin(); it != m_states.end(); ++it )
	{
		auto pState = it->second;
		if ( pState )
		{
			pState->RemoveFromParent();
		}
	}
}

void UIManager::OnExitTransitionDidStart(IScene* pScene)
{

}

