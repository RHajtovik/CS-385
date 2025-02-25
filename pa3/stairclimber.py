def get_ways(n):
    if n <= 0:
        return [[]]
    ways = []
    for i in range(1, 4):
        if n >= i:
            result = get_ways(n - i)
            # Prepending i to all the solutions in result:
            for j in range(len(result)):
                result[j] = [i] + result[j]
            print(result)
            ways += result
    return ways

print(get_ways(5))