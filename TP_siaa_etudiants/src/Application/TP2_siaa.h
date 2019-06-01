#ifndef _Application_TP2_siaa_H
#define _Application_TP2_siaa_H

#include <HelperGl/Camera.h>
#include <HelperGl/LightServer.h>
#include <Application/BaseWithKeyboard.h>
#include <Application/KeyboardStatus.h>
#include <SceneGraph/Group.h>
#include <SceneGraph/MeshVBO_v2.h>
#include <GL/compatibility.h>
#include <SceneGraph/Sphere.h>
#include <SceneGraph/Cylinder.h>
#include <HelperGl/Material.h>
#include <HelperGl/Color.h>
#include <SceneGraph/CoordinateSystem.h>
#include <SceneGraph/Translate.h>
#include <Animation/KinematicChain.h>


namespace Application
{
	class TP2_siaa : public BaseWithKeyboard
	{
	protected:
		HelperGl::Camera m_camera;
		SceneGraph::Group m_root;
		Animation::KinematicChain * m_kinematicChain;

		virtual void handleKeys()
		{
			// The camera translation speed
			float cameraSpeed = 5.0f;
			// The camera rotation speed (currently not used)
			float rotationSpeed = float(Math::pi / 2.0);

			// quit
			if (m_keyboard.isPressed('0')) { quit(); }
			// Go front
			if (m_keyboard.isPressed('+') || m_keyboard.isPressed('=')) { m_camera.translateLocal(Math::makeVector(0.0f, 0.0f, -cameraSpeed * (float)getDt())); }
			// Go back
			if (m_keyboard.isPressed('-')) { m_camera.translateLocal(Math::makeVector(0.0f, 0.0f, (float)cameraSpeed*(float)getDt())); }
			// Go left
			if (m_keyboard.isPressed('1') || m_keyboard.isPressed('q')) { m_camera.translateLocal(Math::makeVector(-cameraSpeed * (float)getDt(), 0.0f, 0.0f)); }
			// Go right
			if (m_keyboard.isPressed('3') || m_keyboard.isPressed('d')) { m_camera.translateLocal(Math::makeVector((float)cameraSpeed*(float)getDt(), 0.0f, 0.0f)); }
			// Go down
			if (m_keyboard.isPressed('2') || m_keyboard.isPressed('s')) { m_camera.translateLocal(Math::makeVector(0.0f, -cameraSpeed * (float)getDt(), 0.0f)); }
			// Go up
			if (m_keyboard.isPressed('5') || m_keyboard.isPressed('z')) { m_camera.translateLocal(Math::makeVector(0.0f, (float)cameraSpeed*(float)getDt(), 0.0f)); }

			//turn left
			if (m_keyboard.isPressed('4') || m_keyboard.isPressed('a')) {
				m_camera.rotateLocal(Math::makeVector(0.0f, 1.0f, 0.0f), (float)cameraSpeed*(float)getDt()*0.2);
				m_camera.translateLocal(Math::makeVector((float)cameraSpeed*(float)getDt(), 0.0f, 0.0f));
			}
			//turn right
			if (m_keyboard.isPressed('6') || m_keyboard.isPressed('e')) {
				m_camera.rotateLocal(Math::makeVector(0.0f, -1.0f, 0.0f), (float)cameraSpeed*(float)getDt()*0.2);
				m_camera.translateLocal(Math::makeVector(-cameraSpeed * (float)getDt(), 0.0f, 0.0f));
			}
		}

	public:
		TP2_siaa()
		{
			//Init camera position
			m_camera.translateFront(-5);

			//Ajout du repere
			SceneGraph::CoordinateSystem * coord = new SceneGraph::CoordinateSystem(1);
			m_root.addSon(coord);

			//KinematicChain
			m_kinematicChain = new Animation::KinematicChain();
			m_root.addSon(buildChain(6));
		}

		virtual void initializeRendering()
		{
			// Light
			HelperGl::Color lightColor(1.0, 1.0, 1.0);
			HelperGl::Color lightAmbiant(0.0, 0.0, 0.0, 0.0);
			Math::Vector4f lightPosition = Math::makeVector(0.0f, 0.0f, 10000.0f, 1.0f); // Point light centered in 0,0,0
			HelperGl::LightServer::Light * light = HelperGl::LightServer::getSingleton()->createLight(lightPosition.popBack(), lightColor, lightColor, lightColor);
			light->enable();
		}

		virtual void render(double dt)
		{
			handleKeys();
			GL::loadMatrix(m_camera.getInverseTransform());
			m_root.draw();
		}

		SceneGraph::Group * buildChain(int nbSegment)
		{
			Math::Vector3f x = Math::makeVector(1.0f, 0.0f, 0.0f);
			Math::Vector3f y = Math::makeVector(0.0f, 1.0f, 0.0f);
	
			SceneGraph::Group * chain = new SceneGraph::Group();

			SceneGraph::Group * temp = chain;
			for (int i = 0; i < nbSegment; i++) {
				addChain(temp);
				SceneGraph::Translate * translate_next = new SceneGraph::Translate(Math::makeVector(0.7f, 0.0f, 0.0f)); //articulation(0.1)+segment(0.5)+articulation(0.1)
				temp->addSon(translate_next);
				temp = translate_next;
			}

			return chain;

		}


		void addChain(SceneGraph::Group * source)
		{
			Math::Vector3f x = Math::makeVector(1.0f, 0.0f, 0.0f);
			Math::Vector3f y = Math::makeVector(0.0f, 1.0f, 0.0f);
			Math::Vector3f z = Math::makeVector(0.0f, 0.0f, 1.0f);

			// ***Materials and geo of the chain
			HelperGl::Material mat_articulation, mat_segment;
			mat_articulation.setDiffuse(HelperGl::Color(1.0f, 0.0f, 0.3f));
			mat_segment.setDiffuse(HelperGl::Color(0.3f, 1.0f, 1.0f));
			SceneGraph::Sphere * articulation = new SceneGraph::Sphere(mat_articulation, 0.2);
			SceneGraph::Cylinder * segment = new SceneGraph::Cylinder(mat_segment, 0.1, 0.1, 0.5);

			// *** Build scene graph
			SceneGraph::Rotate * rotate_articulation_x = new SceneGraph::Rotate(0, x);
			SceneGraph::Rotate * rotate_articulation_z = new SceneGraph::Rotate(0, z);
			SceneGraph::Translate * translate_segment = new SceneGraph::Translate(Math::makeVector(0.5f, 0.0f, 0.0f));
			SceneGraph::Rotate * rotate_segment = new SceneGraph::Rotate(-Math::pi / 2, y); //aligner segment sphere

			//articulation
			source->addSon(rotate_articulation_x);
			rotate_articulation_x->addSon(rotate_articulation_z);
			rotate_articulation_z->addSon(articulation);
			//segment
			rotate_articulation_z->addSon(translate_segment);
			translate_segment->addSon(rotate_segment);
			rotate_segment->addSon(segment);
		}

	};
}

#endif