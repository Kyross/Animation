#pragma once

#include <Math/Vectorf.h>

class HermiteSpline
{

private :
	Math::Vector3f m_p0;
	Math::Vector3f m_p1;
	Math::Vector3f m_m0;
	Math::Vector3f m_m1;

public:
	HermiteSpline(Math::Vector3f p0, Math::Vector3f p1, Math::Vector3f m0, Math::Vector3f m1)
		:m_p0(p0), m_p1(p1), m_m0(m0), m_m1(m1)
	{
		//m_m0 = m_m0.normalized();
		//m_m1 = m_m1.normalized();
	}

	~HermiteSpline();

	Math::Vector3f compute(float u)
	{
		float u3 = pow(u, 3.0f);
		float u2 = pow(u, 2.0f);

		float coeffp0 = (2.0f*u3 - 3.0f*u2 + 1.0f);
		float coeffm0 = (u3 - 2.0f*u2 + u);
		float coeffp1 = (-2.0f*u3 + 3.0f*u2);
		float coeffm1 = (u3 - u2);

		return m_p0 * coeffp0 + m_m0 * coeffm0 + m_p1 * coeffp1 + m_m1 * coeffm1;
	}

	Math::Vector3f getSpeed(float u)
	{
		float u3 = pow(u, 3.0f);
		float u2 = pow(u, 2.0f);

		float coeffp0 = (6.0f*u2 - 6.0f*u);
		float coeffm0 = (3.0 * u2 - 4.0f*u + 1.0);
		float coeffp1 = (-6.0f*u2 + 6.0f*u);
		float coeffm1 = (3.0 * u2 - 2.0 * u);

		return (m_p0 * coeffp0 + m_m0 * coeffm0 + m_p1 * coeffp1 + m_m1 * coeffm1);
	}

	Math::Vector3f HermiteSpline::getSpeedSphericalCoord(float u) {
		
		Math::Vector3f speedVect = getSpeed(u).normalized();

		float r = sqrt(pow(speedVect[0], 2.0) + pow(speedVect[1], 2.0) + pow(speedVect[2], 2.0));
		float phi = acos(speedVect[2] / r);
		float theta = atan(speedVect[1] / speedVect[0]);
		
		return Math::makeVector(r, theta, phi);
	}

};

