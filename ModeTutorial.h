//=====================================================================================================
//
// [SCene.h] Author : Masaki Kuboki
//
//=====================================================================================================
#ifndef _MODE_TUTORIAL_H_
#define _MODE_TUTORIAL_H_
#include "main.h"
#include "Mode.h"

class CScene3D;
class CSceneCamera;
class CSceneLight;
class CScenePlayer;
class CSceneMeshField;
class CSceneMeshField;
class CSceneTime;
class CSceneMeter;
class CSceneCircuit;
class CSceneTime;
class CSceneSkydome;
class CSceneTutorial;

//=====================================================================================================
//
// class
//
//=====================================================================================================
class CModeTutorial :public CMode
{
protected:

public:
	CModeTutorial() {}
	~CModeTutorial() {}

	void Init();
	void Uninit();
	void Update();
	void Draw();

private:
	static CScene3D			*m_3D;
	static CSceneCamera		*m_Camera;
	static CSceneLight		*m_Light;
	static CScenePlayer		*m_Player;
	static CSceneMeshField	*m_MeshField;
	static CSceneMeshField	*m_Field;
	static CSceneTime		*m_SceneTime;
	static CSceneMeter		*m_Meter;
	static CSceneTutorial	*m_Tutorial;
	static CSceneTime    	*m_Time;
	static CSceneSkydome    *m_Skydome;

	int m_nFade;
	bool m_bFade;

};


#endif