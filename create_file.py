from random import seed, shuffle

seed(42)

nodes_num = 1000
nodes_x = list(range(nodes_num))
shuffle(nodes_x)

with open(f"in/in_{nodes_num}.txt", "w") as f:
    f.write(f"{nodes_num}\n")
    for i in range(nodes_num):
        f.write(f"{nodes_x[i]} 0\n")

with open(f"out/out_{nodes_num}.txt", "w") as f:
    f.write(f"{(nodes_num-1)*2}\n")