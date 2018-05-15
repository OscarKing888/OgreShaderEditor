#pragma once
#include "OgreBorderPanelOverlayElement.h"
#include "OgreTextAreaOverlayElement.h"
#include "OgreOverlay.h"
#include "OgreOverlayManager.h"

// Pixels
#define C_TEXT_MARGIN_LEFT 4
#define C_TEXT_MARGIN_TOP 4
#define C_CHAR_HEIGHT 16
#define C_ELEMENT_SPACING 2
#define C_TEXT_SHADOW_OFFSET 1

#define C_DEFAULT_FONT_NAME "MaterialGlyphyFont"



namespace Ogre
{
	class MaterialGlyph
	{
	public:

		MaterialGlyph(const String& name);
		virtual ~MaterialGlyph();

		const String& getName() const { return _name; }
		void setName(const String& name);

		virtual bool intersects(Real x, Real y) const;

		virtual void setDimisions(Real w, Real h) = 0;
		virtual Vector2 getDimisions() const;
		virtual RealRect getBoundingRect() const;

		virtual Real getWidth() const = 0;
		virtual void setWidth(Real w) = 0;

		virtual Real getHeight() const = 0;
		virtual void setHeight(Real h) = 0;

		virtual void setPosition(Real x, Real y) = 0;
		virtual void setPosition(const Vector2& pos);
		virtual Vector2 getPosition() const = 0;

		virtual void addToContainer(OverlayContainer* c);
		virtual void removeFromContainer() = 0;

		virtual void layout();

	protected:

		String _name;
		OverlayContainer* _parentContainer;
	};
}