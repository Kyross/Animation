#include "SceneGraph/HermiteSpline.h"



HermiteSpline::HermiteSpline(Math::Vector3f p0, Math::Vector3f p1, Math::Vector3f m0, Math::Vector3f m1)
	:m_p0(p0), m_p1(p1), m_m0(m0), m_m1(m1)
{
	m_m0.normalized();
	m_m1.normalized();
}


HermiteSpline::~HermiteSpline()
{
}

Math::Vector3f HermiteSpline::compute(float u)
{
	
	float u3 = pow(u, 3.0f);
	float u2 = pow(u, 2.0f);

	float coeffp0 = (2.0f*u3 -3.0f*u2 + 1.0f);
	float coeffm0 = (u3 -2.0f*u2 + u);
	float coeffp1 = (-2.0f*u3 + 3.0f*u2);
	float coeffm1 = (u3 - u2);


	return m_p0 * coeffp0 + m_m0 * coeffm0 + m_p1 * coeffp1 + m_m1 * coeffm1;
}
