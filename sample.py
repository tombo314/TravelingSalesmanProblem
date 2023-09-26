from random import seed, shuffle

seed(42)

nodes_num = 20
nodes_x = list(range(nodes_num))
shuffle(nodes_x)

with open(f"in_{nodes_num}.txt", "w") as f:
    f.write(f"{nodes_num}\n")
    for i in range(nodes_num):
        f.write(f"{nodes_x[i]} 0\n")