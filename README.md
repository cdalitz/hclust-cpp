C++ fast hierarchical clustering algorithms
===========================================

This is a simplified C++ interface to the fast implementations of hierarchical
clustering by Daniel Müllner. The original library with interfaces to R and
Python can be found on [danifold.net](http://danifold.net/fastcluster.html)
and is described in:

> Daniel Müllner: ["fastcluster: Fast Hierarchical, Agglomerative Clustering Routines for R and Python."}(http://www.jstatsoft.org/v53/i09/)
> Journal of Statistical Software 53, no. 9, pp. 1-18 (2013)


About
-----

Hierarchical, or agglomerative clustering is a powerful technique for
partitioning a set of observables. In contrast to clustering schemes like
K-means, hierarchical clustering does not require the observables to be
members of a vector space, but it works on a distance matrix and is thus
applicable to arbitrary observables for which a distance metric can be defined.

Daniel Müllner has compared the performance of different hierarchical
clustering algorithms and implemented the fastest of them in C++ with R and
Python interfaces. Whilst these interfaces are described in the R journal
article listed above, direct use of the underlying C++ functions is tricky
and undocumented. To simplify this, I have written a C++ interface that hides
the intricacies of the internal output formats behind a single function
(*hclust_fast*) and provides two simple functions for the actual partitioning
step (*cutree_k and cutree_cdist*). 