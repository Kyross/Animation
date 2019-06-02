#pragma once

#include <SceneGraph/Sphere.h>
#include <SceneGraph/Group.h>
#include <SceneGraph/Translate.h>
#include <SceneGraph/Scale.h>
#include <SceneGraph/Rotate.h>

namespace SceneGraph{
	class BeeModel
	{
	protected : 
		SceneGraph::Group * m_graph;

		SceneGraph::Rotate * m_wing1Rotate;
		SceneGraph::Rotate * m_wing2Rotate;

		SceneGraph::Scale * m_beeScale;

		SceneGraph::Rotate * m_beeRotateY;
		SceneGraph::Rotate * m_beeRotateZ;

		SceneGraph::Translate * m_beeTranslate;


		int m_direction;


	public:
		BeeModel() : m_direction(1)
		{
			//Materials
			m_graph = new SceneGraph::Group;
			HelperGl::Material bodyMat;
			HelperGl::Color colBody(1.0, 1.0f, 0.0f);
			bodyMat.setDiffuse(colBody);

			HelperGl::Material wingMat;
			HelperGl::Color colWings(0.8, 0.8f, 0.8f);
			wingMat.setDiffuse(colWings);

			HelperGl::Material eyesMat;
			HelperGl::Color colEyes(0.1, 0.1f, 0.1f);
			eyesMat.setDiffuse(colEyes);
			//---//

			//Body
			SceneGraph::Sphere * body = new SceneGraph::Sphere(bodyMat);
			SceneGraph::Scale * bodyScale = new SceneGraph::Scale(Math::makeVector(1.0f, 0.3f, 0.3f));
			bodyScale->addSon(body);
			//---//

			//Eyes
			SceneGraph::Sphere * eye1 = new SceneGraph::Sphere(eyesMat, 0.05);
			SceneGraph::Sphere * eye2 = new SceneGraph::Sphere(eyesMat, 0.05);

			SceneGraph::Translate * eye1Translate = new SceneGraph::Translate(Math::makeVector(0.7f, 0.2f, 0.1f));
			SceneGraph::Translate * eye2Translate = new SceneGraph::Translate(Math::makeVector(0.7f, -0.2f, 0.1f));

			eye1Translate->addSon(eye1);
			eye2Translate->addSon(eye2);

			//---//


			//Wings
			SceneGraph::Sphere * wing1 = new SceneGraph::Sphere(wingMat);
			SceneGraph::Sphere * wing2 = new SceneGraph::Sphere(wingMat);

			SceneGraph::Scale * wing1Scale = new SceneGraph::Scale(Math::makeVector(0.3f, 0.3f, 0.05f));
			SceneGraph::Scale * wing2Scale = new SceneGraph::Scale(Math::makeVector(0.3f, 0.3f, 0.05f));

			wing1Scale->addSon(wing1);
			wing2Scale->addSon(wing2);

			SceneGraph::Translate * wing1Translate = new SceneGraph::Translate(Math::makeVector(0.0f, 0.55f, 0.0f));
			SceneGraph::Translate * wing2Translate = new SceneGraph::Translate(Math::makeVector(0.0f, -0.55f, 0.0f));

			wing1Translate->addSon(wing1Scale);
			wing2Translate->addSon(wing2Scale);

			m_wing1Rotate = new SceneGraph::Rotate(0.0, Math::makeVector(1.0f, 0.0f, 0.0f));
			m_wing2Rotate = new SceneGraph::Rotate(0.0, Math::makeVector(1.0f, 0.0f, 0.0f));

			m_wing1Rotate->addSon(wing1Translate);
			m_wing2Rotate->addSon(wing2Translate);

			//---//



			//Full bee
			m_beeScale = new SceneGraph::Scale(Math::makeVector(1.0f, 1.0f, 1.0f));

			m_beeScale->addSon(bodyScale);
			m_beeScale->addSon(m_wing1Rotate);
			m_beeScale->addSon(m_wing2Rotate);

			m_beeScale->addSon(eye1Translate);
			m_beeScale->addSon(eye2Translate);

			//Rotate X
			SceneGraph:Rotate * beeRotateX = new SceneGraph::Rotate(-Math::pi/2.0, Math::makeVector(1.0f, 0.0f, 0.0f));
			beeRotateX->addSon(m_beeScale);

			//Rotate Y
			m_beeRotateY = new SceneGraph::Rotate(0.0, Math::makeVector(0.0f, 1.0f, 0.0f));
			m_beeRotateY->addSon(beeRotateX);

			//Rotate Z
			m_beeRotateZ = new SceneGraph::Rotate(0.0, Math::makeVector(0.0f, 0.0f, 1.0f));
			m_beeRotateZ->addSon(m_beeRotateY);

			//Translate
			m_beeTranslate = new SceneGraph::Translate(Math::makeVector(0.0f, 0.0f, 0.0f));
			m_beeTranslate->addSon(m_beeRotateZ);
			//--//
			m_graph->addSon(m_beeTranslate);

		}

		~BeeModel()
		{
			delete m_graph;
		}

		SceneGraph::Group * getGraph()
		{
			return m_graph;
		}

		void rotateWings(float angle, float speed)
		{
			if (m_wing1Rotate->getAngle() >= 1.0) {
				m_direction = -1;
			}
			else if (m_wing1Rotate->getAngle() <= -1.0) {
				m_direction = 1;
			}
			m_wing1Rotate->setAngle(m_wing1Rotate->getAngle() + angle * m_direction*speed);
			m_wing2Rotate->setAngle(m_wing2Rotate->getAngle() - angle * m_direction*speed);
		}

		void moveBee(Math::Vector3f movement)
		{
			m_beeTranslate->setTranslation(m_beeTranslate->getTranslation() + movement);
		}

		void setPositionBee(Math::Vector3f newPosition)
		{
			m_beeTranslate->setTranslation(newPosition);
		}

		const Math::Vector3f getPositionBee()
		{
			return m_beeTranslate->getTranslation();
		}

		void setRotationBeeY(float newAngle)
		{
			m_beeRotateY->setAngle(newAngle);
		}

		void setRotationBeeZ(float newAngle)
		{
			m_beeRotateZ->setAngle(newAngle);
		}

	};
}
