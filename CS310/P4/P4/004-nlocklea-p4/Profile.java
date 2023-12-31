import java.util.ArrayList;

/**
 * This class represents one user profile that will be inserted into a graph.
 * @author Nicholas Locklear
 * @version 1.3
 */


public class Profile {
    /**
     * the name of the profile owner.
     */
    protected String name;
    /**
     * the status of the profile owner.
     */
    protected String status;
    /**
     * an array list of the friends of the profile owner.
     */
    protected ArrayList<Profile> friendProfiles;
    /**
     * Standard constructor, creates an empty profile.
     */
    public Profile(){
        this.name = "";
        this.status = "";
        this.friendProfiles = new ArrayList<>();
    }
    /**
     * An overloaded constructor for if you want to input specific data upon creation.
     * @param name the account holder's name.
     * @param status the status of the account holder.
     * @param friendProfiles the friends of the account holder.
     */
    public Profile( String name, String status, ArrayList<Profile> friendProfiles){
        this.name = name;
        this.status = status;
        this.friendProfiles = friendProfiles;
    }
    /**
     * overloaded constructor for if you just want a profile with a name and status.
     * @param name the account holder's name.
     * @param status the status of the account holder.
     */
    public Profile(String name, String status){
        this.name = name;
        this.status = status;
        this.friendProfiles = new ArrayList<>();
    }
    /**
     * Sets the name of the profile holder.
     * @param firstName the first name.
     * @param lastName the last name.
     */
    public void setName(String firstName, String lastName){
        this.name = firstName + " " + lastName;
    }
    /**
     * Getter method, fetches the account holder's name.
     * @return a string representing the name of the profile owner.
     */
    public String getName(){
        return name;
    }
    /**
     *  A setter, sets the status of the profile to a string.
     * @param status the new status.
     */
    public void setStatus(String status){
        this.status = status;
    }
    /**
     * a getter method for the status.
     * @return a string representing the status.
     */
    public String getStatus(){
        return status;
    }

    @Override
    public String toString(){
        return ("Name: " + name + "\n\tStatus: " + status + "\n\tNumber of friend profiles: " + friendProfiles.size() + "\n");
    }
    /**
     * A display method, for outputting the profile along with their associated friends.
     */
    public void display(){
        System.out.println(toString() + "Friends:");
        if(getFriendProfiles().size() >0){
            for(int i = 0; i < friendProfiles.size(); i++){
                System.out.println(friendProfiles.get(i).getName());
            }
            System.out.println();
        }

    }
    /**
     * a getter method for the arraylist of friends' profiles.
     * @return an array list of profiles.
     */
    public ArrayList<Profile> getFriendProfiles(){
        return friendProfiles;
    }
    /**
     * a method to add a friend to the profile.
     * @param user the friend being added.
     */
    public void addFriend(Profile user){
        friendProfiles.add(user);
    }
    /**
     * A method to remove a friend.
     * @param user the friend being removed.
     * @return the account removed.
     */
    public boolean unFriend(Profile user){
        if(friendProfiles.contains(user) == false || user == null){
            return false;
        }
        friendProfiles.remove(user);
        return true;
    }


}
