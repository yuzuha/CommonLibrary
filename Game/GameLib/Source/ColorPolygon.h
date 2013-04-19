#pragma once
#include "Global.h"
class RenderTargetBase;

typedef struct{
	D3DXVECTOR3	m_vecCenter;	///< 頂点座標
	//DWORD		m_nColor;		///< 頂点色
}ST_ColorPolygon;

/**
 * 色有ポリゴン
 */
class ColorPolygon : public RenderTargetBase
{
private:
	DWORD		m_nColor;		///< 色
	D3DXVECTOR3	m_vecCenter;	///< 中心
	D3DXVECTOR2	m_vecSize;		///< 長さ
public:
	// コンストラクタ
	ColorPolygon();
	// デストラクタ
	~ColorPolygon();
	// 描画
	void Render();
	/**
	 * 中心座標の設定
	 */
	void SetCenter( D3DXVECTOR3 *_center )
	{
		m_vecCenter = *_center;
	}
	/**
	 * 中心座標の取得
	 */
	D3DXVECTOR3* GetCenter()
	{
		return &m_vecCenter;
	}
	/**
	 * サイズの設定
	 */
	void SetSize( D3DXVECTOR2 *_size )
	{
		m_vecSize = *_size;
	}
	/**
	 * サイズの取得
	 */
	D3DXVECTOR2* GetSize()
	{
		return &m_vecSize;
	}
	/**
	 * 色の設定
	 */
	void SetColor( DWORD _color )
	{
		m_nColor = _color;
	}
	/**
	 * 色の取得
	 */
	DWORD GetColor()
	{
		return m_nColor;
	}
};
