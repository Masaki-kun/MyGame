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
// �}�N���錾
//
//=====================================================================================================================
//#define SCREEN_WIDTH	(800)				// ��ʂ̕�
//#define SCREEN_HEIGHT	(600)				// ��ʂ̍���

//#define SCREEN_WIDTH (1280)		//�E�B���h�E�̕�
//#define SCREEN_HEIGHT (720)		//�E�B���h�E�̍���

//#define SCREEN_WIDTH (1440)		//�E�B���h�E�̕�
//#define SCREEN_HEIGHT (810)		//�E�B���h�E�̍���

#define SCREEN_WIDTH	(1920)				// ��ʂ̕� �t���T�C�Y
#define SCREEN_HEIGHT	(1080)				// ��ʂ̍����@�t���T�C�Y

//#define SCREEN_WIDTH	(2736)				// ��ʂ̕� �t���T�C�Y
//#define SCREEN_HEIGHT	(1824)				// ��ʂ̍����@�t���T�C�Y

#define FADE_SPEED (5)

#define CLASS_NAME		"game"
#define WINDOW_NAME		"The Cars 2"

#endif			//_MAIN_H    

