#pragma once
#include "Global.h"
using namespace std;

/**
 * ウィンドウを管理するクラス
 */
class Window
{
private:
	static Window			*m_pInstance;			///< 自身の唯一のインスタンス

	MSG						m_msg;					///< ウィンドウプロージャ用
	HWND					m_hWnd;					///< ウィンドウハンドル
	HINSTANCE				m_hInst;				///< インスタンスハンドル
	DWORD					m_nWidth;				///< ウィンドウ時のクライアント領域サイズ
	DWORD					m_nHeight;				///< ウィンドウ時のクライアント領域サイズ
	float					m_fAspect;				///< ビューポートのアスペクト比
	string					m_strWindowName;		///< ウィンドウ名

	ID3D11Device			*m_pDevice;				///< デバイス
	ID3D11DeviceContext		*m_pDeviceContext;		///< デバイスコンテキスト
	IDXGISwapChain			*m_pSwapChain;			///< スワップチェーン
	ID3D11RenderTargetView	*m_pRenderTargetView;	///< レンダーターゲット
	ID3D11DepthStencilView	*m_pDepthStencilView;	///< デプスステンシルビュー
	IDXGIAdapter			*m_pAdapter;			///< アダプター
	D3D_FEATURE_LEVEL		m_eFeatureLevel;		///< 使用するビデオカード
public:
	/**
	 * インスタンスの取得
	 */
	static Window* GetInstance( void )
	{
		if( m_pInstance == NULL ){
			m_pInstance = new Window();
		}
		return m_pInstance;
	}

#pragma region Init
	/**
	 * 初期化
	 */
	static HRESULT Init( HINSTANCE _hInst )
	{
		return GetInstance()->_Init( _hInst );
	}
	/**
	 * 初期化
	 */
	HRESULT _Init( HINSTANCE _hInst );
#pragma endregion Init

#pragma region Cleanup
	/**
	 * 開放
	 */
	static void Cleanup( void )
	{
		GetInstance()->_Cleanup();
	}
	/**
	 * 開放
	 */
	void _Cleanup( void );
#pragma endregion Cleanup

#pragma region Destroy
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
#pragma endregion Destroy

#pragma region RenderBegin
	/**
	 * 描画前
	 */
	static BOOL RenderBegin( void )
	{
		return GetInstance()->_RenderBegin();
	}
	/**
	 * 描画前
	 */
	BOOL _RenderBegin( void );
#pragma endregion RenderBegin

#pragma region RenderEnd
	/**
	 * 描画後
	 */
	static void RenderEnd( void )
	{
		GetInstance()->_RenderEnd();
	}
	/**
	 * 描画後
	 */
	void _RenderEnd( void );
#pragma endregion RenderEnd

#pragma region ProcessEvent
	/**
	 * プロセスイベント
	 */
	static BOOL ProcessEvent()
	{
		return GetInstance()->_ProcessEvent();
	}
	/**
	 * プロセスイベント
	 */
	BOOL _ProcessEvent();
#pragma endregion ProcessEvent

#pragma region GetDevice
	/**
	 * デバイスの取得
	 */
	static ID3D11Device* GetDevice()
	{
		return GetInstance()->_GetDevice();
	}
	/**
	 * デバイスの取得
	 */
	ID3D11Device* _GetDevice()
	{
		return m_pDevice;
	}
#pragma endregion GetDevice

#pragma region GetDeviceContext
	/**
	 * デバイスコンテキストの取得
	 */
	static ID3D11DeviceContext* GetDeviceContext()
	{
		return GetInstance()->_GetDeviceContext();
	}
	/**
	 * デバイスコンテキストの取得
	 */
	ID3D11DeviceContext* _GetDeviceContext()
	{
		return m_pDeviceContext;
	}
#pragma endregion GetDeviceContext

#pragma region GetSwapChain
	/**
	 * スワップチェーンの取得
	 */
	static IDXGISwapChain* GetSwapChain()
	{
		return GetInstance()->_GetSwapChain();
	}
	/**
	 * スワップチェーンの取得
	 */
	IDXGISwapChain* _GetSwapChain()
	{
		return m_pSwapChain;
	}
#pragma endregion GetSwapChain

#pragma region GetWindowName
	/**
	 * ウィンドウ名の取得
	 */
	static string GetWindowNameToString()
	{
		return GetInstance()->_GetWindowNameToString();
	}
	/**
	 * ウィンドウ名の取得
	 */
	string _GetWindowNameToString()
	{
		return m_strWindowName;
	}
	/**
	 * ウィンドウ名の取得
	 */
	static const char* GetWindowNameToChar()
	{
		return GetInstance()->_GetWindowNameToChar();
	}
	/**
	 * ウィンドウ名の取得
	 */
	const char* _GetWindowNameToChar()
	{
		return m_strWindowName.c_str();
	}
#pragma endregion GetWindowName

private:
	// コンストラクタ
	Window( void );
	// デストラクタ
	~Window();
	// デフォルトアダプターのインターフェースを作成する
	HRESULT createAdapter();
	// ウィンドウの生成
	HRESULT createWindow();
	// デバイスの作成
	HRESULT createDevice();
	// スワップチェーンの作成
	HRESULT createSwapChain();
	// ターゲットビューの作成
	HRESULT createTargetView();
	// 深度ステンシルビューの作成
	HRESULT createDepthStencilView();
	// ビューポートの作成
	HRESULT createViewports();
	// デフォルトのラスタライザを設定する
	HRESULT setDefaultRasterize();
	// デフォルトの深度ステンシルステートを設定する
	HRESULT setDefaultDepthStencilState();
	// ウィンドウプロージャ
	static LRESULT WINAPI msgProc(HWND hWnd , UINT msg , WPARAM wParam , LPARAM lParam);
};