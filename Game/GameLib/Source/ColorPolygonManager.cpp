#include "RenderManagerBase.h"
#include "ColorPolygonManager.h"
#include "RenderTargetBase.h"
#include "ColorPolygon.h"
#include "Window.h"

/**
 * コンストラクタ
 */
ColorPolygonManager::ColorPolygonManager()
{
}


/**
 * デストラクタ
 */
ColorPolygonManager::~ColorPolygonManager()
{
}


/**
 * 初期化
 */
void ColorPolygonManager::_Init()
{
}


/**
 * 開放
 */
void ColorPolygonManager::_Cleanup()
{
}


/**
 * 破棄
 */
void ColorPolygonManager::_Destroy()
{
}


/**
 * 描画
 */
void ColorPolygonManager::_Render()
{
}



/**
 * 描画
 */
void ColorPolygonManager::_Render(ColorPolygon* _obj)
{
	ID3D11Device *pDevice = Window::GetDevice();
	ID3D11DeviceContext *pDeviceContext = Window::GetDeviceContext();

	D3DXVECTOR3 vecCenter	= *_obj->GetCenter();
	D3DXVECTOR2 vecSize	= *_obj->GetSize();
	DWORD	 nColor		= _obj->GetColor();

	//四角形
	ST_ColorPolygon vertices[] =
	{
		//D3DXVECTOR3( vecCenter.x-vecSize.x, vecCenter.y-vecSize.y, vecCenter.z ), nColor,
		//D3DXVECTOR3( vecCenter.x-vecSize.x, vecCenter.y+vecSize.y, vecCenter.z ), nColor,
		//D3DXVECTOR3( vecCenter.x+vecSize.x, vecCenter.y-vecSize.y, vecCenter.z ), nColor,
		//D3DXVECTOR3( vecCenter.x+vecSize.x, vecCenter.y+vecSize.y, vecCenter.z ), nColor,
		D3DXVECTOR3( vecCenter.x-vecSize.x, vecCenter.y-vecSize.y, vecCenter.z ),
		D3DXVECTOR3( vecCenter.x-vecSize.x, vecCenter.y+vecSize.y, vecCenter.z ),
		D3DXVECTOR3( vecCenter.x+vecSize.x, vecCenter.y-vecSize.y, vecCenter.z ),
		D3DXVECTOR3( vecCenter.x+vecSize.x, vecCenter.y+vecSize.y, vecCenter.z ),
	};
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof( ST_ColorPolygon ) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;
	if( FAILED( pDevice->CreateBuffer( &bd, &InitData, &m_pVertexBuffer ) ) )
	{
		return;
	}

	//バーテックスバッファーをセット
	UINT stride = sizeof( ST_ColorPolygon );
	UINT offset = 0;
	pDeviceContext->IASetVertexBuffers( 0, 1, &m_pVertexBuffer, &stride, &offset );

	//プリミティブ・トポロジーをセット
	pDeviceContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );

	pDeviceContext->VSSetShader( m_pVertexShader, NULL, 0 );
	pDeviceContext->PSSetShader( m_pPixelShader, NULL, 0 );
	//プリミティブをレンダリング
	pDeviceContext->Draw( 4, 0 );
}
