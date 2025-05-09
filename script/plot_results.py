import matplotlib.pyplot as plt

def plot_results(results_file, analytical_file):
    x_values_results = []
    y_values_results = []

    # Read data from results.txt
    with open(results_file, 'r') as file:
        next(file)  # Skip the header line
        for line in file:
            x, y = map(float, line.split())
            x_values_results.append(x)
            y_values_results.append(y)

    x_values_analytical = []
    y_values_analytical = []

    # Read data from analytical-sol.txt
    with open(analytical_file, 'r') as file:
        next(file)  # Skip the header line
        for line in file:
            x, y = map(float, line.split())
            x_values_analytical.append(x)
            y_values_analytical.append(y)

    # Plot the data
    plt.figure(figsize=(8, 6))
    plt.plot(x_values_analytical, y_values_analytical, marker='', linestyle='--', color='r', label='Analytical Solution')
    plt.plot(x_values_results, y_values_results, marker='o', linestyle='', color='b', label='Simulation Results')  # Results with markers only
    plt.xlabel('x-coordinate (m)')
    plt.ylabel('Temperature (K)')
    plt.title('Temperature Distribution')
    plt.legend()
    plt.grid(True)
    plt.savefig('./validation/temperature_comparison.png')  # Save the plot to the validation directory

if __name__ == "__main__":
    import sys
    if len(sys.argv) != 3:
        print("Usage: python plot_results.py <path_to_results.txt> <path_to_analytical-sol.txt>")
        sys.exit(1)

    results_file = sys.argv[1]
    analytical_file = sys.argv[2]
    plot_results(results_file, analytical_file)
