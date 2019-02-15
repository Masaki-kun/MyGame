//=====================================================================================================
//
// [SCene.h] Author : Masaki Kuboki
//
//=====================================================================================================
#ifndef _SCENE_H_
#define _SCENE_H_
#include "main.h"

//=====================================================================================================
//
// É}ÉNÉçêÈåæ
//
//=====================================================================================================
#define SCENE_COUNT (12)
#define PRIORITY_NUM (3)

//=====================================================================================================
//
// class
//
//=====================================================================================================
class CScene
{
protected:
	D3DXVECTOR3 m_Position;

public:
	CScene(int Priority);
	virtual ~CScene(){}

	virtual void Init() {}
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	static void UninitAll();
	static void UpdateAll();
	static void DrawAll();
	static void ReleaseAll();

	void Release();
	void SetPosition(D3DXVECTOR3 Position);

private:
	static CScene *m_Scene[3][SCENE_COUNT];
	int m_Priority;
};

#endif