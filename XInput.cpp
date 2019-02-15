//=================================================================================================
// 
// XInput(コントローラー)    Author:	Masaki Kuboki
// 
//=================================================================================================
#pragma comment (lib, "xinput.lib")				// ライブラリのインポート
#include "main.h"
#include "XInput.h"

//=====================================================================================================
//
// staticメンバ変数
//
//=====================================================================================================
XINPUT_STATE CXinput::m_State[PLAYER_MAX];		// インスタンス作成
XINPUT_STATE CXinput::m_Oldstate[PLAYER_MAX];	// 過去の状態を取得
int			 CXinput::m_nRegisterNum;			// プレイヤーの登録数
DWORD		 CXinput::m_dwResult;				// 取得の結果

//=================================================================================================
//
// 構造体
//
//=================================================================================================
//XINPUT_STATE g_State[PLAYER_MAX];				// インスタンス作成
//XINPUT_STATE g_Oldstate[PLAYER_MAX];				// 過去の状態を取得
//
//static int g_nRegisterNum = 0;					// プレイヤーの登録数
//
//DWORD dwResult;				// 取得の結果

//=================================================================================================
//	
// Init
//
//=================================================================================================
void CXinput::Init(PLAYER_NUM playerNum, HWND hWnd)
{
	// 登録数の代入
	m_nRegisterNum = playerNum + 1;

	for(WORD i = 0; i < m_nRegisterNum; i++)
	{
		// 中身をきれいにする
		ZeroMemory(&m_State[i], sizeof(XINPUT_STATE));

		// コントローラーの情報の取得(dwResultに結果)
		m_dwResult = XInputGetState(i,					// コントローラーの番号
									&m_State[i]);		// 状態格納されている先の先頭アドレス

		//取得失敗時のメッセージ
		if(m_dwResult != ERROR_SUCCESS)
		{
			MessageBox(hWnd, "コントローラーが接続されていません", "失敗", MB_OK | MB_ICONEXCLAMATION);
		}
	}
}

//=================================================================================================
//	XInput終了
//
//
//=================================================================================================
void CXinput::Uninit(void)
{

}

//=================================================================================================
//	XInput更新
//
//
//=================================================================================================
void CXinput::Update(void)
{
	for(WORD i = 0 ; i < m_nRegisterNum; i++)
	{
		// 過去のコントローラ情報の取得
		m_Oldstate[i] = m_State[i];

		// コントローラーの情報の取得
		XInputGetState(i, &m_State[i]);

		// 左スティックのデッドゾーン
		if( (m_State[i].Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && m_State[i].Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) && 
			(m_State[i].Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && m_State[i].Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)    )
		{
			m_State[i].Gamepad.sThumbLX = 0;
			m_State[i].Gamepad.sThumbLY = 0;
		}

		// 右スティックのデッドゾーン
		if( (m_State[i].Gamepad.sThumbRX < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && m_State[i].Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) && 
			(m_State[i].Gamepad.sThumbRY < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && m_State[i].Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)    )
		{
			m_State[i].Gamepad.sThumbRX = 0;
			m_State[i].Gamepad.sThumbRY = 0;
		}
		
	}

}

//=================================================================================================
//
// PRESSでキーの取得
//
//=================================================================================================
bool CXinput::GetPress(int button,int playerNum)
{
	// プレス
	return m_State[playerNum].Gamepad.wButtons & button;
}

//=================================================================================================
//
// TRIGGERでキーの取得
//
//=================================================================================================
bool CXinput::GetTrigger(int button,int playerNum)
{
	// トリガー関数を呼ぶ
	return KeyTrigger( m_State[playerNum].Gamepad.wButtons & button, m_Oldstate[playerNum].Gamepad.wButtons & button);
}

//=================================================================================================
//
// RELEASEでキーの取得
//
//=================================================================================================
bool CXinput::GetRelease(int button,int playerNum)
{
	// リリース関数を呼ぶ
	return KeyRelease( m_State[playerNum].Gamepad.wButtons & button, m_Oldstate[playerNum].Gamepad.wButtons & button);
}

//=================================================================================================
//
// アナログスティック左の取得
//
//=================================================================================================
bool CXinput::GetAnalogL(int playerNum)
{
		// 左スティック上
	if( m_State[playerNum].Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ||
		m_State[playerNum].Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ||
		m_State[playerNum].Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ||
		m_State[playerNum].Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ){ return true;}
	else{ return false; }
}

//=================================================================================================
//
// アナログスティック右の取得
//
//=================================================================================================
bool CXinput::GetAnalogR(int playerNum)
{
	// 右スティック
	if( m_State[playerNum].Gamepad.sThumbRY > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ||
		m_State[playerNum].Gamepad.sThumbRY < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ||
		m_State[playerNum].Gamepad.sThumbRX < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ||
		m_State[playerNum].Gamepad.sThumbRX > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ){ return true;}
	else{ return false; }
}

//=================================================================================================
//
// アナログスティック左の正規化されたベクトルを取得
//
//=================================================================================================
D3DXVECTOR3 CXinput::GetAnalogLDir(int playerNum)
{
	D3DXVECTOR3 dir;
	dir = D3DXVECTOR3(CXinput::GetState(playerNum)->Gamepad.sThumbLX, 0.0f, CXinput::GetState(playerNum)->Gamepad.sThumbLY);
	D3DXVec3Normalize(&dir,&dir);
	return dir;
}

//=================================================================================================
//
// アナログスティック右の正規化されたベクトルを取得
//
//=================================================================================================
D3DXVECTOR3 CXinput::GetAnalogRDir(int playerNum)
{
	D3DXVECTOR3 dir;
	dir = D3DXVECTOR3(CXinput::GetState(playerNum)->Gamepad.sThumbRX, 0.0f, CXinput::GetState(playerNum)->Gamepad.sThumbRY);
	D3DXVec3Normalize(&dir,&dir);
	return dir;
}

//=================================================================================================
//
// アナログスティック右の正規化されたベクトルを取得
//
//=================================================================================================
bool CXinput::GetLT(int playerNum)
{
	if(m_State[playerNum].Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD){ return true ;}
	else{ return false; }
}

//=================================================================================================
//
// アナログスティック右の正規化されたベクトルを取得
//
//=================================================================================================
bool CXinput::GetRT(int playerNum)
{
	if(m_State[playerNum].Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD){ return true; }
	else{ return false; }
}

//=================================================================================================
//
// トリガー判定（トリガー）
//
//=================================================================================================
bool CXinput::KeyTrigger ( bool bComand, bool bOldComand )			// コントローラのキートリガー
{
	bool trigger = false;
	trigger = (bOldComand ^ bComand) & bComand ;			// &が優先されて計算される
	return trigger;
}

//=================================================================================================
//
// リリース判定（リリース）
//
//=================================================================================================
bool CXinput::KeyRelease ( bool bComand, bool bOldComand )	// コントローラのキーリリース
{
	bool release = false;
	release = bOldComand ^ bComand & bOldComand;
	return release;
}

//=================================================================================================
//
// コントローラの情報渡し
//
//=================================================================================================
XINPUT_STATE* CXinput::GetState(int playerNum)
{
	return &m_State[playerNum];
}