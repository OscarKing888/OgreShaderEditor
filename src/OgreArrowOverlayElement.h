#pragma once
#include "OgreOverlayElement.h"
#include "OgreOverlayElementFactory.h"

namespace Ogre
{
	typedef std::vector<Vector2> Vector2List;

	class ArrowOverlayElement : public OverlayElement
	{
	public:


		ArrowOverlayElement(const String& name);
		virtual ~ArrowOverlayElement(void);

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

		void setStartPoint(Real x, Real y);
		void setStartPoint(const Vector2& pt);
		const Vector2& getStartPoint() const{ return mStartPoint; }

		void setEndPoint(Real x, Real y);
		void setEndPoint(const Vector2& pt);
		const Vector2& getEndPoint() const{ return mEndPoint; }

		void setWidthRatio(Real r);
		Real getWidthRatio() const { return mArrowWidthRatio; }

	protected:

		Vector2 mStartPoint;
		Vector2 mEndPoint;

		// arrowWidth = distance(end - start) * mArrowWidthRatio
		Real mArrowWidthRatio;

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
	class /*_OgreExport*/ ArrowOverlayElementFactory: public OverlayElementFactory
	{
	public:
		/** See OverlayElementFactory */
		OverlayElement* createOverlayElement(const String& instanceName)
		{
			return new ArrowOverlayElement(instanceName);
		}
		/** See OverlayElementFactory */
		const String& getTypeName(void) const
		{
			static String name = "Arrow";
			return name;
		}
	};

}