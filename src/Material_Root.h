#pragma once
#include "BlockWithView.h"

namespace Ogre
{
	class Material_Technique;

	//--------------------------------------------------------------------------------
	// TechniqueSocket
	//--------------------------------------------------------------------------------
	class TechniqueSocket : public InputOutputSocket
	{
	public:

		TechniqueSocket(const String& name, Material_Technique* tech, GlyphBlock* parent);
		virtual ~TechniqueSocket();

	protected:

		Material_Technique* _tech;
	};

	//--------------------------------------------------------------------------------
	// Material_Root
	//--------------------------------------------------------------------------------
	class Material_Root : public BlockWithView
	{
	public:

		Material_Root(const String& name);
		virtual ~Material_Root();

		Material_Technique* createTechnique(const String& schemeName = "");
		size_t addTechnique(Material_Technique* tech);
		Material_Technique* removeTechnique(size_t idx);

		MaterialPtr compile();

	protected:

		typedef std::vector<Material_Technique*> TechList;
		TechList _techList;
	};
}