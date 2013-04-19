#include "Window.h"
#include "DebugManager.h"
Window* Window::m_pInstance = NULL;


/**
 * �R���X�g���N�^
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
 * �f�X�g���N�^
 */
Window::~Window( void )
{
	_Cleanup();
}


/**
 * ������
 */
HRESULT Window::_Init( HINSTANCE _hInst )
{
	m_hInst = _hInst;

	// �E�B���h�E�̍쐬
	if( HRESULT( createWindow() ) )
	{
		return E_FAIL;
	}
	// �A�_�v�^�[�̍쐬
	if( HRESULT( createAdapter() ) )
	{
		return E_FAIL;
	}
	// �f�o�C�X�̍쐬
	if( HRESULT( createDevice() ) )
	{
		return E_FAIL;
	}
	// �X���b�v�`�F�[���̍쐬
	if( HRESULT( createSwapChain() ) )
	{
		return E_FAIL;
	}
	// �^�[�Q�b�g�r���[�̍쐬
	if( HRESULT( createTargetView() ) )
	{
		return E_FAIL;
	}
	// �[�x�X�e���V���r���[�r���[�̍쐬
	if( HRESULT( createDepthStencilView() ) )
	{
		return E_FAIL;
	}
	// �^�[�Q�b�g�r���[�̐ݒ�
	m_pDeviceContext->OMSetRenderTargets( 1, &m_pRenderTargetView, m_pDepthStencilView);
	// �r���[�|�[�g�̐ݒ�
	if( HRESULT( createViewports() ) )
	{
		return E_FAIL;
	}
	// �f�t�H���g�̃��X�^���C�U��ݒ肷��
	if( HRESULT( setDefaultRasterize() ) )
	{
		return E_FAIL;
	}
	// �f�t�H���g�̐[�x�X�e���V���X�e�[�g��ݒ肷��
	if( HRESULT( setDefaultDepthStencilState() ) )
	{
		return E_FAIL;
	}

	//�E�C���h�E�\��
	ShowWindow( m_hWnd, SW_SHOW );
	UpdateWindow(m_hWnd);

	return S_OK;
}


/**
 * �J��
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
 * �j��
 */
void Window::_Destroy()
{
	SAFE_DELETE( m_pInstance );
}


/**
 * �`��O
 */
BOOL Window::_RenderBegin()
{
	// �f�o�C�X��Ԃ̃`�F�b�N
#if 0
	HRESULT hr = m_pDevice->TestCooperativeLevel();
	if( FAILED( hr ) ){		// �f�o�C�X�������Ă���
		if (hr == D3DERR_DEVICELOST)
			return 0;	// �f�o�C�X�͂܂������Ă���
		if (hr != D3DERR_DEVICENOTRESET)
			return -1;	// �\�����ʃG���[

		// �J��
		m_pHelper->Cleanup();

		HRESULT hr = m_pd3dDevice->Reset( &m_d3dpp );
		switch( hr ){
		case D3DERR_DEVICELOST:				// �f�o�C�X���X�g
			hr = -2;
			return -2;
			break;
		case D3DERR_DRIVERINTERNALERROR:	// �����h���C�o�[�G���[
			hr = -3;
			return -3;
			break;
		case D3DERR_INVALIDCALL:			// ���\�b�h�̌Ăяo���������ł�
			hr = -4;
			return -4;
			break;
		case S_OK:							// ����
			hr = 1;
			break;
		default:
			hr = 0;
			break;
		}

		// ������
		m_pHelper->Init();
	}

#endif

	// ��ʂ̃N���A
	float ClearColor[4] = { 1, 0, 0, 1 };		// �N���A�F�쐬�@RGBA�̏�
	m_pDeviceContext->ClearRenderTargetView( m_pRenderTargetView, ClearColor );	//��ʃN���A

	// �����_�����O�J�n
#if 0
	if( !SUCCEEDED( m_pd3dDevice->BeginScene() ) ){
		// �����_�����O���s
		//		MessageBox(NULL , TEXT("�����_�����O�J�n�Ɏ��s���܂���") ,TEXT("�G���[") , MB_OK);
		//		m_pd3dDevice->EndScene();
		//		m_pd3dDevice->Present( NULL, NULL, NULL, NULL );
		return 0;
	}
#endif

	return TRUE;
}


/**
 * �`���
 */
void Window::_RenderEnd()
{
	m_pSwapChain->Present( 0, 0 );
}


/**
 * �E�B���h�E�̕\���F���[�v�p
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
 * �E�B���h�E�v���[�W��
 */
LRESULT WINAPI Window::msgProc( HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam )
{
	switch( _msg ){
	case WM_DESTROY:	// �E�B���h�E�폜
		PostQuitMessage(0);
		return 0;
	case WM_KEYDOWN:	// �E�B���h�E�폜���߂��o��
		if(_wParam == VK_ESCAPE)
			PostMessage( _hWnd, WM_CLOSE, 0, 0 );
		return 0;
	case WM_SYSKEYDOWN:
		switch( _wParam ){	// Alt + Enter
		case VK_RETURN:		// �E�B���h�E���[�h�؂�ւ�
			//Window::GetInstance()->ChangeScreen();
			break;
		}
	default:
		break;
	}
	return DefWindowProc( _hWnd, _msg, _wParam, _lParam );
}


/**
 * �f�t�H���g�A�_�v�^�[�̃C���^�[�t�F�[�X���쐬����
 */
HRESULT Window::createAdapter()
{
	HRESULT hr = E_FAIL;
	IDXGIFactory* pFactory = NULL;

	if( !m_pAdapter )
	{
		// �t�@�N�g�����쐬����B
		hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)(&pFactory) );
		if( FAILED( hr ) )
		{
#ifdef DEBUG_MODE
			DebugManager::Output( "CreateDXGIFactory Error!!" );
#endif
			return E_FAIL;
		}

		// �f�t�H���g�A�_�v�^�[���擾
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
 * �E�B���h�E�̐���
 */
HRESULT Window::createWindow()
{
	//�E�C���h�E�N���X�̓o�^
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

	//�^�C�g���o�[�ƃE�C���h�E�g�̕����܂߂ăE�C���h�E�T�C�Y��ݒ�
	RECT rect;
	SetRect( &rect, 0, 0, m_nWidth, m_nHeight);
	AdjustWindowRect( &rect,  WS_BORDER | WS_MINIMIZEBOX | WS_CAPTION | WS_SYSMENU, FALSE );
	rect.right	= rect.right  - rect.left;
	rect.bottom	= rect.bottom - rect.top;
	rect.top	= 0;
	rect.left	= 0;
	//�E�C���h�E�̐���
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
 * �f�o�C�X�̍쐬
 */
HRESULT Window::createDevice()
{
	// �f�o�C�X�쐬���Ɏg�p����r�f�I�J�[�h�̐��\�ꗗ
	D3D_FEATURE_LEVEL FeatureLevel[] =  {
		D3D_FEATURE_LEVEL_11_0,  // Direct3D 11.0 SM 5
		D3D_FEATURE_LEVEL_10_1,  // Direct3D 10.1 SM 4
		D3D_FEATURE_LEVEL_10_0,  // Direct3D 10.0 SM 4
		D3D_FEATURE_LEVEL_9_3,   // Direct3D 9.3  SM 3
		D3D_FEATURE_LEVEL_9_2,   // Direct3D 9.2  SM 2
		D3D_FEATURE_LEVEL_9_1,   // Direct3D 9.1  SM 2
	};
	int nFeatureCount = sizeof( FeatureLevel ) / sizeof( D3D_FEATURE_LEVEL );

	 // �\�t�g�E�F�A ���C���[
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
	// DirectX�̃o�[�W�����A�V�F�[�_���f���̃o�[�W�����ƍ̗p�����A�_�v�^�[�̖��O���f�o�b�N�E�B���h�E�ɏo��
	// �A�_�v�^�[�̏����擾
	DXGI_ADAPTER_DESC desc;
	m_pAdapter->GetDesc( &desc );

	// DirectX�̃o�[�W�����A�V�F�[�_���f���̃o�[�W�����ƍ̗p�����A�_�v�^�[�̖��O���f�o�b�N�E�B���h�E�ɏo��
	char buf[256];
	switch( m_eFeatureLevel )
	{
	case D3D_FEATURE_LEVEL_11_0:
		sprintf_s( buf, 256, "Direct3D(11.0) SM(5)�@%s", desc.Description );
		break;
	case D3D_FEATURE_LEVEL_10_1:
		sprintf_s( buf, 256, "Direct3D(10.1) SM(4)�@%s", desc.Description );
		break;
	case D3D_FEATURE_LEVEL_10_0:
		sprintf_s( buf, 256, "Direct3D(10.0) SM(4)�@%s", desc.Description );
		break;
	case D3D_FEATURE_LEVEL_9_3:
		sprintf_s( buf, 256, "Direct3D(9.3) SM(3)�@%s", desc.Description );
		break;
	case D3D_FEATURE_LEVEL_9_2:
		sprintf_s( buf, 256, "Direct3D(9.2) SM(2)�@%s", desc.Description );
		break;
	case D3D_FEATURE_LEVEL_9_1:
		sprintf_s( buf, 256, "Direct3D(9.1) SM(2)�@%s", desc.Description );
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
 * �X���b�v�`�F�[���̍쐬
 */
HRESULT Window::createSwapChain()
{
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory( &sd, sizeof(sd) );
	sd.BufferCount = 1;									// �o�b�N�o�b�t�@�̐�
	sd.BufferDesc.Width = m_nWidth;						// �o�b�t�@�̕�
	sd.BufferDesc.Height = m_nHeight;					// �o�b�t�@�̍���
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// �o�b�t�@�̃t�H�[�}�b�g
	sd.BufferDesc.RefreshRate.Numerator = 60;			// ���t���b�V�����[�g
	sd.BufferDesc.RefreshRate.Denominator = 1;			
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	// �o�b�N�o�b�t�@�Ƀ����_�����O�\�ɂ���
	sd.OutputWindow = m_hWnd;							// �o�̓E�B���h�E�ւ� HWND �n���h��
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;			// �T�[�t�F�X�̃X���b�v������Ƀo�b�N�o�b�t�@�̓��e��ێ����Ȃ�
	sd.Windowed = TRUE;									// �E�B���h�E���[�h
	//sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;	// �t���X�N���[�����[�h�ɐ؂�ւ���ƁA�A�v���P�[�V���� �E�B���h�E�̃T�C�Y�ɍ��킹�ĉ𑜓x���ύX�����B
	// �}���`�T���v�����g�p���Ȃ��ꍇ�̐ݒ�
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;

	// �t�@�N�g���[���쐬����
	IDXGIFactory* pFactory = NULL;
	// CreateDXGIFactory�ō쐬�����t�@�N�g���[���g�p����Ǝ��s�ł��邪���[�j���O�G���[�ɂȂ�̂� IDXGIAdapter ����쐬����B
	if( HRESULT( m_pAdapter->GetParent( __uuidof(IDXGIFactory), (void**)&pFactory ) ) )
	{
#ifdef DEBUG_MODE
		DebugManager::Output( "GetParent Error!!" );
#endif
		return E_FAIL;
	}

	int startMultisample;

	// �T���v�����O�����ő�̂��̂��̗p����
	startMultisample = D3D11_MAX_MULTISAMPLE_SAMPLE_COUNT;
	// �}���`�T���v���𖳌��ɂ���B
	//startMultisample = 1;

	UINT Quality = 0;
	for( int i=startMultisample; i>=0; i-- )
	{
		// �T�|�[�g����N�H���e�B���x���̍ő�l���擾����
		// CheckMultisampleQualityLevels
		if( HRESULT( m_pDevice->CheckMultisampleQualityLevels( DXGI_FORMAT_R8G8B8A8_UNORM, (UINT)i, &Quality ) ) )
		{
#ifdef DEBUG_MODE
			DebugManager::Output( "CheckMultisampleQualityLevels Error!!" );
#endif
			return E_FAIL;
		}

		// 0 �ȊO�̂Ƃ��t�H�[�}�b�g�ƃT���v�����O���̑g�ݍ��킹���T�|�[�g����
		// �I�����C���w���v�ł�CheckMultisampleQualityLevels�̖߂�l�� 0 �̂Ƃ��T�|�[�g����Ȃ��Ƃ�����Ă��邪
		// pNumQualityLevels �̖߂�l�� 0 ���Ŕ��f����B
		// Direct3D 10 �� �̃I�����C���w���v�ɂ͂���������Ă���̂ŁA�I�����C���w���v�̊ԈႢ�B
		if( Quality != 0 )
		{
			sd.SampleDesc.Count = i;
			sd.SampleDesc.Quality = Quality - 1;

			// �X���b�v�`�F�[�����쐬����B
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
 * �^�[�Q�b�g�r���[�̍쐬
 */
HRESULT Window::createTargetView()
{
	//�����_�[�^�[�Q�b�g�r���[�̍쐬
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
 * �[�x�X�e���V���r���[�̍쐬
 */
HRESULT Window::createDepthStencilView()
{
	ID3D11Texture2D* pBackBuffer = NULL;
	ID3D11Texture2D* pDepthBuffer = NULL;
	D3D11_TEXTURE2D_DESC descDS;
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	DXGI_SWAP_CHAIN_DESC chainDesc;

	// �X���b�v�`�F�[���̐ݒ���擾����
	if( HRESULT( m_pSwapChain->GetDesc( &chainDesc ) ) )
	{
#ifdef DEBUG_MODE
		DebugManager::Output( "GetDesc Error!!" );
#endif
		return E_FAIL;
	}

	ZeroMemory( &descDS, sizeof( D3D11_TEXTURE2D_DESC ) );
	descDS.Width              = chainDesc.BufferDesc.Width;			// �o�b�N�o�b�t�@�Ɠ����ɂ���B
	descDS.Height             = chainDesc.BufferDesc.Height;		// �o�b�N�o�b�t�@�Ɠ����ɂ���B
	descDS.MipLevels          = 1;									// �~�b�v�}�b�v���쐬���Ȃ�
	descDS.ArraySize          = 1;									// �e�N�X�`���[�̔z��
	descDS.Format             = DXGI_FORMAT_R16_TYPELESS;			// �t�H�[�}�b�g
	descDS.SampleDesc.Count   = chainDesc.SampleDesc.Count;			// �o�b�N�o�b�t�@�Ɠ����ɂ���B
	descDS.SampleDesc.Quality = chainDesc.SampleDesc.Quality;		// �o�b�N�o�b�t�@�Ɠ����ɂ���B
	descDS.Usage              = D3D11_USAGE_DEFAULT;				// GPU �ɂ��ǂݎ�肨��я������݃A�N�Z�X��K�v�Ƃ��郊�\�[�X�B
	//descDS.BindFlags		  = D3D11_BIND_DEPTH_STENCIL;			// �X�e���V���o�b�t�@
	descDS.BindFlags          = D3D11_BIND_DEPTH_STENCIL |			// �[�x�X�e���V���o�b�t�@�Ƃ��č쐬����
								D3D11_BIND_SHADER_RESOURCE;			// �V�F�[�_�[���\�[�X�r���[�Ƃ��č쐬����
	descDS.CPUAccessFlags     = 0;									// CPU �A�N�Z�X���s�v�B
	descDS.MiscFlags          = 0;									// ���̑��̃t���O���ݒ肵�Ȃ��B
	// �[�x�o�b�t�@�p�̃e�N�X�`���[�쐬
	if( HRESULT( m_pDevice->CreateTexture2D( &descDS, NULL, &pDepthBuffer ) ) )
	{
#ifdef DEBUG_MODE
		DebugManager::Output( "CreateTexture2D Error!!" );
#endif
		return E_FAIL;
	}

	ZeroMemory( &descDSV, sizeof( D3D11_DEPTH_STENCIL_VIEW_DESC ) );

	// �e�N�X�`���[�쐬���Ɏw�肵���t�H�[�}�b�g�ƌ݊���������A�[�x�X�e���V���r���[�Ƃ��Ďw��ł���t�H�[�}�b�g���w�肷��
	//   descDSV.Format = descDS.Format;
	switch( descDS.Format )
	{
		// 8�r�b�g�t�H�[�}�b�g�͎g�p�ł��Ȃ��H
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

	// �}���`�T���v�����g�p���Ă���ꍇ
	if( chainDesc.SampleDesc.Count > 1 )
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	// �}���`�T���v�����g�p���Ă��Ȃ��ꍇ
	else
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

	descDSV.Texture2D.MipSlice = 0;
	// �[�x�X�e���V���r���[���쐬
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
 * �r���[�|�[�g�̍쐬
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
 * �f�t�H���g�̃��X�^���C�U��ݒ�
 */
HRESULT Window::setDefaultRasterize()
{
	ID3D11RasterizerState* pRasterState = NULL;
	D3D11_RASTERIZER_DESC rsState;
	rsState.FillMode = D3D11_FILL_SOLID;    // �|���S���ʕ`��
	rsState.CullMode = D3D11_CULL_BACK;     // ���ʂ�`�悵�Ȃ�
	//   rsState.FrontCounterClockwise = FALSE;  // ���v����\��
	rsState.FrontCounterClockwise = TRUE;   // �����v����\��
	rsState.DepthBias = 0;
	rsState.DepthBiasClamp = 0;
	rsState.SlopeScaledDepthBias = 0;
	rsState.DepthClipEnable = TRUE;
	rsState.ScissorEnable = FALSE;          // �V�U�[��`����

	// �X���b�v�`�F�[���̃}���`�T���v�����O�̐ݒ�ɂ��킹��
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
 * �f�t�H���g�̐[�x�X�e���V���X�e�[�g��ݒ�
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

