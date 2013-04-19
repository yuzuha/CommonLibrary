#include "GameMain.h"

/**
 * ������
 * @param hInst		�C���X�^���X
 * @param IsFull	�t���X�N���[�����ǂ���
 */
void GameMain::Init( HINSTANCE hInst )
{
	// ��������
	srand( (unsigned)time( NULL ) );
	// �E�B���h�E�̏�����
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
 * ���������
 */
void GameMain::Destroy( void )
{
	m_pWindow->_Destroy();
}


/**
 * �Q�[���{�̂̃��C���֐�
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
		// �`��J�n
		if( m_pWindow->_RenderBegin() ){
			/*
			// �`��X���b�h�̃o�b�t�@�؂�ւ�
			m_pDrawThread->Clear();
			// �`��X���b�h���ғ�������
			m_pDrawThread->SetSleep( false );
			// �X�V
			CSceneBase* pNext;
			if( m_pFileLoadThread->GetYetLoadNum() > 0 ){
				m_pNowLoadingEffect->Update();
				m_pNowLoadingEffect->Draw();
				pNext = m_pChild;
			} else {
				// �X�V
				pNext = m_pChild->Update();
				// �`��o�^
				m_pChild->Draw();
			}

			// �`��X���b�h�̕`�悪�I���܂őҋ@������
			while( !m_pDrawThread->GetSleep() ){
				Sleep(1);
			}
			// �Q�[���V�[���̕ύX
			if( pNext != m_pChild ){
				if( pNext == NULL )
					break;
				SAFE_DELETE( m_pChild );
				m_pChild = pNext;
			}
			*/
			obj->Render();

			// �`��I��
			m_pWindow->_RenderEnd();
		}
		/*
		// FPS�Ǘ�
		m_pTime->FPSTimer();

#ifdef _DEBUG
		// FPS���E�B���h�E���ɕ`��
		char buffer[100];
		sprintf_s( buffer, 100, "%s : FPS %d", m_pWindow->GetWindowName(), m_pTime->GetFrameRate() );
		SetWindowText( m_pWindow->GethWnd(), buffer );
#endif
		*/
	}while( m_pWindow->_ProcessEvent() );

}

