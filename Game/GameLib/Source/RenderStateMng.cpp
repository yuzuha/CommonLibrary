#include "RenderStateMng.h"
RenderStateMng* RenderStateMng::m_pInstance = NULL;


/**
 * ������
 */
int RenderStateMng::Init()
{
	return 1;
}


/**
 * ���������
 */
int RenderStateMng::Destroy()
{
	return 1;
}


/**
 * RenderState�̍X�V
 */
HRESULT RenderStateMng::_SetRenderState( _D3DRENDERSTATETYPE type, DWORD state )
{
	bool result = false;
	switch( type ){
	case D3DRS_ZWRITEENABLE:
		result = ( state == (DWORD)m_isZWriteEnable ? false : true );
		break;
	case D3DRS_ZENABLE:
		result = ( state == (DWORD)m_isZEnable ? false : true );
		break;
	case D3DRS_CULLMODE:
		result = ( state == m_nCullMode ? false : true );
		break;
	}
	if( result )
		return Window::GetD3DDevice()->SetRenderState( type, state );
	return S_OK;
}

