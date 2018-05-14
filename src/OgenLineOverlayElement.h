#pragma once
#include "OgreOverlayElement.h"
#include "OgreOverlayElementFactory.h"

namespace Ogen
{
	typedef std::vector<Vector2> Vector2List;

	class LineOverlayElement : public OverlayElement
	{
	public:


		LineOverlayElement(const String& name);
		virtual ~LineOverlayElement(void);

		virtual void initialise(void);

		/** See OverlayElement. */
		virtual const String& getTypeName(void) const;
		/** See Renderable. */
		void getRenderOperation(RenderOperation& op);

		/** Sets the colour of the text. 
		@remarks
		This method establishes a constant colour for 
		the entire text. Also see setColourBottom and 
		setColourTop which allow you to set a colour gradient.
		*/
		void setColour(const ColourValue& col);

		/** Gets the colour of the text. */
		const ColourValue& getColour(void) const;

		/** Overridden from OverlayElement */
		void _update(void);

		void setPoints(const Vector2List& lst);
		const Vector2List& getPoints() const{ return mPoints; }

	protected:

		Vector2List mPoints;

		/// Render operation
		RenderOperation mRenderOp;

		/// Colours to use for the vertices
		ColourValue mColour;
		bool mColoursChanged;
		size_t mAllocSize;

		static String msTypeName;

		/// Method for setting up base parameters for this class
		void addBaseParameters(void);


		/// Internal method to allocate memory, only reallocates when necessary
		void checkMemoryAllocation( size_t numChars );

		/// Updates vertex colours
		virtual void updateColours(void);

		/// Inherited function
		virtual void updatePositionGeometry();

		/// Inherited function
		virtual void updateTextureGeometry();

	};

	//--------------------------------------------------------------------------------

	/** Factory for creating BorderPanelOverlayElement instances. */
	class /*_OgreExport*/ LineOverlayElementFactory: public OverlayElementFactory
	{
	public:
		/** See OverlayElementFactory */
		OverlayElement* createOverlayElement(const String& instanceName)
		{
			return new LineOverlayElement(instanceName);
		}
		/** See OverlayElementFactory */
		const String& getTypeName(void) const
		{
			static String name = "Line";
			return name;
		}
	};

}