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

vector<Point> points;
vector<int> label;

int main(int argc, char **argv){
	ios_base::sync_with_stdio(false); 
    cin.tie(NULL);   
	int min_points = stoi(argv[1]);
	double eps = stof(argv[2]);
  	string file_name = argv[3];
  	ifstream f(file_name);
	int act_dim;
  	int n = 0;
  	string line;
  	while(getline(f, line)) {
    	stringstream stream(line);
    	vector<double> pt;
    	while(1) {
      		double pt1;
      		stream >> pt1;
      		pt.push_back(pt1);
      		if(!stream)
        		break;
    	}
    	act_dim = pt.size();
    	Point p;
    	for(int i=0;i<5;i++){
    		p[i] = 0.0;
    	}
    	for(int i=0;i<act_dim;i++){
    		p[i] = pt[i];
    	}
    	points.push_back(p);
    	label.push_back(-1);
	    n+=1;
  	}
	KDTree<Point> kdtree(points,act_dim);
	int cluster_count =0;
	for(int i=0;i<n;i++){
		if(label[i]!=-1)
			continue;
		const vector<int> radIndices = kdtree.radiusSearch(points[i], eps, act_dim);
		if(radIndices.size()<min_points){
			label[i] = 0;
			continue;
		}
		cout << "#" << cluster_count <<"\n";
		label[i] = cluster_count;
		set <int> seed;
		seed.insert(radIndices.begin(),radIndices.end());
		seed.erase(i);
		while(seed.size()!=0){
			int q = *seed.begin();
			seed.erase(q);
			if(label[q]==0){
				cout << q <<"\n";
				label[q] = cluster_count;
				continue;
			}
			if(label[q]!=-1)
				continue;
			cout << q <<"\n";
			label[q] = cluster_count;
			const vector<int> radIndices2 = kdtree.radiusSearch(points[q], eps, act_dim);
			if(radIndices2.size() >= min_points){
				seed.insert(radIndices2.begin(),radIndices2.end());
			}
		}
		cluster_count +=1;
	}
	int outlier = 0;
	for(int i=0;i<n;i++){
		if(label[i]==0)
			outlier++;
	}
	if(outlier==0)
		return 0;
	cout << "#outlier\n";
	for(int i=0;i<n;i++){
		if(label[i]==0)
			cout << i <<"\n";
	}
	return 0;
}

