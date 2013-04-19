#pragma once
#include "Global.h"

/**
 * 描画ターゲット基底
 */
class RenderTargetBase
{
protected:
	D3DXMATRIX m_matWorld;		///< ワールド行列
public:
	// コンストラクタ
	RenderTargetBase();
	// デストラクタ
	virtual~RenderTargetBase();
	/**
	 * ワールド行列の設定
	 */
	void SetWorldMatrix( D3DXMATRIX *_mat )
	{
		m_matWorld = *_mat;
	}
	/**
	 * ワールド行列の取得
	 */
	D3DXMATRIX* GetWorldMatrix()
	{
		return &m_matWorld;
	}
	/**
	 * 描画
	 */
	virtual void Render();
};
