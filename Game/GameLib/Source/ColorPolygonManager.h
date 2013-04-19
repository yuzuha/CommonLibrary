#pragma once
#include "Global.h"
class RenderManagerBase;
class ColorPolygon;

/**
 * 色有ポリの描画管理
 */
class ColorPolygonManager : public RenderManagerBase
{
private:
public:
	/**
	 * インスタンスの取得
	 */
	static ColorPolygonManager* GetInstance()
	{
		if( !m_pInstance ){
			m_pInstance = new ColorPolygonManager();
		}
		return dynamic_cast<ColorPolygonManager*>(m_pInstance);
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
	void _Init();
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
	void _Cleanup();
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
	void _Destroy();
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
	void _Render();
	/**
	 * 描画
	 */
	static void Render(ColorPolygon* _obj)
	{
		GetInstance()->_Render(_obj);
	}
	/**
	 * 描画
	 */
	void _Render(ColorPolygon* _obj);
private:
	// コンストラクタ
	ColorPolygonManager();
	// デストラクタ
	~ColorPolygonManager();
};

