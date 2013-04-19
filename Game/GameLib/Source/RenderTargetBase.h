#pragma once
#include "Global.h"

/**
 * �`��^�[�Q�b�g���
 */
class RenderTargetBase
{
protected:
	D3DXMATRIX m_matWorld;		///< ���[���h�s��
public:
	// �R���X�g���N�^
	RenderTargetBase();
	// �f�X�g���N�^
	virtual~RenderTargetBase();
	/**
	 * ���[���h�s��̐ݒ�
	 */
	void SetWorldMatrix( D3DXMATRIX *_mat )
	{
		m_matWorld = *_mat;
	}
	/**
	 * ���[���h�s��̎擾
	 */
	D3DXMATRIX* GetWorldMatrix()
	{
		return &m_matWorld;
	}
	/**
	 * �`��
	 */
	virtual void Render();
};
