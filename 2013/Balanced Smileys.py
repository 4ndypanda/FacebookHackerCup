def balanced(s):
    open, frowny, close, smiley = 0, 0, 0, 0
    possible = True
    for i in range(len(s)):
        if s[i] == '(':
            open += 1
            if i > 0 and s[i - 1] == ':':
                frowny += 1
        elif s[i] == ')':
            close += 1
            if i > 0 and s[i - 1] == ':':
                smiley += 1
        if close - smiley > open:
            return "NO"
        if close - smiley == open:    
            open, frowny, close, smiley = 0, 0, 0, 0
        possible = (open - frowny <= close)
    return "YES" if possible else "NO"
    
def isBalanced(message):
    minOpen = 0
    maxOpen = 0
 
    for i in xrange(len(message)):
        if message[i] == '(':
            maxOpen += 1
            if i == 0 or message[i-1] != ':':
                minOpen += 1
        elif message[i] == ')':
            minOpen = max(0, minOpen-1)
            if i == 0 or message[i-1] != ':':
                maxOpen -= 1
                if maxOpen < 0:
                    break
 
    if maxOpen >= 0 and minOpen == 0:
        return "YES"
    else:
        return "NO"

def main():
    input = open("input.txt", "r")
    output = open("output.txt", "w")
    T = int(input.readline())
    for t in range(T):
        s = input.readline()[:-1]
        output.write("Case #%d: %s\n" % (t + 1, balanced(s)))
        if balanced(s) != isBalanced(s):
            output.write("Difference for Case %d\n" % (t + 1));
    input.close()
    output.close()

if __name__ == "__main__":
    main()