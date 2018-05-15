#pragma once
#include "MaterialGlyph.h"
#include "PanelGlyph.h"
#include "IMaterialExpression.h"

namespace Ogre
{
	class CaptionBar;
	class GlyphBlock;
	class ConnectionLine;

	typedef std::vector<ConnectionLine*> ConnectionLineList;

	class InputOutputSocket : public PanelGlyph, public IExpressionParameter
	{
	public:

		InputOutputSocket(const String& name, bool isInputSocket, GlyphBlock* parent,
			const DisplayString& displayString, const String& parameterType, const String& components = "");
		virtual ~InputOutputSocket();

		bool isInputSocket() const { return _isInputSocket; }
		GlyphBlock* getParent() const { return _parent; }

		virtual IMaterialExpression* getParentExpression() const;

		const ConnectionLineList& getConnectionLineList() const;
		void addConnectionLine(ConnectionLine* connectionLine);
		void removeConnectionLine(ConnectionLine* connectionLine);
		bool isConnected() const;

		RealRect getWorldBoundingRect() const;

		virtual void addToContainer(OverlayContainer* c);
		virtual void removeFromContainer();

		virtual void setPosition(Real x, Real y);

		virtual const String& getParameterType() const;
		void setParameterType(const String& tp) { _parameterType = tp; }

		
		virtual const String& getComponents() const;

		void updatePosition();

		virtual size_t getConnectionLineCount() const;
		virtual IExpressionParameterConnectionLine* getConnectionLine(size_t idx) const;

	protected:

		String _parameterType;
		String _components;

		GlyphBlock* _parent;
		bool _isInputSocket;
		TextAreaOverlayElement* _label;
		TextAreaOverlayElement* _labelShadow;

		ConnectionLineList _connectionLineList;
	};
	
	//--------------------------------------------------------------------------------

	class GlyphBlock : public MaterialGlyph
	{
	public:

		GlyphBlock(const String& name);
		virtual ~GlyphBlock();

		virtual void setDimisions(Real w, Real h);

		virtual Real getWidth() const;
		virtual void setWidth(Real w);

		virtual Real getHeight() const;
		virtual void setHeight(Real h);

		virtual void setPosition(Real x, Real y);
		virtual Vector2 getPosition() const;


		void setCaption(const DisplayString& cap);
		const DisplayString& getCaption() const;

		void addInputSocket(InputOutputSocket* inputSocket);
		void removeInputSocket(const String& name);

		void addOutputSocket(InputOutputSocket* outputSocket);
		void removeOutputSocket(const String& name);

		InputOutputSocket* getInputSocket(size_t idx) const;
		InputOutputSocket* getOutputSocket(size_t idx) const;

		size_t getInputSocketCount() const;
		size_t getOutputSocketCount() const;

		RealRect getClientRect() const;

		virtual void layout();

		virtual String compileCode() const;

		PanelOverlayElement* getRootContainer() const { return _container; }

	protected:
		
		PanelOverlayElement* _container;
		CaptionBar* _caption;
		PanelGlyph* _panel;

		typedef std::vector<InputOutputSocket*> InputOutputSocketList;
		InputOutputSocketList _inputSocketList;
		InputOutputSocketList _outputSocketList;

		virtual void addToContainer(OverlayContainer* c);
		virtual void removeFromContainer();
	};
}