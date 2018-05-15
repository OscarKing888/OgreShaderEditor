#include "stdafx.h"
#include "Material_Pass.h"
#include "OgreMaterialManager.h"
#include "OgreTechnique.h"
#include "OgrePass.h"
#include "OgreTextureUnitState.h"
#include "OgreGpuProgram.h"
#include "OgreHighLevelGpuProgramManager.h"
#include "MaterialGlobalGpuParameters.h"

namespace Ogre
{
	Material_Pass::Material_Pass(Material_Technique* parent, const String& name)
		: BlockWithView(name)
		, _parent(parent)
	{
		addInputSocket(new InputOutputSocket(name + "/Diffuse", true, this, "Diffuse", "float4"));
		//addInputSocket(new InputOutputSocket(name + "/Emissive", true, this, "Emissive", "float4"));
		//addInputSocket(new InputOutputSocket(name + "/Specular", true, this, "Specular", "float4"));
		//addInputSocket(new InputOutputSocket(name + "/SpecularPower", true, this, "Sp.Power", "float4"));
	
		addOutputSocket(new InputOutputSocket(name + "/Output", false, this, "", "float4"));

		setDimisions(140, 130);
		setViewFillColour(ColourValue::Black);
		setCaption(name);
	}
	//--------------------------------------------------------------------------------
	Material_Pass::~Material_Pass()
	{
	}
	//--------------------------------------------------------------------------------
	void Material_Pass::compile(MaterialPtr mat, Technique* tech, size_t passIdx)
	{
		ShaderCompileContex::reset();

		if(passIdx >= tech->getNumPasses())
		{
			tech->createPass();
		}

		Pass* pass = tech->getPass((unsigned short)passIdx);

		ShaderCompileContex::CurrentPass = pass;

		HighLevelGpuProgramPtr gpuProg = ShaderUtil::createOrGetPS(_name);
		
		ShaderCompileContex::CurrentPS = gpuProg.get();
		//GpuProgramManager::getSingleton().getSupportedSyntax()

		// generate shader code(HLSL only current)

		// reset the texture unit stage index
		ShaderCompileContex::TextureSamplerStageIndex = 0;

		String hlslCode;

		IExpressionParameter* diffuseInput = getInputSocket(0);
		compilePSDeclaration(diffuseInput, hlslCode);
		
		hlslCode += "//--------------------------------------------------------------------------------\n\n";

		hlslCode += String("struct PS_INPUT\n{\n");
		StrMap structMap;
		compilePSInputStruct(diffuseInput, structMap);
		for (StrMap::const_iterator it = structMap.begin();
			it != structMap.end(); ++it)
		{
			hlslCode += formatString("\tfloat4 %s : %s;\n", it->second.c_str(), it->first.c_str());
		}

		hlslCode += String("};\n");

		hlslCode += "//--------------------------------------------------------------------------------\n\n";

		compilePSCode(diffuseInput, hlslCode);


#if 0
		hlslCode += String("uniform float timeVal;")
			+ "float4 ps_main_2_0() : COLOR\n"
			+ "{\n"
			+ "		return float4(cos(timeVal), 1, sin(timeVal), 1);\n"
			+ "}\n";
#else
		//hlslCode += String("uniform float timeVal;\n");

		String psCall;
		compilePSCall(diffuseInput, psCall);
		hlslCode += String("float4 diffuse(PS_INPUT ")
					+ ShaderCompileContex::PSInputParameterName
					+ ")\n"
					+ "{\n"
					+ "\treturn "
					+ psCall
					+ ";\n"
					+ "}\n\n";

		hlslCode += "//--------------------------------------------------------------------------------\n\n";

		hlslCode += String("float4 ps_2_0(PS_INPUT ")
					+ ShaderCompileContex::PSInputParameterName
					+ ") : COLOR\n"
					+ "{\n"
					+ "\treturn diffuse("
					+ ShaderCompileContex::PSInputParameterName
					+ ");\n"
					+ "}\n";
#endif

		LogManager::getSingleton().logMessage("----HLSL-------------------------------\n");
		LogManager::getSingleton().logMessage(hlslCode);
		LogManager::getSingleton().logMessage("---------------------------------------\n");

		gpuProg->setSource(hlslCode);

		gpuProg->load();


		//gpuProg->getNamedConstants()->generateConstantDefinitionArrayEntries()
		//GpuProgramParametersSharedPtr gps = pass->getFragmentProgramParameters();
		GpuProgramParametersSharedPtr gps = gpuProg->getDefaultParameters();
		//GpuProgramParameters::AutoConstantDefinition* acd = gps->getAutoConstantDefinition("time");
		
		//gpuProg->getConstantDefinitions()->generateConstantDefinitionArrayEntries("time", GpuConstantDefinition);
		//gps->setAutoConstant(0, GpuProgramParameters::ACT_TIME);
		//gps->setNamedAutoConstant("timeVal", GpuProgramParameters::ACT_TIME, 1);
		//gps->setNamedConstantFromTime("timeVal", 1);
		gpuProg->getNamedConstants().save("test.txt");
		
		diffuseInput->getConnectionLine(0)->getOutputParameter()->getParentExpression()->postCompile();

		//::Sleep(3000);
		//gps->setNamedAutoConstantReal("timeVal", GpuProgramParameters::ACT_TIME, 1);
		pass->setFragmentProgram(_name);

		ShaderCompileContex::CurrentPass = 0;
	}
	//--------------------------------------------------------------------------------
	void Material_Pass::compilePSInputStruct(IExpressionParameter* root, StrMap& structMap)
	{
		if(root->getConnectionLineCount() == 0)
		{
			return;
		}
		else
		{
			IExpressionParameterConnectionLine* l = root->getConnectionLine(0);
			IExpressionParameter* output = l->getOutputParameter();
			IMaterialExpression* me = output->getParentExpression();

			// pre-order traversal
			size_t inCount = me->getInputParametersCount();
			for (size_t i = 0; i < inCount; ++i)
			{
				IExpressionParameter* ep = me->getInputParameter(i);
				compilePSInputStruct(ep, structMap);
			}

			me->compileInputStruct(structMap);
		}
	}
	//--------------------------------------------------------------------------------
	void Material_Pass::compilePSDeclaration(IExpressionParameter* root, String& outCode)
	{
		// if is the end leaf parameter
		if(root->getConnectionLineCount() == 0)
		{
			return;
		}
		else
		{
			IExpressionParameterConnectionLine* l = root->getConnectionLine(0);
			IExpressionParameter* output = l->getOutputParameter();
			IMaterialExpression* me = output->getParentExpression();

			// pre-order traversal
			size_t inCount = me->getInputParametersCount();
			for (size_t i = 0; i < inCount; ++i)
			{
				IExpressionParameter* ep = me->getInputParameter(i);
				compilePSDeclaration(ep, outCode);
			}

			me->startCompileExpressionDeclaration();
			me->compileExpressionDeclaration(outCode);
			me->endCompileExpressionDeclaration();
			
			outCode += "\n";
			//outCode += "\n//--------------------------------------------------------------------------------\n";
		}
	}
	//--------------------------------------------------------------------------------
	void Material_Pass::compilePSCode(IExpressionParameter* root, String& outCode)
	{
		// if is the end leaf parameter
		if(root->getConnectionLineCount() == 0)
		{
			return;
		}
		else
		{
			IExpressionParameterConnectionLine* l = root->getConnectionLine(0);
			IExpressionParameter* output = l->getOutputParameter();
			IMaterialExpression* me = output->getParentExpression();

			// pre-order traversal
			size_t inCount = me->getInputParametersCount();
			for (size_t i = 0; i < inCount; ++i)
			{
				IExpressionParameter* ep = me->getInputParameter(i);
				compilePSCode(ep, outCode);
			}

			me->compileExpression(outCode, output);

			outCode += "\n";
			//outCode += "\n//--------------------------------------------------------------------------------\n";
		}
	}
	//--------------------------------------------------------------------------------
	void Material_Pass::compilePSCall(IExpressionParameter* root, String& outCode)
	{
		// if is the end leaf parameter
		if(root->getConnectionLineCount() == 0)
		{
			return;
		}
		else
		{
			IExpressionParameterConnectionLine* l = root->getConnectionLine(0);
			IExpressionParameter* output = l->getOutputParameter();
			IMaterialExpression* me = output->getParentExpression();

			outCode += me->compileExpressionCallStart(output);
			outCode += me->compileExpressionCallArguments(output);

// 			// pre-order traversal
// 			size_t inCount = me->getInputParametersCount();
// 			for (size_t i = 0; i < inCount; ++i)
// 			{
// 				IExpressionParameter* ep = me->getInputParameter(i);
// 				compilePSCall(ep, outCode);
// 			}

			outCode += me->compileExpressionCallEnd(output);
		}
	}

}