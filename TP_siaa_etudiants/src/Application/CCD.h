#ifndef _CCD_H
#define _CCD_H

#include <Animation/KinematicChain.h>
class CCD
{
private:
	Animation::KinematicChain *m_kinematic_chain;
	Animation::KinematicChain::Node *m_extremity_node;
	std::vector<Animation::KinematicChain::DegreeOfFreedom> m_dof
		;
public:
	CCD(Animation::KinematicChain *kinematic_chain, Animation::KinematicChain::Node *extremity_node)
		: m_kinematic_chain(kinematic_chain), m_extremity_node(extremity_node)
	{
		m_extremity_node->collectDegreesOfFreedom(m_dof);
	}

	//iteration de convergence CCD sur tous les dof de la chaine concerne
	void convergeToward(Math::Vector3f & offset, float max_angular_variation)
	{
		Math::Vector3f world_extremity = m_extremity_node->getGlobalTransformation() * Math::makeVector(0.0f, 0.0f, 0.0f);
		Math::Vector3f target = world_extremity +offset;
		for (int i = 0; i < m_dof.size(); i++) {
			// Use the correct column of the jacobian
			Math::Vector3f jacob_theta = m_kinematic_chain->derivate(m_extremity_node, offset, m_dof[i], 0.01);
			float delta_dof = (jacob_theta.inv() * offset) / jacob_theta.norm();
			delta_dof = delta_dof < max_angular_variation ? (delta_dof > -max_angular_variation ? delta_dof : -max_angular_variation) : max_angular_variation;
			// Update DOF
			m_dof[i] = (float)m_dof[i] + 0.5f * delta_dof;

			// Update dP
			world_extremity = m_extremity_node->getGlobalTransformation() * Math::makeVector(0.0f, 0.0f, 0.0f);
			offset = target - world_extremity;
		}	
	}
};
#endif