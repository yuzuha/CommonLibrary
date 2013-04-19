#include "Window.h"
#include "DebugManager.h"
Window* Window::m_pInstance = NULL;


/**
 * コンストラクタ
 */
Window::Window( void )
{
	m_hWnd				= NULL;
	m_hInst				= NULL;
	m_pDevice			= NULL;
	m_pDeviceContext	= NULL;
	m_pSwapChain		= NULL;
	m_pRenderTargetView	= NULL;
	m_pDepthStencilView	= NULL;
	m_pAdapter			= NULL;
	m_eFeatureLevel		= D3D_FEATURE_LEVEL_11_0;

	m_nWidth			= 1280;
	m_nHeight			= 720;
	m_strWindowName		= "Test App";
}


/**
 * デストラクタ
 */
Window::~Window( void )
{
	_Cleanup();
}


/**
 * 初期化
 */
HRESULT Window::_Init( HINSTANCE _hInst )
{
	m_hInst = _hInst;

	// ウィンドウの作成
	if( HRESULT( createWindow() ) )
	{
		return E_FAIL;
	}
	// アダプターの作成
	if( HRESULT( createAdapter() ) )
	{
		return E_FAIL;
	}
	// デバイスの作成
	if( HRESULT( createDevice() ) )
	{
		return E_FAIL;
	}
	// スワップチェーンの作成
	if( HRESULT( createSwapChain() ) )
	{
		return E_FAIL;
	}
	// ターゲットビューの作成
	if( HRESULT( createTargetView() ) )
	{
		return E_FAIL;
	}
	// 深度ステンシルビュービューの作成
	if( HRESULT( createDepthStencilView() ) )
	{
		return E_FAIL;
	}
	// ターゲットビューの設定
	m_pDeviceContext->OMSetRenderTargets( 1, &m_pRenderTargetView, m_pDepthStencilView);
	// ビューポートの設定
	if( HRESULT( createViewports() ) )
	{
		return E_FAIL;
	}
	// デフォルトのラスタライザを設定する
	if( HRESULT( setDefaultRasterize() ) )
	{
		return E_FAIL;
	}
	// デフォルトの深度ステンシルステートを設定する
	if( HRESULT( setDefaultDepthStencilState() ) )
	{
		return E_FAIL;
	}

	//ウインドウ表示
	ShowWindow( m_hWnd, SW_SHOW );
	UpdateWindow(m_hWnd);

	return S_OK;
}


/**
 * 開放
 */
void Window::_Cleanup()
{
	SAFE_RELEASE( m_pDevice );
	SAFE_RELEASE( m_pDeviceContext );
	SAFE_RELEASE( m_pSwapChain );
	SAFE_RELEASE( m_pRenderTargetView );
	SAFE_RELEASE( m_pDepthStencilView );
	SAFE_RELEASE( m_pAdapter );
}


/**
 * 破棄
 */
void Window::_Destroy()
{
	SAFE_DELETE( m_pInstance );
}


/**
 * 描画前
 */
BOOL Window::_RenderBegin()
{
	// デバイス状態のチェック
#if 0
	HRESULT hr = m_pDevice->TestCooperativeLevel();
	if( FAILED( hr ) ){		// デバイスが失われている
		if (hr == D3DERR_DEVICELOST)
			return 0;	// デバイスはまだ失われている
		if (hr != D3DERR_DEVICENOTRESET)
			return -1;	// 予期せぬエラー

		// 開放
		m_pHelper->Cleanup();

		HRESULT hr = m_pd3dDevice->Reset( &m_d3dpp );
		switch( hr ){
		case D3DERR_DEVICELOST:				// デバイスロスト
			hr = -2;
			return -2;
			break;
		case D3DERR_DRIVERINTERNALERROR:	// 内部ドライバーエラー
			hr = -3;
			return -3;
			break;
		case D3DERR_INVALIDCALL:			// メソッドの呼び出しが無効です
			hr = -4;
			return -4;
			break;
		case S_OK:							// 成功
			hr = 1;
			break;
		default:
			hr = 0;
			break;
		}

		// 初期化
		m_pHelper->Init();
	}

#endif

	// 画面のクリア
	float ClearColor[4] = { 1, 0, 0, 1 };		// クリア色作成　RGBAの順
	m_pDeviceContext->ClearRenderTargetView( m_pRenderTargetView, ClearColor );	//画面クリア

	// レンダリング開始
#if 0
	if( !SUCCEEDED( m_pd3dDevice->BeginScene() ) ){
		// レンダリング失敗
		//		MessageBox(NULL , TEXT("レンダリング開始に失敗しました") ,TEXT("エラー") , MB_OK);
		//		m_pd3dDevice->EndScene();
		//		m_pd3dDevice->Present( NULL, NULL, NULL, NULL );
		return 0;
	}
#endif

	return TRUE;
}


/**
 * 描画後
 */
void Window::_RenderEnd()
{
	m_pSwapChain->Present( 0, 0 );
}


/**
 * ウィンドウの表示：ループ用
 */
BOOL Window::_ProcessEvent( void )
{
	while( m_msg.message != WM_QUIT ){
		if( PeekMessage( &m_msg, NULL, 0U, 0U, PM_REMOVE ) ){
			TranslateMessage( &m_msg );
			DispatchMessage( &m_msg );
		} else {
			return TRUE;
		}
	}
	return FALSE;
}


/**
 * ウィンドウプロージャ
 */
LRESULT WINAPI Window::msgProc( HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam )
{
	switch( _msg ){
	case WM_DESTROY:	// ウィンドウ削除
		PostQuitMessage(0);
		return 0;
	case WM_KEYDOWN:	// ウィンドウ削除命令を出す
		if(_wParam == VK_ESCAPE)
			PostMessage( _hWnd, WM_CLOSE, 0, 0 );
		return 0;
	case WM_SYSKEYDOWN:
		switch( _wParam ){	// Alt + Enter
		case VK_RETURN:		// ウィンドウモード切り替え
			//Window::GetInstance()->ChangeScreen();
			break;
		}
	default:
		break;
	}
	return DefWindowProc( _hWnd, _msg, _wParam, _lParam );
}


/**
 * デフォルトアダプターのインターフェースを作成する
 */
HRESULT Window::createAdapter()
{
	HRESULT hr = E_FAIL;
	IDXGIFactory* pFactory = NULL;

	if( !m_pAdapter )
	{
		// ファクトリを作成する。
		hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)(&pFactory) );
		if( FAILED( hr ) )
		{
#ifdef DEBUG_MODE
			DebugManager::Output( "CreateDXGIFactory Error!!" );
#endif
			return E_FAIL;
		}

		// デフォルトアダプターを取得
		hr = pFactory->EnumAdapters( 0, &m_pAdapter );
		if( FAILED( hr ) )
		{
#ifdef DEBUG_MODE
			DebugManager::Output( "EnumAdapters Error!!" );
#endif
			SAFE_RELEASE( pFactory );
			return E_FAIL;
		}
	}

	SAFE_RELEASE( pFactory );

#ifdef DEBUG_MODE
	DebugManager::Output( "createAdapter Success!!" );
#endif
	return S_OK;
}


/**
 * ウィンドウの生成
 */
HRESULT Window::createWindow()
{
	//ウインドウクラスの登録
	WNDCLASSEX wc;
	wc.cbSize			= sizeof(WNDCLASSEX);
	wc.style			= CS_HREDRAW | CS_VREDRAW;;
	wc.lpfnWndProc 		= msgProc;
	wc.cbClsExtra  		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance    	= m_hInst;
	wc.hIcon        	= LoadIcon (NULL,  IDI_APPLICATION);
	wc.hCursor      	= LoadCursor (NULL, IDC_ARROW);
	wc.lpszMenuName 	= NULL;
	wc.lpszClassName	= "className";
	wc.hIconSm      	= LoadIcon (NULL,IDI_APPLICATION);
	wc.hbrBackground	= NULL;
	RegisterClassEx( &wc );

	//タイトルバーとウインドウ枠の分を含めてウインドウサイズを設定
	RECT rect;
	SetRect( &rect, 0, 0, m_nWidth, m_nHeight);
	AdjustWindowRect( &rect,  WS_BORDER | WS_MINIMIZEBOX | WS_CAPTION | WS_SYSMENU, FALSE );
	rect.right	= rect.right  - rect.left;
	rect.bottom	= rect.bottom - rect.top;
	rect.top	= 0;
	rect.left	= 0;
	//ウインドウの生成
	m_hWnd = CreateWindow( "className",
						 m_strWindowName.c_str(),
						 WS_BORDER | WS_MINIMIZEBOX | WS_CAPTION | WS_SYSMENU,
						 CW_USEDEFAULT,
						 CW_USEDEFAULT,
						 rect.right,
						 rect.bottom,
						 NULL,
						 NULL,
						 wc.hInstance,
						 NULL );

	if( !m_hWnd )
	{
#ifdef DEBUG_MODE
		DebugManager::Output( "createWindow Error!!" );
#endif
		return E_FAIL;
	}

#ifdef DEBUG_MODE
	DebugManager::Output( "createWindow Success!!" );
#endif
	return S_OK;
}


/**
 * デバイスの作成
 */
HRESULT Window::createDevice()
{
	// デバイス作成時に使用するビデオカードの性能一覧
	D3D_FEATURE_LEVEL FeatureLevel[] =  {
		D3D_FEATURE_LEVEL_11_0,  // Direct3D 11.0 SM 5
		D3D_FEATURE_LEVEL_10_1,  // Direct3D 10.1 SM 4
		D3D_FEATURE_LEVEL_10_0,  // Direct3D 10.0 SM 4
		D3D_FEATURE_LEVEL_9_3,   // Direct3D 9.3  SM 3
		D3D_FEATURE_LEVEL_9_2,   // Direct3D 9.2  SM 2
		D3D_FEATURE_LEVEL_9_1,   // Direct3D 9.1  SM 2
	};
	int nFeatureCount = sizeof( FeatureLevel ) / sizeof( D3D_FEATURE_LEVEL );

	 // ソフトウェア レイヤー
#ifdef DEBUG_MODE
	//UINT createDeviceFlag = D3D11_CREATE_DEVICE_DEBUG;
	UINT createDeviceFlag = 0;
#else
	UINT createDeviceFlag = 0;
#endif
	if( FAILED( D3D11CreateDevice( m_pAdapter,
								   D3D_DRIVER_TYPE_UNKNOWN,
								   NULL,
								   createDeviceFlag,
								   FeatureLevel,
								   nFeatureCount,
								   D3D11_SDK_VERSION,
								   &m_pDevice,
								   &m_eFeatureLevel,
								   &m_pDeviceContext ) ) )
	{
#ifdef DEBUG_MODE
		DebugManager::Output( "D3D11CreateDevice Error!!" );
#endif
		return E_FAIL;
	}

#ifdef DEBUG_MODE
	// DirectXのバージョン、シェーダモデルのバージョンと採用したアダプターの名前をデバックウィンドウに出力
	// アダプターの情報を取得
	DXGI_ADAPTER_DESC desc;
	m_pAdapter->GetDesc( &desc );

	// DirectXのバージョン、シェーダモデルのバージョンと採用したアダプターの名前をデバックウィンドウに出力
	char buf[256];
	switch( m_eFeatureLevel )
	{
	case D3D_FEATURE_LEVEL_11_0:
		sprintf_s( buf, 256, "Direct3D(11.0) SM(5)　%s", desc.Description );
		break;
	case D3D_FEATURE_LEVEL_10_1:
		sprintf_s( buf, 256, "Direct3D(10.1) SM(4)　%s", desc.Description );
		break;
	case D3D_FEATURE_LEVEL_10_0:
		sprintf_s( buf, 256, "Direct3D(10.0) SM(4)　%s", desc.Description );
		break;
	case D3D_FEATURE_LEVEL_9_3:
		sprintf_s( buf, 256, "Direct3D(9.3) SM(3)　%s", desc.Description );
		break;
	case D3D_FEATURE_LEVEL_9_2:
		sprintf_s( buf, 256, "Direct3D(9.2) SM(2)　%s", desc.Description );
		break;
	case D3D_FEATURE_LEVEL_9_1:
		sprintf_s( buf, 256, "Direct3D(9.1) SM(2)　%s", desc.Description );
		break;
	}
	DebugManager::Output( buf );
#endif

#ifdef DEBUG_MODE
	DebugManager::Output( "createDevice Success!!" );
#endif

	return S_OK;
}


/**
 * スワップチェーンの作成
 */
HRESULT Window::createSwapChain()
{
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory( &sd, sizeof(sd) );
	sd.BufferCount = 1;									// バックバッファの数
	sd.BufferDesc.Width = m_nWidth;						// バッファの幅
	sd.BufferDesc.Height = m_nHeight;					// バッファの高さ
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// バッファのフォーマット
	sd.BufferDesc.RefreshRate.Numerator = 60;			// リフレッシュレート
	sd.BufferDesc.RefreshRate.Denominator = 1;			
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	// バックバッファにレンダリング可能にする
	sd.OutputWindow = m_hWnd;							// 出力ウィンドウへの HWND ハンドル
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;			// サーフェスのスワップ処理後にバックバッファの内容を保持しない
	sd.Windowed = TRUE;									// ウィンドウモード
	//sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;	// フルスクリーンモードに切り替えると、アプリケーション ウィンドウのサイズに合わせて解像度が変更される。
	// マルチサンプルを使用しない場合の設定
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;

	// ファクトリーを作成する
	IDXGIFactory* pFactory = NULL;
	// CreateDXGIFactoryで作成したファクトリーを使用すると実行できるがワーニングエラーになるので IDXGIAdapter から作成する。
	if( HRESULT( m_pAdapter->GetParent( __uuidof(IDXGIFactory), (void**)&pFactory ) ) )
	{
#ifdef DEBUG_MODE
		DebugManager::Output( "GetParent Error!!" );
#endif
		return E_FAIL;
	}

	int startMultisample;

	// サンプリング数が最大のものを採用する
	startMultisample = D3D11_MAX_MULTISAMPLE_SAMPLE_COUNT;
	// マルチサンプルを無効にする。
	//startMultisample = 1;

	UINT Quality = 0;
	for( int i=startMultisample; i>=0; i-- )
	{
		// サポートするクォリティレベルの最大値を取得する
		// CheckMultisampleQualityLevels
		if( HRESULT( m_pDevice->CheckMultisampleQualityLevels( DXGI_FORMAT_R8G8B8A8_UNORM, (UINT)i, &Quality ) ) )
		{
#ifdef DEBUG_MODE
			DebugManager::Output( "CheckMultisampleQualityLevels Error!!" );
#endif
			return E_FAIL;
		}

		// 0 以外のときフォーマットとサンプリング数の組み合わせをサポートする
		// オンラインヘルプではCheckMultisampleQualityLevelsの戻り値が 0 のときサポートされないとかかれているが
		// pNumQualityLevels の戻り値が 0 かで判断する。
		// Direct3D 10 版 のオンラインヘルプにはそうかかれているので、オンラインヘルプの間違い。
		if( Quality != 0 )
		{
			sd.SampleDesc.Count = i;
			sd.SampleDesc.Quality = Quality - 1;

			// スワップチェーンを作成する。
			HRESULT hr = pFactory->CreateSwapChain( m_pDevice, &sd, &m_pSwapChain );
#ifdef DEBUG_MODE
			char buf[256];
			sprintf_s( buf, 256, "Count(%d) Quality(%d)", sd.SampleDesc.Count, sd.SampleDesc.Quality );
			DebugManager::Output( buf );
#endif
			if( SUCCEEDED( hr ) ) break;
		}
	}

	if( m_pSwapChain == NULL )
	{
#ifdef DEBUG_MODE
		DebugManager::Output( "CreateSwapChain Error!!" );
#endif
		return E_FAIL;
	}

#ifdef DEBUG_MODE
	DebugManager::Output( "createSwapChain Success!!" );
#endif

	return S_OK;
}


/**
 * ターゲットビューの作成
 */
HRESULT Window::createTargetView()
{
	//レンダーターゲットビューの作成
	ID3D11Texture2D *BackBuffer;
	if( HRESULT( m_pSwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), (LPVOID*)&BackBuffer ) ) )
	{
#ifdef DEBUG_MODE
		DebugManager::Output( "GetBuffer Error!!" );
#endif
		return E_FAIL;
	}
	if( HRESULT( m_pDevice->CreateRenderTargetView( BackBuffer, NULL, &m_pRenderTargetView ) ) )
	{
#ifdef DEBUG_MODE
		DebugManager::Output( "CreateRenderTargetView Error!!" );
#endif
		return E_FAIL;
	}
	BackBuffer->Release();

#ifdef DEBUG_MODE
	DebugManager::Output( "createTargetView Success!!" );
#endif
	return S_OK;
}


/**
 * 深度ステンシルビューの作成
 */
HRESULT Window::createDepthStencilView()
{
	ID3D11Texture2D* pBackBuffer = NULL;
	ID3D11Texture2D* pDepthBuffer = NULL;
	D3D11_TEXTURE2D_DESC descDS;
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	DXGI_SWAP_CHAIN_DESC chainDesc;

	// スワップチェーンの設定を取得する
	if( HRESULT( m_pSwapChain->GetDesc( &chainDesc ) ) )
	{
#ifdef DEBUG_MODE
		DebugManager::Output( "GetDesc Error!!" );
#endif
		return E_FAIL;
	}

	ZeroMemory( &descDS, sizeof( D3D11_TEXTURE2D_DESC ) );
	descDS.Width              = chainDesc.BufferDesc.Width;			// バックバッファと同じにする。
	descDS.Height             = chainDesc.BufferDesc.Height;		// バックバッファと同じにする。
	descDS.MipLevels          = 1;									// ミップマップを作成しない
	descDS.ArraySize          = 1;									// テクスチャーの配列数
	descDS.Format             = DXGI_FORMAT_R16_TYPELESS;			// フォーマット
	descDS.SampleDesc.Count   = chainDesc.SampleDesc.Count;			// バックバッファと同じにする。
	descDS.SampleDesc.Quality = chainDesc.SampleDesc.Quality;		// バックバッファと同じにする。
	descDS.Usage              = D3D11_USAGE_DEFAULT;				// GPU による読み取りおよび書き込みアクセスを必要とするリソース。
	//descDS.BindFlags		  = D3D11_BIND_DEPTH_STENCIL;			// ステンシルバッファ
	descDS.BindFlags          = D3D11_BIND_DEPTH_STENCIL |			// 深度ステンシルバッファとして作成する
								D3D11_BIND_SHADER_RESOURCE;			// シェーダーリソースビューとして作成する
	descDS.CPUAccessFlags     = 0;									// CPU アクセスが不要。
	descDS.MiscFlags          = 0;									// その他のフラグも設定しない。
	// 深度バッファ用のテクスチャー作成
	if( HRESULT( m_pDevice->CreateTexture2D( &descDS, NULL, &pDepthBuffer ) ) )
	{
#ifdef DEBUG_MODE
		DebugManager::Output( "CreateTexture2D Error!!" );
#endif
		return E_FAIL;
	}

	ZeroMemory( &descDSV, sizeof( D3D11_DEPTH_STENCIL_VIEW_DESC ) );

	// テクスチャー作成時に指定したフォーマットと互換性があり、深度ステンシルビューとして指定できるフォーマットを指定する
	//   descDSV.Format = descDS.Format;
	switch( descDS.Format )
	{
		// 8ビットフォーマットは使用できない？
	case DXGI_FORMAT_R8_TYPELESS:
		descDSV.Format = DXGI_FORMAT_R8_UNORM;
		break;
	case DXGI_FORMAT_R16_TYPELESS:
		descDSV.Format = DXGI_FORMAT_D16_UNORM;
		break;
	case DXGI_FORMAT_R32_TYPELESS:
		descDSV.Format = DXGI_FORMAT_D32_FLOAT;
		break;
	case DXGI_FORMAT_R24G8_TYPELESS:
		descDSV.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		break;
	default:
		descDSV.Format = descDS.Format;
	}

	// マルチサンプルを使用している場合
	if( chainDesc.SampleDesc.Count > 1 )
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	// マルチサンプルを使用していない場合
	else
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

	descDSV.Texture2D.MipSlice = 0;
	// 深度ステンシルビューを作成
	if( HRESULT( m_pDevice->CreateDepthStencilView( pDepthBuffer, &descDSV, &m_pDepthStencilView ) ) )
	{
#ifdef DEBUG_MODE
		DebugManager::Output( "CreateDepthStencilView Error!!" );
#endif
		return E_FAIL;
	}

	SAFE_RELEASE( pDepthBuffer );
	SAFE_RELEASE( pBackBuffer );

#ifdef DEBUG_MODE
	DebugManager::Output( "createDepthStencilView Success!!" );
#endif

	return S_OK;
}


/**
 * ビューポートの作成
 */
HRESULT Window::createViewports()
{
	D3D11_VIEWPORT vp;
	vp.Width = (float)m_nWidth;
	vp.Height = (float)m_nHeight;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	m_pDeviceContext->RSSetViewports( 1, &vp );

#ifdef DEBUG_MODE
	DebugManager::Output( "createViewports Success!!" );
#endif
	return S_OK;
}


/**
 * デフォルトのラスタライザを設定
 */
HRESULT Window::setDefaultRasterize()
{
	ID3D11RasterizerState* pRasterState = NULL;
	D3D11_RASTERIZER_DESC rsState;
	rsState.FillMode = D3D11_FILL_SOLID;    // ポリゴン面描画
	rsState.CullMode = D3D11_CULL_BACK;     // 裏面を描画しない
	//   rsState.FrontCounterClockwise = FALSE;  // 時計回りを表面
	rsState.FrontCounterClockwise = TRUE;   // 反時計回りを表面
	rsState.DepthBias = 0;
	rsState.DepthBiasClamp = 0;
	rsState.SlopeScaledDepthBias = 0;
	rsState.DepthClipEnable = TRUE;
	rsState.ScissorEnable = FALSE;          // シザー矩形無効

	// スワップチェーンのマルチサンプリングの設定にあわせる
	DXGI_SWAP_CHAIN_DESC swapDesc;
	m_pSwapChain->GetDesc( &swapDesc );
	if( swapDesc.SampleDesc.Count != 1 )
		rsState.MultisampleEnable = TRUE;
	else
		rsState.MultisampleEnable = FALSE;

	rsState.AntialiasedLineEnable = FALSE;

	if( HRESULT( m_pDevice->CreateRasterizerState( &rsState, &pRasterState ) ) )
	{
#ifdef DEBUG_MODE
		DebugManager::Output( "CreateRasterizerState Error!!" );
#endif
		return E_FAIL;
	}

	m_pDeviceContext->RSSetState( pRasterState );

#ifdef DEBUG_MODE
	DebugManager::Output( "setDefaultRasterize Success!!" );
#endif

	SAFE_RELEASE( pRasterState );
	return S_OK;
}


/**
 * デフォルトの深度ステンシルステートを設定
 */
HRESULT Window::setDefaultDepthStencilState()
{
	ID3D11DepthStencilState* pDepthStencilState = NULL;
	D3D11_DEPTH_STENCIL_DESC dsState;
	ZeroMemory( &dsState, sizeof( D3D11_DEPTH_STENCIL_DESC ) );
	dsState.DepthEnable = TRUE;
	dsState.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsState.DepthFunc = D3D11_COMPARISON_LESS;
	dsState.StencilEnable = FALSE;

	if( HRESULT( m_pDevice->CreateDepthStencilState( &dsState, &pDepthStencilState ) ) )
	{
#ifdef DEBUG_MODE
		DebugManager::Output( "CreateDepthStencilState Error!!" );
#endif
		return E_FAIL;
	}

	m_pDeviceContext->OMSetDepthStencilState( pDepthStencilState, 0 );

#ifdef DEBUG_MODE
	DebugManager::Output( "setDefaultDepthStencilState Success!!" );
#endif

	SAFE_RELEASE( pDepthStencilState );
	return S_OK;
}

