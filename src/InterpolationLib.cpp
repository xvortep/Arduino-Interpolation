/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)
Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/
 
 #include "InterpolationLib.h"

Interpolation::Interpolation(const double* x, const double* y, size_t len, double threshold = 1)
{
	this->xValues = x;
	this->yValues = y;
	this->threshold = threshold;
	this->numValues = len;
}

// double Interpolation::Step(double pointX, int from = 0)
// {
// 	// corner cases
// 	if (pointX <= xValues[0]) return yValues[0];
// 	if (pointX >= xValues[numValues - 1]) return yValues[numValues - 1];

// 	auto i = getIndex(pointX);
// 	// while (pointX >= xValues[i + 1]) i++;
// 	if (pointX == xValues[i + 1]) return yValues[i + 1]; // exact match

// 	auto t = (pointX - xValues[i]) / (xValues[i + 1] - xValues[i]);  // ratio of distances between pointx and ones around it
// 	return t < threshold ? yValues[i] : yValues[i + 1];
// }

double Interpolation::Linear(double pointX, int& cap, bool trim = true, int from = 0)
{
	if (trim)
	{
		if (pointX <= xValues[0]) return yValues[0];
		if (pointX >= xValues[numValues - 1]) return yValues[numValues - 1];
	}

	auto i = getIndex(pointX);
	double rst = 0;
	if (pointX > xValues[0] && pointX < xValues[numValues - 1])
	{
		cap = 0;
		// while (pointX >= xValues[i + 1]) i++;
		// i = getIndex(pointX);
		auto t = (pointX - xValues[i]) / (xValues[i + 1] - xValues[i]);
		rst = yValues[i] * (1 - t) + yValues[i + 1] * t;
	}
	else if (pointX <= xValues[0])
	{
		cap = 1;
		auto t = (pointX - xValues[i]) / (xValues[i + 1] - xValues[i]);
		rst = yValues[i] * (1 - t) + yValues[i + 1] * t;
	}
	else
	{
		cap = -1;
		auto t = (pointX - xValues[numValues - 2]) / (xValues[numValues - 1] - xValues[numValues - 2]);
		rst = yValues[numValues - 2] * (1 - t) + yValues[numValues - 1] * t;
	}


	return rst;

}

// double Interpolation::SmoothStep(double pointX, bool trim)
// {
// 	if (trim)
// 	{
// 		if (pointX <= xValues[0]) return yValues[0];
// 		if (pointX >= xValues[numValues - 1]) return yValues[numValues - 1];
// 	}

// 	auto i = 0;
// 	if (pointX <= xValues[0]) 
// 		i = 0;
// 	else if (pointX >= xValues[numValues - 1]) 
// 		i = numValues - 1;
// 	else 
// 		i = getIndex(pointX);
// 	// while (pointX >= xValues[i + 1]) i++;
// 	if (pointX == xValues[i + 1]) return yValues[i + 1];

// 	auto t = (pointX - xValues[i]) / (xValues[i + 1] - xValues[i]);
// 	t = t * t * (3 - 2 * t);
// 	return yValues[i] * (1 - t) + yValues[i + 1] * t;
// }

// double Interpolation::CatmullSpline(double pointX, bool trim)
// {
// 	if (trim)
// 	{
// 		if (pointX <= xValues[0]) return yValues[0];
// 		if (pointX >= xValues[numValues - 1]) return yValues[numValues - 1];
// 	}

// 	auto i = 0;
// 	if (pointX <= xValues[0]) i = 0;
// 	else if (pointX >= xValues[numValues - 1]) i = numValues - 1;
// 	else while (pointX >= xValues[i + 1]) i++;
// 	if (pointX == xValues[i + 1]) return yValues[i + 1];

// 	auto t = (pointX - xValues[i]) / (xValues[i + 1] - xValues[i]);
// 	auto t_2 = t * t;
// 	auto t_3 = t_2 * t;

// 	auto h00 = 2 * t_3 - 3 * t_2 + 1;
// 	auto h10 = t_3 - 2 * t_2 + t;
// 	auto h01 = 3 * t_2 - 2 * t_3;
// 	auto h11 = t_3 - t_2;

// 	auto x0 = xValues[i];
// 	auto x1 = xValues[i + 1];
// 	auto y0 = yValues[i];
// 	auto y1 = yValues[i + 1];

// 	double m0;
// 	double m1;
// 	if (i == 0)
// 	{
// 		m0 = (yValues[1] - yValues[0]) / (xValues[1] - xValues[0]);
// 		m1 = (yValues[2] - yValues[0]) / (xValues[2] - xValues[0]);
// 	}
// 	else if (i == numValues - 2)
// 	{
// 		m0 = (yValues[numValues - 1] - yValues[numValues - 3]) / (xValues[numValues - 1] - xValues[numValues - 3]);
// 		m1 = (yValues[numValues - 1] - yValues[numValues - 2]) / (xValues[numValues - 1] - xValues[numValues - 2]);
// 	}
// 	else
// 	{
// 		m0 = catmullSlope(xValues, yValues, numValues, i);
// 		m1 = catmullSlope(xValues, yValues, numValues, i + 1);
// 	}

// 	auto rst = h00 * y0 + h01 * y1 + h10 * (x1 - x0) * m0 + h11 * (x1 - x0) * m1;
// 	return rst;
// }

// double Interpolation::catmullSlope(int i)
// {
// 	if (xValues[i + 1] == xValues[i - 1]) return 0;
// 	return (yValues[i + 1] - yValues[i - 1]) / (xValues[i + 1] - xValues[i - 1]);
// }

int Interpolation::getIndex(double pointX, int from = 0)
{
	int i = from;
	if (pointX >= xValues[numValues - 1]) return numValues - 1;
	while (pointX >= xValues[i + 1]) i++;
	return i;
}