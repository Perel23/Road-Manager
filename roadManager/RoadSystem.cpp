#include "RoadSystem.h"


RoadSystem::RoadSystem(int maxRoads) : heapSize(0), maxSize(maxRoads), allocated(false) {
	roadArr = new Road[maxRoads];
	roadHeap = new Road[maxRoads];

	for (int i = 0; i < maxSize; ++i) {
		roadArr[i].roadP = &roadHeap[i];
		roadHeap[i].roadP = &roadArr[i];
	}

}

bool RoadSystem::compare(const Road& a, const Road& b) const {
	if (a.bridgeCount == 0 && b.bridgeCount > 0) {
		return true; // Empty road has higher priority
	}
	if (b.bridgeCount == 0 && a.bridgeCount > 0) {
		return false; 
	}
	if (a.minBridgeHeight == b.minBridgeHeight) {
		return a.roadP - roadArr < b.roadP - roadArr;  // Road with lower numerical ID has higher sub-priority 
	}
	return a.minBridgeHeight > b.minBridgeHeight; // Main priority is the highest minimal road height
}

void RoadSystem::FixHeap(int node) {
	int largest = node;
	int left = Left(node);
	int right = Right(node);

	if (left < heapSize && compare(roadHeap[left], roadHeap[largest])) {
		largest = left;
	}
	if (right < heapSize && compare(roadHeap[right], roadHeap[largest])) {
		largest = right;
	}

	if (largest != node) {

		swap(roadHeap[node], roadHeap[largest]);

		roadHeap[node].roadP->roadP = &roadHeap[node];
		roadHeap[largest].roadP->roadP = &roadHeap[largest];
	
		FixHeap(largest);
	}
}


void RoadSystem::init(int m) {
	if (allocated) {
		throw runtime_error("invalid input");
	}
	heapSize = m;
	allocated = true;
}

void RoadSystem::addBridge(float h, int r) {
	if (r < 1 || r > maxSize || h < 0 || !allocated) {
		throw runtime_error("invalid input");
	}

	roadArr[r - 1].AddBridge(h);
	
	roadArr[r - 1].roadP->minBridgeHeight = roadArr[r - 1].minBridgeHeight;
	roadArr[r - 1].roadP->bridgeCount = roadArr[r - 1].bridgeCount;

	
	

	int index = roadArr[r - 1].roadP - roadHeap;
	FixHeap(index);
}

void RoadSystem::whichRoad(float height) {
	if (!allocated) {
		throw runtime_error("invalid input");
	}
	if (heapSize == 0 || roadHeap[0].minBridgeHeight <= height) {
		cout << 0 << endl;
	}
	else {
		cout << roadHeap[0].roadP - roadArr + 1 << endl;
	}
}

void RoadSystem::print(int r) {
	if (r < 1 || r > maxSize || !allocated) {
		throw runtime_error("invalid input");
	}

	Road& road = roadArr[r - 1];
	
	road.printBridges();
}


Road RoadSystem::DeleteMax() {
	if (heapSize < 1) {
		throw runtime_error("Heap is empty, cannot delete max.");
	}

	Road maxRoad = roadHeap[0]; 
	heapSize--;  
	roadHeap[0] = roadHeap[heapSize];  
	roadHeap[0].roadP->roadP = &roadHeap[0]; // Update the bidirectional pointer
	FixHeap(0);  

	return maxRoad;
}


RoadSystem::RoadSystem(Road roads[], int n) {
	heapSize = maxSize = n;
	allocated = false; 

	roadArr = new Road[n];
	roadHeap = new Road[n];

	// Copy roads array into roadArr and establish bidirectional pointers.
	for (int i = 0; i < n; ++i) {
		roadArr[i] = roads[i];
		roadArr[i].roadP = &roadHeap[i];
		roadHeap[i] = roads[i];
		roadHeap[i].roadP = &roadArr[i];
	}

	
	for (int i = n / 2 - 1; i >= 0; i--) {
		FixHeap(i);
	}
}




