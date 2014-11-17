

namespace Task {


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    template <class NodeT, class EdgeT>
    typename Graph<NodeT, EdgeT>::Node::pred_iterator Graph<NodeT, EdgeT>::Node::preds_begin()
        {
            return list_of_preds.begin();
        } // the first pred. edge //



    template <class NodeT, class EdgeT>
    typename Graph<NodeT, EdgeT>::Node::pred_iterator Graph<NodeT, EdgeT>::Node::preds_end()
        {
            return list_of_preds.end();
        } // the end of pred. list //

    template <class NodeT, class EdgeT>
    typename Graph<NodeT, EdgeT>::Node::succ_iterator Graph<NodeT, EdgeT>::Node::succs_begin()
        {
            return list_of_succs.begin();
        } // the first succ. edge //


    template <class NodeT, class EdgeT>
    typename Graph<NodeT, EdgeT>::Node::succ_iterator Graph<NodeT, EdgeT>::Node::succs_end()
        {
            return list_of_succs.end();
        } // the end of succ. list //


	template <class NodeT, class EdgeT>
 	Graph<NodeT, EdgeT>& Graph<NodeT, EdgeT>::Node::graph()
        {
            return _graph;
        } // Get the graph reference //

	template <class NodeT, class EdgeT>
	typename Graph<NodeT, EdgeT>::UId Graph<NodeT, EdgeT>::Node::uid() const
        {
            return id_my;
        } // Get the node's unique id //


	template <class NodeT, class EdgeT>
	UInt32 Graph<NodeT, EdgeT>::Node::num_preds() const
        {
            return list_of_preds.size();
	}

	template <class NodeT, class EdgeT>
        UInt32 Graph<NodeT, EdgeT>::Node::num_succs() const
        {
            return list_of_succs.size();
        }

	template <class NodeT, class EdgeT>
	NodeT &Graph<NodeT, EdgeT>::Edge::pred()
            {
                return one_of_preds;
            } // Get edge predecessor

	template <class NodeT, class EdgeT>
	NodeT &Graph<NodeT, EdgeT>::Edge::succ()
            {
                return one_of_succs;
            } // Get edge successor

	template <class NodeT, class EdgeT>
	Graph<NodeT, EdgeT> &Graph<NodeT, EdgeT>::Edge::graph()
            {
                return _graph;
            } // Get the graph

	template <class NodeT, class EdgeT>
	typename Graph<NodeT, EdgeT>::UId Graph<NodeT, EdgeT>::Edge::uid() const
            {
                return id_my;
            }// Get the edge's unique id

	template <class NodeT, class EdgeT>
	typename Graph<NodeT, EdgeT>::node_iterator Graph<NodeT, EdgeT>::nodes_begin()
            {
                return list_of_nodes.begin();
            } // the first node

	template <class NodeT, class EdgeT>
	typename Graph<NodeT, EdgeT>::node_iterator Graph<NodeT, EdgeT>::nodes_end()
            {
                return list_of_nodes.end();
            } // the nodes' end


	template <class NodeT, class EdgeT>
	typename Graph<NodeT, EdgeT>::edge_iterator Graph<NodeT, EdgeT>::edges_begin()
            {
                return list_of_edges.begin();
            } // the first edge

	template <class NodeT, class EdgeT>
	typename Graph<NodeT, EdgeT>::edge_iterator Graph<NodeT, EdgeT>::edges_end()
            {
                return list_of_edges.end();
            } // the edges' end


	template <class NodeT, class EdgeT>
	UInt32 Graph<NodeT, EdgeT>::num_nodes() const
            {
                return list_of_nodes.size();
            } // Get the number of nodes


	template <class NodeT, class EdgeT>
	UInt32 Graph<NodeT, EdgeT>::num_edges() const
            {
                return list_of_edges.size();
            } // Get the number of edges


    template <class NodeT, class EdgeT> EdgeT &Graph<NodeT, EdgeT>::Node::first_pred()
    {
        if (list_of_preds.size())

            return *list_of_preds.front();
        else {
            Error err;
            err.type = NOTHING;
            throw err;
        }
    }
    
    template <class NodeT, class EdgeT> EdgeT &Graph<NodeT, EdgeT>::Node::first_succ()
    {
        if (list_of_succs.size())
            return *list_of_succs.front();
        else {
            Error err;
            err.type = NOTHING;
            throw err;
        }
    }
    
    
    template <class NodeT, class EdgeT> Graph<NodeT, EdgeT>::Node::Node(Graph<NodeT, EdgeT> &g):
    _graph(g) {
        id_my = g.list_of_id.back();
        
        g.list_of_id.pop_back();
        
        if (g.list_of_id.empty())
            
            g.list_of_id.push_back(id_my + 1);
    }

    
    
    template <class NodeT, class EdgeT> Graph<NodeT, EdgeT>::Edge::Edge(NodeT &p, NodeT &s):
    _graph(p._graph), one_of_preds(p), one_of_succs(s) {
        
        id_my = _graph.list_of_id.back();
        
        _graph.list_of_id.pop_back();
        
        if (_graph.list_of_id.empty())
            
            _graph.list_of_id.push_back(id_my + 1);
    }

    
    
    template <class NodeT, class EdgeT> NodeT &Graph<NodeT, EdgeT>::create_node()
    {
        list_of_nodes.emplace_back(*this);
        
        NodeT &res = list_of_nodes.back();
        
        res.iter = --list_of_nodes.end();
        
        
        return res;
    }
    
    template <class NodeT, class EdgeT> EdgeT &Graph<NodeT, EdgeT>::create_edge(NodeT& pred, NodeT& succ)
    {
        list_of_edges.emplace_back(pred, succ);
        
        EdgeT &res = list_of_edges.back();
        
        res.iter = --list_of_edges.end();
        
        pred.list_of_succs.push_back(res.iter);
        
        succ.list_of_preds.push_back(res.iter);
        
        res.this_class_pred_iter = --pred.list_of_succs.end();
        
        res.this_class_succ_iter = --succ.list_of_preds.end();
        
        return res;
    }
    
    template <class NodeT, class EdgeT> void Graph<NodeT, EdgeT>::remove(NodeT &node)
    {
        
        int num = (int) node.num_preds();
        
        for (int i = 0; i < num; i++)
            
            remove(*node.list_of_preds.front());
        
        for (int i = 0; i < (int) node.num_succs(); i++)
            
            remove(*node.list_of_succs.front());
        
        list_of_id.push_back(node.id_my);
        list_of_nodes.erase(node.iter);
    }
    
    
    template <class NodeT, class EdgeT> void Graph<NodeT, EdgeT>::remove(EdgeT &edge)
    {
        edge.one_of_preds.list_of_succs.erase(edge.this_class_pred_iter);
        edge.one_of_succs.list_of_preds.erase(edge.this_class_succ_iter);
        list_of_id.push_back(edge.id_my);
        list_of_edges.erase(edge.iter);
    }

}; // namespace Task