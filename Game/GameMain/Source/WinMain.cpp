#include "global.h"
#include "GameMain.h"

/**
 * メイン関数
 */
int WINAPI WinMain( HINSTANCE hInst, HINSTANCE hPInst, LPSTR lpCmd , int nCmd )
{
#ifdef _DEBUG
	// デバッグ用（メモリリークの確認）
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	// ゲームメイン管理マネージャーの生成
	GameMain *pGameMain = new GameMain();
	pGameMain->Init( hInst );

	// ゲームの更新
	pGameMain->Main();

	// 開放
	SAFE_DELETE( pGameMain );

	return 1;
}