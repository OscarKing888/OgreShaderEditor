#pragma once
#include "MaterialGlyph.h"
#include "IMaterialExpression.h"

namespace Ogre
{
	class InputOutputSocket;
	class LineOverlayElement;
	class ArrowOverlayElement;

	class ConnectionLine : public MaterialGlyph, public IExpressionParameterConnectionLine
	{
	public:

		ConnectionLine(InputOutputSocket* inputSocket, InputOutputSocket* outputSocket);
		virtual ~ConnectionLine();

		InputOutputSocket* getInputSocket() const;
		InputOutputSocket* getOutputSocket() const;

		virtual void addToContainer(OverlayContainer* c);
		virtual void removeFromContainer();

		virtual bool intersects(Real x, Real y) const;

		virtual void setDimisions(Real w, Real h);

		virtual Real getWidth() const;
		virtual void setWidth(Real w);

		virtual Real getHeight() const;
		virtual void setHeight(Real h);

		virtual void setPosition(Real x, Real y);
		virtual Vector2 getPosition() const;

		void updatePosition();

		const String& getParameterType() const;

		virtual IExpressionParameter* getInputParameter() const;
		virtual IExpressionParameter* getOutputParameter() const;

	protected:

		InputOutputSocket* _input;
		InputOutputSocket* _output;
		LineOverlayElement* _line;
		ArrowOverlayElement* _arrow;
	};
}