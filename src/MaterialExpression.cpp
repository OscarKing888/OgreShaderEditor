#include "stdafx.h"
#include "MaterialExpression.h"

namespace Ogen
{
	MaterialExpression::MaterialExpression(const String& name, bool needDeclaration)
		: BlockWithView(name)
		, _needDeclaration(needDeclaration)
		, _compileDeclarationOnce(false)
	{

	}
	//--------------------------------------------------------------------------------
	MaterialExpression::~MaterialExpression()
	{

	}
	//--------------------------------------------------------------------------------
	void MaterialExpression::startCompileExpressionDeclaration()
	{
		_compileDeclarationOnce = false;
	}
	//--------------------------------------------------------------------------------
	void MaterialExpression::compileExpressionDeclaration(String& outCode)
	{
		if(_needDeclaration)
		{
			if(!_compileDeclarationOnce)
			{
				_compileDeclarationOnce = true;
				compileExpressionDeclarationImp(outCode);
			}
		}
	}
	//--------------------------------------------------------------------------------
	void MaterialExpression::endCompileExpressionDeclaration()
	{
		_compileDeclarationOnce = false;
	}
	//--------------------------------------------------------------------------------
	void MaterialExpression::compileExpression(String& outCode, IExpressionParameter* outputParameter)
	{

	}
	//--------------------------------------------------------------------------------
	void MaterialExpression::compileExpressionDeclarationImp(String& outCode)
	{

	}
	//--------------------------------------------------------------------------------
	size_t MaterialExpression::getInputParametersCount() const
	{
		return _inputSocketList.size();
	}
	//--------------------------------------------------------------------------------
	size_t MaterialExpression::getOutputParametersCount() const
	{
		return _outputSocketList.size();
	}
	//--------------------------------------------------------------------------------
	IExpressionParameter* MaterialExpression::getInputParameter(size_t idx) const
	{
		return getInputSocket(idx);
	}
	//--------------------------------------------------------------------------------
	IExpressionParameter* MaterialExpression::getOutputParameter(size_t idx) const
	{
		return getOutputSocket(idx);
	}
	//--------------------------------------------------------------------------------
	void MaterialExpression::compileInputStruct(StrMap& outMap)
	{

	}
	//--------------------------------------------------------------------------------
	String MaterialExpression::compileExpressionCallStart() const
	{
		return "";
	}
	//--------------------------------------------------------------------------------
	String MaterialExpression::compileExpressionCallArguments() const
	{
		return "";
	}
	//--------------------------------------------------------------------------------
	String MaterialExpression::compileExpressionCallEnd() const
	{
		return "";
	}
	//--------------------------------------------------------------------------------	
}