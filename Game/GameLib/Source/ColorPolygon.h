#pragma once
#include "Global.h"
class RenderTargetBase;

typedef struct{
	D3DXVECTOR3	m_vecCenter;	///< ���_���W
	//DWORD		m_nColor;		///< ���_�F
}ST_ColorPolygon;

/**
 * �F�L�|���S��
 */
class ColorPolygon : public RenderTargetBase
{
private:
	DWORD		m_nColor;		///< �F
	D3DXVECTOR3	m_vecCenter;	///< ���S
	D3DXVECTOR2	m_vecSize;		///< ����
public:
	// �R���X�g���N�^
	ColorPolygon();
	// �f�X�g���N�^
	~ColorPolygon();
	// �`��
	void Render();
	/**
	 * ���S���W�̐ݒ�
	 */
	void SetCenter( D3DXVECTOR3 *_center )
	{
		m_vecCenter = *_center;
	}
	/**
	 * ���S���W�̎擾
	 */
	D3DXVECTOR3* GetCenter()
	{
		return &m_vecCenter;
	}
	/**
	 * �T�C�Y�̐ݒ�
	 */
	void SetSize( D3DXVECTOR2 *_size )
	{
		m_vecSize = *_size;
	}
	/**
	 * �T�C�Y�̎擾
	 */
	D3DXVECTOR2* GetSize()
	{
		return &m_vecSize;
	}
	/**
	 * �F�̐ݒ�
	 */
	void SetColor( DWORD _color )
	{
		m_nColor = _color;
	}
	/**
	 * �F�̎擾
	 */
	DWORD GetColor()
	{
		return m_nColor;
	}
};
