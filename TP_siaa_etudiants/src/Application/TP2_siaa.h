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
#include <ctime>
#include<Application/CCD.h>


namespace Application
{
	class TP2_siaa : public BaseWithKeyboard
	{
	protected:
		HelperGl::Camera m_camera;
		SceneGraph::Group m_root;
		std::vector<std::pair<SceneGraph::Rotate*, Animation::KinematicChain::DegreeOfFreedom>> m_animations;
		Animation::KinematicChain::Node * m_extremity_node;
		SceneGraph::Translate * m_target;
		CCD * m_ccd;

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

			//moveTarget
			if (m_keyboard.isPressed('n')) {
				moveTarget(m_target, m_extremity_node);
			}
		}

	public:
		TP2_siaa()
		{
			//Init camera position
			m_camera.translateFront(-10);

			//Ajout du repere
			SceneGraph::CoordinateSystem * coord = new SceneGraph::CoordinateSystem(1);
			m_root.addSon(coord);

			//Chain
			Animation::KinematicChain * kinematic_chain = new Animation::KinematicChain();
			m_extremity_node= buildChain(6, kinematic_chain);

			//Target
			HelperGl::Material mat;
			mat.setDiffuse(HelperGl::Color(1.0f, 0.0f, 0.0f));
			SceneGraph::Sphere * sphere = new SceneGraph::Sphere(mat, 0.2);
			m_target = new SceneGraph::Translate(Math::makeVector(0.0f, 0.0f, 0.0f));
			m_target->addSon(sphere);
			m_root.addSon(m_target);
			moveTarget(m_target, m_extremity_node);

			//CCD
			m_ccd = new CCD(kinematic_chain, m_extremity_node);
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

			//Chain
			Math::Vector3f offset = m_target->getTranslation() - (m_extremity_node->getGlobalTransformation() * Math::makeVector(0.0f, 0.0f, 0.0f));
			m_ccd->convergeToward(offset, 1.0f);
			for (int i = 0; i < m_animations.size(); i++) {
				m_animations[i].first->setAngle((float)m_animations[i].second); //upd angles
			}
				
			m_root.draw();
		}

		Animation::KinematicChain::Node * buildChain(const int nbSegment, Animation::KinematicChain * kc) {
			SceneGraph::Group * father = new SceneGraph::Group();

			// ***Materials and geo -- OK
			HelperGl::Material mat_articulation, mat_segment;
			mat_articulation.setDiffuse(HelperGl::Color(0.5f, 0.5f, 0.5f));
			mat_segment.setDiffuse(HelperGl::Color(0.5f, 0.5f, 1.0f));
			SceneGraph::Sphere * articulation = new SceneGraph::Sphere(mat_articulation, 0.2);
			SceneGraph::Cylinder * segment = new SceneGraph::Cylinder(mat_segment, 0.1, 0.1, 0.5);

			// ***Kinematic
			Math::Interval<float> interval(-Math::pi / 2, Math::pi / 2);
			Animation::KinematicChain::DynamicNode * dnode_r_x;
			Animation::KinematicChain::DynamicNode * dnode_r_z;
			Animation::KinematicChain::StaticNode * snode_translate;

			SceneGraph::Group * last_segment = new SceneGraph::Group();
			father->addSon(last_segment);
			for (int i = 0; i < nbSegment; i++)
			{
				// ***Transforms
				SceneGraph::Rotate * rotate_articulation_x = new SceneGraph::Rotate(0, Math::makeVector(1.0f, 0.0f, 0.0f));
				SceneGraph::Rotate * rotate_articulation_z = new SceneGraph::Rotate(0, Math::makeVector(0.0f, 0.0f, 1.0f));
				SceneGraph::Translate * translate_segment = new SceneGraph::Translate(Math::makeVector(0.5f, 0.0f, 0.0f));
				SceneGraph::Rotate * rotate_segment = new SceneGraph::Rotate(-Math::pi / 2, Math::makeVector(0.0f, 1.0f, 0.0f));
				SceneGraph::Translate * extremity = new SceneGraph::Translate(Math::makeVector(0.2f, 0.0f, 0.0f));

				// ***Scene graph
				//articulation
				last_segment->addSon(rotate_articulation_x);
				rotate_articulation_x->addSon(rotate_articulation_z);
				rotate_articulation_z->addSon(articulation);
				//segment
				rotate_articulation_z->addSon(translate_segment);
				translate_segment->addSon(rotate_segment);
				rotate_segment->addSon(segment);
				translate_segment->addSon(extremity);
				last_segment = extremity;
				
				// ***Kinematic 
				if (i == 0) {
					dnode_r_x = kc->addDynamicRotation(nullptr, Math::makeVector(1.0f, 0.0f, 0.0f), interval, 0); //init root with no parent
				}
				else {
					dnode_r_x = kc->addDynamicRotation(snode_translate, Math::makeVector(1.0f, 0.0f, 0.0f), interval, 0);
				}
				dnode_r_z = kc->addDynamicRotation(dnode_r_x, Math::makeVector(0.0f, 0.0f, 1.0f), interval, 0);
				snode_translate = kc->addStaticTranslation(dnode_r_z, Math::makeVector(0.7f, 0.0f, 0.0f));

				m_animations.push_back(::std::pair<SceneGraph::Rotate*, Animation::KinematicChain::DegreeOfFreedom>(rotate_articulation_x, dnode_r_x->getDOF()[0]));
				m_animations.push_back(::std::pair<SceneGraph::Rotate*, Animation::KinematicChain::DegreeOfFreedom>(rotate_articulation_z, dnode_r_z->getDOF()[0]));	
			}

			m_root.addSon(father);

			return snode_translate;
		}

		void moveTarget(SceneGraph::Translate * target, Animation::KinematicChain::Node * extremity_node)
		{
			// Random translation
			srand(time(nullptr)); // use current time as seed for random generator
			float x = (((float)rand() > 0.5 ? 1 : -1)) * ((float)(rand() % 30) / 10);
			float y = (((float)rand() > 0.5 ? 1 : -1)) * ((float)(rand() % 30) / 10);
			float z = (((float)rand() > 0.5 ? 1 : -1)) * ((float)(rand() % 30) / 10);

			//float x = 0;
			//float y = 2.2;
			//float z = 0.8;

			target->setTranslation(Math::makeVector(x, y, z));
			std::cout <<"target position : "<< target->getTranslation()<<std::endl;
		}
	};
}

#endif