#include "DebugManager.h"

/**
 * コンストラクタ
 */
DebugManager::DebugManager()
{
}


/**
 * デストラクタ
 */
DebugManager::~DebugManager()
{
}


/**
 * デバッグ用文字列の出力
 */
void DebugManager::Output( const string _str )
{
	Output( _str.c_str() );
}


/**
 * デバッグ用文字列の出力
 */
void DebugManager::Output( const char *_str )
{
	OutputDebugStringA( _str );
	OutputDebugStringA( "\n" );
}


