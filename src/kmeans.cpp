#include <bits/stdc++.h>
using namespace std;

vector<vector<double> > points;
vector<int> clusters;
vector<vector<double> > centers;

double cal_dist(vector<double> &a,vector<double> &b){
  double num = 0.0;
  for(int i=0;i<a.size();i++)
  {
    num += (a[i]-b[i])*(a[i]-b[i]);
  }
  return num;
}

int find_closest(vector<double> &point)
{
  double min_dist = DBL_MAX;
  int min_cluster = -1;
  for(int i=0;i<centers.size();i++)
  {
    double dist = cal_dist(point,centers[i]);
    if(dist<min_dist)
    {
      min_cluster = i;
      min_dist = dist;
    }
  }
  return min_cluster;
}

int update_cluster()
{
  vector<vector<double> > new_centers;
  for(int i=0;i<centers.size();i++)
  {
    vector<double> ct;
    for(int j=0;j<centers[i].size();j++){
      ct.push_back(0.0);
    }
    new_centers.push_back(ct);
  }

  vector<int> num_pts;
  for(int i=0;i<centers.size();i++)
  {
    num_pts.push_back(0);
  }

  int flag = 0;
  for(int i=0;i<points.size();i++)
  {
    int cl = find_closest(points[i]);
    for(int j=0;j<new_centers[cl].size();j++)
    {
      new_centers[cl][j] = new_centers[cl][j]+points[i][j];
    }
    num_pts[cl] += 1;
    if(clusters[i]!=cl)
      flag = 1;
    clusters[i] = cl;
  }
  for(int i=0;i<centers.size();i++)
  {
    for(int j=0;j<centers[i].size();j++)
    {
      if(num_pts[i]!=0)
        centers[i][j] = new_centers[i][j]/num_pts[i];
    }
  }
  return flag;
}
int main (int argc,char *argv[]) {
  ios_base::sync_with_stdio(false); 
  cin.tie(NULL);   
  string file_name = argv[2];
  ifstream f(file_name);
  int num_pts = 0;
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
    points.push_back(pt);
    clusters.push_back(0);
    num_pts+=1;
  }
  int dim = points[0].size();
  int num_cl = stoi(argv[1]);
  vector <int> samplingIndex;
  for (int i = 0; i < num_pts; i++) { samplingIndex.push_back(i); } 
   srand(50); 
   random_shuffle(samplingIndex.begin(), samplingIndex.end());
  for(int i=0;i<num_cl;i++)
  {
    if(i<num_pts)
      centers.push_back(points[samplingIndex[i]]);
    else{
      vector<double> p;
      p.resize(dim);
      centers.push_back(p);
    }
  }
  while(update_cluster()){}
  vector <int> final[num_cl];
  for(int i=0;i<num_pts;i++){
    final[clusters[i]].push_back(i);
  }
  for(int i=0;i<num_cl;i++){
    if(final[i].size()!=0)
      cout << "#"<<i <<"\n";
    for(int j=0;j<final[i].size();j++){
      cout << final[i][j]<<"\n";
    }
  }

  return 0;
}