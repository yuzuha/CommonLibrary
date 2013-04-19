#pragma once
#include "Global.h"
using namespace std;

/**
 * �f�o�b�O�֌W���Ǘ�
 */
class DebugManager
{
private:
	static DebugManager *m_pInstance;	///< �C���X�^���X
public:
	/**
	 * �C���X�^���X�̎擾
	 */
	static DebugManager *GetInstance()
	{
		if( !m_pInstance )
		{
			m_pInstance = new DebugManager();
		}
		return m_pInstance;
	}
	// �f�o�b�O�p������̏o��
	static void Output( const string _str );
	static void Output( const char *_str );
private:
	// �R���X�g���N�^
	DebugManager();
	// �f�X�g���N�^
	~DebugManager();

};