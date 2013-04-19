#include "global.h"
#include "GameMain.h"

/**
 * ���C���֐�
 */
int WINAPI WinMain( HINSTANCE hInst, HINSTANCE hPInst, LPSTR lpCmd , int nCmd )
{
#ifdef _DEBUG
	// �f�o�b�O�p�i���������[�N�̊m�F�j
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	// �Q�[�����C���Ǘ��}�l�[�W���[�̐���
	GameMain *pGameMain = new GameMain();
	pGameMain->Init( hInst );

	// �Q�[���̍X�V
	pGameMain->Main();

	// �J��
	SAFE_DELETE( pGameMain );

	return 1;
}