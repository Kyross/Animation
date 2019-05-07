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
	HermiteSpline(Math::Vector3f p0, Math::Vector3f p1, Math::Vector3f m0, Math::Vector3f m1);
	~HermiteSpline();
	Math::Vector3f compute(float u);
	float HermiteSpline::getSpeed(float u);
};

