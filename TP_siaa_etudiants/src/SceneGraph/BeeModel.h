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
		SceneGraph::Rotate * m_beeRotate;
		SceneGraph::Translate * m_beeTranslate;


		int m_direction;


	public:
		BeeModel();
		~BeeModel();
		SceneGraph::Group * getGraph();
		void rotateWings(float angle, float speed);
		void moveBee(Math::Vector3f movement);
		void setPositionBee(Math::Vector3f newPosition);
	};
}
