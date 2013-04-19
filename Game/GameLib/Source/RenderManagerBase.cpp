#include "RenderManagerBase.h"
#include "Window.h"
#include "DebugManager.h"
RenderManagerBase* RenderManagerBase::m_pInstance = NULL;


/**
 * �R���X�g���N�^
 */
RenderManagerBase::RenderManagerBase()
{
	_Init();
}


/**
 * �f�X�g���N�^
 */
RenderManagerBase::~RenderManagerBase()
{
	_Cleanup();
}



/**
 * ������
 */
void RenderManagerBase::_Init()
{
	m_pVertexShader	= NULL;
	m_pPixelShader	= NULL;
	m_pVertexBuffer	= NULL;
	m_pVertexLayout	= NULL;
	m_strPath		= "";
}


/**
 * �J��
 */
void RenderManagerBase::_Cleanup()
{
	SAFE_RELEASE(m_pVertexShader);
	SAFE_RELEASE(m_pPixelShader);
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pVertexLayout); 
}


/**
 * �j��
 */
void RenderManagerBase::_Destroy()
{
	SAFE_DELETE(m_pInstance);
}


/**
 * �`��
 */
void RenderManagerBase::_Render()
{

}


/**
 * �`��
 */
void RenderManagerBase::_Render( RenderTargetBase* _base )
{

}


/**
 * �V�F�[�_�[�ǂݍ���
 */
HRESULT RenderManagerBase::_LoadShader( string _path )
{
	m_strPath = _path;
	LPCTSTR pPath = _path.c_str();
	ID3D11Device *pDevice = Window::GetDevice();
	ID3D11DeviceContext *pDeviceContext = Window::GetDeviceContext();
	ID3DBlob *pCompiledShader	= NULL;
	ID3DBlob *pErrors			= NULL;
	string strError;
	//�u���u���璸�_�V�F�[�_�[�쐬
	if( FAILED( D3DX11CompileFromFile( pPath, NULL, NULL, "VS", "vs_5_0", 0, 0, NULL, &pCompiledShader, &pErrors, NULL ) ) )
	{
#ifdef DEBUG_MODE
		DebugManager::Output((char*)pErrors->GetBufferPointer());
#endif
		return E_FAIL;
	}
	SAFE_RELEASE(pErrors);

	if( FAILED( pDevice->CreateVertexShader( pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), NULL, &m_pVertexShader)))
	{
#ifdef DEBUG_MODE
		DebugManager::Output("CreateVertexShader Error!!");
#endif
		SAFE_RELEASE(pCompiledShader);
		return E_FAIL;
	}
	//���_�C���v�b�g���C�A�E�g���` 
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }, 
		//{ "COLOR", 0,  DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }, 
	};
	UINT numElements = sizeof(layout)/sizeof(layout[0]);

	//���_�C���v�b�g���C�A�E�g���쐬
	if( FAILED( pDevice->CreateInputLayout( layout, numElements, pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), &m_pVertexLayout ) ) )
		return FALSE;
	//���_�C���v�b�g���C�A�E�g���Z�b�g
	pDeviceContext->IASetInputLayout( m_pVertexLayout );

	//�u���u����s�N�Z���V�F�[�_�[�쐬
	if( FAILED( D3DX11CompileFromFile( pPath, NULL, NULL, "PS", "ps_5_0", 0, 0, NULL, &pCompiledShader, &pErrors, NULL ) ) )
	{
#ifdef DEBUG_MODE
		DebugManager::Output((char*)pErrors->GetBufferPointer());
#endif
		return E_FAIL;
	}
	SAFE_RELEASE( pErrors );
	if(FAILED( pDevice->CreatePixelShader( pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), NULL, & m_pPixelShader ) ) )
	{
#ifdef DEBUG_MODE
		DebugManager::Output("CreatePixelShader Error!!");
#endif
		SAFE_RELEASE( pCompiledShader );
		return E_FAIL;
	}

#ifdef DEBUG_MODE
	char buf[128];
	sprintf_s( buf, 128, "LoadShader Success!! - %s", _path.c_str() );
	DebugManager::Output(buf);
#endif

	return S_OK;
}

