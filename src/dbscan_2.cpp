#include <bits/stdc++.h>
#include "RTree.h"


using namespace std;

typedef RTree<int, double, 5, double> MyTree;

vector<vector<double> > points;
vector<int> label;
vector<int> radIndices;
int true_dim;
MyTree tree;
double eps;

bool MySearchCallback(int id)
{
	radIndices.push_back(id);
  	return true; // keep going
}
bool valid_dist(int i,int j){
	double dist =0.0;
	for(int ii=0;ii<true_dim;ii++){
		dist += ((points[i][ii]-points[j][ii])*(points[i][ii]-points[j][ii]));
	}
	return (dist<=(eps*eps));
}

void populate_rand(int i,int act_dim){
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


int main(int argc, char **argv){
	ios_base::sync_with_stdio(false); 
    cin.tie(NULL);   
	int min_points = stoi(argv[1]);
	eps = stof(argv[2]);
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
    	true_dim = pt.size();
    	for(int i=true_dim;i<5;i++){
    		pt.push_back(0);
    	}
    	act_dim = pt.size();
    	points.push_back(pt);
    	label.push_back(-1);
	    n+=1;
  	}
  	for(int i=0;i<n;i++){
  		double point_arr[act_dim];
  		for(int j=0;j<act_dim;j++){
  			point_arr[j] = points[i][j];
  		}
  		tree.Insert(point_arr,point_arr,i);
  	}  	
	int cluster_count =0;
	for(int i=0;i<n;i++){
		if(label[i]!=-1)
			continue;

		populate_rand(i, act_dim);
		if(radIndices.size()<min_points){
			label[i] = -2;
			continue;
		}
		cout << "#" << cluster_count <<"\n";
		cout << i << "\n";
		label[i] = cluster_count;
		set <int> seed;
		vector<int> elem;
		for(int j=0;j<radIndices.size();j++){
			if(label[radIndices[j]]<0)
				elem.push_back(radIndices[j]);
		}
		seed.insert(elem.begin(),elem.end());
		while(seed.size()!=0){
			int q = *seed.begin();
			seed.erase(q);
			if(label[q]==-2){
				cout << q <<"\n";
				label[q] = cluster_count;
				continue;
			}
			if(label[q]!=-1)
				continue;
			cout << q <<"\n";
			label[q] = cluster_count;
			populate_rand(q, act_dim);
			if(radIndices.size() >= min_points){
				vector <int> elem2;
				for(int j=0;j<radIndices.size();j++){
					if(label[radIndices[j]]<0)
						elem2.push_back(radIndices[j]);
				}
				seed.insert(elem2.begin(),elem2.end());
			}
		}
		cluster_count +=1;
	}
	int outlier = 0;
	for(int i=0;i<n;i++){
		if(label[i]==-2)
			outlier++;
	}
	if(outlier==0)
		return 0;
	cout << "#outlier\n";
	for(int i=0;i<n;i++){
		if(label[i]==-2)
			cout << i <<"\n";
	}
	return 0;
}

