import matplotlib.pyplot as plt
import pandas as pd

# Read into dataframe
data = pd.read_csv("results.txt", sep=" ")

# Plot
plt.figure(figsize=(8,5))
for algo in data["Algorithm"].unique():
    subset = data[data["Algorithm"] == algo]
    plt.plot(subset["Size"], subset["Time"], marker="o", label=algo)

plt.xlabel("Matrix Size (n x n)")
plt.ylabel("Time (seconds)")
plt.title("Matrix Multiplication Performance (Iterative vs Recursive vs Strassen)")
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.show()
