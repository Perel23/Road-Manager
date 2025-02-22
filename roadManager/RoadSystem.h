#pragma once
#include <iostream>
#include <stdexcept>
#include <limits>
#include <algorithm>
#include "Road.h"

using namespace std;


class RoadSystem
{
private:
	Road* roadArr;
	Road* roadHeap;

	int heapSize;
	int maxSize;
	bool allocated;

	static int Left(int node) {return 2 * node + 1;}
	static int Right(int node) {return 2 * node + 2;}
	static int Parent(int node) {return (node - 1) / 2;}

	void FixHeap(int node);
	
	bool compare(const Road& a, const Road& b) const;


public:
	RoadSystem(int maxRoads);
	RoadSystem(Road roads[], int n);

	~RoadSystem() {
		delete[] roadArr;
		delete[] roadHeap;
	}
	void init(int m);
	void addBridge(float h, int r);
	void whichRoad(float height);
	void print(int r);
	Road DeleteMax();
};

