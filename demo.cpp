//
// Demonstration program for hierarchical clustering
// with fastcluster by Daniel Muellner
//
// Line segments are clustered in two directions
//
// Author: Christoph Dalitz, 2018
//

#include <math.h>
#include <string.h>

#include <string>
#include <vector>
#include <stdio.h>
#include <algorithm>

#include "fastcluster.h"


// 2D point or vector
class Point {
public:
  double x;
  double y;
  Point(double xx=0.0, double yy=0.0) { x=xx; y=yy; }
  Point(const Point& p) { x=p.x; y=p.y; }
  double norm() { return(sqrt(x*x + y*y)); }
};

// line segment
class Segment {
public:
  Point p1;
  Point p2;
  Point dir;
  Segment(const Point p, const Point q) { p1=p, p2=q; dir=direction(); }
  Segment(const Segment& s) { p1=s.p1, p2=s.p2; dir=direction(); }
private:
  Point direction() {
    Point d(p2.x-p1.x, p2.y-p1.y);
    double n = d.norm();
    if (n > 0.0) {
      d.x /= n; d.y /= n;
    }
    return d;
  }
};

// line segment distance (cosine dissimilarity)
double distance(const Segment& s1, const Segment& s2) {
  double sprod = s1.dir.x*s2.dir.x + s1.dir.y*s2.dir.y;
  double d = 1 - sprod*sprod;
  if (d < 0.0)
    return 0;
  else
    return d;
}


// main program
int main(int argc, char** argv)
{

  int i,j,k,npoints;

  // parse command line
  std::string opt_infile;
  int opt_method = HCLUST_METHOD_SINGLE;
  const char* usagemsg = "Usage: hclust-demo <infile> [-m (single|complete|average|median)]\n";
  for (i=1; i<argc; i++) {
    if (0 == strcmp(argv[i], "-m")) {
      i++;
      if (i<argc) {
        if (0 == strcmp(argv[i], "single"))
            opt_method = HCLUST_METHOD_SINGLE;
        else if (0 == strcmp(argv[i], "complete"))
            opt_method = HCLUST_METHOD_COMPLETE;
        else if (0 == strcmp(argv[i], "average"))
            opt_method = HCLUST_METHOD_AVERAGE;
        else if (0 == strcmp(argv[i], "median"))
            opt_method = HCLUST_METHOD_MEDIAN;
        else {
          fputs(usagemsg, stderr);
          return 1;
        }
      } else {
        fputs(usagemsg, stderr);
        return 1;
      }
    }
    else if (argv[i][0] == '-') {
      fputs(usagemsg, stderr);
      return 1;
    }
    else {
      opt_infile = argv[i];
    }
  }
  if (opt_infile == "") {
    fputs(usagemsg, stderr);
    return 1;
  }
  
  // read line segments from input file
  std::vector<Segment> segs;
  double x1,x2,y1,y2;
  FILE* f = fopen(opt_infile.c_str(), "r");
  if (!f) {
    fprintf(stderr, "Cannot open '%s'\n", opt_infile.c_str());
    return 2;
  }
  npoints = 0;
  while (!feof(f)) {
    npoints++;
    k = fscanf(f, "%lf,%lf,%lf,%lf\n", &x1, &x2, &y1, &y2);
    if (k != 4) {
      fprintf(stderr, "Error in line %i of '%s': wrong format\n", npoints, argv[1]);
      return 3;
    }
    segs.push_back(Segment(Point(x1,x2), Point(y1,y2)));
  }
  fclose(f);

  // computation of condensed distance matrix
  double* distmat = new double[(npoints*(npoints-1))/2];
  k = 0;
  for (i=0; i<npoints; i++) {
    for (j=i+1; j<npoints; j++) {
      distmat[k] = distance(segs[i], segs[j]);
      k++;
    }
  }

  // clustering call
  int* merge = new int[2*(npoints-1)];
  double* height = new double[npoints-1];
  hclust_fast(npoints, distmat, opt_method, merge, height);

  int* labels = new int[npoints];
  cutree_k(npoints, merge, 2, labels);
  //cutree_cdist(npoints, merge, height, 0.5, labels);
  
  // print result
  for (i=0; i<npoints; i++) {
    printf("%3.2f,%3.2f,%3.2f,%3.2f,%i\n",
           segs[i].p1.x, segs[i].p1.y, segs[i].p2.x, segs[i].p2.y, labels[i]);
  }
  
  // clean up
  delete[] distmat;
  delete[] merge;
  delete[] height;
  delete[] labels;

  
  return 0;
}
