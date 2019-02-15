//=====================================================================================================
// 
// XInput(コントローラー)
//	Author:	Masaki Kuboki
//
//=====================================================================================================
#ifndef _MYXINPUT_H_
#define _MYXINPUT_H_
#pragma comment (lib, "xinput.lib")				// ライブラリのインポート

#include <Windows.h>
#include <XInput.h>

// プレイヤー人数(Init引数での使用)
typedef enum 
{
	PLAYER_ONE,		// １人 値は０
	PLAYER_TWO,		// ２人 値は１
	PLAYER_TREE,	// ３人 値は２
	PLAYER_MAX		// ４人 値は３
}PLAYER_NUM;

//=====================================================================================================
//
// class
//
//=====================================================================================================
class CXinput
{
public:
	CXinput() { m_nRegisterNum = 0; };
	~CXinput() {};

	// 基本関数(必ず入れる)
	static void Init(PLAYER_NUM playerNum, HWND hWnd);	
	static void Uninit(void);			
	static void Update(void);	

	// ボタン判定の種類
	static bool GetPress(int button, int playerNum);		// プレス
	static bool GetTrigger(int button, int playerNum);		// トリガー
	static bool GetRelease(int button, int playerNum);		// リリース
	
	// アナログスティックの情報取得
	// 引数：コントローラナンバー　戻り値：bool型で	押されていたらtrue、押されていなかったらfalse を返す
	static bool GetAnalogL(int playerNum);				// アナログスティック左の入力の有無
	static bool GetAnalogR(int playerNum);				// アナログスティック右の入力の有無

	static D3DXVECTOR3 GetAnalogLDir(int playerNum);			// アナログスティック左の正規化されたベクトルを取得
	static D3DXVECTOR3 GetAnalogRDir(int playerNum);			// アナログスティック右の正規化されたベクトルを取得

	// トリガーボタン(LT、RT、LB、RB)情報の取得
	// 引数：コントローラナンバー　戻り値：bool型で	押されていたらtrue、押されていなかったらfalse を返す
	static bool GetLT(int playerNum);				// トリガーボタン左
	static bool GetRT(int playerNum);				// トリガーボタン右

	// コントローラの情報の取得
	// 引数：コントローラナンバー　 戻り値：XINPUT_STATE型のアドレスが返ってくる
	static XINPUT_STATE* GetState(int playerNum);

	// 以下は使わない
	static bool KeyTrigger(bool bComand, bool bOldComand);	// コントローラのキートリガー
	static bool KeyRelease(bool bComand, bool bOldComand);	// コントローラのキーリリース

private:
	static XINPUT_STATE m_State[PLAYER_MAX];				// インスタンス作成
	static XINPUT_STATE m_Oldstate[PLAYER_MAX];				// 過去の状態を取得

	static int m_nRegisterNum;					// プレイヤーの登録数

	static DWORD m_dwResult;				// 取得の結果

};

//=====================================================================================================
//
// 基本関数（必ず入れる）
//
//=====================================================================================================
//void InitXInput(PLAYER_NUM playerNum, HWND hWnd);	// コントローラ接続数の初期化
//void UninitXInput(void);				// 
//void UpdateXInput(void);				// アナログスティックのデッドゾーン制御

//=====================================================================================================
// ボタン使用の有無の確認関数
//=====================================================================================================
//
// 引数：（第一）確認するボタン、（第二）コントローラナンバー
//		 <xinput.h>内のもの		int型で０から３の範囲でセット
//
// 戻り値：bool型で	押されていたらtrue		押されていなかったらfalse を返す
//
// 使用例：GetXInputTrigger(XINPUT_GAMEPAD_DPAD_UP,0);
// XINPUT_GAMEPAD_DPAD_UP			↑
// XINPUT_GAMEPAD_DPAD_DOWN			↓
// XINPUT_GAMEPAD_DPAD_LEFT			←
// XINPUT_GAMEPAD_DPAD_RIGHT		→
// XINPUT_GAMEPAD_START				STARTボタン
// XINPUT_GAMEPAD_BACK				BACKボタン
// XINPUT_GAMEPAD_LEFT_THUMB		左スティック押し込み
// XINPUT_GAMEPAD_RIGHT_THUMB		右スティック押し込み
// XINPUT_GAMEPAD_LEFT_SHOULDER		左トリガー
// XINPUT_GAMEPAD_RIGHT_SHOULDER	右トリガー
// XINPUT_GAMEPAD_A					Aボタン
// XINPUT_GAMEPAD_B					Bボタン
// XINPUT_GAMEPAD_X					Xボタン
// XINPUT_GAMEPAD_Y					Yボタン
//=====================================================================================================
//bool GetXInputPress(int button,int playerNum);			// プレス
//bool GetXInputTrigger(int button,int playerNum);		// トリガー
//bool GetXInputRelease(int button,int playerNum);		// リリース

//=====================================================================================================
// アナログスティック情報の取得
//=====================================================================================================
//
// 引数：コントローラナンバー
//
// 戻り値：bool型で	押されていたらtrue		押されていなかったらfalse を返す
//=====================================================================================================
//bool GetXInputAnalogL(int playerNum);				// アナログスティック左の入力の有無
//bool GetXInputAnalogR(int playerNum);				// アナログスティック右の入力の有無
//
//D3DXVECTOR3 GetAnalogLDir(int playerNum);			// アナログスティック左の正規化されたベクトルを取得
//D3DXVECTOR3 GetAnalogRDir(int playerNum);			// アナログスティック右の正規化されたベクトルを取得

//=====================================================================================================
// トリガーボタン（LT、RTボタン）情報の取得
//=====================================================================================================
//
// 引数：コントローラナンバー
//
// 戻り値：bool型で	押されていたらtrue		押されていなかったらfalse を返す
//=====================================================================================================
//bool GetXInputLT(int playerNum);				// トリガーボタン左
//bool GetXInputRT(int playerNum);				// トリガーボタン右

//=====================================================================================================
// コントローラの情報の取得
//=====================================================================================================
//
// 引数：コントローラナンバー
//
// 戻り値：XINPUT_STATE型のアドレスが返ってくる
//=====================================================================================================
//XINPUT_STATE* GetXInputState(int playerNum);

//=====================================================================================================
// ここは使わない
//=====================================================================================================
//bool KeyTrigger ( bool bComand, bool bOldComand );	// コントローラのキートリガー
//bool KeyRelease ( bool bComand, bool bOldComand );	// コントローラのキーリリース

#endif