#include "stdafx.h"
#include "Material_Technique.h"
#include "Material_Pass.h"
#include "Material_Root.h"
#include "OgreTechnique.h"
#include "ConnectionLine.h"
#include "MaterialGlobalGpuParameters.h"

namespace Ogen
{
	//--------------------------------------------------------------------------------
	// TechniqueSocket
	//--------------------------------------------------------------------------------
	PassSocket::PassSocket(const String& name, Material_Pass* pass, GlyphBlock* parent)
		: InputOutputSocket(name, true, parent, "", "Pass")
		, _pass(pass)
	{

	}
	//--------------------------------------------------------------------------------
	PassSocket::~PassSocket()
	{

	}
	//--------------------------------------------------------------------------------
	// Material_Technique
	//--------------------------------------------------------------------------------
	Material_Technique::Material_Technique(Material_Root* parent, const String& name, const String& schemeName)
		: BlockWithView(name)
		, _parent(parent)
		, _schemeName(schemeName)
	{
		addOutputSocket(new InputOutputSocket(name + "/Output", false, this, "", "float4"));

		setDimisions(140, 130);
		setViewFillColour(ColourValue::Black);
		setCaption(name);
	}
	//--------------------------------------------------------------------------------
	Material_Technique::~Material_Technique()
	{
	}
	//--------------------------------------------------------------------------------
	size_t Material_Technique::addPass(Material_Pass* pass)
	{
		size_t idx = _passList.size();
		_passList.push_back(pass);
		//pass->addToContainer(_container);

		PassSocket* ts = new PassSocket(pass->getName() + "/Socket", pass, this);
		addInputSocket(ts);
		layout();

		ConnectionLine* c = new ConnectionLine(ts, pass->getOutputSocket(0));
		c->addToContainer(_container);

		return idx;
	}
	//--------------------------------------------------------------------------------
	Material_Pass* Material_Technique::removePass(size_t idx)
	{
		if(idx < _passList.size())
		{
			Material_Pass* p = _passList[idx];
			_passList.erase(_passList.begin() + idx);
			//p->removeFromContainer();
			return p;
		}

		assert(false && "[Material_Technique::removePass]Pass index out of range!");

		return 0;
	}
	//--------------------------------------------------------------------------------
	Material_Pass* Material_Technique::createPass()
	{
		size_t idx = _passList.size();
		Material_Pass* pass = new Material_Pass(this,/* _name + */"Pass " + 
			StringConverter::toString(idx));
		return pass;
	}
	//--------------------------------------------------------------------------------
	void Material_Technique::compile(MaterialPtr mat, size_t techIndex)
	{
		if(techIndex >= mat->getNumTechniques())
		{
			mat->createTechnique();
		}

		Technique* t = mat->getTechnique((unsigned short)techIndex);
		t->setSchemeName(_schemeName);

		ShaderCompileContex::CurrentTechnique = t;

		for (size_t i = 0; i < _passList.size(); ++i)
		{
			Material_Pass* pass = _passList[i];
			pass->compile(mat, t, i);
		}

		ShaderCompileContex::CurrentTechnique = 0;
	}
}