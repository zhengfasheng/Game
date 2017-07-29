#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "IScene.h"

class LoginScene : public IScene
{
public:
	IMPLEMENT_CREATE_SCENE(LoginScene,SceneType::Login);

	virtual void DidEnter() override;
};

#endif // __HELLOWORLD_SCENE_H__
