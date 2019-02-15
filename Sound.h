//=====================================================================================================================
//
// [sound.h]  Author : Masaki Kuboki
//
//=====================================================================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//=====================================================================================================================
//
// �p�����[�^�\���̒�`
//
//=====================================================================================================================
typedef struct
{
	char *pFilename;	// �t�@�C����
	int nCntLoop;		// ���[�v�J�E���g
} SOUNDPARAM;


//=====================================================================================================================
//
// �T�E���h�t�@�C��
//
//=====================================================================================================================
typedef enum
{
	SOUND_LABEL_BGM_START = 0,		// BGM0
	SOUND_LABEL_BGM_RACE,		// �e���ˉ�
	SOUND_LABEL_SE_SKIL,		// �q�b�g��
	SOUND_LABEL_SE_AFTER_FIRE,	// �A�t�^�[�t�@�C�A

	SOUND_LABEL_MAX,
} SOUND_LABEL;

// �e���f�ނ̃p�����[�^ -1:���[�v 0:�P��
static const SOUNDPARAM g_aParam[SOUND_LABEL_MAX] =
{   
	 
	{ "data/sound/bgm_start.wav",  -1 },	// BGM0      
	{ "data/sound/bgm_race.wav",   -1 },	// �e���ˉ�
	{ "data/sound/skil.wav", 0 },			// �X�L�[����
	{ "data/sound/after_fire.wav", 0 }		// �A�t�^�[�t�@�C�A
};


//==========================================================================================
//
// class
//
//==========================================================================================
class CSound
{
public:
	CSound() {};
	~CSound() {}

	static HRESULT InitSound(HWND hWnd);
	static void UninitSound(void);
	static HRESULT PlaySound(SOUND_LABEL label);
	static void StopSound(SOUND_LABEL label);
	static void StopSound(void);


private:


};


#endif


/*

//=====================================================================================================================
//
// �v���g�^�C�v�錾
//
//=====================================================================================================================
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

*/