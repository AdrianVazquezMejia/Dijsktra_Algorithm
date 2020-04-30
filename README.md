# Dijsktra_Algorithm
Implementing a dijstra's 
shortest path algorithm for a Monte Carlo simulation of a graph.
Dijkstra’s algorithm is the basis for many route calculations and optimizations programs.
# Description
Graph algorithms and graph representation are a critical tool in CS. We want to create a graph as an ADT (Abstract Data Type) 
using C++ classes. The basic problem is to write Dijkstra’s algorithm as a class member function (method in OO speak). 

An edge will have a positive cost that is its distance. Have a procedure that produces a randomly generated
set of edges with positive distances. Assume the graphs are undirected. The random graph procedure should have
edge density as a parameter and distance range as a parameter. So a graph whose density is 0.1 would have 10% of
its edges picked at random and its edge distance would be selected at random from the distance range. The procedure 
should run through all possible undirected edges, say (i,j) and place the edge in the graph if a random probability 
calculation is less than the density.
Compute for a set of randomly generated graphs an average shortest path.
# Installation
Just clone `git clone https://github.com/AdrianVazquezMejia/Dijsktra_Algorithm.git`

This program is developed under Cross GCC compile.

# Credits

**Professor** Ira Pohl, California University.

**Professor** Steven S. Skiena, State University of New York.
 # License
 
 MIT License

Copyright (c) [2020] [Adrian Vazquez]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.


