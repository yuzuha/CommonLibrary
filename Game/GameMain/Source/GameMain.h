#pragma once
#include "global.h"

/**
 * �Q�[�����C�����Ǘ�����N���X
 */
class GameMain
{
private:
	Window *m_pWindow;		///< �E�B���h�E�Ǘ�
public:
	/**
	 * �f�t�H���g�R���X�g���N�^
	 */
	GameMain( void ){};
	/**
	 * �f�X�g���N�^
	 */
	~GameMain( void ){ Destroy(); };
	// ������
	void Init( HINSTANCE hInst );
	// ���������
	void Destroy( void );	
	// �Q�[���{�̂̃��C���֐�
	void Main( void );
private:
};