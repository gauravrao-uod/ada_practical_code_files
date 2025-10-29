import matplotlib.pyplot as plt

# Read data
sizes = []
times = []

with open("fib_memo_results.txt", "r") as f:
    next(f)  # skip header line
    for line in f:
        size, t = line.split()
        sizes.append(int(size))
        times.append(float(t))

# Plot
plt.figure(figsize=(8, 5))
plt.plot(sizes, times, marker="o", linestyle="-")
plt.xlabel("Size")
plt.ylabel("Time (seconds)")
plt.title("Memo Fib vs time (in secs)")
plt.grid(True)
plt.tight_layout()
plt.show()
