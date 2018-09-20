#include <bits/stdc++.h>
#include "kdtree.h"


using namespace std;
using namespace kdt;


class Point : public std::array<double, 5>
{
public:
	static const int DIM = 5;
	Point () {}
	Point(double x, double y, double z, double a, double b)
	{ 
		(*this)[0] = x;
		(*this)[1] = y;
		(*this)[2] = z;
		(*this)[3] = a;
		(*this)[4] = b;
	}
};


int main(){
	int n = 100000;
	double eps = 0.1;
	int min_points = 3;
	int act_dim = 2;
	vector<Point> points(n);
	vector<int> label(n);
	for(int i=0;i<n;i++){
		points[i] = Point(i+0.1,i+0.2,0.0,0.0,0.0);
		label[i] = -1;
	}
	KDTree<Point> kdtree(points,act_dim);
	vector<vector<int> >clusters;
	int cluster_count =0;
	for(int i=0;i<n;i++){
		if(label[i]!=-1)
			continue;
		const vector<int> radIndices = kdtree.radiusSearch(points[i], eps, act_dim);
		if(radIndices.size()<min_points){
			label[i] = 0;
			continue;
		}
		label[i] = cluster_count;
		set <int> seed;
		seed.insert(radIndices.begin(),radIndices.end());
		seed.erase(i);
		while(seed.size()!=0){
			int q = *seed.begin();
			seed.erase(q);
			if(label[q]==0)
				label[q] = cluster_count;
			if(label[q]!=-1)
				continue;
			label[q] = cluster_count;
			const vector<int> radIndices2 = kdtree.radiusSearch(points[q], eps, act_dim);
			if(radIndices2.size() >= min_points){
				seed.insert(radIndices2.begin(),radIndices2.end());
			}
		}
		cluster_count +=1;

	}


	return 0;
}

