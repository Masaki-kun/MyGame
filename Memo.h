#include "main.h"
#include "Scene.h"
#include "2D.h"


class CMeshEffect
{

};

D3DXVECTOR3 m_VertexPos[8];

void update()
{
	for (int i = 0; i < 0 ; i++ )
	{
		m_VertexPos[i * 2] = m_VertexPos[];
		m_VertexPos[i * 2 + 1] = m_VertexPos[];
	}

	//m_VertexPos[6] = playerPosTop;
	//m_VertexPos[7] = playerPoaBottom;
}

class CSceneBall:public CScene
{
public:
	CSceneBall();
	~CSceneBall();
	
	void Init(void);
	void Update(void);
	void Draw(void);

private:
	D3DXVECTOR3 m_Rotation;
	D3DXQUATERNION m_Quaternion;
};


void CSceneBall::Init()
{
	D3DXQuaternionIdentity(&m_Quaternion);	// èâä˙âª
}

void CSceneBall::Update()
{
	if (CInput::GetKeyboardPress(DIK_S))
	{
		D3DXQUATERNION quaternion;

		D3DXQuaternionRotationAxis(&quaternion, &D3DXVECTOR3(1.0f, 0.0f, 0.0f), 0.1f);
		D3DXQuaternionMultiply(&m_Quaternion, &quaternion, &m_Quaternion);
	}
}

void CSceneBall::Draw()
{

}



class CBullet : public CScene
{
	static LPDIRECT3DBASETEXTURE9 m_Texture;

	static void Load();
	static void Unload();

	void Init();
	void Uninit();
	void Update();
	void Draw();
};

void  CBullet::Load()
{
//	D3DXCreateTextureFromFile();
}

void CBullet::Init()
{

}

//CBullete:::Load();
//Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`
//CBullet::Create(); 
//CBullet::Create();
//Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`
//CBullet::Unload();

/*
// à⁄ìÆè∞
class CGimmick:public CScene

{
public:
	CGimmick(){ m_Position; m_OldPosition;}	
	~CGimmick(); 
	void Init();
	void Uninit();
	void Update();
	void Draw();

private:
	// à⁄ìÆè∞
	D3DXVECTOR3 m_Position;
	D3DXVECTOR3 m_OldPosition;

	// âÒì]ÉMÉ~ÉbÉN
	D3DXMATRIX m_Matrix;
	D3DXMATRIX m_MOldatrix;
};

void CGimmick::Update()
{
	m_OldPosition = m_Position;
	m_Position = à⁄ìÆó ;
}

void CScenePlayer::Update()
{
	// à⁄ìÆè∞
	for (-- - )
	{
		if (scene->GetType() == SCENE_TYPE_GIMMICK)
		{
			CGimmick *gimmick = (CGimmick*)scene;
			if (è’ìÀîªíË)
			{
				D3DXVECTOR3 gimmickPos = gimmick->GetPosition();
				D3DXVECTOR3 gimmickOilPos = gimmick -> GetOldposition();
				m_Position += gimmickOilPos;
			}
		}
	}

	//âÒì]ÉMÉ~ÉbÉN
	if (è’ìÀîªíË)
	{
		D3DXMatrixInverse(&incGimmickoldmtx, NULL, &gimmickOldMatrix);
		D3DXVec3transformCoord(&oldlocalPos, &m_Position, &invGimmickOldMtx);
		D3DXVec3TransformCoord(&m_Position, &oldLocalPos, &gimmickMtx);
	}
}




*/


