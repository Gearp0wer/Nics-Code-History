import java.util.Iterator;
import java.util.List;
import java.util.ArrayList;

/**
 * A vertex representing a point on the graph.
 * @param <T> is the generic, so that any object can be made a vertex.
 * @author Nicholas Locklear
 * @version 1.1
 */

public class Vertex<T> implements VertexInterface<T> {
    /**
     * the label of the point.
     */
    private T label;
    /**
     * whether or not the point was visited.
     */
    private boolean visited;
    /**
     * the previous vertex (used for shortest path).
     */
    private VertexInterface<T> previousVertex;
    /**
     * the cost associated with traveling to this vertex (also used in shortest path).
     */
    private double cost;
    /**
     * a list of all edges connected to this vertex.
     */
    private List<Edge> edgeList;

    /**
     * The constructor.
     * @param vertexLabel is the label being passed in.
     */
    public Vertex(T vertexLabel){
        this.label = vertexLabel;
        this.visited = false;
        this.cost = 0.0;
        this.previousVertex = null;
        this.edgeList = new ArrayList<Edge>();
    }
    /**
     * An inner class representing an edge between vertex points.
     */
    protected class Edge{
        /**
         * the vertex we're connected to.
         */
        private VertexInterface<T> vertex;
        /**
         * the cost associated with traveling to that point.
         */
        private double weight;
        /**
         * Standard constructor.
         * @param endVertex the edge we are traveling to.
         * @param edgeWeight the weight of that edge.
         */
        protected Edge(VertexInterface<T> endVertex, double edgeWeight){
            vertex = endVertex;
            weight = edgeWeight;
        }
        /**
         * an overloaded constructor, for if you just want to input a vertex on an unweighted graph.
         * @param endVertex the vertex we are traveling to.
         */
        protected Edge(VertexInterface<T> endVertex){
            vertex = endVertex;
            weight = 0;
        }
        /**
         * a getter, fetches the end vertex connected to us.
         * @return the vertex we are connected to.
         */
        protected VertexInterface<T> getEndVertex(){
            return vertex;
        }
        /**
         * a getter, fetches the weight of the edge we are connected with.
         * @return a double representing the weight.
         */
        protected double getWeight(){
            return weight;
        }
    }

    /**
     * {@inheritDoc}
     */
    public T getLabel() {
        return this.label;
    }

    /**
     * {@inheritDoc}
     */
    public int getNumberOfNeighbors() {
        ArrayList<VertexInterface<T>> neighbors = new ArrayList<>();
        for (Edge edge : edgeList){
            if(neighbors.contains(edge.getEndVertex()) == false){
                neighbors.add(edge.getEndVertex());
            }
        }
        return neighbors.size();
    }

    /**
     * {@inheritDoc}
     */
    public void visit() {
        visited = true;
    }

    /**
     * {@inheritDoc}
     */
    public void unvisit() {
        visited = false;
    }

    /**
     * {@inheritDoc}
     */
    public boolean isVisited() {
        return visited == true;
    }

    /** 
     * {@inheritDoc}
     */
    public boolean connect(VertexInterface<T> endVertex, double edgeWeight) {
        for (Edge edge : edgeList) { 
            //basically, if the weight and label of the vertex matches a pair already contained in the edgelist
            if (endVertex.getLabel().equals(edge.getEndVertex().getLabel())){
                return false;
            }
        }
        edgeList.add(new Edge(endVertex, edgeWeight));
        
        return true;
    }

    /**
     * {@inheritDoc}
     */
    public boolean connect(VertexInterface<T> endVertex) {
        for (Edge edge : edgeList) { 
            //basically, if the weight and label of the vertex matches a pair already contained in the edgelist
            if (endVertex.getLabel().equals(edge.getEndVertex().getLabel())){
                return false;
            }
        }
        edgeList.add(new Edge(endVertex));
        return true;
    }

    /**
     * {@inheritDoc}
     */
    public boolean disconnect(VertexInterface<T> endVertex, double edgeWeight) {
        boolean check = false;
        int index = 0;
        int i = 0;
        for (Edge edge : edgeList) {
            i += 1;
            if(edge.getEndVertex().getLabel().equals(endVertex.getLabel()) && edgeWeight == edge.weight){
                check = true;
                index = i;
            }
            else{
                continue;
            }
        }
        if(check == true){
            edgeList.remove(i-1);
            return true;
        }
        return false;
    }

    /**
     * {@inheritDoc}
     */
    public boolean disconnect(VertexInterface<T> endVertex) {
        boolean check = false;
        int index = 0;
        int i = 0;
        for (Edge edge : edgeList) {
            i += 1;
            if(edge.getEndVertex().getLabel().equals(endVertex.getLabel())){
                check = true;
                index = i;
            }
            else{
                continue;
            }
        }
        if(check == true){
            edgeList.remove(i-1);
            return true;
        }
        return false;
    }

    /**
     * {@inheritDoc}
     */
    public Iterator<VertexInterface<T>> getNeighborIterator() {
        ArrayList<VertexInterface<T>> neighbors = new ArrayList<>();
        for (Edge edge : edgeList) {
            neighbors.add(edge.getEndVertex());
        }
        Iterator<VertexInterface<T>> neighborIterator = neighbors.iterator();
        return neighborIterator;
    }

    /**
     * {@inheritDoc}
     */
    public Iterator<Double> getWeightIterator() {
        ArrayList<Double> weights = new ArrayList<>();
        for (Edge edge : edgeList) {
            weights.add(edge.getWeight());
        }
        Iterator<Double> weightIterator = weights.iterator();
        return weightIterator;
    }

    /**
     * {@inheritDoc}
     */
    public boolean hasNeighbor() {
        if(edgeList.size() >= 1){
            return true;
        }
        return false;
    }

    /**
     * {@inheritDoc}
     */
    public VertexInterface<T> getUnvisitedNeighbor() {
        for(Edge vertex : edgeList){
            if(vertex.getEndVertex().isVisited() == false){
                return vertex.getEndVertex();
            }
        }
        return null;
    }

    /**
     * {@inheritDoc}
     */
    public void setPredecessor(VertexInterface<T> predecessor) {
        this.previousVertex = predecessor;
    }

    /**
     * {@inheritDoc}
     */
    public VertexInterface<T> getPredecessor() {
        return this.previousVertex;
    }

    /**
     * {@inheritDoc}
     */
    public boolean hasPredecessor() {
        return getPredecessor() == null ? false : true;
    }

    /**
     * {@inheritDoc}
     */
    public void setCost(double newCost) {
        cost = newCost;
    }

    /**
     * {@inheritDoc}
     */
    public double getCost() {
        return cost;
    }

    @Override
    @SuppressWarnings ("unchecked")
    public boolean equals(Object input){
        Vertex<T> newCast =  (Vertex<T>) input;
        if(newCast.getLabel() == label){
            return true;
        }
        else{
            return false;
        }
    }
    /**
     * the main method. tests commented out for clarity.
     * @param args command line arguments.
     */
    public static void main(String[] args) {
        /*
        VertexInterface<String> baseVertex = new Vertex<>("Jesus");
        VertexInterface<String> Matthew = new Vertex<>("Mathew");
        VertexInterface<String> Mark = new Vertex<>("Mark");
        VertexInterface<String> Luke = new Vertex<>("Luke");
        VertexInterface<String> John = new Vertex<>("John");
        if(baseVertex.connect(Matthew) == true){
            System.out.println("Test 1: passed");
        }
        if(baseVertex.connect(Mark) == true){
            System.out.println("Test 2: passed");
        }
        if(baseVertex.connect(Luke) == true){
            System.out.println("Test 3: passed");
        }
        if(baseVertex.connect(John) == true){
            System.out.println("Test 4: passed");
        }
        if(baseVertex.connect(John) == false){
            System.out.println("Test 5: passed");
        }
        if(baseVertex.disconnect(John) == true && baseVertex.getNumberOfNeighbors() == 3){
            System.out.println("Test 6: passed");
        }
        if(Mark.connect(John) == true && baseVertex.getNumberOfNeighbors() == 3 ){
            System.out.println("Test 7: passed");
        }
        if(Mark.getNumberOfNeighbors() == 1){
            System.out.println("Test 8: passed");
        }
        else{
            System.out.println("Mark's neighbors: " + Mark.getNumberOfNeighbors());
            System.out.println("Luke's neighbors: " + Luke.getNumberOfNeighbors());
        }
        */
    }

}
