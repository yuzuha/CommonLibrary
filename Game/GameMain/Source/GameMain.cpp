#include "GameMain.h"

/**
 * 初期化
 * @param hInst		インスタンス
 * @param IsFull	フルスクリーンかどうか
 */
void GameMain::Init( HINSTANCE hInst )
{
	// 乱数調整
	srand( (unsigned)time( NULL ) );
	// ウィンドウの初期化
	m_pWindow = Window::GetInstance();
	if( HRESULT ( m_pWindow->_Init( hInst ) ) )
	{
#ifdef DEBUG_MODE
		DebugManager::Output( "Window Init Error!!" );
#endif
		return;
	}

}


/**
 * メモリ解放
 */
void GameMain::Destroy( void )
{
	m_pWindow->_Destroy();
}


/**
 * ゲーム本体のメイン関数
 */
void GameMain::Main( void )
{
	ColorPolygonManager *pCPMng = ColorPolygonManager::GetInstance();
	string strPath = "../../GameLib/Resource/Shader/base.hlsl";
	pCPMng->_LoadShader(strPath);
	ColorPolygon *obj = new ColorPolygon();
	obj->SetCenter( &D3DXVECTOR3(0.0f, 0.0f, 0.0f) );
	obj->SetSize( &D3DXVECTOR2(0.1f, 0.1f) );
	obj->SetColor( 0xff00ffff );

	do{
		// 描画開始
		if( m_pWindow->_RenderBegin() ){
			/*
			// 描画スレッドのバッファ切り替え
			m_pDrawThread->Clear();
			// 描画スレッドを稼働させる
			m_pDrawThread->SetSleep( false );
			// 更新
			CSceneBase* pNext;
			if( m_pFileLoadThread->GetYetLoadNum() > 0 ){
				m_pNowLoadingEffect->Update();
				m_pNowLoadingEffect->Draw();
				pNext = m_pChild;
			} else {
				// 更新
				pNext = m_pChild->Update();
				// 描画登録
				m_pChild->Draw();
			}

			// 描画スレッドの描画が終わるまで待機させる
			while( !m_pDrawThread->GetSleep() ){
				Sleep(1);
			}
			// ゲームシーンの変更
			if( pNext != m_pChild ){
				if( pNext == NULL )
					break;
				SAFE_DELETE( m_pChild );
				m_pChild = pNext;
			}
			*/
			obj->Render();

			// 描画終了
			m_pWindow->_RenderEnd();
		}
		/*
		// FPS管理
		m_pTime->FPSTimer();

#ifdef _DEBUG
		// FPSをウィンドウ名に描画
		char buffer[100];
		sprintf_s( buffer, 100, "%s : FPS %d", m_pWindow->GetWindowName(), m_pTime->GetFrameRate() );
		SetWindowText( m_pWindow->GethWnd(), buffer );
#endif
		*/
	}while( m_pWindow->_ProcessEvent() );

}

