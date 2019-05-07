#ifndef _Application_TP1_siaa_H
#define _Application_TP1_siaa_H

#include <HelperGl/Camera.h>
#include <HelperGl/LightServer.h>
#include <Application/BaseWithKeyboard.h>
#include <Application/KeyboardStatus.h>
#include <SceneGraph/Group.h>
#include <SceneGraph/MeshVBO_v2.h>
#include <GL/compatibility.h>
#include <SceneGraph/Sphere.h>
#include <HelperGl/Material.h>
#include <HelperGl/Color.h>
#include <SceneGraph/CoordinateSystem.h>
#include <SceneGraph/Translate.h>
#include <SceneGraph/BeeModel.h>


namespace Application
{
	class TP1_siaa : public BaseWithKeyboard
	{
	protected:
		HelperGl::Camera m_camera ;

		SceneGraph::Group m_root ;
		SceneGraph::BeeModel * m_bee;

		virtual void handleKeys() 
		{
			// The camera translation speed
			float cameraSpeed = 5.0f ;
			// The camera rotation speed (currently not used)
			float rotationSpeed = float(Math::pi/2.0) ;

			// quit
			if(m_keyboard.isPressed('q')) { quit() ; }
			// Go front
			if(m_keyboard.isPressed('+')) { m_camera.translateLocal(Math::makeVector(0.0f,0.0f,-cameraSpeed*(float)getDt())) ; } 
			// Go back
			if(m_keyboard.isPressed('-')) { m_camera.translateLocal(Math::makeVector(0.0f,0.0f,(float)cameraSpeed*(float)getDt())) ; } 
			// Go left
			if(m_keyboard.isPressed('1')) { m_camera.translateLocal(Math::makeVector(-cameraSpeed*(float)getDt(),0.0f,0.0f)) ; }
			// Go right
			if(m_keyboard.isPressed('3')) { m_camera.translateLocal(Math::makeVector((float)cameraSpeed*(float)getDt(),0.0f,0.0f)) ; }
			// Go down
			if(m_keyboard.isPressed('2')) { m_camera.translateLocal(Math::makeVector(0.0f,-cameraSpeed*(float)getDt(),0.0f)) ; }
			// Go up
			if(m_keyboard.isPressed('5')) { m_camera.translateLocal(Math::makeVector(0.0f,(float)cameraSpeed*(float)getDt(),0.0f)) ; }

			if (m_keyboard.isPressed('4')) { m_camera.rotateLocal(Math::makeVector(0.0f, 1.0f, 0.0f), (float)cameraSpeed*(float)getDt()*0.2f); }

			if (m_keyboard.isPressed('6')) { m_camera.rotateLocal(Math::makeVector(0.0f, 1.0f, 0.0f), (float)cameraSpeed*(float)getDt()*-0.2f); }
		}

	public:
		TP1_siaa()
		{
		}

		virtual void initializeRendering()
		{
			HelperGl::Material mat;
			HelperGl::Color col(0, 1.0f, 1.0f);
			mat.setDiffuse(col);
			//mat.setAmbiant(col);
			//mat.setShininess(3.0f);
			//mat.setEmission(col);
			//mat.setSpecular(col);
			
			SceneGraph::CoordinateSystem * coord = new SceneGraph::CoordinateSystem(1);
			m_root.addSon(coord);

			/*
			SceneGraph::Sphere * s = new SceneGraph::Sphere(mat);
			//m_root.addSon(s);
			SceneGraph::Translate * transl = new SceneGraph::Translate();
			transl->setTranslation(Math::makeVector(2.0f,0.0f,0.0f));
			transl->addSon(s);
			m_root.addSon(transl);
			*/

			m_bee = new SceneGraph::BeeModel;
			m_root.addSon(m_bee->getGraph());
			
			// Light
			HelperGl::Color lightColor(1.0,1.0,1.0);
			HelperGl::Color lightAmbiant(0.0,0.0,0.0,0.0);
			Math::Vector4f lightPosition = Math::makeVector(0.0f,0.0f,10000.0f,1.0f) ; // Point light centered in 0,0,0
			HelperGl::LightServer::Light * light = HelperGl::LightServer::getSingleton()->createLight(lightPosition.popBack(), lightColor, lightColor, lightColor) ;
			light->enable();
			m_camera.translateFront(-10);
		}

		virtual void render(double dt)
		{
			handleKeys();
			GL::loadMatrix(m_camera.getInverseTransform());
			m_root.draw();
			m_bee->rotateWings(dt, 30);
			m_bee->moveBee(Math::makeVector(dt, dt, dt));

		}
	};
}

#endif