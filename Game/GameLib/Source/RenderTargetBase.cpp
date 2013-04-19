#include "RenderTargetBase.h"
#include "RenderManagerBase.h"


/**
 * コンストラクタ
 */
RenderTargetBase::RenderTargetBase()
{
}


/**
 * デストラクタ
 */
RenderTargetBase::~RenderTargetBase()
{
}


/**
 * 描画
 */
void RenderTargetBase::Render()
{
	RenderManagerBase::Render(this);
}

