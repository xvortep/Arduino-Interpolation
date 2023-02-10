/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)
Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/
 
 #ifndef _INTERPOLATIONLIB_h
#define _INTERPOLATIONLIB_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class Interpolation
{
public:
	Interpolation(const double* x, const double* y, size_t len, double threshold = 1);

	//double Step(double yValues[], int numValues, double pointX, double threshold = 1);
	//double Step(double minX, double maxX, double yValues[], int numValues, double pointX, double threshold = 1);
	// double Step(double pointX);
	// double Step(double pointx, int from = 0);

	// double Linear(double pointX, bool trim = true);
	double Linear(double pointX, int& cap, bool trim = true, int from = 0);
	//double Linear(double minX, double maxX, double yValues[], int numValues, double pointX, bool trim = true);
	//double Linear(double xValues[], double yValues[], int numValues, double pointX, bool trim = true);	
	// double SmoothStep(double pointX, bool trim = true);
	// double SmoothStep(double pointX, bool trim = true, int from = 0);
	// double CatmullSpline(double pointX, bool trim = true);
	// double CatmullSpline(double pointX, bool trim = true, int from = 0);

private:
	const double* xValues;
	const double* yValues;
	size_t numValues;
	double threshold;

	// int getIndex(double pointX);
	int getIndex(double pointX, int from = 0);

	// double catmullSlope(int i);
};

#endif