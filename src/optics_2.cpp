#include <bits/stdc++.h>
#define pdi pair<double,int>
#include "RTree.h"


using namespace std;

typedef RTree<int, double, 5, double> MyTree;


vector<vector<double> > points;
vector <int> radIndices;
int act_dim;
int n;
double eps;
int min_points;
vector<int> processed;
vector<double> reachability;
MyTree tree;
int true_dim;

double distance(int i, int j){
	double dist = 0;
	for (size_t ii = 0; ii <true_dim; ii++)
		dist += ((points[i][ii] - points[j][ii]) * (points[i][ii] - points[j][ii]));
	return sqrt(dist);
}

bool MySearchCallback(int id)
{
	radIndices.push_back(id);
  	return true; // keep going
}
bool valid_dist(int i,int j){
	return (distance(i,j)<=eps);
}
void populate_rand(int i){
	radIndices.clear();
	double search_min[act_dim];
	double search_max[act_dim];
	for(int j=0;j<true_dim;j++){
		search_min[j] = points[i][j] - eps;
		search_max[j] = points[i][j] + eps;
	}
	for(int j=true_dim;j<act_dim;j++){
		search_min[j] = 0;
		search_max[j] = 0;
	}
	tree.Search(search_min, search_max, MySearchCallback);
	vector<int> circle_rand;
	for(int j=0;j<radIndices.size();j++){
		if(valid_dist(i,radIndices[j]))
			circle_rand.push_back(radIndices[j]);
	}
	radIndices = circle_rand;
}



double core_dis_fn(int ind, vector<int> &rnn){
	vector <double> dist;
	for(int i=0;i<rnn.size();i++){
		dist.push_back(distance(ind,rnn[i]));
	}
	nth_element(dist.begin(),dist.begin()+min_points-1,dist.end());
	return dist[min_points-1];
}

void update(vector<int> &rnn, int ind, set<pdi> &seeds){
	double core_dis = core_dis_fn(ind, rnn);
	for(int i=0;i<rnn.size();i++){
		int o = rnn[i];
		if(processed[o]==0){
			double new_reachability_dist = max(core_dis, distance(ind,o));
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



int main(int argc, char **argv){
	ios_base::sync_with_stdio(false); 
    cin.tie(NULL);   
	min_points = stoi(argv[1]);
	eps = stod(argv[2]);
  	string file_name = argv[3];
  	ifstream f(file_name);
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
    	pt.pop_back();
    	true_dim = pt.size();
    	for(int i=true_dim;i<5;i++){
    		pt.push_back(0);
    	}
    	act_dim = pt.size();
    	points.push_back(pt);
	    n+=1;
  	}
	processed.resize(n);
	reachability.resize(n);
	for(int i=0;i<n;i++){
		processed[i] = 0;
		reachability[i] = DBL_MAX;
		double point_arr[act_dim];
  		for(int j=0;j<act_dim;j++){
  			point_arr[j] = points[i][j];
  		}
  		tree.Insert(point_arr,point_arr,i);
	}
	vector <int> order;
	for(int i=0;i<n;i++){
		if(processed[i]==1)
			continue;
		processed[i]=1;
		order.push_back(i);
		populate_rand(i);
		if(radIndices.size()>=min_points){
			set<pdi> seeds;
			update(radIndices, i, seeds);
			while(seeds.size()!=0){
				auto itr = seeds.begin();
				seeds.erase(itr);
				int q = itr->second;
				processed[q] = 1;
				order.push_back(q);
				populate_rand(q);
				if(radIndices.size()>=min_points){
					update(radIndices, q, seeds);
				}
			}
		}
	}
	double maxx = DBL_MIN;
	for(int i=0;i<n;i++){
		if(reachability[i]!=DBL_MAX)
			maxx = max(maxx,reachability[i]);
	}
	for(int i=0;i<n;i++){
		if(reachability[order[i]]==DBL_MAX)
			cout << 1.5 * maxx <<"\n";
		else
			cout << reachability[order[i]] <<"\n";
	}
	return 0;
}

