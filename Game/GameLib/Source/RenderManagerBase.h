#pragma once
#include "Global.h"
using namespace std;
class RenderTargetBase;

/**
 * �`����N���X
 */
class RenderManagerBase
{
protected:
	static RenderManagerBase	*m_pInstance;		///< �C���X�^���X
	ID3D11InputLayout			*m_pVertexLayout;
	ID3D11Buffer				*m_pVertexBuffer;
	ID3D11VertexShader			*m_pVertexShader;	///< ���_�V�F�[�_�[
	ID3D11PixelShader			*m_pPixelShader;	///< �s�N�Z���V�F�[�_�[
	string						m_strPath;			///< �V�F�[�_�[��
public:
	/**
	 * �C���X�^���X�̎擾
	 */
	static RenderManagerBase* GetInstance()
	{
		if( !m_pInstance ){
			m_pInstance = new RenderManagerBase();
		}
		return m_pInstance;
	}
	/**
	 * ������
	 */
	static void Init()
	{
		GetInstance()->_Init();
	}
	/**
	 * ������
	 */
	virtual void _Init();
	/**
	 * �J��
	 */
	static void Cleanup()
	{
		GetInstance()->_Cleanup();
	}
	/**
	 * �J��
	 */
	virtual void _Cleanup();
	/**
	 * �j��
	 */
	static void Destroy()
	{
		GetInstance()->_Destroy();
	}
	/**
	 * �j��
	 */
	virtual void _Destroy();
	/**
	 * �`��
	 */
	static void Render()
	{
		GetInstance()->_Render();
	}
	/**
	 * �`��
	 */
	virtual void _Render();
	/**
	 * �`��
	 */
	static void Render( RenderTargetBase* _base )
	{
		GetInstance()->_Render(_base);
	}
	/**
	 * �`��
	 */
	virtual void _Render( RenderTargetBase* _base );
	/**
	 * �V�F�[�_�[�ǂݍ���
	 */
	static HRESULT LoadShader( string _path )
	{
		return GetInstance()->_LoadShader( _path );
	}
	/**
	 * �V�F�[�_�[�ǂݍ���
	 */
	virtual HRESULT _LoadShader( string _path );
protected:
	// �R���X�g���N�^
	RenderManagerBase();
	// �f�X�g���N�^
	virtual ~RenderManagerBase();
};

