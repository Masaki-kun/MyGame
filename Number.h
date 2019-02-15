//==========================================================================================
//
// [SCene2D.h] Author : Masaki Kuboki
//
//==========================================================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "Scene.h"

//==========================================================================================
//
// class
//
//==========================================================================================
class CSceneNumber
{
public:
	CSceneNumber() {};
	~CSceneNumber(){}

	static void Init();
	static void Uninit();
	static void Update();
	static void Draw(int num, D3DCOLOR color,float posX, float posY, float scaleX, float scaleY);


private:


};

#endif