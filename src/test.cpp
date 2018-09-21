#include <bits/stdc++.h>


using namespace std;


vector<vector<double> > points;
vector<int> label;
vector<int> radIndices;
int true_dim;
double eps;

double dist(int i,int j){
	double ans=0.0;
	for(int jj=0;jj<5;jj++){
		double anss = ( (points[i][jj] - points[j][jj]) * (points[i][jj] - points[j][jj]) );
		ans = ans + anss;
	}
	return sqrt(ans);
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
  	vector <double> disst;
  	for(int i=0;i<n;i++){
  		disst.push_back(dist(0,i));
  	}  	
  	sort(disst.begin(),disst.end());
  	for(int i=0;i<n;i++){
  		cout << disst[i] <<" ";
  	}
	return 0;
}

