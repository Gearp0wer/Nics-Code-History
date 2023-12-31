import java.io.*;
import java.util.*;
import org.junit.*;
import static org.junit.Assert.*;

/**
 *  This is a JUnit test class which verifies you have the correct
 *  output for your AppleOrange program.
 *  
 *  @author K. Raven Russell
 */
public class AppleOrangeTest {
	/**
	 *  These store the output from the program (instead of allowing
	 *  them to go to stdout and stderr).
	 */
	private static ByteArrayOutputStream localOut, localErr;
	
	/**
	 *  These keep track of stdout and stderr so we can put them back
	 *  when we're done comparing the outputs.
	 */
	private static PrintStream sysOut, sysErr;
	
	/**
	 *  This method tracks stdout and stderr for later use.
	 */
	@BeforeClass
	public static void setup() {
		sysOut = System.out;
		sysErr = System.err;
	}

	/**
	 *  Before every test is run, reset the streams to capture stdout/stderr.
	 */
	@Before
	public void setupStreams() {
		localOut = new ByteArrayOutputStream();
		localErr = new ByteArrayOutputStream();
		System.setOut(new PrintStream(localOut));
		System.setErr(new PrintStream(localErr));
	}

	/**
	 *  After every test, restore stdout/stderr.
	 */
	@After
	public void cleanUpStreams() {
		System.setOut(null);
		System.setErr(null);
		System.setOut(sysOut);
		System.setErr(sysErr);
	}
	
	/**
	 *  This is a template for all the tests. It takes the expected output
	 *  for stdout and stderr and the command line arguments to call, then
	 *  compares it to the actual (student generated) output.
	 *  
	 *  @param expectedOut the output we expect to see on stdout
	 *  @param expectedErr the output we expect to see on stderr
	 *  @param mainArgs the string array required by the main program
	 */
	public void runTest(String expectedOut, String expectedErr, String[] mainArgs) {
		//get expected output lines
		String[] expectedOutput = expectedOut.trim().split("\n");
		String[] expectedErrors = expectedErr.split("\n");
		
		//get student output lines
		AppleOrange.main(mainArgs);
		String[] studentOutput = localOut.toString().split("\n");
		String[] studentErrors = localErr.toString().split("\n");
		
		//compare
		assertOutputMatch(expectedOutput, studentOutput);
		assertOutputMatch(expectedErrors, studentErrors);
	}
	
	/**
	 *  This helper method compares each line of the output (for
	 *  multi-line outputs) and gives more helpful feedback then
	 *  just saying they did not match.
	 *  
	 *  @param expected the lines we expect to see
	 *  @param student the lines the student code generated
	 */
	public void assertOutputMatch(String[] expected, String[] student) {
		if(expected.length != student.length) {
			if(student.length == 0) {
				fail("No student output. Expected: \n\"" + String.join("\n", expected) + "\"");
			}
			else if(expected.length == 0) {
				fail("No expected output. Got: \n\"" + String.join("\n", student) + "\"");
			}
			else{
				fail("Extra line or missing line. Expected: \n\"" + String.join("\n", expected) + "\"\nGot:\n\"" + String.join("\n", student) + "\"");
			}
		}
		
		for(int i = 0; i < expected.length; i++) {
			//clean up output a little
			expected[i] = expected[i].replaceAll("\\s","");
			student[i] = student[i].replaceAll("\\s","");
			
			StringBuilder sb1 = new StringBuilder();
			StringBuilder sb2 = new StringBuilder();
			
			//check that the two lines match
			assertTrue("Line " + (i+1) + " incorrect."
				+ "\nExpected:\n"+expected[i]
				+ "\nGot:\n"+student[i],
				student[i].equals(expected[i]));
		}
	}
	
	/**
	 *  Tests for the output for the numbers 1-10.
	 */
	@Test(timeout = 2000)
	public void test1() {
		String expectedOut = "1 2 apple 4 5 apple orange 8 apple 10";
		String expectedErr = "";
		String[] mainArgs = {"10"};
		runTest(expectedOut, expectedErr, mainArgs);
	}
	
	/**
	 *  Tests for the output for the numbers 1-25.
	 */
	@Test(timeout = 2000)
	public void test2() {
		String expectedOut = "1 2 apple 4 5 apple orange 8 apple 10 11 apple 13 orange apple 16 17 apple 19 20 appleorange 22 23 apple 25";
		String expectedErr = "";
		String[] mainArgs = {"25"};
		runTest(expectedOut, expectedErr, mainArgs);
	}
	
	/**
	 *  Tests for the output for the numbers 1-50.
	 */
	@Test(timeout = 2000)
	public void test3() {
		String expectedOut = "1 2 apple 4 5 apple orange 8 apple 10 11 apple 13 orange apple 16 17 apple 19 20 appleorange 22 23 apple 25 26 apple orange 29 apple 31 32 apple 34 orange apple 37 38 apple 40 41 appleorange 43 44 apple 46 47 apple orange 50";
		String expectedErr = "";
		String[] mainArgs = {"50"};
		runTest(expectedOut, expectedErr, mainArgs);
	}
	
	/**
	 *  Tests for the output when no arguments are given.
	 */
	@Test(timeout = 2000)
	public void test4() {
		String expectedOut = "";
		String expectedErr = "One positive number required as a command line argument.\nExample Usage: java AppleOrange [number]";
		String[] mainArgs = {};
		runTest(expectedOut, expectedErr, mainArgs);
	}
	
	/**
	 *  Tests for the output when an invalid number is given.
	 */
	@Test(timeout = 5000)
	public void test5() {
		String expectedOut = "";
		String expectedErr = "One positive number required as a command line argument.\nExample Usage: java AppleOrange [number]";
		String[] mainArgs = {"0"};
		runTest(expectedOut, expectedErr, mainArgs);
	}
	
	/**
	 *  Tests for the output when too many arguments are given.
	 */
	@Test(timeout = 5000)
	public void test6() {
		String expectedOut = "";
		String expectedErr = "One positive number required as a command line argument.\nExample Usage: java AppleOrange [number]";
		String[] mainArgs = {"1","1"};
		runTest(expectedOut, expectedErr, mainArgs);
	}
	
	/**
	 *  Tests for the output when something other than a number is given.
	 */
	@Test(timeout = 5000)
	public void test7() {
		String expectedOut = "";
		String expectedErr = "One positive number required as a command line argument.\nExample Usage: java AppleOrange [number]";
		String[] mainArgs = {"apple"};
		runTest(expectedOut, expectedErr, mainArgs);
	}
	
	/**
	 *  Tests for the output for the numbers 1-100.
	 */
	@Test(timeout = 5000)
	public void test8() {
		String expectedOut = "1 2 apple 4 5 apple orange 8 apple 10 11 apple 13 orange apple 16 17 apple 19 20 appleorange 22 23 apple 25 26 apple orange 29 apple 31 32 apple 34 orange apple 37 38 apple 40 41 appleorange 43 44 apple 46 47 apple orange 50 apple 52 53 apple 55 orange apple 58 59 apple 61 62 appleorange 64 65 apple 67 68 apple orange 71 apple 73 74 apple 76 orange apple 79 80 apple 82 83 appleorange 85 86 apple 88 89 apple orange 92 apple 94 95 apple 97 orange apple 100";
		String expectedErr = "";
		String[] mainArgs = {"100"};
		runTest(expectedOut, expectedErr, mainArgs);
	}
	
	/**
	 *  Main method that runs the tests.
	 *  @param args command line arguments (not used)
	 */
	public static void main(String[] args) {
        org.junit.runner.JUnitCore.main("AppleOrangeTest");
    }
}
