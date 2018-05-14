#include "stdafx.h"
#include "PanelGlyph.h"
#include "OgreMaterialManager.h"
#include "OgreTechnique.h"
#include "OgrePass.h"
#include "OgreTextureUnitState.h"

namespace Ogen
{
	PanelGlyph::PanelGlyph(const String& name)
		: MaterialGlyph(name)
		, _borderPanel(0)
		, _borderColor(ColourValue::Black)
		, _fillColor(ColourValue(140.0f/255.0f, 140.0f/255.0f, 140.0f/255.0f))
	{
		_borderPanel = dynamic_cast<BorderPanelOverlayElement*>(
			OverlayManager::getSingleton().createOverlayElement(
			"BorderPanel", name + "/PanelGlyph"));

		_borderPanel->setMetricsMode(GMM_PIXELS);

		MaterialPtr baseWhite = MaterialPtr(MaterialManager::getSingleton().getByName("BaseWhiteNoLighting"));

		_fillMaterial = baseWhite->clone(name + "/Fill");
		TextureUnitState* ts = _fillMaterial->getTechnique(0)->getPass(0)->createTextureUnitState();

		_borderMaterial = baseWhite->clone(name + "/Border");
		ts = _borderMaterial->getTechnique(0)->getPass(0)->createTextureUnitState();

		setFillColour(_fillColor);
		setBorderColour(_borderColor);

		_borderPanel->setMaterialName(_fillMaterial->getName());
		_borderPanel->setBorderMaterialName(_borderMaterial->getName());		

		setBorderWidth(1);
	}
	//--------------------------------------------------------------------------------
	PanelGlyph::~PanelGlyph()
	{
		OverlayManager::getSingleton().destroyOverlayElement(_borderPanel);
		_borderPanel = 0;
	}
	//--------------------------------------------------------------------------------
	void PanelGlyph::setBorderWidth(Real w)
	{
		_borderPanel->setBorderSize(w, w, w, w);
	}
	//--------------------------------------------------------------------------------
	Real PanelGlyph::getBorderWidth() const
	{
		return _borderPanel->getLeftBorderSize();
	}
	//--------------------------------------------------------------------------------
	void PanelGlyph::setBorderColour(const ColourValue& clr)
	{
		_borderColor = clr;
		TextureUnitState* ts = _borderMaterial->getTechnique(0)->getPass(0)->getTextureUnitState(0);
		ts->setColourOperationEx(LBX_SOURCE1, LBS_MANUAL, LBS_CURRENT, clr, clr);
	}
	//--------------------------------------------------------------------------------
	const ColourValue& PanelGlyph::getBorderColour() const
	{
		return _borderColor;
	}
	//--------------------------------------------------------------------------------
	void PanelGlyph::setFillColour(const ColourValue& clr)
	{
		_fillColor = clr;
		TextureUnitState* ts = _fillMaterial->getTechnique(0)->getPass(0)->getTextureUnitState(0);
		ts->setColourOperationEx(LBX_SOURCE1, LBS_MANUAL, LBS_CURRENT, clr, clr);
	}
	//--------------------------------------------------------------------------------
	const ColourValue& PanelGlyph::getFillColour() const
	{
		return _fillColor;
	}
	//--------------------------------------------------------------------------------
	void PanelGlyph::setColour(const ColourValue& clr)
	{
		setFillColour(clr);
		setBorderColour(clr);
	}
	//--------------------------------------------------------------------------------
	void PanelGlyph::setDimisions(Real w, Real h)
	{
		_borderPanel->setDimensions(w, h);
	}	
	//--------------------------------------------------------------------------------
	Real PanelGlyph::getWidth() const
	{
		return _borderPanel->getWidth();
	}
	//--------------------------------------------------------------------------------
	void PanelGlyph::setWidth(Real w)
	{
		_borderPanel->setWidth(w);
	}
	//--------------------------------------------------------------------------------
	Real PanelGlyph::getHeight() const
	{
		return _borderPanel->getHeight();
	}
	//--------------------------------------------------------------------------------
	void PanelGlyph::setHeight(Real h)
	{
		_borderPanel->setHeight(h);
	}
	//--------------------------------------------------------------------------------
	void PanelGlyph::addToContainer(OverlayContainer* c)
	{
		MaterialGlyph::addToContainer(c);
		c->addChild(_borderPanel);
	}
	//--------------------------------------------------------------------------------
	void PanelGlyph::removeFromContainer()
	{
		_parentContainer->removeChild(_borderPanel->getName());
	}
	//--------------------------------------------------------------------------------
	void PanelGlyph::setPosition(Real x, Real y)
	{
		_borderPanel->setPosition(x, y);
	}
	//--------------------------------------------------------------------------------
	Vector2 PanelGlyph::getPosition() const
	{
		return Vector2(_borderPanel->getLeft(), _borderPanel->getTop());
	}
	//--------------------------------------------------------------------------------
	void PanelGlyph::setBorderMaterialName(const String& matName)
	{
		_borderPanel->setBorderMaterialName(matName);
	}
	//--------------------------------------------------------------------------------
	const String& PanelGlyph::getBorderMaterialName() const
	{
		return _borderPanel->getBorderMaterialName();
	}
	//--------------------------------------------------------------------------------
	void PanelGlyph::setFillMaterialName(const String& matName)
	{
		_borderPanel->setMaterialName(matName);
	}
	//--------------------------------------------------------------------------------
	const String& PanelGlyph::getFillMaterialName() const
	{
		return _borderPanel->getMaterialName();
	}

}