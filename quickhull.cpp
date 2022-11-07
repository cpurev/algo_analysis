// to find convex hull.
#include <bits/stdc++.h>
#include <random>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <vector>
using namespace std;
using namespace std::chrono;

// Convex hull
set<pair<int, int>> hull;

// Find which side point(p) is in from line(p1, p2)
int FindSide(pair<int, int> p1, pair<int, int> p2, pair<int, int> p)
{
	int val = (p.second - p1.second) * (p2.first - p1.first) - (p2.second - p1.second) * (p.first - p1.first);

	if (val > 0)
		return 1;
	if (val < 0)
		return -1;
	return 0;
}

// FindHull
// Checks for maximum distance from point in Sk to line (p1, p2)
// If then recurse with the 2 new line (found point, p1) and (found point, p2)
// else it is part of hull
void FindHull(pair<int, int> Sk[], int n, pair<int, int> p1, pair<int, int> p2, int side)
{
    // Find the farthest point from line p1, p2 in Sk[]
	int ind = -1;
	int max_dist = 0;
	for (int i=0; i<n; i++)
	{
		int temp = abs ((Sk[i].second - p1.second) * (p2.first - p1.first) - (p2.second - p1.second) * (Sk[i].first - p1.first));
		if (FindSide(p1, p2, Sk[i]) == side && temp > max_dist)
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

	// Recurse for the two parts divided by a[ind]
	FindHull(Sk, n, Sk[ind], p1, -FindSide(Sk[ind], p1, p2));
	FindHull(Sk, n, Sk[ind], p2, -FindSide(Sk[ind], p2, p1));
}

// QuickHull
// Given set of points and its array size, print out its convext hull
void QuickHull(pair<int, int> S[], int n)
{
    // Base case
	if (n < 3)
	{
		cout << "Only 3 points\n";
		return;
	}
    
    // Find min and max of x-cordinate
	int min_x = 0, max_x = 0;
	for (int i=1; i<n; i++)
	{
		if (S[i].first < S[min_x].first)
			min_x = i;
		if (S[i].first > S[max_x].first)
			max_x = i;
	}
    
    // Find hull
	FindHull(S, n, S[min_x], S[max_x], 1);
	FindHull(S, n, S[min_x], S[max_x], -1);

	cout << "The points in Convex Hull are:\n";
	for(auto x : hull){
	    cout << "(" << x.first << ", " << x.second << "), ";
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
	QuickHull(a, n);
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
	QuickHull(b, n);
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
	QuickHull(c, n);
	// Get ending timepoint
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "100n time: "  << duration.count() << " microseconds" << endl;
    
	return 0;
}
