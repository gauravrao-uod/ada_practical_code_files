import matplotlib.pyplot as plt

# Read data
sizes = []
times = []

with open("results.txt", "r") as f:
    next(f)  # skip header line
    for line in f:
        size, t = line.split()
        sizes.append(int(size))
        times.append(float(t))

# Plot
plt.figure(figsize=(8, 5))
plt.plot(sizes, times, marker="o", linestyle="-")
plt.xlabel("Array Size")
plt.ylabel("Time (seconds)")
plt.title("Quick Sort Performance vs Array Size")
plt.grid(True)
plt.tight_layout()
plt.show()
