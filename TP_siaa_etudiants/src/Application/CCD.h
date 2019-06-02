#ifndef _CCD_H
#define _CCD_H

#include <Animation/KinematicChain.h>
class CCD
{
private:
	Animation::KinematicChain *m_kinematic_chain;
	Animation::KinematicChain::Node *m_extremity_node;
	std::vector<Animation::KinematicChain::DegreeOfFreedom> m_dof;
	float m_epsilon;

public:
	CCD(Animation::KinematicChain *kinematic_chain, Animation::KinematicChain::Node *extremity_node)
		: m_kinematic_chain(kinematic_chain), m_extremity_node(extremity_node)
	{
		m_epsilon = 0.01f;
		m_extremity_node->collectDegreesOfFreedom(m_dof);
	}

	//iteration de convergence CCD sur tous les dof de la chaine concerne
	void convergeToward(Math::Vector3f & offset, float max_angular_variation)
	{
		//Math::Vector3f test;
		//m_extremity_node->getGlobalTransformation().getTranslation(test);
		Math::Vector3f world_extremity = m_extremity_node->getGlobalTransformation() * Math::makeVector(0.0f, 0.0f, 0.0f);
		Math::Vector3f target = world_extremity +offset;

		for (int i = 0; i < m_dof.size(); i++) {
			Math::Vector3f theta = m_kinematic_chain->derivate(m_extremity_node, offset, m_dof[i], m_epsilon);
			float delta = (theta.inv() * offset) / theta.norm();

			//check if correct
			if (delta < max_angular_variation && delta < -max_angular_variation) {
				delta = -max_angular_variation;		
			}else if(delta > max_angular_variation){
				delta = max_angular_variation;
			}
			//update
			m_dof[i] = (float)m_dof[i] + 0.5f * delta;
			world_extremity = m_extremity_node->getGlobalTransformation() * Math::makeVector(0.0f, 0.0f, 0.0f);
			offset = target - world_extremity;
		}	
	}

	//signal la reussite ou l'echec de la converge
	bool solve(Math::Vector3f & offset, float max_angular_variation)
	{
		// si offset a moin de (0.05, 0.05, 0.05) de target alors reussite
		if (abs(offset[0]) > 0.05 || abs(offset[1]) > 0.05 || abs(offset[2]) > 0.05)
		{
			convergeToward(offset, max_angular_variation);
			return false;
		}

		return true;
	}
};
#endif