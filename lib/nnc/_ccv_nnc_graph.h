/**********************************************************
 * C-based/Cached/Core Computer Vision Library
 * Liu Liu, 2010-02-01
 **********************************************************/

/**********************************************************
 * CCV - Neural Network Collection
 **********************************************************/

#ifndef GUARD_ccv_nnc_graph_internal_h
#define GUARD_ccv_nnc_graph_internal_h

#include "ccv_nnc.h"

typedef struct {
	int input_size;
	int output_size;
	ccv_nnc_tensor_t** inputs;
	ccv_nnc_tensor_t** outputs;
	ccv_array_t* outgoings; // outgoing nodes
	ccv_nnc_cmd_t cmd;
	ccv_nnc_hint_t hint;
	int graph_ref; // Reference to the sub-graph. Starts at 1.
	int wrapped; // Use wrapped inputs / outputs (thus, the inputs and outputs may contain multiview tensor).
	ccv_nnc_tensor_t** unwrapped_inputs; // Unwrapped inputs / outputs (naked ones are wrapped).
	ccv_nnc_tensor_t** unwrapped_outputs;
} ccv_nnc_graph_exec_info_t;

struct ccv_nnc_graph_s {
	ccv_array_t* exec_info; // deferred exec info
	// I think that I can be more explicit about which are sources and which are destinations.
	ccv_array_t* sources;
	ccv_array_t* destinations;
	// Some extra information piggy-back on graph struct.
	ccv_array_t* sub_graphs; // A list of its sub-graphs (for while loop).
	// Why some of these I choose to be flat * array, some of these I choose to be ccv_array_t?
	// for flat * array, these are not going to be modified until next time call ccv_nnc_symbolic_graph_backward
	// for ccv_array_t, we can continue to modify what's inside.
	int cond_eval_size;
	ccv_nnc_graph_exec_t* cond_evals;
	ccv_nnc_graph_while_f while_expr;
	const void* while_data;
	// End of while loop handling.
};

#endif