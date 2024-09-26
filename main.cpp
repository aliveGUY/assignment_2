#include <stdio.h>
#include <mpi.h>
#include <time.h>

int main(int argc, char **argv)
{
  int my_node, total_nodes;
  int sum, start_val, end_val, accum;
  double start_time, end_time, elapsed_time;

  MPI_Status status;

  MPI_Init(&argc, &argv);

  MPI_Comm_size(MPI_COMM_WORLD, &total_nodes);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_node);

  start_time = MPI_Wtime();

  sum = 0;
  start_val = 1000 * my_node / total_nodes + 1;
  end_val = 1000 * (my_node + 1) / total_nodes;

  for (int i = start_val; i <= end_val; i++)
  {
    sum += i;
  }

  if (my_node != 0)
  {
    MPI_Send(&sum, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
  }
  else
  {
    for (int j = 1; j < total_nodes; j++)
    {
      MPI_Recv(&accum, 1, MPI_INT, j, 1, MPI_COMM_WORLD, &status);
      sum += accum;
    }

    end_time = MPI_Wtime();
    elapsed_time = end_time - start_time;

    printf("The sum from 1 to 1000 is: %d\n", sum);
    printf("Execution time on %d nodes: %f seconds\n", total_nodes, elapsed_time);
  }

  MPI_Finalize();
  return 0;
}
