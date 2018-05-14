#include "stdafx.h"
#include "Material_Root.h"
#include "OgreMaterialManager.h"
#include "OgreTechnique.h"
#include "OgrePass.h"
#include "OgreTextureUnitState.h"
#include "OgreResourceGroupManager.h"
#include "Material_Technique.h"
#include "ConnectionLine.h"
#include "MaterialGlobalGpuParameters.h"

namespace Ogen
{
	//--------------------------------------------------------------------------------
	// TechniqueSocket
	//--------------------------------------------------------------------------------
	TechniqueSocket::TechniqueSocket(const String& name, Material_Technique* tech, GlyphBlock* parent)
		: InputOutputSocket(name, true, parent, tech->getSchemeName(), "Technique")
		, _tech(tech)
	{

	}
	//--------------------------------------------------------------------------------
	TechniqueSocket::~TechniqueSocket()
	{

	}
	//--------------------------------------------------------------------------------
	// Material_Root
	//--------------------------------------------------------------------------------
	Material_Root::Material_Root(const String& name)
		: BlockWithView(name)
	{
		setDimisions(140, 130);
		compile();
		setViewMaterial(name);
		setCaption(name);
	}
	//--------------------------------------------------------------------------------
	Material_Root::~Material_Root()
	{
	}
	//--------------------------------------------------------------------------------
	Material_Technique* Material_Root::createTechnique(const String& schemeName)
	{
		size_t idx = _techList.size();
		Material_Technique* t = new Material_Technique(this, /*_name + */"Technique " + 
			StringConverter::toString(idx) + " " + schemeName, schemeName);
		return t;
	}
	//--------------------------------------------------------------------------------
	size_t Material_Root::addTechnique(Material_Technique* tech)
	{
		size_t idx = _techList.size();
		_techList.push_back(tech);
		
		TechniqueSocket* ts = new TechniqueSocket(tech->getName() + "/Socket", tech, this);
		addInputSocket(ts);
		layout();

		ConnectionLine* c = new ConnectionLine(ts, tech->getOutputSocket(0));
		c->addToContainer(_container);

		return idx;
	}
	//--------------------------------------------------------------------------------
	Material_Technique* Material_Root::removeTechnique(size_t idx)
	{
		if(idx < _techList.size())
		{
			Material_Technique* p = _techList[idx];
			_techList.erase(_techList.begin() + idx);
			p->removeFromContainer();
			return p;
		}

		assert(false && "[Material_Root::Material_Root]Technique index out of range!");

		return 0;
	}
	//--------------------------------------------------------------------------------
	MaterialPtr Material_Root::compile()
	{
		MaterialPtr mat = MaterialPtr(MaterialManager::getSingleton().createOrRetrieve(_name,
			ResourceGroupManager::INTERNAL_RESOURCE_GROUP_NAME).first);

		ShaderCompileContex::CurrentMaterial = mat.get();
		//mat->applyDefaults();

		for (size_t i = 0; i < _techList.size(); ++i)
		{
			Material_Technique* tech = _techList[i];
			tech->compile(mat, i);
 		}

		ShaderCompileContex::CurrentMaterial = 0;

		return mat;
	}
}