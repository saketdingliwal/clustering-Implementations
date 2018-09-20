#include <bits/stdc++.h>
#include "kdtree.h"
#define pdi pair<double,int>

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

vector<Point> points;
int act_dim;
int n;
double eps;
int min_points;
vector<int> processed;
vector<double> reachability;
double distance(const Point& p, const Point& q){
	double dist = 0;
	for (size_t i = 0; i <act_dim; i++)
		dist += (p[i] - q[i]) * (p[i] - q[i]);
	return sqrt(dist);
}
double core_dis_fn(int ind, vector<int> &rnn){
	vector <double> dist;
	for(int i=0;i<rnn.size();i++){
		dist.push_back(distance(points[ind],points[rnn[i]]));
	}
	nth_element(dist.begin(),dist.begin()+min_points-1,dist.end());
	return dist[min_points-1];
}
void update(vector<int> &rnn, int ind, set<pdi> &seeds){
	double core_dis = core_dis_fn(ind, rnn);
	for(int i=0;i<rnn.size();i++){
		int o = rnn[i];
		if(processed[o]==0){
			double new_reachability_dist = min(core_dis, distance(points[i],points[o]));
			if(reachability[o]==DBL_MAX){
				reachability[o] = new_reachability_dist;
				seeds.insert(make_pair(new_reachability_dist, o));
			}
			else{
				if(new_reachability_dist < reachability[o]){
					seeds.erase(make_pair(reachability[o], o));
					reachability[o] = new_reachability_dist;
					seeds.insert(make_pair(new_reachability_dist, o));
				}
			}
		}
	}
}



int main(){
	n = 1000000;
	eps = 0.3;
	min_points = 4;
	points.resize(n);
	act_dim = 2;
	processed.resize(n);
	reachability.resize(n);
	for(int i=0;i<n;i++){
		points[i] = Point(i+0.1,i+0.2,0.0,0.0,0.0);
		processed[i] = 0;
		reachability[i] = DBL_MAX;
	}
	KDTree<Point> kdtree(points,act_dim);
	vector <int> order;
	for(int i=0;i<n;i++){
		if(processed[i]==1)
			continue;
		processed[i]=1;
		order.push_back(i);
		vector<int> radIndices = kdtree.radiusSearch(points[i], eps, act_dim);
		if(radIndices.size()>=min_points){
			set<pdi> seeds;
			update(radIndices, i, seeds);
			while(seeds.size()!=0){
				auto itr = seeds.begin();
				int q = itr->second;
				processed[q] = 1;
				order.push_back(q);
				vector<int> radIndices2 = kdtree.radiusSearch(points[q], eps, act_dim);
				if(radIndices2.size()>=min_points){
					update(radIndices2, q, seeds);
				}
			}
		}
	}

	return 0;
}
