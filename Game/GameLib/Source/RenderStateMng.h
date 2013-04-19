#pragma once
#include "Global.h"
#include "Window.h"

/**
 * RenderStateを行う際はこのクラスを通して行う
 */
class RenderStateMng
{
private:
	static RenderStateMng	*m_pInstance;		///< 自身のインスタンス
	bool					m_isZWriteEnable;	///< Z深度バッファフラグ
	bool					m_isZEnable;		///< Zバッファフラグ
	_D3DCULL				m_nCullMode;		///< カリング状態
public:
	int Init();
	static int Destroy();
	static HRESULT SetRenderState( _D3DRENDERSTATETYPE type, DWORD state )
	{
		return GetInstance()->_SetRenderState( type, state );
	}
private:
	/**
	 * デフォルトコンストラクタ
	 */
	RenderStateMng( void )
	{
		Init();
	}
	/**
	 * デストラクタ
	 */
	~RenderStateMng( void )
	{
		Destroy();
	}
	/**
	 * 自身のインスタンスを取得
	 */
	static RenderStateMng* GetInstance( void )
	{
		if( !m_pInstance )
			m_pInstance = new RenderStateMng();
		return m_pInstance;
	}
	HRESULT _SetRenderState( _D3DRENDERSTATETYPE type, DWORD state );
};