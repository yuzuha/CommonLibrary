#pragma once
#include "global.h"

/**
 * ゲームメインを管理するクラス
 */
class GameMain
{
private:
	Window *m_pWindow;		///< ウィンドウ管理
public:
	/**
	 * デフォルトコンストラクタ
	 */
	GameMain( void ){};
	/**
	 * デストラクタ
	 */
	~GameMain( void ){ Destroy(); };
	// 初期化
	void Init( HINSTANCE hInst );
	// メモリ解放
	void Destroy( void );	
	// ゲーム本体のメイン関数
	void Main( void );
private:
};