import java.util.Iterator;
import java.util.List;
import java.util.ArrayList;

import java.util.Queue;

import java.util.LinkedList;
import java.util.HashMap;
import java.util.Stack;
/**
* This class represents the graph of vertices.
* @param <T> is a generic to make sure this graph can hold any type of object.
* @author Nicholas Locklear
* @version 1.4
*
*/
public class Graph<T> implements GraphInterface<T> {
	/** vertices is a map of the label and the vertex pairs.
	 */
	private HashMap<T, Vertex<T>> vertices;
	/**
	 * edges tracks how many total edges there are on the graph.
	 */
	private int edges;
	/**
	 * A standard constructor, intitializes a clean map.
	 */
	public Graph(){
		vertices = new HashMap<T, Vertex<T>>();
	}

	/**
	 * {@inheritDoc}
	 */
	public boolean addVertex(T vertexLabel){
		if(vertexLabel.equals(null)){
			return false;
		}
		if(vertexLabel.equals(vertices.get(vertexLabel))){
			return true;
		}
		else{
			return (vertices.put(vertexLabel, new Vertex<T>(vertexLabel)) == null) ? true : false;

		}
	}

	/**
	 * {@inheritDoc}
	 */
	public VertexInterface<T> removeVertex(T vertexLabel) { //might also want to remove the edges from the vertex
		VertexInterface<T> removal = vertices.remove(vertexLabel);
		return removal;
	}

	/**
	 * {@inheritDoc}
	 * this checks if both the vertices are NOT null (meaning something is there),
	 * then connects the edges to eachother with the weighted amount.
	 * returns false iff a complete weighted connection already existed for both ends.
	 */
	public boolean addEdge(T begin, T end, double edgeWeight) { //might also want to add an edge back the other way
		VertexInterface<T> beginningVertex = vertices.get(begin);
		VertexInterface<T> endingVertex = vertices.get(end);
		edges += 2;
		if(vertices.get(begin) == null || vertices.get(end) == null){
			return false;
		}
		if(hasEdge(begin, end) == true){
			return false;
		}
		boolean check1 = beginningVertex.connect(endingVertex, edgeWeight);
		boolean check2 = endingVertex.connect(beginningVertex, edgeWeight);
		return(check1 || check2 ? true : false);
	}

	/**
	 * {@inheritDoc}
	 * connects the edges to eachother with the weighted amount.
	 * returns false iff a complete weighted connection already existed for both ends.
	 */
	public boolean addEdge(T begin, T end) {
		VertexInterface<T> beginningVertex = vertices.get(begin);
		VertexInterface<T> endingVertex = vertices.get(end);
		edges += 2;
		if(vertices.get(begin) == null || vertices.get(end) == null){
			return false;
		}
		if(hasEdge(begin, end) == true || hasEdge(end, begin) == true){
			return false;
		}
		else{
			boolean check1 = beginningVertex.connect(endingVertex);
			boolean check2 = endingVertex.connect(beginningVertex);
			return (check1 || check2 ? true : false);
		}
	}

	/**
	 * {@inheritDoc}
	 */
	public boolean removeEdge(T begin, T end, double edgeWeight) {
		VertexInterface<T> beginningVertex = vertices.get(begin);
		VertexInterface<T> endingVertex = vertices.get(end);
		edges -= 2;
		if(vertices.get(begin) == null || vertices.get(end) == null){
			return false;
		}
		return(beginningVertex.disconnect(endingVertex, edgeWeight) ||
			endingVertex.disconnect(beginningVertex, edgeWeight) ? true : false);
	}


	/**
	 * {@inheritDoc}
	 */
	public boolean removeEdge(T begin, T end) {
		VertexInterface<T> beginningVertex = vertices.get(begin);
		VertexInterface<T> endingVertex = vertices.get(end);
		edges -= 2;
		if(vertices.get(begin) == null || vertices.get(end) == null){
			return false;
		}
		return(beginningVertex.disconnect(endingVertex) || endingVertex.disconnect(beginningVertex) ? true : false);
	}

	/**
	 * {@inheritDoc}
	 */
	public boolean hasEdge(T begin, T end){
		boolean check1 = false;
		boolean check2 = false;

		if(vertices.get(begin) == null || vertices.get(end) == null) {
			//System.out.println(" beginning[ \n" + begin +  " ] \n");
			return false;
		}

		VertexInterface<T> beginningVertex = vertices.get(begin);
		VertexInterface<T> endingVertex = vertices.get(end);
		Iterator<VertexInterface<T>> beginningIterator = beginningVertex.getNeighborIterator();
		Iterator<VertexInterface<T>> endingIterator = endingVertex.getNeighborIterator();
		//System.out.println("\n\n comparing: \n" + beginningVertex.getLabel().toString() +  "with :\n"
		//+ endingVertex.getLabel().toString() + "\n");

		while(beginningIterator.hasNext()){
			VertexInterface<T> element = beginningIterator.next();
			//System.out.println(element.getLabel().toString());
			if(element.equals(endingVertex)){
				check1 = true;
			}
		}
		while(endingIterator.hasNext()){
			VertexInterface<T> element = endingIterator.next();
			if(element.equals(beginningVertex)){
				check2 = true;
			}
		}
		if(check1 == true || check2 == true){
			return true;
		}
		return false;
	}

	/**
	 * {@inheritDoc}
	 */
	public int getNumberOfVertices() {
		return vertices.size();

	}

	/**
	 * {@inheritDoc}
	 */
	public int getNumberOfEdges() {
		if (edges == 0){
			return 0;
		}
		return edges/2;
	}

	/**
	 * {@inheritDoc}
	 */
	public boolean isEmpty() {
		if(vertices.size() == 0){
			return true;
		}
		return false;
	}

	/**
	 * {@inheritDoc}
	 */
	public List<VertexInterface<T>> getVertices() {
		List<VertexInterface<T>> output = new ArrayList<VertexInterface<T>>(vertices.values());
		return output;
	}

	/**
	 * {@inheritDoc}
	 */
	public void clear() {
		vertices = new HashMap<T, Vertex<T>>();
	}

	/**
	 * {@inheritDoc}
	 */
	public Queue<T> getBreadthFirstTraversal(T origin) {
		Queue<T> queue = new LinkedList<T>();
		Queue<T> finalQueue = new LinkedList<T>();
		if(origin == null || vertices.get(origin) == null){
			return null;
		}
		queue.add(origin);
		finalQueue.add(origin);
		while (queue.size() != 0){
			VertexInterface<T> label = vertices.get(queue.poll());
			label.visit();
			Iterator<VertexInterface<T>> neighborIterator = label.getNeighborIterator();
			while(neighborIterator.hasNext()){
				VertexInterface<T> neighbor = neighborIterator.next();
				if(neighbor.isVisited() == false){
					neighbor.visit();
					queue.add(neighbor.getLabel());
					finalQueue.add(neighbor.getLabel());

				}
			}
		}
		return finalQueue;
	}

	/**
	 * {@inheritDoc}
	 */
	public int getShortestPath(T origin, T destination, Stack<T> path) {
		if(origin.equals(destination)){
			return 0;
		}
		if(vertices.get(origin) == null || vertices.get(destination) == null){
			return -1;
		}
		VertexInterface<T> start = vertices.get(origin);
		VertexInterface<T> end = vertices.get(destination);
		boolean done = false;
		Queue<T> locations = new LinkedList<>();
		start.visit();
		start.setCost(0);
		locations.add(origin);
		while(!done && !locations.isEmpty()){
			VertexInterface<T> front = vertices.get(locations.poll());
			while(!done && front.getUnvisitedNeighbor() != null){
				VertexInterface<T> nextNeighbor = front.getUnvisitedNeighbor();
				if(nextNeighbor.isVisited() == false){
					nextNeighbor.visit();
					nextNeighbor.setCost(front.getCost()+1);
					nextNeighbor.setPredecessor(front);
					locations.add(nextNeighbor.getLabel());
				}
				if(nextNeighbor.equals(end)){
					done = true;
				}
			}
		}
		int pathLength = (int) end.getCost();
		path.push(end.getLabel());
		while(end.getPredecessor() != null){
			path.push(end.getPredecessor().getLabel());
			end = end.getPredecessor();
		}
		return pathLength +1;
	}
	/**
	 * This is the main method, I commented out a bunch of the tests just for clarity's sake.
	 * @param args command line arguments.
	 */
	public static void main(String[] args) {
	/*
		System.out.println("Creating profiles and the network.");
		Graph<Profile> network = new Graph<>();

		Profile malcom = new Profile();
		malcom.setName("Malcom", "X");
		malcom.setStatus("My name is Malcom.");

		Profile fannie = new Profile();
		fannie.setName("Fannie-lou ", "Hamer");
		fannie.setStatus("My name is Fannie.");

		Profile brown = new Profile();
		brown.setName("John", "Brown");
		brown.setStatus("My name is John Brown!");

		Profile lewis = new Profile();
		lewis.setName("John", "Lewis");
		lewis.setStatus("My name is also John.");

		network.addVertex(malcom);
		network.addVertex(fannie);
		network.addVertex(brown);
		network.addVertex(lewis);

		malcom.display();
		fannie.display();
		brown.display();
		lewis.display();

		System.out.println("-------------------------------------\n");
		System.out.println("Creating friendships.\n");

		network.addEdge(malcom, fannie);
		network.addEdge(fannie, brown);
		network.addEdge(lewis, fannie);
		network.addEdge(brown, lewis);

		System.out.println("-------------------------------------\n");
		System.out.println("Checking Friendships .\n");

		Profile friendless1 = new Profile();
		brown.setName(" ", " ");
		brown.setStatus("My name is nameless!");
		System.out.println(network.getVertices().contains(friendless1));
		network.addVertex(friendless1);
		System.out.println(network.getVertices().contains(brown));
		System.out.println(network.hasEdge(friendless1, fannie));
		System.out.println(network.hasEdge(fannie, brown));
		System.out.println(network.hasEdge(malcom, lewis));
		System.out.println(network.hasEdge(friendless1, fannie));
		System.out.println(network.hasEdge(brown, lewis));
*/

		/*
		Graph<String> bible = new Graph<>();
		if(bible.addVertex("Jesus") == true && bible.addVertex("Mathew") == true
		&& bible.addVertex("Mark") == true && bible.addVertex("Luke") == true
		&& bible.addVertex("John") == true && bible.addVertex("Judas") == true){
			System.out.println("Test1: passed");
		}
		if(bible.addVertex("Jesus") == false){
			System.out.println("Test2: passed");
		}
		if(bible.getNumberOfVertices() == 6){
			System.out.println("Test3: passed");
		}
		else{
			System.out.println("Number of Vertices: " + bible.getNumberOfVertices());
		}
		if(bible.isEmpty() == false){
			System.out.println("Test4: passed");
		}
		if(bible.removeVertex("Nic") == null){
			System.out.println("Test5: passed");
		}
		VertexInterface<String> Jimmy = new Vertex<String>("Jimmy");
		bible.addVertex("Jimmy");
		Jimmy = bible.removeVertex("Jimmy");
		if(Jimmy.getLabel().equals("Jimmy")){
			System.out.println("Test6: passed");
		}
		if(bible.addEdge("Jesus", "Mark") == true && bible.addEdge("Jesus", "Mathew", 6.0) == true){
			System.out.println("Test7: passed");
		}
		if(bible.addEdge("Jesus", "Mark", 5.0) == true && bible.addEdge("Jesus", "Luke") == true
		&& bible.addEdge("Luke", "John") == true && bible.addEdge("Noah", "Mark") == false){
			System.out.println("Test8: passed");
		}
		bible.addVertex("Jonathan");
		bible.addVertex("Jameson");
		bible.addEdge("Jesus", "Jameson");
		bible.addEdge("Jameson", "Jonathan", 6.0);
		if(bible.removeEdge("Jameson", "Noah") == false && bible.removeEdge("Jesus", "Jameson") == true &&
		bible.removeEdge("Jameson", "Jonathan", 6.0)){
			System.out.println("Test9: passed");
		}
		if(bible.hasEdge("Jameson", "Jonathan") == false ){
			System.out.println("Test10: passed");
		}
		if(bible.hasEdge("Jesus", "Mark") == true && bible.hasEdge("Mark", "Jesus") == true){
			System.out.println("Test11: passed");
		}
		bible.clear();
		if(bible.addVertex("0") == true && bible.addVertex("1") == true
		&& bible.addVertex("2") == true && bible.addVertex("3") == true
		&& bible.addVertex("4") == true && bible.addVertex("5") == true ){
			System.out.println("Test12: passed");
		}
		if(bible.addEdge("0", "1")&& bible.addEdge("0", "2") && bible.addEdge("1", "3") &&
		 bible.addEdge("1", "4") && bible.addEdge("2", "4") && bible.addEdge("4", "5") && bible.addEdge("3", "5")
		  ){
			System.out.println("Test13: passed");
		}
		System.out.println(bible.getBreadthFirstTraversal("0"));
	}
	*/
	}
}
