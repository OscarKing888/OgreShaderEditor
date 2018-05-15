#pragma once
#include "BlockWithView.h"

namespace Ogre
{
	class Material_Pass;
	class Material_Root;

	//--------------------------------------------------------------------------------
	// TechniqueSocket
	//--------------------------------------------------------------------------------
	class PassSocket : public InputOutputSocket
	{
	public:

		PassSocket(const String& name, Material_Pass* pass, GlyphBlock* parent);
		virtual ~PassSocket();

	protected:

		Material_Pass* _pass;
	};

	//--------------------------------------------------------------------------------
	// Material_Technique
	//--------------------------------------------------------------------------------
	class Material_Technique : public BlockWithView
	{
	public:

		Material_Technique(Material_Root* parent, const String& name, const String& schemeName);
		virtual ~Material_Technique();

		Material_Pass* createPass();
		size_t addPass(Material_Pass* pass);
		Material_Pass* removePass(size_t idx);

		void compile(MaterialPtr mat, size_t techIndex);

		const String& getSchemeName() const { return _schemeName; }

	protected:

		typedef std::vector<Material_Pass*> PassList;
		PassList _passList;

		String _schemeName;

		Material_Root* _parent;
	};
}