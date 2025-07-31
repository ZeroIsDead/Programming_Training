# Input the text as a single string
import ast
input_text = input()  # Example: "shock;979;23"

from collections import deque

def shortest_path(grid):

    if not grid or grid[0][0] == 1 or grid[-1][-1] == 1:
        return -1  # If start or end is blocked
    
    rows, cols = len(grid), len(grid[0])
    directions = [(-1,0), (1,0), (0,-1), (0,1)]  # Up, Down, Left, Right
    queue = deque([(0, 0, 1)])  # (row, col, path_length)
    visited = set()
    visited.add((0, 0))

    while queue:
        r, c, length = queue.popleft()
        print(r, c, grid[r][c])
        # If we reach the bottom-right corner
        if grid[r][c] == 'E':
            return length

        for dr, dc in directions:
            nr, nc = r + dr, c + dc
            if 0 <= nr < rows and 0 <= nc < cols and grid[nr][nc] != 1 and (nr, nc) not in visited:
                queue.append((nr, nc, length + 1))
                visited.add((nr, nc))

    return -1  # No path found


c = ast.literal_eval(input_text)
print(shortest_path(c))
