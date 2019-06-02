#ifndef _Application_TP3_siaa_H
#define _Application_TP3_siaa_H

#include <HelperGl/Camera.h>
#include <HelperGl/LightServer.h>
#include <Application/BaseWithKeyboard.h>
#include <Application/KeyboardStatus.h>
#include <SceneGraph/Group.h>
#include <SceneGraph/MeshVBO_v2.h>
#include <GL/compatibility.h>
#include <HelperGL\Material.h>
#include <HelperGL\Color.h>
#include <Animation\SpringMassSystem.h>
#include <SceneGraph\Patch.h>


namespace Application
{
	std::pair<Math::Vector3f, Math::Vector3f> computeEuler(const Animation::SpringMassSystem::Mass & previous, const Animation::SpringMassSystem::Mass & current, float dt) {
		Math::Vector3f newSpeed = current.m_forces * (dt / current.m_mass) + current.m_speed;
		Math::Vector3f newPosition = current.m_position + ((current.m_speed + newSpeed) / 2.0) * dt;

		return std::pair<Math::Vector3f, Math::Vector3f>(newPosition, newSpeed);
	}

	Math::Vector3f computeForce(const Animation::SpringMassSystem::Mass & mass)
	{
		return Math::makeVector(0.0, 0.0, -mass.m_mass*9.81);
	}

	Math::Vector3f computeLink(const Animation::SpringMassSystem::Mass & mass1, const Animation::SpringMassSystem::Mass & mass2, const Animation::SpringMassSystem::Link & link) {
		float stiffness = 10.0f;
		float viscosity = 0.01f;
		Math::Vector3f damping = mass1.m_speed*viscosity;

		return (mass2.m_position - mass1.m_position) * (1 - (link.m_initialLength / (mass1.m_position - mass2.m_position).norm())) * stiffness - damping;
	}

	std::pair<Math::Vector3f, Math::Vector3f> computeGround(const Animation::SpringMassSystem::Mass &previous, const Animation::SpringMassSystem::Mass &current) {
		if (current.m_position[2] < -1.49f)
		{
			Math::Vector3f newPosition = Math::makeVector(current.m_position[0], current.m_position[1], -1.49f);
			Math::Vector3f newSpeed = Math::makeVector(0.0f, 0.0f, 0.0f);
			return ::std::pair<Math::Vector3f, Math::Vector3f>(newPosition, newSpeed);	
		}
		else {
			return std::pair<Math::Vector3f, Math::Vector3f>(current.m_position, current.m_speed);
		}
	}

	std::pair<Math::Vector3f, Math::Vector3f> computeSphere(const Animation::SpringMassSystem::Mass &previous, const Animation::SpringMassSystem::Mass &current) {
		
		Math::Vector3f spherePosition = Math::makeVector(0.0f, -0.3f, -1.0f);
		
		Math::Vector3f dist = current.m_position - spherePosition;

		if (dist.norm() <= 0.22f) {
			Math::Vector3f newPosition = previous.m_position;
			Math::Vector3f newSpeed = Math::makeVector(0.0f, 0.0f, 0.0f);
			return std::pair<Math::Vector3f, Math::Vector3f>(newPosition, newSpeed);
		}
		else {
			return std::pair<Math::Vector3f, Math::Vector3f>(current.m_position, current.m_speed);
		}

	}

	
	class TP3_siaa : public BaseWithKeyboard
	{
	protected:
		HelperGl::Camera m_camera;

		SceneGraph::Group m_root;

		Animation::SpringMassSystem * m_system;
		Animation::SpringMassSystem::PatchDescriptor m_patch;
		SceneGraph::Patch * m_patchGraph;

		std::vector<int> constrainedMasses;

		Animation::SpringMassSystem * m_systemGround;
		Animation::SpringMassSystem::PatchDescriptor m_groundPatch;
		SceneGraph::Patch * m_groundGraph;

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

			//Contraintes
			//bool pressed = false;
			if (m_keyboard.isPressed('r') && !constrainedMasses.empty()) {
				//pressed = true;
				m_keyboard.release('r');
				int constrainedMass = constrainedMasses.back();
				m_system->unconstrainPosition(constrainedMass);
				//std::cout << "unconstrained id : " << constrainedMasses.back() << std::endl;
				constrainedMasses.pop_back();
			}

		}

	public:
		TP3_siaa()
		{
			//Init camera position
			m_camera.translateFront(-5);

			//Ajout du repere
			SceneGraph::CoordinateSystem * coord = new SceneGraph::CoordinateSystem(1);
			m_root.addSon(coord);

			//Simulateur
			m_system = new Animation::SpringMassSystem();
			m_system->setIntegrator(computeEuler);
			m_system->addForceFunction(computeForce);
			m_system->addLinkForceFunction(computeLink);

			{
				//Patch
				Math::Vector4f row1 = Math::makeVector(1.0f, 0.0f, 0.0f, -3.0f / 2.0f);
				Math::Vector4f row2 = Math::makeVector(0.0f, 1.0f, 0.0f, -3.0f / 2.0f);
				Math::Vector4f row3 = Math::makeVector(0.0f, 0.0f, 1.0f, 0.0f);
				Math::Vector4f row4 = Math::makeVector(0.0f, 0.0f, 0.0f, 1.0f);
				Math::Matrix4x4f positionMatrix(row1, row2, row3, row4);
				m_patch = m_system->createPatch(3.0f, 50, 3.0f, 50, 1, 10.0f, positionMatrix);
			}

			//Contraintes
			m_system->constrainPosition(m_patch.massIndex(0, 0));
			constrainedMasses.push_back(m_patch.massIndex(0, 0));
			m_system->constrainPosition(m_patch.massIndex(0, 50));
			constrainedMasses.push_back(m_patch.massIndex(0, 50));
			m_system->constrainPosition(m_patch.massIndex(50, 0));
			constrainedMasses.push_back(m_patch.massIndex(50, 0));
			m_system->constrainPosition(m_patch.massIndex(50, 50));
			constrainedMasses.push_back(m_patch.massIndex(50, 50));

			//Affichage
			HelperGl::Material patchMat;
			patchMat.setDiffuse(HelperGl::Color(0.0f, 1.0f, 0.0f));
			m_patchGraph = new SceneGraph::Patch(51, 51, patchMat);
			m_root.addSon(m_patchGraph);

			//******//

			//Sol
			m_systemGround = new Animation::SpringMassSystem();
			{
				Math::Vector4f row1 = Math::makeVector(1.0f, 0.0f, 0.0f, -10.0f / 2.0f);
				Math::Vector4f row2 = Math::makeVector(0.0f, 1.0f, 0.0f, -10.0f / 2.0f);
				Math::Vector4f row3 = Math::makeVector(0.0f, 0.0f, 1.0f, -1.5f);
				Math::Vector4f row4 = Math::makeVector(0.0f, 0.0f, 0.0f, 1.0f);
				Math::Matrix4x4f g_transform(row1, row2, row3, row4);
				m_systemGround->createPatch(10, 2, 10, 2, 1, 0, g_transform);
			}
			//Affichage Sol
			HelperGl::Material groundMat;
			groundMat.setDiffuse(HelperGl::Color(0.2, 0.2, 0.2));
			m_groundGraph = new SceneGraph::Patch(3, 3, groundMat);
			m_root.addSon(m_groundGraph);
		
			//Contrainte sol
			m_system->addPositionConstraint(computeGround);

			//******//

			//Sphere
			HelperGl::Material sphereMat;
			sphereMat.setDiffuse(HelperGl::Color(1.0f, 0.0f, 0.0f));
			SceneGraph::Sphere * sphere = new SceneGraph::Sphere(sphereMat, 0.2f);
			SceneGraph::Translate * sphereTranslate = new SceneGraph::Translate(Math::makeVector(0.0f, -0.3f, -1.0f));
			sphereTranslate->addSon(sphere);

			m_root.addSon(sphereTranslate);
			
			//Contrainte sol
			m_system->addPositionConstraint(computeSphere);
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

			m_system->copyMassesPositionsTo(m_patchGraph->getVertices().begin());
			m_systemGround->copyMassesPositionsTo(m_groundGraph->getVertices().begin());
			m_system->update(dt);
			m_root.draw();

		}
	};
}

#endif