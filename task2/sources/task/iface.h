
#include "../Utils/utils_iface.h"
#include <unordered_set>
#include <list>
#include <iterator>
#include <exception>
/* namespaces import */
using namespace Utils;
using namespace std;
//Debug assert with diagnostic info
#if !defined(GRAPH_ASSERTXD)
# define GRAPH_ASSERTXD(cond, what) ASSERT_XD(cond, "Graph", what)
#endif
// Simple debug assert
#if !defined(GRAPH_ASSERTD)
# define GRAPH_ASSERTD(cond) ASSERT_XD(cond, "Graph", "")
#endif


enum ErrType
{
UNEXP, 
BADDR, 
NOTHING, 
};
namespace Task //< Namespace for the programming task
{

template <class NodeT, class EdgeT> class Graph
{
public:
    typedef UInt32 UId; 
    
    static const UId INVALID_UID = (UId) (-1);
    
    typedef typename list<EdgeT>::iterator edge_iterator_1;
    
    typedef typename list<NodeT>::iterator node_iterator_1;
    
    template <class Param> class new_iterator
    {
            typename list<Param>::iterator iter;
        public:
            new_iterator(const typename list<Param>::iterator &get_it): iter(get_it)
            {}
            new_iterator &operator++()
            {
                ++iter;
                return *this;
            }
            new_iterator &operator--()
            {
                --iter;
                return *this;
            }
            bool operator==(const new_iterator &get_par)
            {
                return iter == get_par.iter;
            }
        
            bool operator!=(const new_iterator &get_par)
            {
                return iter != get_par.iter;
            }
        
            Param &operator* ()
            {
                return *iter;
            }
    };
    
    
    class Error: public exception
    {
        public:
        inline virtual const char *what() const throw() { return "Graph exception happened"; }
        ErrType type;
    };
    
    
    class Node
    {
        friend class Graph;
        
        public:
        
        typedef new_iterator<edge_iterator_1> pred_iterator; // node's predecessor edges 
        typedef new_iterator<edge_iterator_1> succ_iterator; // node's successor edges 

        
        pred_iterator preds_begin();
        
        pred_iterator preds_end();
        
        succ_iterator succs_begin();
        
        succ_iterator succs_end();

        Graph& graph();
        
        UId uid() const;
        

        EdgeT &first_pred();
        
        EdgeT &first_succ();

      
        UInt32 num_preds() const;
    
        UInt32 num_succs() const;
        

        protected:
        
        Node(Graph &g);
        
        virtual ~Node() {};

        private:
        
        Node();

        Node(const Node &n);

        UId id_my;
        
        node_iterator_1 iter;
        
        Graph &_graph;
        
        list<edge_iterator_1> list_of_preds;
        
        list<edge_iterator_1> list_of_succs;

    };
    
    
        class Edge
        {
            friend class Graph;
            
        public:
            NodeT &pred();
            
            NodeT &succ();
            
            Graph &graph();
            
            UId uid() const;
            

        protected:
            
            Edge(NodeT &p, NodeT &s);
            virtual ~Edge() {};

        private:
            
            Edge();
            Edge(const Edge &e);

            UId id_my;
            
            edge_iterator_1 iter;
            
            Graph &_graph;
            
            NodeT &one_of_preds;
            
            NodeT &one_of_succs;
            
            typename list<edge_iterator_1>::iterator this_class_pred_iter;
            typename list<edge_iterator_1>::iterator this_class_succ_iter;

};

            typedef new_iterator<NodeT> node_iterator;
            typedef new_iterator<EdgeT> edge_iterator;

            node_iterator nodes_begin();
    
            node_iterator nodes_end();
    
            edge_iterator edges_begin();
    
            edge_iterator edges_end();

            UInt32 num_nodes() const;

    
            UInt32 num_edges() const;
            

            NodeT &create_node(); // Create a new node and return reference to it
    
            EdgeT &create_edge(NodeT &pred, NodeT &succ); // Create an edge between nodes

            void remove(NodeT &node); // Remove and delete node
            void remove(EdgeT &edge); // Remove and delete edge

            Graph()
            {
                list_of_id.push_back(1);
            }
    
            virtual ~Graph() {}
    
            list<UId> list_of_id;
        private:
    
            list<NodeT> list_of_nodes;
            list<EdgeT> list_of_edges;

};
bool uTest (UnitTest *utest_p);
};
#include "graph_impl.h"