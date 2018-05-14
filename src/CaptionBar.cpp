#include "stdafx.h"
#include "CaptionBar.h"
#include "PanelGlyph.h"
#include "OgreFontManager.h"
#include "OgreRoot.h"

namespace Ogen
{
	CaptionBar::CaptionBar(const String& name, const DisplayString& caption)
		: MaterialGlyph(name)
		, _autoSize(true)
		, _dimisionChange(true)
	{
		_textShadow = dynamic_cast<TextAreaOverlayElement*>(
			OverlayManager::getSingleton().createOverlayElement("TextArea", name + "/Text/Shadow"));

		_text = dynamic_cast<TextAreaOverlayElement*>(
			OverlayManager::getSingleton().createOverlayElement("TextArea", name + "/Text"));

		
		//ResourceHandle rh = FontManager::getSingleton().getResourceIterator().peekNextKey();
		//FontPtr pfnt = FontPtr(FontManager::getSingleton().getByHandle(rh));
		_textShadow->setPosition(C_TEXT_MARGIN_LEFT + C_TEXT_SHADOW_OFFSET,
			C_TEXT_MARGIN_TOP + C_TEXT_SHADOW_OFFSET);

		_text->setPosition(C_TEXT_MARGIN_LEFT, C_TEXT_MARGIN_TOP);
		

		_textShadow->setMetricsMode(GMM_PIXELS);
		_textShadow->setCharHeight(C_CHAR_HEIGHT);
		_textShadow->setFontName(C_DEFAULT_FONT_NAME);
		_textShadow->setColour(ColourValue::Black);

	
		_text->setMetricsMode(GMM_PIXELS);
		_text->setCharHeight(C_CHAR_HEIGHT);
		_text->setFontName(C_DEFAULT_FONT_NAME);
		_panel = new PanelGlyph(name);

		setCaption(caption);

		Root::getSingleton().addFrameListener(this);
	}
	//--------------------------------------------------------------------------------
	CaptionBar::~CaptionBar(void)
	{
		delete _panel;
		_panel = 0;

		OverlayManager::getSingleton().destroyOverlayElement(_text);
		_text = 0;

		OverlayManager::getSingleton().destroyOverlayElement(_textShadow);
		_textShadow = 0;
	}
	//--------------------------------------------------------------------------------
	void CaptionBar::setFontName(const String& name)
	{
		_text->setFontName(name);
		_textShadow->setFontName(name);
	}
	//--------------------------------------------------------------------------------
	const String& CaptionBar::getFontName() const
	{
		return _text->getFontName();
	}
	//--------------------------------------------------------------------------------
	void CaptionBar::setCaption(const DisplayString& caption)
	{
		_text->setCaption(caption);
		_textShadow->setCaption(caption);
		_dimisionChange = true;
	}
	//--------------------------------------------------------------------------------
	const DisplayString& CaptionBar::getCaption() const
	{
		return _text->getCaption();
	}
	//--------------------------------------------------------------------------------
	void CaptionBar::setTextColour(const ColourValue& clr)
	{
		_text->setColour(clr);
	}
	//--------------------------------------------------------------------------------
	const ColourValue& CaptionBar::getTextColour() const
	{
		return _text->getColour();
	}
	//--------------------------------------------------------------------------------
	void CaptionBar::setDimisions(Real w, Real h)
	{
		_text->setDimensions(w, h);
		_textShadow->setDimensions(w, h);
		_panel->setDimisions(w, h);
	}
	//--------------------------------------------------------------------------------
	Real CaptionBar::getWidth() const
	{
		return _panel->getWidth();
	}
	//--------------------------------------------------------------------------------
	void CaptionBar::setWidth(Real w)
	{
		_text->setWidth(w);
		_textShadow->setWidth(w);
		_panel->setWidth(w);
	}
	//--------------------------------------------------------------------------------
	Real CaptionBar::getHeight() const
	{
		return _panel->getHeight();
	}
	//--------------------------------------------------------------------------------
	void CaptionBar::setHeight(Real h)
	{
		_text->setHeight(h);
		_textShadow->setHeight(h);
		_panel->setHeight(h);
	}
	//--------------------------------------------------------------------------------
	void CaptionBar::setCharHeight(Real h)
	{
		_text->setCharHeight(h);
		_textShadow->setCharHeight(h);
		_dimisionChange = true;
	}
	//--------------------------------------------------------------------------------
	Real CaptionBar::getCharHeight() const
	{
		return _text->getCharHeight();
	}
	//--------------------------------------------------------------------------------
	void CaptionBar::setPosition(Real x, Real y)
	{
		_textShadow->setPosition(x + C_TEXT_MARGIN_LEFT + C_TEXT_SHADOW_OFFSET,
			y + C_TEXT_MARGIN_TOP + C_TEXT_SHADOW_OFFSET);
		_text->setPosition(x + C_TEXT_MARGIN_LEFT, y + C_TEXT_MARGIN_TOP);
		_panel->setPosition(x, y);
	}
	//--------------------------------------------------------------------------------
	Vector2 CaptionBar::getPosition() const
	{
		return _panel->getPosition();
	}
	//--------------------------------------------------------------------------------
	void CaptionBar::addToContainer(OverlayContainer* c)
	{
		MaterialGlyph::addToContainer(c);
		_panel->addToContainer(c);
		c->addChild(_textShadow);
		c->addChild(_text);
	}
	//--------------------------------------------------------------------------------
	void CaptionBar::removeFromContainer()
	{
		_parentContainer->removeChild(_textShadow->getName());
		_parentContainer->removeChild(_text->getName());
		_panel->removeFromContainer();
	}
	//--------------------------------------------------------------------------------
	void CaptionBar::autoUpdateSize()
	{		
		if(OverlayManager::getSingleton().hasViewportChanged())
		{
			forceAutoUpdateSize();
			_dimisionChange = false;
		}
	}
	//--------------------------------------------------------------------------------
	void CaptionBar::forceAutoUpdateSize()
	{
		_panel->setDimisions(_text->getWidth() + C_TEXT_MARGIN_LEFT * 2,
			_text->getCharHeight() + C_TEXT_MARGIN_TOP * 2);
	}
	//--------------------------------------------------------------------------------
	bool CaptionBar::frameStarted(const FrameEvent& evt)
	{
		if(_dimisionChange && _autoSize)
		{
			autoUpdateSize();
		}

		return true;
	}
} // namespace