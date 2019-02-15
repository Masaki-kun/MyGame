//=====================================================================================================================
//
// [main.h]  Author : Masaki Kuboki
//
//=====================================================================================================================

#ifndef	_MAIN_H_
#define	_MAIN_H_

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <time.h>
#include "Input.h"

HWND GethWnd(void);

//=====================================================================================================================
//
// マクロ宣言
//
//=====================================================================================================================
//#define SCREEN_WIDTH	(800)				// 画面の幅
//#define SCREEN_HEIGHT	(600)				// 画面の高さ

//#define SCREEN_WIDTH (1280)		//ウィンドウの幅
//#define SCREEN_HEIGHT (720)		//ウィンドウの高さ

//#define SCREEN_WIDTH (1440)		//ウィンドウの幅
//#define SCREEN_HEIGHT (810)		//ウィンドウの高さ

#define SCREEN_WIDTH	(1920)				// 画面の幅 フルサイズ
#define SCREEN_HEIGHT	(1080)				// 画面の高さ　フルサイズ

//#define SCREEN_WIDTH	(2736)				// 画面の幅 フルサイズ
//#define SCREEN_HEIGHT	(1824)				// 画面の高さ　フルサイズ

#define FADE_SPEED (5)

#define CLASS_NAME		"game"
#define WINDOW_NAME		"The Cars 2"

#endif			//_MAIN_H    

