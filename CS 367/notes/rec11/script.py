import subprocess

progname = "./rec11"

def ensure_built():
    makey = subprocess.getoutput("make")
    print("calling make... ", end="", flush=True)
    if "Error" in makey:
        print(makey)
        print("\n\nfailed to make; not running any tests.")
        exit()
    print("\tcode built.")

def call_it(*args):
    return subprocess.getoutput(progname + " " + " ".join(args))

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
    # the exact arguments we'd pass to ./rec11.
    tests = [
        (  "1", "checkeq",  '0',  '0'),
        (  "0", "checkeq",  '0',  '1'),
        (  "0", "checkeq",  '1',  '0'),
        (  "1", "checkeq",  '1',  '1'),
        (  "0", "checkeq",  '3',  '1'),
        (  "0", "checkeq",  '1',  '3'),
        (  "1", "checkeq",  '3',  '3'),
        (  "0", "checkeq", '-2',  '1'),
        (  "1", "checkeq", '-4', '-4'),
        
        (  "1", "power", '1',  '1'),
        (  "1", "power", '1', '10'),
        (  "1", "power", '10', '0'),
        (  "2", "power", '2',  '1'),
        (  "4", "power", '2',  '2'),
        (  "8", "power", '2',  '3'),
        ("512", "power", '2',  '9'),
        (  "9", "power", '3',  '2'),
        ( "81", "power", '3',  '4'),
        
        ("0", "countPos",  "0"),
        ("1", "countPos",  "1"),
        ("1", "countPos",  "2"),
        ("2", "countPos",  "3", "4"),
        ("2", "countPos",  "5", "0", "6"),
        ("3", "countPos",  "7", "1", "2"),
        ("1", "countPos", "16", "-1"),
        ("2", "countPos", "18", "-2", "1", "0"),
        ("4", "countPos", "1", "3", "-2", "4", "6", "-3", "0"),
        
        (  '1', "middleSum", '0', '1'),
        (  '3', "middleSum", '1', '2'),
        (  '2', "middleSum", '2', '2'),
        ( '18', "middleSum", '3', '6'),
        ( '15', "middleSum", '1', '5'),
        
        (   '1', "collatzLength", '1'),
        (   '3', "collatzLength", '4'),
        (   '6', "collatzLength", '5'),
        (  '17', "collatzLength", '7'),
        (   '4', "collatzLength", '8'),
        (  '20', "collatzLength", '9'),
        (   '7', "collatzLength", '10'),
        (  '26', "collatzLength", '100'),
        (  '12', "collatzLength", '2048'),
        
        ]    
    
    tally = 0
    for test in tests:
        tally += score(*test)
    
    print("\n\nscore: %s/%s" % (tally,len(tests)))

if __name__=="__main__":
    main()
