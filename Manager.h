//=========================================================================================
//
// [Manager.h] Author : Masaki Kuboki
//
//=========================================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"
#include "Input.h"
#include "XInput.h"
#include "2D.h"
#include "Sound.h"

#include "Scene.h"
#include "Scene3D.h"
#include "SceneCamera.h"
#include "ScenePlayer.h"
#include "SceneLight.h"
#include "SceneMeshField.h"
#include "SceneTime.h"
#include "SceneCircuit.h"
#include "SceneMeter.h"

#include "Mode.h"

#include "Number.h"
#include "RendererDX.h"

//*************************************
// class
//*************************************
class CManager
{
public:
	CManager();
	~CManager();

	static bool Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	static void Uninit(void);
	static void Update(void);
	static void Draw(void);
	static CSceneMeshField *GetField();
	static void SetMode(CMode *Mode);

private:
	//static CScene2D     *m_Scene2D;
	/*static CScene3D     *m_Scene3D;
	static CSceneCamera *m_SceneCamera;
	static CSceneLight  *m_SceneLight;
	static CScenePlayer  *m_ScenePlayer;
	static CSceneMeshField *m_SceneMeshField;
	static CSceneMeshField *m_Field;
	static CSceneTime *m_SceneTime;
	static CSceneMeter *m_Meter;
	static CSceneCircuit *m_SceneCircuit;*/

	static CMode *m_Mode;
};

#endif