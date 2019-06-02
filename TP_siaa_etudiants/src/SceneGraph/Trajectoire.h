#pragma once

#include <SceneGraph\HermiteSpline.h>
#include <vector>
#include <Math/Vectorf.h>


class Trajectoire {

private :
	std::vector<HermiteSpline *> splines;

public :
	Trajectoire(std::vector<Math::Vector3f> points, std::vector<Math::Vector3f> tangentes) {
		Math::Vector3f m1prec = Math::makeVector(0.0f, 0.0f, 0.0f);
		for (int i = 0; i < points.size(); i++) {

			int startIndex = i;
			int endIndex = (i+1)%points.size();

			Math::Vector3f p0 = points[startIndex];
			Math::Vector3f p1 = points[endIndex];

			//Math::Vector3f m0 = tangentes[startIndex];
			//Math::Vector3f m1 = tangentes[endIndex];

			Math::Vector3f m0, m1;
			m0 = m1prec;

			if (i == points.size() - 1) {
				m1 = Math::makeVector(0.0f, 0.0f, 0.0f);
			}
			else {
				m1 = (p1 - p0).normalized();
			}
			m1prec = m1;

			//Coordonnates order : p0, p1, m0, m1
			HermiteSpline * currentSpline = new HermiteSpline(p0, p1, m0, m1);

			splines.push_back(currentSpline);
		}
	}

	~Trajectoire()
	{
		for (int i = 0; i < splines.size(); i++) {
			delete splines[i];
		}
	}

	Math::Vector3f computeTrajectoire(float u) {

		int currentSplineIndex = floor(u);
		HermiteSpline * currentSpline = splines[currentSplineIndex];

		return currentSpline->compute(u - currentSplineIndex);
	}

	Math::Vector3f getSpeedTrajectoire(float u) {

		int currentSplineIndex = floor(u);
		HermiteSpline * currentSpline = splines[currentSplineIndex];

		return currentSpline->getSpeed(u - currentSplineIndex);
	}

	Math::Vector3f getSpeedSphericalCoordTrajectoire(float u) {

		int currentSplineIndex = floor(u);
		HermiteSpline * currentSpline = splines[currentSplineIndex];

		return currentSpline->getSpeedSphericalCoord(u - currentSplineIndex);
	}





};