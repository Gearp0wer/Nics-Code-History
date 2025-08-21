/**
	A driver for the classes Profile and MasonConnect.

	@author 
	@version 
 */
public class Driver2
{
	public static void main(String[] args)
	{
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
     
		//displaying MasonConnect
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
		
		
	} // end main
} // end Driver2

/*
 Creating profiles and the network.
Name: Malcom X
	Status: My name is Malcom.
	Number of friend profiles: 0
Friends:
Name: Fannie-lou  Hamer
	Status: My name is Fannie.
	Number of friend profiles: 0
Friends:
Name: John Brown
	Status: My name is John Brown!
	Number of friend profiles: 0
Friends:
Name: John Lewis
	Status: My name is also John.
	Number of friend profiles: 0
Friends:
-------------------------------------

Creating friendships.

Name: Malcom X
	Status: My name is Malcom.
	Number of friend profiles: 1
Friends:
	Fannie-lou  Hamer

Name: Fannie-lou  Hamer
	Status: My name is Fannie.
	Number of friend profiles: 3
Friends:
	Malcom X
	John Brown
	John Lewis

Name: John Brown
	Status: My name is John Brown!
	Number of friend profiles: 2
Friends:
	Fannie-lou  Hamer
	John Lewis

Name: John Lewis
	Status: My name is also John.
	Number of friend profiles: 2
Friends:
	Fannie-lou  Hamer
	John Brown

-------------------------------------

Changing statuses / names.

Name: Fannie Smith
	Status: Now Mrs. Smith!
	Number of friend profiles: 3
Friends:
	Malcom X
	John Brown
	John Lewis
Name: John Lewis
	Status: Just got married!
	Number of friend profiles: 2
Friends:
	Fannie Smith
	John Brown
-------------------------------------

Checking Friendships .

false
true
false
true
false
false
true
---------------Suggestion----------------------------------
[Name: Malcom X
	Status: My name is Malcom.
	Number of friend profiles: 1
, Name:    
	Status: My name is nameless!
	Number of friend profiles: 2
, Name: 
	Status: 
	Number of friend profiles: 2
]
[Name: 
	Status: 
	Number of friend profiles: 2
, Name:    
	Status: My name is nameless!
	Number of friend profiles: 2
]
---------------Distance----------------------------------
1
3
1
3
-1
-1
2

 */
