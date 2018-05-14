/*
-----------------------------------------------------------------------------
This source file is part of OGRE
    (Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2006 Torus Knot Software Ltd
Also see acknowledgements in Readme.html

You may use this sample code for anything you like, it is not covered by the
LGPL like the rest of the engine.
-----------------------------------------------------------------------------
*/

/**
    \file 
        Lighting.cpp
    \brief
        Shows lighting support in OGRE.
*/
#include "stdafx.h"
#include "MaterialEditor.h"

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#include <ObjBase.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

namespace MaterialEditor
{

	ArrowOverlayElement* _arrow;
	MaterialPtr _material;

	 
	SceneNode* mRedYellowLightsNode;
	SceneNode* mGreenBlueLightsNode;
	std::vector<AnimationState*> mAnimStateList;

	GlyphBlock* _blk1 = 0;
	Vector2 _blk1pos(700, 100);

// 
// #if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
// INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
// #else
// int main(int argc, char **argv)
// #endif
// {
// 	//CoInitializeEx(NULL, COINIT_MULTITHREADED);
//     // Create application object
//     MaterialEditorApplication app;
// 
//     //try {
//         app.go();
//    // } catch( Ogre::Exception& e ) {
// #if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
//        // MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
// #else
//        // std::cerr << "An exception has occured: " << e.getFullDescription();
// #endif
//     //}
// 
// 	//CoUninitialize();
//     return 0;
// }
}

#ifdef __cplusplus
}
#endif

