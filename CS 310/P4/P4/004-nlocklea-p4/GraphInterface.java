import java.util.List;
import java.util.Queue;
import java.util.Stack;
/**
* This class represents the graph of vertices.
* @param <T> is a generic to make sure this graph can hold any type of object.
* @author Nicholas Locklear
* @version 1.4
*
*/

public interface GraphInterface<T>  {

    /**
     * Adds a given vertex to the graph. 
     * @param vertexLabel the vertex being added.
     * @return If vertexLabel is null, it returns false. Else, true.
     */
    public boolean addVertex(T vertexLabel);

    /**
     * Removes a vertex with the given vertexLabel from this graph.
     * @param vertexLabel the vertex being removed.
     * @return Returns the removed vertex. If vertex does not exist, it will return null.
     */
    public VertexInterface<T> removeVertex(T vertexLabel);

    /**
     * Adds a weighted edge between two given distinct vertices that are currently in this graph.
     * The desired edge must not already be in the graph.
     * @param begin pt. 1 of the edge.
     * @param end pt. 2 of the edge.
     * @param edgeWeight the weight of the edge.
     * @return true if added, false if edge already exists. 
     */
    public boolean addEdge(T begin, T end, double edgeWeight);

    /**
     * Adds an unweighted edge between two given distinct vertices that are currently in this graph.
     * @param begin pt. 1 of the edge.
     * @param end pt. 2 of the edge.
     * @return true if added, false if edge already exists. 
     */
    public boolean addEdge(T begin, T end);

    /**
     * Removes a weighted edge between two given distinct vertices that are currently in this graph.
     * The desired edge must already be in the graph.   
     * @param begin pt. 1 of the edge.
     * @param end pt. 2 of the edge.
     * @param edgeWeight the weight of the edge being removed. 
     * @return true if removed, false if removal failed. 
     */
    public boolean removeEdge(T begin, T end, double edgeWeight);

    /**
     * Removes a weighted edge between two given distinct vertices that are currently in this graph.
     *  The desired edge must already be in the graph.
     * @param begin pt. 1 of the edge.
     * @param end pt. 2 of the edge.
     * @return true if removed, false if removal failed. 
     */
    public boolean removeEdge(T begin, T end);

    /**
     * Sees whether an undirected edge exists between two given vertices.
     * @param begin pt. 1 of the edge.
     * @param end pt. 2 of the edge.
     * @return T/F depending on if the points share/dont share an edge.
     */
    public boolean hasEdge(T begin, T end);

    /**
     * Gives us the number of Vertices being stored in the instance of a graph.
     * @return The number of vertices. 
     */
    public int getNumberOfVertices();

    /**
     * Gives the number of undirected Edges in this graph.
     * @return The number of edges. 
     */
    public int getNumberOfEdges();

    /**
     * Checks if the graph is empty.
     * @return True if empty, false if not.
     */
    public boolean isEmpty();

    /**
     * Gives the list of all vertices in the graph.
     * @return If the graph is empty, it returns null. Else, it returns a list of vertices.
     */
    public List<VertexInterface<T>> getVertices();

    /**
     * Clears the graph.
     */
    public void clear();

    /**
     * Performs a breadth first traversal of the graph. 
     * @param origin The start point of the graph. 
     * @return a queue of the result. 
     */
    public Queue<T> getBreadthFirstTraversal(T origin);

    /**
     * returns the shortest distance between the origin and destination. 
     * If a path does not exist, it returns the maximum integer (to simulate infinity). 
     * @param origin The start point of the path.
     * @param destination The end point of the graph. 
     * @param path A stack representing the path taken. 
     * @return returns an int representing the shortest distance between the points, or the max int (to represent infinity)
     */
    public int getShortestPath(T origin, T destination, Stack<T> path);
}