#include <stdio.h>
#include "util.h"
#include "symbol.h"
#include "table.h"
#include "temp.h"
#include "graph.h"
#include "assem.h"
#include "flowgraph.h"
#include "liveness.h"

static G_table in, out;
static Temp_tempList allregs; /* i hope fix the blemish */
TAB_table tempMapNode;

static void initLivenessInfo(G_nodeList);
static void livenessAnalyze(G_graph);
static void reqAllRegs(G_nodeList);
static G_graph confilictGraph(G_nodeList);

L_moveList L_MoveList(G_node src, G_node dst, L_moveList tail)
{
	/* the constructor of L_moveList
	 * alloc the same register in move-instr. src <=> dst @1 
	 * L_moveList is a list of @1
	 */
	L_moveList moves = checked_malloc(sizeof(*moves));
	moves->src = src;
	moves->dst = dst;
	moves->tail = tail;
	return moves;
}

struct L_graph L_liveness(G_graph flow)
{
	assert(flow);
	struct L_graph lg;
	livenessAnalyze(flow); /* solution of data-flow */
	G_graph g = confilictGraph(G_nodes(flow));
	//show_graph(g);
	lg.graph = g;
	/* there ignore L_moveList due to dont know how to do */
	return lg;
}

static void initConflictg(G_graph g)
{
	Temp_tempList tl = allregs;
	tempMapNode = TAB_empty();

	for (; tl; tl = tl->tail) {
		G_node n = G_Node(g, tl->head);
		TAB_enter(tempMapNode, tl->head, n);
	}
}

static G_graph confilictGraph(G_nodeList nl)
{
	/* init a graph node-info save temp type
	 * with create a all-regs list
	 * with ctrate a temp -> node table
	 */
	G_graph g = G_Graph();
	reqAllRegs(nl);
	initConflictg(g);
	//show_graph(g);
	for (; nl; nl = nl->tail) {
		/*
		 * get AS_instr-node info
		 * get def-set
		 */
		AS_instr i = (AS_instr)G_nodeInfo(nl->head);
		assert(i);
		Temp_tempList defs = FG_def(nl->head);

		for (; defs; defs = defs->tail) {

			/*
			 * get out-live-set in the AS_instr node
			 */
			Temp_tempList outlives = G_look(out, nl->head);

			for (; outlives; outlives = outlives->tail) { 

				/*
				 * look which node by map temp -> node
				 */
				G_node a = (G_node)TAB_look(tempMapNode, defs->head);
				G_node b = (G_node)TAB_look(tempMapNode, outlives->head);
				/*
				 * only add-edge between 2 diff edges
				 */
				if (a != b) {

					if (i->kind == I_MOVE) {
						Temp_tempList uses = FG_use(nl->head);

						for (; uses; uses = uses->tail){
							G_node c = (G_node)TAB_look(tempMapNode, uses->head);
							if (b != c) G_addEdge(a, b);
						}

					} else if (i->kind == I_OPER || i->kind == I_LABEL) {

						G_addEdge(a, b);

					} else assert(0);
				}
			}
		}
	}
	return g;
}

Temp_temp L_gtemp(G_node n)
{
	return (Temp_temp)G_nodeInfo(n);
}

static Temp_tempList LiveMap(G_node n)
{
	return unionn(TAB_look(in, n), TAB_look(out, n));
}

static void reqAllRegs(G_nodeList nl)
{
	allregs = NULL;
	for (; nl; nl = nl->tail) {
		allregs = unionn(allregs, unionn(FG_def(nl->head), FG_use(nl->head)));
	}
	//printTempList(allregs);
}

/*
 * caculate flow-graph liveness
 * save a static local graph in, out
 * no-return
 */
static void livenessAnalyze(G_graph flow)
{
	assert(flow);
	G_nodeList nll = G_nodes(flow), nl;
	initLivenessInfo(nll);

	bool done;
	do {
		done = TRUE; /* is done flag */
		nl = nll;

		for (; nl; nl = nl->tail) {

			/* save in[n], out[n] */
			Temp_tempList intl =  (Temp_tempList)G_look(in, nl->head);
			Temp_tempList outtl =  (Temp_tempList)G_look(out, nl->head);
			Temp_tempList in1tl = Temp_copyList(intl);
			Temp_tempList out1tl = Temp_copyList(outtl);

			/*
			 * in[n] = use[n] U (out[n] - def[n]) 
			 * equation 1
			 */
			intl = unionn(FG_use(nl->head), except(outtl, FG_def(nl->head)));
			G_enter(in, nl->head, intl); // update in-table

			/*
			 * out[n] = U in[s] {s, s->succ[n]} 
			 * equation 2
			 */
			G_nodeList succ = G_succ(nl->head);

			for (; succ; succ = succ->tail) {
				outtl = unionn(outtl, (Temp_tempList)G_look(in, succ->head));
			}	
			G_enter(out, nl->head, outtl); // update out-table

			/*
			 * repeat until in = in1, out = out1
			 */
			if (!isequalTempList(in1tl, intl) || !isequalTempList(outtl, out1tl)) done = FALSE;
		}
	} while (done == FALSE);
}

static void initLivenessInfo(G_nodeList nl) 
{
	in = G_empty();
	out = G_empty();

	for (; nl; nl = nl->tail) {
		G_enter(in, nl->head, NULL);
		G_enter(out, nl->head, NULL);
	}
}
