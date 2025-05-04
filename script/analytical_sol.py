def calculate_analytical_solution(output_file, num_points=101):
    x_values = [i / (num_points - 1) for i in range(num_points)]  # Generate x values in [0, 1]
    y_values = [100 * (1 - x) + 273 for x in x_values]  # analytical solution of 2D steady-state heat conduction equation for a a simple case

    # Write x and y values to the output file
    with open(output_file, 'w') as file:
        file.write("x_coordinate temperature\n")
        for x, y in zip(x_values, y_values):
            file.write(f"{x} {y}\n")

if __name__ == "__main__":
    output_file = "./validation/analytical-sol.txt"  # Save in the validation directory
    calculate_analytical_solution(output_file)
    print(f"Analytical solution written to {output_file}")
