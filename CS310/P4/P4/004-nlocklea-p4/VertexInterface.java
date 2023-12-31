import java.util.Iterator;

/**
* This class represents the vertex on the graph.
* @param <T> is a generic to make sure this vertex can be any type of object.
* @author Nicholas Locklear
* @version 1.4
*
*/
public interface VertexInterface<T> {

    /**
     * Gets this vertex’s label.
     * @return The vertex label. 
     */
    public T getLabel();

    /**
     * Finds the number of neighbors to the vertex.
     * @return an int representing the number of neighbors.
     */
    public int getNumberOfNeighbors();

    /**
     * Marks a vertex as visited. 
     */
    public void visit();

    /**
     * Marks a vertex as not visited.
     */
    public void unvisit();

    /**
     * Checks if a vertex was visited. 
     * @return a boolean representing the visited/not visited status of the vertex.
     */
    public boolean isVisited();

    /**
     * Connects this vertex and endVertex with a weighted edge.
     * The two vertices cannot be the same, and must not already have this edge between them.
     * Two vertices are equal (same)if their labels are equal (same).
     * @param endVertex The end vertex we connect to. 
     * @param edgeWeight The weight of the edge we use to connect the vertexes. 
     * @return Returns true if the connection is successful, false otherwise.
     */
    public boolean connect(VertexInterface<T> endVertex, double edgeWeight);

    /**
     * Connects this vertex and endVertex with an unweighted edge.
     * The two vertices cannot be the same, and must not already have this edge between them.
     * Two vertices are equal (same)if their labels are equal (same).
     * @param endVertex The end vertex we connect to. 
     * @return Returns true if the connection is successful, false otherwise.
     */
    public boolean connect(VertexInterface<T> endVertex);

    /**
     * Disconnects this vertex from a given vertex with a weighted edge, i.e., removes the edge.
     * The Edge should exist in order to be disconnected.
     * @param endVertex The vertex we are disconnecting from.
     * @param edgeWeight The weight of the edge we are disconnecting.
     * @return Returns true if the disconnection is successful, false otherwise.
     */
    public boolean disconnect(VertexInterface<T> endVertex, double edgeWeight);

    /**
     * Disconnects this vertex from a given vertex with an unewighted edge, i.e., removes the edge.
     * The Edge should exist in order to be disconnected.
     * @param endVertex The vertex we are disconnecting from.
     * @return Returns true if the disconnection is successful, false otherwise.
     */
    public boolean disconnect(VertexInterface<T> endVertex);

    /**
     * creates an iterator of this vertex's neighbors by following all edges that begin at this vertex.
     * @return An iterator of the vertex's neighbors.
     */
    public Iterator<VertexInterface<T>> getNeighborIterator();

    /**
     * creates an iterator of the weights of the edges this vertex's neighbors by following all edges that begin at this vertex.
     * @return An iterator of the vertex's edge weights.
     */
    public Iterator<Double> getWeightIterator();

    /**
     * Sees whether this vertex has at least one neighbor.
     * @return T/F if the boolean has/doesn't have a neighbor. 
     */
    public boolean hasNeighbor();

    /**
     * Gets an unvisited neighbor, if any, of this vertex.
     * @return The unvisited vertex, or null. 
     */
    public VertexInterface<T> getUnvisitedNeighbor();

    /**
     * Records the previous vertex on a path to this vertex.
     * @param predecessor the vertex we are recording. 
     */
    public void setPredecessor(VertexInterface<T> predecessor);

    /**
     * Gets the recorded predecessor of this vertex.
     * @return the predecessor vertex (or null if there is none).
     */
    public VertexInterface<T> getPredecessor();

    /**
     * Sees whether a predecessor was recorded for this vertex.
     * @return T/F if the current vertex has/doesn't have a predecessor vertex.
     */
    public boolean hasPredecessor();

    /**
     * Records the cost of a path to this vertex.
     * @param newCost the cost of the path. 
     */
    public void setCost(double newCost);

    /**
     * Returns the cost of the path.
     * @return the path's cost.
     */
    public double getCost();
}