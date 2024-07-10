#include <bits/stdc++.h>
using namespace std;

struct SegmentTree {
	int size;
	vector<int> tree;
	SegmentTree() : size(1 << 20) { tree.assign(size * 2, 0); }

	/**
	 * Increase the value at x by value, i.e. a[x] += value
	 */
	void update(int x, int value) {
		x += size;
		tree[x] += value;
		while (x > 0) {
			x /= 2;
			tree[x] = tree[2 * x] + tree[2 * x + 1];
		}
	}

	/**
	 * Binary search on the x coordinates s.t. the maximum number of cows M
	 * in the regions is minimized.
	 * @param other The other horizontally divided region to be searched on
	 * simultaneously
	 * @return int The minimized number of cows based on current north/south
	 * partition
	 */
	int query(SegmentTree &other) {
		// the size of the four regions
		int west_size, east_size, other_west_size, other_east_size;
		west_size = east_size = other_west_size = other_east_size = 0;
		// start with the whole segment tree as our subtree to search
		int mid = 1;
		while (mid < size) {
			int l = mid * 2;
			int r = mid * 2 + 1;
			// add the subtree which minimizes the overall maximum count of cows
			if (max(west_size + tree[l], other_west_size + other.tree[l]) <
			    max(east_size + tree[r], other_east_size + other.tree[r])) {
				mid = r;
				west_size += tree[l];
				other_west_size += other.tree[l];
			} else {
				mid = l;
				east_size += tree[r];
				other_east_size += other.tree[r];
			}
		}

		// Add the last x coordinate either to the west or the east side
		if (max(west_size + tree[mid], other_west_size + other.tree[mid]) <
		    max(east_size + tree[mid], other_east_size + other.tree[mid])) {
			west_size += tree[mid];
			other_west_size += other.tree[mid];
		} else {
			east_size += tree[mid];
			other_east_size += other.tree[mid];
		}

		/*
		 * the M value corresponding to the best west/east partition based on
		 * the current given north/south partitions
		 */
		return max(max(west_size, east_size),
		           max(other_west_size, other_east_size));
	}
};

int main() {
	//freopen("balancing.in", "r", stdin);
	//freopen("balancing.out", "w", stdout);

	int N;
	cin >> N;
	vector<pair<int, int>> cows(N);
	for (pair<int, int> &c : cows) { cin >> c.first >> c.second; }

	// sort after the y coordinates and divide the farm into north and south
	sort(cows.begin(), cows.end(),
	     [&](const pair<int, int> &c1, const pair<int, int> &c2) {
		     return make_pair(c1.second, c1.first) <
		            make_pair(c2.second, c2.first);
	     });

	// north and south store the number of points on the x coordinates
	SegmentTree north;
	SegmentTree south;

	/*
	 * we begin the sweeping line from the bottom, i.e. the whole farm is in the
	 * northern region
	 */
	for (int i = 0; i < N; i++) { north.update(cows[i].first, 1); }

	// the minimum possible number of cows as defined in the problem statement
	int M = N;

	// sweeping from bottom to top
	for (int i = 0; i < N;) {
		// each time, move points on the line from north to south
		int j = i;
		while (j < N && cows[i].second == cows[j].second) {
			north.update(cows[j].first, -1);
			south.update(cows[j].first, 1);
			j++;
		}
		/*
		 * for current partition of north and south, we determine the optimal
		 * partition between west and east by performing a binary search
		 */
		M = min(M, north.query(south));
        cout<<north.query(south)<<" ";
		// move the sweeping line to the next y coordinate of interest
		i = j;
	}

	cout << M << endl;
}