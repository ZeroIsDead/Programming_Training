def smaller_subset_sum(arr):
    total_sum = sum(arr)
    n = len(arr)
    half_sum = total_sum // 2

    # Initialize DP table
    dp = [[False] * (half_sum + 1) for _ in range(n + 1)]

    for i in range(n + 1):
        dp[i][0] = True  # sum 0 is always possible

    # Fill DP table
    for i in range(1, n + 1):
        for j in range(1, half_sum + 1):
            if arr[i - 1] <= j:
                dp[i][j] = dp[i - 1][j] or dp[i - 1][j - arr[i - 1]]
            else:
                dp[i][j] = dp[i - 1][j]

    # Find largest j <= total_sum // 2 where dp[n][j] is True
    for j in range(half_sum, -1, -1):
        if dp[n][j]:
            smaller = min(j, total_sum - j)
            return smaller

    return 0  # Edge case: no valid subset found

input("")

arr = list(map(int, input("").split(" ")))
print(smaller_subset_sum(arr))
