C++ fast hierarchical clustering algorithms
===========================================

This is a simplified C++ interface to the fast implementations of hierarchical
clustering by Daniel Müllner. The original library with interfaces to R and
Python can be found on [danifold.net](http://danifold.net/fastcluster.html)
and is described in:

> Daniel Müllner:
> ["fastcluster: Fast Hierarchical, Agglomerative Clustering Routines for R and Python."](http://www.jstatsoft.org/v53/i09/)
> Journal of Statistical Software 53, no. 9, pp. 1-18 (2013)

Daniel Müllner has compared the performance of different hierarchical
clustering algorithms and implemented the fastest of them in C++ with R and
Python interfaces. Whilst these interfaces are described in the above journal
article, direct use of the underlying C++ functions is tricky
and undocumented. To simplify this, I have written a C++ interface that hides
the intricacies of the internal output formats behind a single function
(*hclust_fast*) and provides two simple functions for the actual partitioning
step (*cutree_k* and *cutree_cdist*).


How to call the library
-----------------------

The interface for the basic clustering algorithms requires a condensed
distance matrix, which is the upper triangle (without the diagonal elements)
of the full distance matrix. Here is an example for its construction where *n*
is the number of observables *x*:

    double* distmat = new double[(n*(n-1))/2];
    int k,i,j;
    for (i=k=0; i<n; i++) {
      for (j=i+1; j<n; j++) {
        // compute distance between observables i and j  
        distmat[k] = distance(x[i], x[j]);
        k++;
      }
    }

The actual clustering is done by the function *hclust_fast*, which supports
four methods for defining a cluster distance from individual distances
(see *fastcluster.h* for a description of the methods):

    int* merge = new int[2*(n-1)];
    double* height = new double[n-1];
    hclust_fast(n, distmat, HCLUST_METHOD_SINGLE, merge, height);

*height* is filled with the cluster distance for each step. This can be useful 
for automatically determining the clustering break point, e.g, with the
"elbow method". *merge* contains the dendrogram in the encoding of the R
function *hclust*. Fortunately, you do not need to understand this encoding,
because there are two function for further processing the output:

    int* labels = new int[n];
    // partitioning into nclust clusters
    cutree_k(n, merge, nclust, labels);
    // stop clustering at step with custer distance >= cdist
    cutree_cdist(npoints, merge, height, cdist, labels);

*labels\[i\]* is filled with the cluster label of observable *x\[i\]*.
Cluster labels start at zero. Final note: do not forget to free the memory
after you are done with the variables:

    delete[] distmat;
    delete[] merge;
    delete[] height;
    delete[] labels;


How to compile the library
--------------------------

For using the library, the following source files are needed:

- *fastcluster\_dm.cpp*, *fastcluster\_R\_dm.cpp*  
  This is the original code by Daniel Müllner, which is included by
  *fastcluster.cpp* and therefore need not be compiled to object code

- *fastcluster.[h|cpp]*  
  This is the simplified C++ interface and *fastcluster.cpp* is the only
  file that must be compiled.

A simple demo is implemented in *demo.cpp*, which can be compiled and run with

    make
    ./hclust-demo -m complete lines.csv

It creates two clusters of line segments such that the segment angle between
line segments of different clusters have a maximum (cosine) dissimilarity.
For visualizing the result, plotresult.r can be used as follows
(requires [R](https://r-project.org/) to be installed):

    ./hclust-demo -m complete lines.csv | Rscript plotresult.r


Authors & Copyright
-------------------

- Daniel Müllner, 2011,
  <http://danifold.net>

- Christoph Dalitz, 2018-2020,
  <https://lionel.kr.hs-niederrhein.de/~dalitz/data/hclust/>


License
-------

This code is provided under a BSD-style license.
See the file LICENSE for details.
