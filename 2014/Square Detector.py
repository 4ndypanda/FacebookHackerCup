def main():
    T = int(raw_input())
    for t in range(T):
        N = int(raw_input())
        top, bottom, left, right = N, -1, N, -1
        cnt = 0
        for i in range(N):
            row = raw_input()
            for j in range(N):
                if row[j] == ".":
                    continue
                top = min(top, i)
                bottom = max(bottom, i)
                left = min(left, j)
                right = max(right, j)
                cnt += 1
        side1, side2 = (bottom - top + 1), (right - left + 1)
        expected = side1 * side2 
        print "Case #%d: %s" % (t + 1, "YES" if side1 == side2 and cnt == expected else "NO")


if __name__ == "__main__":
    main()