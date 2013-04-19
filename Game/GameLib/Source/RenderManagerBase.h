#pragma once
#include "Global.h"
using namespace std;
class RenderTargetBase;

/**
 * 描画基底クラス
 */
class RenderManagerBase
{
protected:
	static RenderManagerBase	*m_pInstance;		///< インスタンス
	ID3D11InputLayout			*m_pVertexLayout;
	ID3D11Buffer				*m_pVertexBuffer;
	ID3D11VertexShader			*m_pVertexShader;	///< 頂点シェーダー
	ID3D11PixelShader			*m_pPixelShader;	///< ピクセルシェーダー
	string						m_strPath;			///< シェーダー名
public:
	/**
	 * インスタンスの取得
	 */
	static RenderManagerBase* GetInstance()
	{
		if( !m_pInstance ){
			m_pInstance = new RenderManagerBase();
		}
		return m_pInstance;
	}
	/**
	 * 初期化
	 */
	static void Init()
	{
		GetInstance()->_Init();
	}
	/**
	 * 初期化
	 */
	virtual void _Init();
	/**
	 * 開放
	 */
	static void Cleanup()
	{
		GetInstance()->_Cleanup();
	}
	/**
	 * 開放
	 */
	virtual void _Cleanup();
	/**
	 * 破棄
	 */
	static void Destroy()
	{
		GetInstance()->_Destroy();
	}
	/**
	 * 破棄
	 */
	virtual void _Destroy();
	/**
	 * 描画
	 */
	static void Render()
	{
		GetInstance()->_Render();
	}
	/**
	 * 描画
	 */
	virtual void _Render();
	/**
	 * 描画
	 */
	static void Render( RenderTargetBase* _base )
	{
		GetInstance()->_Render(_base);
	}
	/**
	 * 描画
	 */
	virtual void _Render( RenderTargetBase* _base );
	/**
	 * シェーダー読み込み
	 */
	static HRESULT LoadShader( string _path )
	{
		return GetInstance()->_LoadShader( _path );
	}
	/**
	 * シェーダー読み込み
	 */
	virtual HRESULT _LoadShader( string _path );
protected:
	// コンストラクタ
	RenderManagerBase();
	// デストラクタ
	virtual ~RenderManagerBase();
};

