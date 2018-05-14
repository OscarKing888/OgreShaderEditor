#pragma once
#include "MaterialGlyph.h"

namespace Ogen
{
	class PanelGlyph : public MaterialGlyph
	{
	public:

		PanelGlyph(const String& name);
		virtual ~PanelGlyph();

		void setBorderWidth(Real w);
		Real getBorderWidth() const;

		void setBorderColour(const ColourValue& clr);
		const ColourValue& getBorderColour() const;

		void setFillColour(const ColourValue& clr);
		const ColourValue& getFillColour() const;

		void setColour(const ColourValue& clr);

		virtual void setDimisions(Real w, Real h);

		virtual Real getWidth() const;
		virtual void setWidth(Real w);

		virtual Real getHeight() const;
		virtual void setHeight(Real h);

		virtual void setPosition(Real x, Real y);
		virtual Vector2 getPosition() const;

		void setFillMaterialName(const String& matName);
		const String& getFillMaterialName() const;

		void setBorderMaterialName(const String& matName);
		const String& getBorderMaterialName() const;

		virtual void addToContainer(OverlayContainer* c);
		virtual void removeFromContainer();

	protected:

		BorderPanelOverlayElement* _borderPanel;
		MaterialPtr _fillMaterial;
		MaterialPtr _borderMaterial;
		ColourValue _fillColor;
		ColourValue _borderColor;
	};
}