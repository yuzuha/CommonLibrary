#pragma once
#include "Global.h"
#include "Window.h"

/**
 * RenderState���s���ۂ͂��̃N���X��ʂ��čs��
 */
class RenderStateMng
{
private:
	static RenderStateMng	*m_pInstance;		///< ���g�̃C���X�^���X
	bool					m_isZWriteEnable;	///< Z�[�x�o�b�t�@�t���O
	bool					m_isZEnable;		///< Z�o�b�t�@�t���O
	_D3DCULL				m_nCullMode;		///< �J�����O���
public:
	int Init();
	static int Destroy();
	static HRESULT SetRenderState( _D3DRENDERSTATETYPE type, DWORD state )
	{
		return GetInstance()->_SetRenderState( type, state );
	}
private:
	/**
	 * �f�t�H���g�R���X�g���N�^
	 */
	RenderStateMng( void )
	{
		Init();
	}
	/**
	 * �f�X�g���N�^
	 */
	~RenderStateMng( void )
	{
		Destroy();
	}
	/**
	 * ���g�̃C���X�^���X���擾
	 */
	static RenderStateMng* GetInstance( void )
	{
		if( !m_pInstance )
			m_pInstance = new RenderStateMng();
		return m_pInstance;
	}
	HRESULT _SetRenderState( _D3DRENDERSTATETYPE type, DWORD state );
};