/*
 * graph.c - Functions to manipulate and create control flow and
 *           interference graphs.
 */

#include <stdio.h>
#include "util.h"
#include "symbol.h"
#include "temp.h"
#include "tree.h"
#include "absyn.h"
#include "assem.h"
#include "frame.h"
#include "graph.h"
#include "errormsg.h"
#include "table.h"

struct G_graph_ { /* digraph */
    int nodecount;
    G_nodeList mynodes; /* the node-list point the head */
    G_nodeList mylast;  /* the node-list point the tail */
};

struct G_node_ {
  G_graph mygraph;
  int mykey; /*this node is order-x add graph*/
  G_nodeList succs; 
  G_nodeList preds; 
  void *info; /* additional info */
};

G_graph G_Graph(void) /* create empty digraph */
{G_graph g = (G_graph) checked_malloc(sizeof *g);
 g->nodecount = 0;
 g->mynodes = NULL; /* a node-list I point to */
 g->mylast = NULL;  /* a node-list point to Me*/
 return g;
}

G_nodeList G_NodeList(G_node head, G_nodeList tail)
{G_nodeList n = (G_nodeList) checked_malloc(sizeof *n);
 n->head=head;
 n->tail=tail;
 return n;
}

/* generic creation of G_node */
G_node G_Node(G_graph g, void *info)
{assert(g && "graphg is NULL");
 G_node n = (G_node)checked_malloc(sizeof *n);
 G_nodeList p = G_NodeList(n, NULL);
 n->mygraph=g;
 n->mykey=g->nodecount++;

 if (g->mylast==NULL) g->mynodes=g->mylast=p;
 else g->mylast = g->mylast->tail = p;

 n->succs=NULL;
 n->preds=NULL;
 n->info=info;
 return n;
}

G_nodeList G_nodes(G_graph g)
{
  assert(g);
  return g->mynodes;
} 

/* return true if a is in l list */
bool G_inNodeList(G_node a, G_nodeList l) {
  G_nodeList p;
  for(p=l; p!=NULL; p=p->tail)
    if (p->head==a) return TRUE;
  return FALSE;
}

void G_addEdge(G_node from, G_node to) 
{ /* create a diedge like `from -> to` */
  assert(from && "invalid node");  assert(to);
  assert(from->mygraph == to->mygraph && "nodes's graph unmatched");
  if (G_goesTo(from, to)) return;
  to->preds=G_NodeList(from, to->preds);
  from->succs=G_NodeList(to, from->succs);
}

static G_nodeList delete(G_node a, G_nodeList l) {
  /* assis function of rmEdge */
  assert(a && l);
  if (a==l->head) return l->tail;
  else return G_NodeList(l->head, delete(a, l->tail)); /* re-create node-list, waste space*/
}

void G_rmEdge(G_node from, G_node to) {
  /* delete the edge from->to */
  assert(from && to);
  to->preds=delete(from,to->preds);
  from->succs=delete(to,from->succs);
}

G_nodeList G_succ(G_node n) { assert(n); return n->succs; }

G_nodeList G_pred(G_node n) { assert(n); return n->preds; }

bool G_goesTo(G_node from, G_node n) {
  return G_inNodeList(n, G_succ(from));
}

/* return length of predecessor list for node n */
static int inDegree(G_node n)
{ int deg = 0;
  G_nodeList p;
  for(p=G_pred(n); p!=NULL; p=p->tail) deg++;
  return deg;
}

/* return length of successor list for node n */
static int outDegree(G_node n)
{ int deg = 0;
  G_nodeList p; 
  for(p=G_succ(n); p!=NULL; p=p->tail) deg++;
  return deg;
}

int G_degree(G_node n) {return inDegree(n)+outDegree(n);}

/* put list b at the back of list a and return the concatenated list */
static G_nodeList cat(G_nodeList a, G_nodeList b) {
  if (a==NULL) return b;
  else return G_NodeList(a->head, cat(a->tail, b));
}

/* create the adjacency list for node n by combining the successor and 
 * predecessor lists of node n like `G_adj(m) = G_succ(m) U G_pred(m)` */
G_nodeList G_adj(G_node n) { return cat(G_succ(n), G_pred(n)); }

void * G_nodeInfo(G_node n) { return n->info; }



/* G_node table functions */

G_table G_empty(void) {
  return TAB_empty();
}

void G_enter(G_table t, G_node node, void *value)
{
  TAB_enter(t, node, value);
}

void *G_look(G_table t, G_node node)
{
  return TAB_look(t, node);
}

void printtemp(void * temp) { Temp_temp t = (Temp_temp) temp; printf("temp: %d\n", Temp_tempint(t)); }

 /**
  * Print a human-readable dump for debug.
  */
void G_show(FILE *out, G_nodeList p, void showInfo(void *)) {
  for (; p; p=p->tail) {
    G_node n = p->head;
    G_nodeList q;
    assert(n);
	
	
    fprintf(out, "(%d)->succ: ", n->mykey); 
    for(q=G_succ(n); q; q=q->tail) fprintf(out, "%d ", q->head->mykey);
	fprintf(out, "\n(%d)->pred: ", n->mykey);
	for(q=G_pred(n); q; q=q->tail) fprintf(out, "%d ", q->head->mykey);
    fprintf(out, "\nNodeInfo: ");	
    if (showInfo) showInfo(n->info);
    fprintf(out, "\n");
  }
}

/* user add */
void show_graph(G_graph g) 
{
	assert(g);
	G_show(stdout, g->mynodes, printtemp);
} 

