#pragma once
#include "Global.h"

/**
 * ウィンドウをサポートするクラス
 */
class WindowHelper
{
private:

public:
	// コンストラクタ
	WindowHelper( void );
	// コンストラクタ
	~WindowHelper( void );
	// 開放
	void Cleanup( void );
	// 初期化
	void Init( void );
private:
};