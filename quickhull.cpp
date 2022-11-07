// to find convex hull.
#include <bits/stdc++.h>
#include <random>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <vector>
using namespace std;
using namespace std::chrono;

// Stores convex hull
set<pair<int, int>> hull;

// Find which side point(p) is in from line(p1, p2)
int findSide(pair<int, int> p1, pair<int, int> p2, pair<int, int> p)
{
	int val = (p.second - p1.second) * (p2.first - p1.first) - (p2.second - p1.second) * (p.first - p1.first);

	if (val > 0)
		return 1;
	if (val < 0)
		return -1;
	return 0;
}

// End points of line L are p1 and p2. side can have value
// 1 or -1 specifying each of the parts made by the line L
void quickHull(pair<int, int> a[], int n, pair<int, int> p1, pair<int, int> p2, int side)
{
    // Find the farthest point from line p1, p2 in a[]
	int ind = -1;
	int max_dist = 0;
	for (int i=0; i<n; i++)
	{
		int temp = abs ((a[i].second - p1.second) * (p2.first - p1.first) - (p2.second - p1.second) * (a[i].first - p1.first));
		if (findSide(p1, p2, a[i]) == side && temp > max_dist)
		{
			ind = i;
			max_dist = temp;
		}
	}

	// If there is no points that are farther away, that is part of convex hull
	if (ind == -1)
	{
		hull.insert(p1);
		hull.insert(p2);
		return;
	}

	// Recur for the two parts divided by a[ind]
	quickHull(a, n, a[ind], p1, -findSide(a[ind], p1, p2));
	quickHull(a, n, a[ind], p2, -findSide(a[ind], p2, p1));
}

void printHull(pair<int, int> a[], int n)
{
    // Base case
	if (n < 3)
	{
		cout << "Convex hull not possible\n";
		return;
	}
    
    // Find min and max of x-cordinate
	int min_x = 0, max_x = 0;
	for (int i=1; i<n; i++)
	{
		if (a[i].first < a[min_x].first)
			min_x = i;
		if (a[i].first > a[max_x].first)
			max_x = i;
	}
    
    // Find hull
	quickHull(a, n, a[min_x], a[max_x], 1);
	quickHull(a, n, a[min_x], a[max_x], -1);

	cout << "The points in Convex Hull are:\n";
	while (!hull.empty())
	{
		cout << "(" <<( *hull.begin()).first << ", "
			<< (*hull.begin()).second << ") ";
		hull.erase(hull.begin());
	}
	cout << endl;
}

// Driver code
int main()
{
	std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> r(1,100); // distribution in range [1, 6]
    
    pair<int, int> a[10];
    for(auto i = 0; i < 10; ++i){
        a[i] = make_pair(r(rng), r(rng));
    }
    
	 // Get starting timepoint
    auto start = high_resolution_clock::now();
	int n = sizeof(a)/sizeof(a[0]);
	printHull(a, n);
	// Get ending timepoint
    auto stop = high_resolution_clock::now();
    
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "10n time: "  << duration.count() << " microseconds" << endl;
    
    pair<int, int> b[100];
    for(auto i = 0; i < 100; ++i){
        b[i] = make_pair(r(rng), r(rng));
    }
    // Get starting timepoint
    start = high_resolution_clock::now();
	n = sizeof(b)/sizeof(b[0]);
	printHull(b, n);
	// Get ending timepoint
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "100n time: "  << duration.count() << " microseconds" << endl;
    
    pair<int, int> c[10000];
    for(auto i = 0; i < 100; ++i){
        c[i] = make_pair(r(rng), r(rng));
    }
    // Get starting timepoint
    start = high_resolution_clock::now();
	n = sizeof(c)/sizeof(c[0]);
	printHull(c, n);
	// Get ending timepoint
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "100n time: "  << duration.count() << " microseconds" << endl;
    
	return 0;
}
