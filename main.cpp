//=====================================================================================================================
//	
//  [main.cpp]  Author : Masaki Kuboki
//
//=====================================================================================================================
#include "main.h"
#include "Manager.h"

//=====================================================================================================================
//
// プロトタイプ宣言
//
//=====================================================================================================================
//戻り値 window特有言語 クラスで作成した名前( , どんなメッセージか, そのmsgの付随の情報)
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


//=====================================================================================================================
//
// グローバル変数
//
//=====================================================================================================================
HWND hWnd;

//====================================================================================================
//
// Winproc関数
//
//======================================================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLime, int nShowCmd)
{
	int w_width, w_height = 0;							// クライアント領域での使用
	RECT wr = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };		// クライアント領域での使用
	RECT dr;											// クライアント領域での使用
	DWORD bStyle = (WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX) ^ WS_THICKFRAME;// クライアント領域での使用

	DWORD dwExecLastTime = 0;				// ゲーム処理が終わった時間
	DWORD dwCurrentTime = 0;				// 現在の時間


											//構造体その① 構造体変数の初期化で入れる *特徴* 打ち込みの量が少ない
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),				// 構造体のサイズ,構造体のサイズに第一クラスを持ってくることが多い
		CS_VREDRAW | CS_HREDRAW,		// CS_VREDRAW == 垂直、CS_REDRAW == 水平。windowのサイズ変化に対応して再描画をする
		WndProc,						// windowプロシージャ 関数のポインタ型。関数名それだけがアドレスになる。ウィンドウ上での発生したイベントの処理
		0,								// 使わない クラス構造体の追加領域 バイト単位で予約
		0,								// 使わない ウィンドウ構造体の追加領域 バイト単位で予約
		hInstance,						// 重要！！ WinMainから 整理券のようなもの インスタンスのハンドル
		NULL,							// アプリケーションのアイコン 
		LoadCursor(NULL, IDC_ARROW),	// カーソルの変更
		(HBRUSH)(COLOR_WINDOW + 1),	    // クライアント領域のデフォルトの背景色の設定
		NULL,							// クラスメニューハンドル
		CLASS_NAME,						// パーツ名 クラス名 実はなんでもよい
		NULL							// ミニアイコンの設定	
	};

	RegisterClassEx(&wcex);			// windowクラスの登録

	//----------------------------------------------------------------
	// クライアント領域のサイズ設定
	//----------------------------------------------------------------

	AdjustWindowRect(&wr, bStyle, false);	// クライアントサイズを求める関数
	w_width = (wr.right - wr.left);		// クライアントサイズの幅
	w_height = (wr.bottom - wr.top);		// クライアントサイズの高さ
	GetWindowRect(GetDesktopWindow(), &dr);
	HWND hWnd = CreateWindowEx(0, CLASS_NAME, WINDOW_NAME, /*WS_POPUP*/bStyle, CW_USEDEFAULT, CW_USEDEFAULT, w_width, w_height, NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, nShowCmd);		// 表示
	UpdateWindow(hWnd);				// 更新

	MSG msg;

	//=====================================================================================================================
	//
	// ゲームループの作成
	//
	//=====================================================================================================================
	CManager::Init(hInstance, hWnd, true);	// 初期化 ShouWindowの前に置くと...
	if (!CManager::Init)
	{
		MessageBox(hWnd, "初期化に失敗しました", "失敗", MB_OK | MB_ICONEXCLAMATION);
		return -1;
	}

	//	分解能を設定
	timeBeginPeriod(1);

	do {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else { // ゲーム処理
			dwCurrentTime = timeGetTime();
			CManager::Update();	// 更新処理
			CManager::Draw();		// 描画処理
		}
	} while (msg.message != WM_QUIT);

	CManager::Uninit();	// 終了処理

				// 分解能を戻す
	timeEndPeriod(1);

	return (int)msg.wParam;

}

//======================================================================================================
//
// WndProc関数
//
//======================================================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;

	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);		//WM_QUITメッセージの送信
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:			//エスケープボタン
			nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2);
			if (nID == IDYES)
			{
				DestroyWindow(hWnd);
				break;
			}
			break;
		}

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam); //重要！！ 基本はこいつが処理してくれる 特別な動きはcaseでreturnを使いこいつを通さないようにする

}

//======================================================================================================
//
// hWnd
//
//======================================================================================================
HWND GethWnd()
{
	return hWnd;
}