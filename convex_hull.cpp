#include <vector>
#include <set>
#include <tuple>
#include <algorithm>
#include <iostream>
#include <cassert>

using namespace std;

struct point {
    long long x, y;
    point(): x(0), y(0) {}
    point(long long _x, long long _y) : x(_x), y(_y) {}

    point operator+(point other) { return {x + other.x, y + other.y}; }
    point operator-(point other) { return {x - other.x, y - other.y}; }
    bool operator==(point other) { return x == other.x && y == other.y; };
    // Overloading this is necessary to use set<point>. It is not used in the polar sort.
    bool operator<(point other) const { return make_pair(x, y) < make_pair(other.x, other.y); }
};

long long dot (point a, point b) { return a.x*b.x + a.y*b.y; }
long long cross (point a, point b) { return a.x*b.y - a.y*b.x; }

long long sq(point a) {
    return a.x*a.x + a.y*a.y;
}

// Returns:
//   Zero if collinear (in any order)
//   Positive if A -> B -> C is a counter clockwise turn
//   Negative if A -> B -> C is a clockwise turn
long long ccw(point a, point b, point c) {
    return cross(b-a, c-a);
}

bool half(point p) { // True if in blue half
  assert(p.x != 0 || p.y != 0);
  return p.y > 0 || (p.y == 0 && p.x < 0);
}

// General polar sort. Not used.
void polarSort(vector<point> &v) {
  sort(v.begin(), v.end(), [](point a, point b) {
    return make_pair(half(a), 0ll        ) <
           make_pair(half(b), cross(a, b));
  });
}


vector<point> convexHull(vector<point> v) {
    // Find the lowest point
    point o = v[0];
    for(auto p: v) {
        if(p.y != o.y ? p.y < o.y : p.x < o.x) {
            o = p;
        }
    }

    // Remove the first point since polar sorting the origin is ill-defined.
    // I don't think its strictly necessary for this implementation but
    // I don't want to think about it.
    v.erase(find(v.begin(), v.end(), o));

    // Polar sort. The half() check is redundant since everything is in the upper half
    // since o is the lowest point.
    sort(v.begin(), v.end(), [&o](point _a, point _b) {
        point a = _a - o;
        point b = _b - o;
        // Tiebreak by distance, so that collinear points are considered in a sane order.
        return make_tuple(half(a), 0ll, sq(a)) < make_tuple(half(b), cross(a, b), sq(b));
    });

    vector<point> hull;
    hull.push_back(o);
    for(auto p: v) {
        // Pop if the three points are clockwise or collinear
        while(hull.size() >= 2 && ccw(hull[hull.size()-2], hull[hull.size()-1], p) <= 0) {
            hull.pop_back();
        }
        hull.push_back(p);
    }

    return hull;
}

int main () {
    int N;
    while(1) {
        cin >> N;
        if(N == 0) {
            return 0;
        }
        vector<point> v;
        set<point> seen;
        for(int i = 0; i < N; i++) {
            point p;
            cin >> p.x >> p.y;
            if(seen.find(p) == seen.end()) {
                seen.insert(p);
                v.push_back(p);
            }
        }
        auto hull = convexHull(v);
        cout << hull.size() << "\n";
        for(auto p: hull) {
            cout << p.x << " " << p.y << "\n";
        }
    }
}
