import subprocess

progname = "./rec12"

def ensure_built():
    makey = subprocess.getoutput("make")
    print("calling make... ", end="", flush=True)
    if "Error" in makey:
        print(makey)
        print("\n\nfailed to make; not running any tests.")
        exit()
    print("\tcode built.")

def call_it(*args):
    #return subprocess.getoutput(progname + " " + " ".join(args))
  try:
    return subprocess.check_output(progname + " " + " ".join(args),timeout = 3, shell=True).decode("utf-8")[:-1]
  except subprocess.TimeoutExpired:
    return "timed out!"


def score(ans,*args):
    got = call_it(*args)
    if ans==got:
        print(".",end="",flush=True)
        return 1
    print("\nERROR:\t %s %s\n\texpected: %s\n\tgot:      %s" % (progname, " ".join(args),ans,got))
    return 0

def main():
    ensure_built()
    
    # each test has the expected answer first, then
    # the exact arguments we'd pass to ./rec12.
    tests = [
        ( "20", "call_dot4"),
        (  "8", "dot4", "1", "1", "1", "1", "2", "2", "2", "2"),
        ("360", "dot4", "2", "1", "4", "5", "10", "20", "30", "40"),

        (   "120", "call_scale"),
        ( "8, 16", "scale", "4", "8", "2"),
        ("21, 27", "scale", "7", "9", "3"),
        
        ( "4", "call_sum", "0", "0"),
        ( "6", "call_sum", "1", "2"),
        ("10", "call_sum", "1", "3"),
        ( "8", "call_sum", "2", "2"),
        ("22", "call_sum", "3", "4"),
        ("22", "call_sum", "4", "3"),

        ( "1", "pow2", "0"),
        ( "2", "pow2", "1"),
        ( "4", "pow2", "2"),
        ( "8", "pow2", "3"),
        ("16", "pow2", "4"),
        ("32", "pow2", "5"),

        ( "0", "rec_fib", "0"),
        ( "1", "rec_fib", "1"),
        ( "1", "rec_fib", "2"),
        ( "5", "rec_fib", '5'),
        ( "8", "rec_fib", '6'),
        ("34", "rec_fib", '9'),
        
        ]    
    
    tally = 0
    for test in tests:
        tally += score(*test)
    
    print("\n\nscore: %s/%s" % (tally,len(tests)))

if __name__=="__main__":
    main()
