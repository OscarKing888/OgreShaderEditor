#pragma once
#include <Ogen.h>

namespace Ogen
{
	class MaterialGlobalGpuParameters
	{
	public:
		
		static ColourValue MaterialAmbientColor;
		static String MaterialAmbientColorName;

		static void setMaterialAmbientColor(GpuProgramParametersSharedPtr gpp);
		static void setMaterialAmbientColor(const String& parameterName, GpuProgramParametersSharedPtr gpp);

	};

	//--------------------------------------------------------------------------------

	class ShaderCompileContex
	{
	public:

		static String PSInputParameterName;

		static ushort TextureSamplerStageIndex;

		static Material* CurrentMaterial;
		static Technique* CurrentTechnique;
		static Pass* CurrentPass;

		static void reset();
	};

}