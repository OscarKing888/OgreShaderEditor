#include "stdafx.h"
#include "Material_TextureSampler.h"
#include "MaterialGlobalGpuParameters.h"

namespace Ogen
{
	Material_TextureSampler::Material_TextureSampler(const String& name)
		: MaterialExpression(name, true)
		, _texturerStageIndex(0)
		, _texCoordIndex(0)
	{
		addInputSocket(new InputOutputSocket(name + "/UV", true, this, "UV", "float2"));		

		addOutputSocket(new InputOutputSocket(name + "/Color", false, this, "C", "float4", ""));
		addOutputSocket(new InputOutputSocket(name + "/R", false, this, "R", "float", ".r"));
		addOutputSocket(new InputOutputSocket(name + "/G", false, this, "G", "float", ".g"));
		addOutputSocket(new InputOutputSocket(name + "/B", false, this, "B", "float", ".b"));
		addOutputSocket(new InputOutputSocket(name + "/A", false, this, "A", "float", ".a"));

		getOutputSocket(1)->setColour(ColourValue::Red);
		getOutputSocket(2)->setColour(ColourValue::Green);
		getOutputSocket(3)->setColour(ColourValue::Blue);
		getOutputSocket(4)->setColour(ColourValue::White);

		setDimisions(180, 130);
		setCaption("Texture Sample");
	}
	//--------------------------------------------------------------------------------
	Material_TextureSampler::~Material_TextureSampler()
	{
	}
	//--------------------------------------------------------------------------------
	void Material_TextureSampler::compileExpressionDeclarationImp(String& outCode)
	{
		_texturerStageIndex = ShaderCompileContex::TextureSamplerStageIndex;
		
		// TODO: sampler3D
		outCode += formatString("sampler2D %s : register(s%d);\n", getVarName().c_str(), _texturerStageIndex);

		++ShaderCompileContex::TextureSamplerStageIndex;
	}
	//--------------------------------------------------------------------------------
	void Material_TextureSampler::compileExpression(String& outCode, IExpressionParameter* outputParameter)
	{
		outCode += formatString("%s %s(PS_INPUT input)\n",
			outputParameter->getParameterType().c_str(),
			getFunctionName().c_str());

		outCode += formatString("{\n\t return tex2D(%s, input.%s)%s; \n}\n",
			getVarName().c_str(),
			getUVName().c_str(),
			outputParameter->getComponents().c_str());

		if(_texturerStageIndex >= ShaderCompileContex::CurrentPass->getNumTextureUnitStates())
		{
			ShaderCompileContex::CurrentPass->createTextureUnitState(_textureName, _texCoordIndex);
		}
	}
	//--------------------------------------------------------------------------------
	String Material_TextureSampler::getVarName() const
	{
		return formatString("autoTextureSampler%d", _texturerStageIndex);
	}
	//--------------------------------------------------------------------------------
	void Material_TextureSampler::compileInputStruct(StrMap& outMap)
	{
		outMap.insert(std::make_pair(formatString("TEXCOORD%d", _texCoordIndex), getUVName()));
	}
	//--------------------------------------------------------------------------------
	String Material_TextureSampler::getUVName() const
	{
		return formatString("uv%d", _texCoordIndex);
	}
	//--------------------------------------------------------------------------------
	String Material_TextureSampler::getFunctionName() const
	{
		return formatString("get_%s", getVarName().c_str());
	}
	//--------------------------------------------------------------------------------
	String Material_TextureSampler::compileExpressionCallStart() const
	{
		return getFunctionName() + "(";
	}
	//--------------------------------------------------------------------------------
	String Material_TextureSampler::compileExpressionCallArguments() const
	{
		return ShaderCompileContex::PSInputParameterName;
	}
	//--------------------------------------------------------------------------------
	String Material_TextureSampler::compileExpressionCallEnd() const
	{
		return ")";
	}
	//--------------------------------------------------------------------------------
}