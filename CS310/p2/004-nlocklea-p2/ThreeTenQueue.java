import java.util.Queue;

import javax.management.monitor.CounterMonitorMBean;

import java.util.NoSuchElementException;

/**
 * a simple queue based on a ThreeTenList.
 * @param <T> is the generic object (in this case a list) that the class operates on.
 * @author K. Raven Russell and Nicholas Locklear
 */
class ThreeTenQueue<T> extends ThreeTenList<T> implements Queue<T> {
	/**
    * {@inheritDoc}
    */
	@Override
	public boolean add(T input){
		if(input == null){throw new NoSuchElementException();}
		super.add(input);
		return true;
	}

	/**
    * {@inheritDoc}
    */
	@Override
	public boolean offer(T input){
		if(input == null){throw new NoSuchElementException();}
		super.add(input);
		//DoubleNode<T> newNode = new DoubleNode<T>(input);
		//System.out.println("head: " + head.value);
		//System.out.println(counter + " " + get(counter));
		return true;
	}

	/**
    * {@inheritDoc}
    */
	@Override
	public T remove(){
		T exitvalue = super.remove(0);
		return exitvalue;
	}

	/**
    * {@inheritDoc}
    */
	@Override
	public T poll(){
		if(size() == 0){return null;}
		T oldValue = null;
		if(head == null){
			return oldValue;
		}
		else{
			oldValue = super.remove(0);
		}
		//System.out.println(oldValue.toString());
		return oldValue;
	}

	/**
    * {@inheritDoc}
    */
	@Override
	public T element(){
		return head.value;
	}

	/**
    * {@inheritDoc}
    */
	@Override
	public T peek(){
		if(head.value == null){ throw new NoSuchElementException();}
		else{
			return head.value;
		}
	}

	//-------------------------------------------------------------
	// Main Method For Your Testing -- Edit all you want
	//-------------------------------------------------------------

	/**
	 *  A main method for testing.
	 *  Print statements left in for posterity. 
	 *  @param args not used
	 */
	public static void main(String[] args) {
		ThreeTenQueue<Integer> nums = new ThreeTenQueue<>();
		
		nums.offer(2);
		nums.offer(3);
		nums.offer(5);
		
		if (nums.peek() == 2 && nums.size()==3){
			System.out.println("Yay 1");
		}
		
		if (nums.poll() == 2 && nums.poll() == 3 
			&& nums.poll() == 5 && nums.poll() == null){
			System.out.println("Yay 2");			
		}
	}
}