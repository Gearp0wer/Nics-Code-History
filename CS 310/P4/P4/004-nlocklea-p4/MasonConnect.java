import java.util.List;
import java.util.ArrayList;
import java.util.Queue;
import java.util.Stack;

/**
 * MasonConnect is a graph of profiles, which are each vertices. 
 * The class has one class variable, network, which is this graph of profiles. 
 * @author Nicholas Locklear
 * @version 1.4
 */

public class MasonConnect {
    /**
     * This is a graph instance containing profiles of people.
     */
    private Graph<Profile> network;

    /**
     * A constructor for the network. 
     */
    public MasonConnect(){
        this.network = new Graph<Profile>();
    }
    /**
     * This method adds a user to the network.
     * @param profile the user being added as a vertex. 
     */
    public void addUser(Profile profile){

        network.addVertex(profile);
    }
    /**
     * This method removes a user from the network, aka "deleting their account".
     * @param profile the user being removed
     * @return the profile of the user removed (or null if unsucessful);
     */
    public Profile removeUser(Profile profile){
        if(profile == null || network.removeVertex(profile) == null){
            return null;
        }
        return profile;
    }
    /**
     * This method adds an edge between a and b to simulate a "friend" on the network.
     * @param a one of two friends connecting on the network
     * @param b the second of the two friends connecting on the network
     * @return T/F to signify if a connection was established
     */
    public boolean createFriendship(Profile a, Profile b){
        if(a == null || b == null){
            return false;
        }
        
        a.addFriend(b);
        b.addFriend(a);
        return( network.addEdge(a, b) || network.addEdge(b,a));
    }
    
    /**
     * this method removes friendship between the two users. 
     * @param a the first user. 
     * @param b the second user. 
     * @return T/F depending on whether or not it was successful.
     */
    public boolean removeFriendship(Profile a, Profile b){
        if(a == null || b == null){
            return false;
        }
        return( network.removeEdge(a, b) || network.removeEdge(b,a));
    }
    /**
     * This method is basically "hasEdge". It looks for an edge connecting the two users.
     * @param a user #1 on the network.
     * @param b user #2 on the network.
     * @return a boolean to signify if the two users have an edge connecting them.
     */
    public boolean hasFriendship(Profile a, Profile b){
        if(a == null || b == null){
            return false;
        }
        //System.out.println(a.getName() + " with " + b.getName());
        // System.out.println(network.hasEdge(a, b) + " " + network.hasEdge(b, a));
        //System.out.println();
        return(network.hasEdge(a, b) || network.hasEdge(b, a));
    }

    /**
     * This method travels over the network and outputs all users connected to the start + their friends.
     * @param startPoint the start of the traversal. Breadth first. 
     */
    public void traverse(Profile startPoint){
        Queue<Profile> breadthFirst = network.getBreadthFirstTraversal(startPoint);
        while(breadthFirst.size() != 0){
            Profile user = breadthFirst.poll();
            user.display();
        }
    }

    /**
     * This method checks if a profile exists. basically, it adds a vertex.
     *  if the adder returns false, we know it already exists.
     * then, we remove for cleanliness. 
     * @param user the profile we're looking for.
     * @return boolean check representing whether or not the profile exists. 
     */
    public boolean exists(Profile user){
        boolean check = network.addVertex(user);
        if(check == true || user == null){
            network.removeVertex(user);
            return false;
        }
        else{
            
            return true;
        }
    }
    /**
     * this method recommends you friends based on whether or not you have a mutual friend.
     * @param user the friend whose mutuals we are browsing through.
     * @return a list of profiles of people we can recommend.
     */
    public List<Profile> friendSuggestion(Profile user){
        if(user == null || exists(user) == false){
            return null;
        }
        List<Profile> suggestions = new ArrayList<Profile>();
        ArrayList<Profile> neighbors = user.getFriendProfiles();
        if(neighbors.size() == 0){
            return null;
        }
        for (Profile profile : neighbors) {
            for (Profile friend : profile.getFriendProfiles()) {
                if(suggestions.contains(friend) == false && network.hasEdge(user, friend) == false ){
                    suggestions.add(friend);
                }
            }
        }
        return suggestions;
    }
    /**
     * a pathfinding algorithm a la 7 degrees of kevin bacon.
     * it tries to find the cheapest possible path between us and our friend.
     * @param a startpoint
     * @param b endpoint
     * @return the cost of the path separating the two
     */
    public int friendshipDistance(Profile a, Profile b){
        if(a == null || b == null || exists(a) == false || exists(b) == false){
            return -1;
        }
        Stack<Profile> path = new Stack<>();
        return network.getShortestPath(a, b, path);
    }
    /**
     * This is the main method. currently contains a lot of testing, which will be commented out for clarity.
     * @param args Command line arguments. 
     */
    public static void main(String[] args) {
        /*
        System.out.println("Creating profiles and the network.");
		MasonConnect m = new MasonConnect();

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

		m.addUser(malcom);
		m.addUser(fannie);
		m.addUser(brown);
		m.addUser(lewis);
      
		malcom.display();
		fannie.display();
        brown.display();
        lewis.display();

		System.out.println("-------------------------------------\n");
		System.out.println("Creating friendships.\n");

		m.createFriendship(malcom, fannie);
		m.createFriendship(fannie, brown);
		m.createFriendship(lewis, fannie);
		m.createFriendship(brown, lewis);
		m.traverse(malcom);

		System.out.println("-------------------------------------\n");
		System.out.println("Changing statuses / names.\n");
		
		lewis.setStatus("Just got married!");
		fannie.setStatus("Now Mrs. Smith!");
		fannie.setName("Fannie", "Smith");

		fannie.display();
        lewis.display();
       
        System.out.println("-------------------------------------\n");
		System.out.println("Checking Friendships .\n");
		
		Profile friendless1 = new Profile();
		brown.setName(" ", " ");
		brown.setStatus("My name is nameless!");
		System.out.println(m.exists(friendless1));
	    m.addUser(friendless1);
		System.out.println(m.exists(brown));
		System.out.println(m.hasFriendship(friendless1, fannie));
		System.out.println(m.hasFriendship(fannie, brown));
		System.out.println(m.hasFriendship(malcom, lewis));
		System.out.println(m.hasFriendship(friendless1, fannie));
		System.out.println(m.hasFriendship(brown, lewis));

		System.out.println("---------------Suggestion----------------------------------");

		Profile friendless2 = new Profile();
		m.addUser(friendless2);
		m.createFriendship(friendless1, friendless2);
		m.createFriendship(friendless2, lewis);
		System.out.println(m.friendSuggestion(brown));
		System.out.println(m.friendSuggestion(friendless2));

        System.out.println("---------------Distance----------------------------------");

		System.out.println(m.friendshipDistance(fannie,brown));
		//System.out.println(m.exists(brown));
		System.out.println(m.friendshipDistance(fannie,friendless1));
		System.out.println(m.friendshipDistance(fannie,lewis));
		System.out.println(m.friendshipDistance(malcom,friendless2));
	  	m.removeUser(friendless2);
	  	m.removeFriendship( fannie, brown);
		System.out.println(m.friendshipDistance(malcom,friendless1));
		System.out.println(m.friendshipDistance(malcom,friendless2));
		System.out.println(m.friendshipDistance(fannie,brown));
        */
    }
}