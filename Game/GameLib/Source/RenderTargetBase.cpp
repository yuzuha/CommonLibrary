#include "RenderTargetBase.h"
#include "RenderManagerBase.h"


/**
 * �R���X�g���N�^
 */
RenderTargetBase::RenderTargetBase()
{
}


/**
 * �f�X�g���N�^
 */
RenderTargetBase::~RenderTargetBase()
{
}


/**
 * �`��
 */
void RenderTargetBase::Render()
{
	RenderManagerBase::Render(this);
}

