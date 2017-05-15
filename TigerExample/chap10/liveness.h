
typedef struct L_moveList_ * L_moveList;
struct L_moveList_ {
	G_node src, dst;
	L_moveList tail;
};

L_moveList L_MoveList(G_node, G_node, L_moveList);

struct L_graph{
	G_graph graph;
	L_moveList moves;
};

Temp_temp L_gtemp(G_node);

struct L_graph L_liveness(G_graph);
