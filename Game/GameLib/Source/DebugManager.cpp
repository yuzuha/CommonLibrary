#include "DebugManager.h"

/**
 * �R���X�g���N�^
 */
DebugManager::DebugManager()
{
}


/**
 * �f�X�g���N�^
 */
DebugManager::~DebugManager()
{
}


/**
 * �f�o�b�O�p������̏o��
 */
void DebugManager::Output( const string _str )
{
	Output( _str.c_str() );
}


/**
 * �f�o�b�O�p������̏o��
 */
void DebugManager::Output( const char *_str )
{
	OutputDebugStringA( _str );
	OutputDebugStringA( "\n" );
}


