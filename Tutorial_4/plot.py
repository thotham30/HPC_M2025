import matplotlib.pyplot as plt

sizes = [50,100, 200, 300, 500, 900, 1000, 1200, 2400, 3000, 10000]

exe_seq     = [0.002000, 0.003000, 0.003500, 0.004000, 0.005000, 0.089000, 0.275000, 1.460000, 4.655000, 19.348733]

omp_1d_8threads = [0.002000, 0.003000, 0.003100, 0.00280009, 0.005000, 0.01998690, 0.09953001, 0.5009000, 1.86299982, 11.235784]

omp_1d_16threads = [0.002000, 0.002700, 0.002700, 0.00280009, 0.005900, 0.01098690, 0.09600001, 0.41900015, 0.86299982, 9.15100002]

omp_2d_8threads = [0, 0, 0, 0, 0.003549454, 0.0645405, 0.20124432, 0.9032455, 0.9934044, 12.3546965]

omp_2d_16threads = [0, 0, 0, 0.00154950, 0.00254020, 0.0403557, 0.2854595, 0.7502455, 0.8934044, 8.3546965]

# Plotting
plt.figure(figsize=(20, 10))
plt.plot(sizes, exe_seq, marker='o', label="Sequential")
plt.plot(sizes, omp_1d_8threads, marker='o', label="OpenMP - 1d - 8 threads")
plt.plot(sizes, omp_1d_16threads, marker='o', label="OpenMP - 1d - 16 threads")
plt.plot(sizes, omp_2d_8threads, marker='o', label="OpenMP - 2d - 8 threads")
plt.plot(sizes, omp_2d_16threads, marker='o', label="OpenMP - 2d - 16 threads")


plt.xlabel("Input Size")
plt.ylabel("Execution Time (seconds)")
plt.title("Execution Time vs Input Size for Different Thread Counts")
plt.legend()
plt.grid(True)
plt.yscale("log")  
plt.show()