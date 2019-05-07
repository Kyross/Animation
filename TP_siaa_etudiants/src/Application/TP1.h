#ifndef _Application_TP1_H
#define _Application_TP1_H

#include <Application/Base.h>
#include <HelperGl/Mesh.h>
#include <HelperGl/Loader3ds.h>
#include <HelperGl/Draw.h>
#include <HelperGl/LightServer.h>
#include <Math/Matrix4x4f.h>
#include <HelperGl/PhongShader.h>

namespace Application
{
	class TP1 : public Base
	{
	protected:
		// The light
		HelperGl::LightServer::Light * m_light ;
		// The white material
		HelperGl::Material m_whiteMaterial ;

	public:
		TP1()
			: m_light(NULL)
		{}

	protected:
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	virtual void TP1::initializeRendering()
		///
		/// \brief	Initializes the rendering.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	16/03/2016
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void initializeRendering()
		{
			// 1 - Lighting setup : creates a light 
			HelperGl::Color lightColor(1.0,1.0,1.0);
			HelperGl::Color lightAmbiant(0.0,0.0,0.0,0.0);
			Math::Vector4f lightPosition = Math::makeVector(0.0f,0.0f,0.0f,1.0f) ; // Point m_light centered in 0,0,20
			m_light = HelperGl::LightServer::getSingleton()->createLight(lightPosition.popBack(), lightColor, lightColor, lightColor) ;
			m_light->enable();
			// White material
			m_whiteMaterial.setDiffuse(HelperGl::Color(0.5f,0.5f,0.5f)) ;
			m_whiteMaterial.setSpecular(HelperGl::Color(0.5f,0.5f,0.5f)) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	virtual void TP1::render(double dt)
		///
		/// \brief	OpenGL rendering happens here.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	16/03/2016
		///
		/// \param	dt	Time elapsed since last call to render (in seconds)
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void render(double dt)
		{
			HelperGl::Draw::draw(m_whiteMaterial) ; // Sets the default material to the white material
			// Type you OpenGL code after this comment.
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	virtual void TP1::keyboard(unsigned char key, int x, int y)
		///
		/// \brief	Keyboard callback
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	16/03/2016
		///
		/// \param	key	The pressed key.
		/// \param	x  	The x coordinate.
		/// \param	y  	The y coordinate.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void keyboard(unsigned char key, int x, int y) 
		{
			if(key == 'q') // If 'q' is pressed, we quit the application
			{
				quit() ;
			}
		}

	};
}

#endif