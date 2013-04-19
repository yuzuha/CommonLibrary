#pragma once
#include "Global.h"
using namespace std;

/**
 * デバッグ関係を管理
 */
class DebugManager
{
private:
	static DebugManager *m_pInstance;	///< インスタンス
public:
	/**
	 * インスタンスの取得
	 */
	static DebugManager *GetInstance()
	{
		if( !m_pInstance )
		{
			m_pInstance = new DebugManager();
		}
		return m_pInstance;
	}
	// デバッグ用文字列の出力
	static void Output( const string _str );
	static void Output( const char *_str );
private:
	// コンストラクタ
	DebugManager();
	// デストラクタ
	~DebugManager();

};