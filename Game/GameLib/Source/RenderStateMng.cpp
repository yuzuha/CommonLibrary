#include "RenderStateMng.h"
RenderStateMng* RenderStateMng::m_pInstance = NULL;


/**
 * 初期化
 */
int RenderStateMng::Init()
{
	return 1;
}


/**
 * メモリ解放
 */
int RenderStateMng::Destroy()
{
	return 1;
}


/**
 * RenderStateの更新
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

