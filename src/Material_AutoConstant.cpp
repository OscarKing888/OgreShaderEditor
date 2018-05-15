#include "stdafx.h"
#include "Material_AutoConstant.h"
#include "OgreGpuProgram.h"
#include "MaterialGlobalGpuParameters.h"

namespace Ogre
{
	Material_AutoConstant::Material_AutoConstant(const String& name)
		: MaterialExpression(name, true)
	{

		addOutputSocket(new InputOutputSocket(name + "/Out", false, this, "", "float"));
	
		setDimisions(140, 130);
		
		_gpuProg = ShaderUtil::createOrGetPS(_name);

		setAutoConstantName("sintime_0_x");
	}
	//--------------------------------------------------------------------------------
	Material_AutoConstant::~Material_AutoConstant()
	{
	}
	//--------------------------------------------------------------------------------
	void Material_AutoConstant::setAutoConstantName(const String& name)
	{
		_constantName = name;

		//setCaption(String("Auto Constant: ") + name);
		setCaption(name);

		const GpuProgramParameters::AutoConstantDefinition* ad =
			GpuProgramParameters::getAutoConstantDefinition(name);

		String tp = "float";

		if((ad->elementCount > 0) && (ad->elementCount <= 4))
		{
			//tp = tp + StringConverter::toString(ad->elementCount);
		}
		else
		{
			//tp = tp + "4x" + StringConverter::toString(ad->elementCount / 4);
		}

		setupViewPS(ad);
		
		getOutputSocket(0)->setParameterType(tp);
	}
	//--------------------------------------------------------------------------------
	void Material_AutoConstant::setupViewPS(const GpuProgramParameters::AutoConstantDefinition* acd)
	{
		switch(acd->elementCount)
		{
		case 1:
			{
				String hlslCode = "uniform float " + acd->name + ";\n";
				hlslCode += "float4 ps_2_0() : COLOR \n {\n return (";
				hlslCode += acd->name;
				hlslCode += "); \n}\n";

				setupViewPSCode(acd, hlslCode);
			}
			break;

		case 4:
			{
				String hlslCode = "uniform float4 " + acd->name + ";\n";
				hlslCode += "float4 ps_2_0() : COLOR \n {\n return (";
				hlslCode += acd->name;
				hlslCode += "); \n}\n";

				setupViewPSCode(acd, hlslCode);
			}
			break;

		default:
			{
				String hlslCode = "float4 ps_2_0() : COLOR { return 0; }";
				setupViewPSCode(acd, hlslCode);
			}
			break;
		}

	}
	//--------------------------------------------------------------------------------
	void Material_AutoConstant::setupViewPSCode(
		const GpuProgramParameters::AutoConstantDefinition* acd, const String& hlslCode)
	{
		_gpuProg->unload();
		_gpuProg->setSource(hlslCode);
		_gpuProg->load();

		GpuProgramParametersSharedPtr gps = _gpuProg->getDefaultParameters();
		//GpuProgramParametersSharedPtr gps = getViewMaterialPass()->getFragmentProgramParameters();
		gps->setNamedAutoConstantReal(acd->name, acd->acType, 1);

		getViewMaterialPass()->setFragmentProgram(_gpuProg->getName());
	}
	//--------------------------------------------------------------------------------
	void Material_AutoConstant::compileExpressionDeclarationImp(String& outCode)
	{
		outCode += formatString("uniform %s %s;\n",
			getOutputParameter(0)->getParameterType().c_str(),
			_constantName.c_str());
	}
	//--------------------------------------------------------------------------------
	String Material_AutoConstant::compileExpressionCallStart(IExpressionParameter* output) const
	{
		return "(";
	}
	//--------------------------------------------------------------------------------
	String Material_AutoConstant::compileExpressionCallArguments(IExpressionParameter* output) const
	{
		return _constantName;
	}
	//--------------------------------------------------------------------------------
	String Material_AutoConstant::compileExpressionCallEnd(IExpressionParameter* output) const
	{
		return ").r";
	}
	//--------------------------------------------------------------------------------
	void Material_AutoConstant::postCompile()
	{
		MaterialExpression::postCompile();

		const GpuProgramParameters::AutoConstantDefinition* acd =
			GpuProgramParameters::getAutoConstantDefinition(_constantName);

		ShaderCompileContex::CurrentPS->getDefaultParameters()->setNamedAutoConstantReal(
			acd->name, acd->acType, 1);
	}
}
