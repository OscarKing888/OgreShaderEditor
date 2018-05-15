#pragma once
#include "MaterialGlyph.h"
#include "OgreFrameListener.h"

namespace Ogre
{
	class PanelGlyph;

	class CaptionBar : public MaterialGlyph, public FrameListener
	{
	public:

		CaptionBar(const String& name, const DisplayString& caption = "");
		virtual ~CaptionBar(void);

		void setCaption(const DisplayString& caption);
		const DisplayString& getCaption() const;

		void setTextColour(const ColourValue& clr);
		const ColourValue& getTextColour() const;

		void setFontName(const String& name);
		const String& getFontName() const;

		void setCharHeight(Real h);
		Real getCharHeight() const;

		void setAutoUpdateSize(bool on) { _autoSize = on; }
		bool getAutoUpdateSize() const { return _autoSize; }
		void forceAutoUpdateSize();

		virtual void setDimisions(Real w, Real h);
		virtual Real getWidth() const;
		virtual void setWidth(Real w);

		virtual Real getHeight() const;
		virtual void setHeight(Real h);

		virtual void setPosition(Real x, Real y);
		virtual Vector2 getPosition() const;

		virtual void addToContainer(OverlayContainer* c);
		virtual void removeFromContainer();

	protected:

		TextAreaOverlayElement* _text;
		TextAreaOverlayElement* _textShadow;
		PanelGlyph* _panel;
		bool _autoSize;
		bool _dimisionChange;

		void autoUpdateSize();
		virtual bool frameStarted(const FrameEvent& evt);
	};

}