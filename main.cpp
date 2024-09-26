#include <iostream.h>
#include <mpi.h>

int main(int argc, char **argv)
{
  int mynode, totalnodes;
  int sum = 0, startval, endval, accum;
  MPI_Status status;

  MPI_Init(argc, argv);
  MPI_Comm_size(MPI_COMM_WORLD, &totalnodes);
  MPI_Comm_rank(MPI_COMM_WORLD, &mynode);

  startval = 1000 * mynode / totalnodes + 1;
  endval = 1000 * (mynode + 1) / totalnodes;

  for (int i = startval; i <= endval; i++)
    sum += i;

  if (mynode != 0)
  {
    MPI_Send(&sum, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
  }
  else
  {
    for (int j = 1; j < totalnodes; j++)
    {
      MPI_Recv(&accum, 1, MPI_INT, j, 1, MPI_COMM_WORLD, &status);
      sum += accum;
    }
    cout << "Сума від 1 до 1000: " << sum << endl;
  }

  MPI_Finalize();
}
