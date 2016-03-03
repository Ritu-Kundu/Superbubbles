SUPBUB : SuperBubbles
=====================================

SUPBUB is a tool that finds out superbubbles in a directed graph.
Detection method in a DAG is based on the algorithm described in the paper titled
[**Linear-time superbubble identification algorithm**](http://www.sciencedirect.com/science/article/pii/S0304397515009147)
by Ljiljana Brankovica, Costas S. Iliopoulos, Ritu Kundu, Manal Mohamed, Solon P. Pissis, Fatima Vayani

To compile SUPBUB, please follow the instructions given in file INSTALL.

To have an overview of the code-organisation, please read DevelopersNotes.md.


**NOTE:** 
When publishing work that is based on the results from Superbubble please cite:

L. Brankovic, C. S. Iliopoulos, R. Kundu, M. Mohamed, S. P. Pissis, F. Vayani, "Linear-Time Superbubble Identification Algorithm for Genome Assembly", Theoretical Computer Science, 2015.


**Usage of the tool:** 
supbub <options>
with the following options:
- -i, --input-file	<str>	Input file  name.
- -o, --output-file	<str>	Output filename.

 Example:  ./supbub -i ./data/sample.txt -o ./result/sampleOutput.txt

Here, the edges of the graph are given in file "sample.txt" which is in subfolder "data" of current folder. 
SuperBubble will be calculated and result will be written in the file "sampleOutput.txt" in subfolder "result" of current folder.

** Notes **
- Vertices are assumed to be zero-based integers.
- Input file format required:
 * First line gives an inetger representing the number of vertices in the graph. Every line afterwards represents an edge.
 * Edges are delimited by new line, i.e.  one edge on a single line.
 * An edge (say u->v) is represented by two numbers(corresponding to vertices u and v) separated by a space or a tab.
 * For example, a graph with say three vertices and three edges 0->1, 0->2, 1->2 will be required in the following format:
```
3
0 1
0 2
1 2
```
- Output file is in the following format:
 * It writes the number of vertices and number of edges.
 * It also gives the time used for calculation (after input file has been read in memory and before writing the results).
 * After that, it indicates the number of superbubbles found.
 * Then it writes the superbubbles found in the following format:
  + <u, v> where u is entrance vertex of the superbubble and v is the exit vertex.
 * For answering rmq queries, following libraries have been used:
  + [sdsl](https://github.com/simongog/sdsl-lite)
- Solon's [MAW](https://github.com/solonas13/maw) helped as an inspiration for better organization of the code.
