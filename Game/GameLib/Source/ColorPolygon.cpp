#include "RenderTargetBase.h"
#include "ColorPolygon.h"
#include "RenderManagerBase.h"
#include "ColorPolygonManager.h"

/**
 * コンストラクタ
 */
ColorPolygon::ColorPolygon()
{
}


/**
 * デストラクタ
 */
ColorPolygon::~ColorPolygon()
{
}


/**
 * 描画
 */
void ColorPolygon::Render()
{
	ColorPolygonManager::Render(this);
}


