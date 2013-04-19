#pragma once
#include "Global.h"
class RenderManagerBase;
class ColorPolygon;

/**
 * �F�L�|���̕`��Ǘ�
 */
class ColorPolygonManager : public RenderManagerBase
{
private:
public:
	/**
	 * �C���X�^���X�̎擾
	 */
	static ColorPolygonManager* GetInstance()
	{
		if( !m_pInstance ){
			m_pInstance = new ColorPolygonManager();
		}
		return dynamic_cast<ColorPolygonManager*>(m_pInstance);
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
	void _Init();
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
	void _Cleanup();
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
	void _Destroy();
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
	void _Render();
	/**
	 * �`��
	 */
	static void Render(ColorPolygon* _obj)
	{
		GetInstance()->_Render(_obj);
	}
	/**
	 * �`��
	 */
	void _Render(ColorPolygon* _obj);
private:
	// �R���X�g���N�^
	ColorPolygonManager();
	// �f�X�g���N�^
	~ColorPolygonManager();
};

