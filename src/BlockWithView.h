#pragma once
#include "GlyphBlock.h"

namespace Ogre
{
	class BlockWithView : public GlyphBlock
	{
	public:

		BlockWithView(const String& name);
		virtual ~BlockWithView();

		virtual void addToContainer(OverlayContainer* c);
		virtual void removeFromContainer();

		void setViewFillColour(const ColourValue& clr);
		void setTextureName(const String& texName);
		const String& getTextureName() const { return _textureName; }

		void setViewMaterial(MaterialPtr mat);
		void setViewMaterial(const String& matName);

		Pass* getViewMaterialPass() const;

		virtual void layout();

	protected:

		String _textureName;
		MaterialPtr _viewMaterial;
		PanelOverlayElement* _viewPanel;
	};
}