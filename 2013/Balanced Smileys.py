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
        output.write("Case #%d: %s\n" % (t + 1, isBalanced(s)))
    input.close()
    output.close()

if __name__ == "__main__":
    main()