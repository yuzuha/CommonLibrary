#include "RenderTargetBase.h"
#include "ColorPolygon.h"
#include "RenderManagerBase.h"
#include "ColorPolygonManager.h"

/**
 * �R���X�g���N�^
 */
ColorPolygon::ColorPolygon()
{
}


/**
 * �f�X�g���N�^
 */
ColorPolygon::~ColorPolygon()
{
}


/**
 * �`��
 */
void ColorPolygon::Render()
{
	ColorPolygonManager::Render(this);
}


