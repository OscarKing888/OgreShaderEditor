#include "stdafx.h"
#include "BlockWithView.h"
#include "OgreMaterialManager.h"
#include "OgreTechnique.h"
#include "OgrePass.h"
#include "OgreTextureUnitState.h"

namespace Ogre
{
	BlockWithView::BlockWithView(const String& name)
		: GlyphBlock(name)
	{
		_viewPanel = dynamic_cast<PanelOverlayElement*>(
			OverlayManager::getSingleton().createOverlayElement("Panel", name + "/ViewPanel"));

		MaterialPtr baseWhite = MaterialPtr(MaterialManager::getSingleton().getByName("BaseWhiteNoLighting"));
		_viewMaterial = baseWhite->clone(name + "/View");
		TextureUnitState* ts = _viewMaterial->getTechnique(0)->getPass(0)->createTextureUnitState();

		_viewPanel->setMaterialName(_viewMaterial->getName());
		_viewPanel->setMetricsMode(GMM_PIXELS);
		_container->addChild(_viewPanel);
		setDimisions(180, 130);
	}
	//--------------------------------------------------------------------------------
	BlockWithView::~BlockWithView()
	{
		OverlayManager::getSingleton().destroyOverlayElement(_viewPanel);
		_viewPanel = 0;

		MaterialManager::getSingleton().remove(_viewMaterial->getName());
	}
	//--------------------------------------------------------------------------------
	void BlockWithView::setTextureName(const String& texName)
	{
		_textureName = texName;
		_viewPanel->setMaterialName(_viewMaterial->getName());
		TextureUnitState* ts = _viewMaterial->getTechnique(0)->getPass(0)->getTextureUnitState(0);
		ts->setTextureName(texName);
		//ts->setColourOperation(LBO_ALPHA_BLEND);
		//ts->setAlphaOperation(LBX_SOURCE1);
	}
	//--------------------------------------------------------------------------------
	void BlockWithView::addToContainer(OverlayContainer* c)
	{
		//_container->addChild(_viewPanel);
		GlyphBlock::addToContainer(c);
	}
	//--------------------------------------------------------------------------------
	void BlockWithView::removeFromContainer()
	{
		//_container->removeChild(_viewPanel->getName());
		GlyphBlock::removeFromContainer();
	}
	//--------------------------------------------------------------------------------
	void BlockWithView::setViewFillColour(const ColourValue& clr)
	{
		_viewPanel->setMaterialName(_viewMaterial->getName());
		TextureUnitState* ts = _viewMaterial->getTechnique(0)->getPass(0)->getTextureUnitState(0);
		ts->setColourOperationEx(LBX_SOURCE1, LBS_MANUAL, LBS_CURRENT, clr, clr);
	}
	//--------------------------------------------------------------------------------
	void BlockWithView::layout()
	{
		GlyphBlock::layout();
		RealRect rc = getClientRect();
		_viewPanel->setPosition(rc.left + C_CHAR_HEIGHT, rc.top + C_TEXT_MARGIN_TOP * 2);
		_viewPanel->setDimensions(rc.width() - C_CHAR_HEIGHT * 3, rc.height() - C_TEXT_MARGIN_TOP * 4);
	}
	//--------------------------------------------------------------------------------
	void BlockWithView::setViewMaterial(MaterialPtr mat)
	{
		_viewPanel->setMaterialName(mat->getName());
	}
	//--------------------------------------------------------------------------------
	void BlockWithView::setViewMaterial(const String& matName)
	{
		_viewPanel->setMaterialName(matName);
	}
	//--------------------------------------------------------------------------------
	Pass* BlockWithView::getViewMaterialPass() const
	{
		return _viewMaterial->getTechnique(0)->getPass(0);
	}
}