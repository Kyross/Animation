#include "SceneGraph/BeeModel.h"

SceneGraph::BeeModel:: BeeModel() 
	: m_direction(1)
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
	SceneGraph::Sphere * eye1 = new SceneGraph::Sphere(eyesMat,0.05);
	SceneGraph::Sphere * eye2 = new SceneGraph::Sphere(eyesMat,0.05);

	SceneGraph::Translate * eye1Translate = new SceneGraph::Translate(Math::makeVector(0.7f, 0.2f, 0.1f));
	SceneGraph::Translate * eye2Translate = new SceneGraph::Translate(Math::makeVector(0.7f, -0.2f, 0.1f));

	eye1Translate->addSon(eye1);
	eye2Translate->addSon(eye2);

	//bodyScale->addSon(eye1Translate);
	//bodyScale->addSon(eye2Translate);
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


	m_beeRotate = new SceneGraph::Rotate(1.0, Math::makeVector(0.0f, 0.0f, 0.0f));
	m_beeRotate->addSon(m_beeScale);

	m_beeTranslate = new SceneGraph::Translate(Math::makeVector(0.0f, 0.0f, 0.0f));
	m_beeTranslate->addSon(m_beeRotate);
	//--//
	m_graph->addSon(m_beeTranslate);

}

SceneGraph::BeeModel::~BeeModel()
{
	delete m_graph;
}

SceneGraph::Group * SceneGraph::BeeModel::getGraph()
{
	return m_graph;
}

void SceneGraph::BeeModel::rotateWings(float angle, float speed)
{	
	if( m_wing1Rotate->getAngle() >= 1.0){
		m_direction = -1;
	}
	else if( m_wing1Rotate->getAngle() <= -1.0){
		m_direction = 1;
	}
	m_wing1Rotate->setAngle(m_wing1Rotate->getAngle() + angle*m_direction*speed);
	m_wing2Rotate->setAngle(m_wing2Rotate->getAngle() - angle*m_direction*speed);
}

void SceneGraph::BeeModel::moveBee(Math::Vector3f movement)
{
	m_beeTranslate->setTranslation(m_beeTranslate->getTranslation() + movement);
}

void SceneGraph::BeeModel::setPositionBee(Math::Vector3f newPosition)
{
	m_beeTranslate->setTranslation(newPosition);
	std::cout << "x : " << newPosition[0] << std::endl;
	std::cout << "y : " << newPosition[1] << std::endl;
	std::cout << "z : " << newPosition[2] << std::endl<<std::endl;
}

void SceneGraph::BeeModel::rotateBee(float angle, Math::Vector3f rotation)
{
	m_beeRotate->setAngle(m_beeRotate->getAngle() + angle);
	m_beeRotate->setAxis(rotation);
}

void SceneGraph::BeeModel::setRotationBee(float newAngle, Math::Vector3f newRotation)
{
	m_beeRotate->setAngle(newAngle);
	m_beeRotate->setAxis(newRotation);
}
