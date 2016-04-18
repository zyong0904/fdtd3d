#include "ParallelGrid.h"

#ifdef GRID_2D
#ifdef PARALLEL_GRID

#if defined (PARALLEL_BUFFER_DIMENSION_1D_X) || defined (PARALLEL_BUFFER_DIMENSION_1D_Y)
void
ParallelGrid::NodeGridInit ()
{
#ifdef PARALLEL_BUFFER_DIMENSION_1D_X
  nodeGridSizeX = totalProcCount;
  nodeGridSizeY = 1;
#endif /* PARALLEL_BUFFER_DIMENSION_1D_X */
#ifdef PARALLEL_BUFFER_DIMENSION_1D_Y
  nodeGridSizeX = 1;
  nodeGridSizeY = totalProcCount;
#endif /* PARALLEL_BUFFER_DIMENSION_1D_Y */

#if PRINT_MESSAGE
  printf ("Nodes' grid process #%d: %dx%d.\n", processId,
    nodeGridSizeX, nodeGridSizeY);
#endif /* PRINT_MESSAGE */
}

GridCoordinate2D
ParallelGrid::GridInit ()
{
  grid_coord c1;
  grid_coord c2;

#ifdef PARALLEL_BUFFER_DIMENSION_1D_X
  CalculateGridSizeForNode (c1, nodeGridSizeX, hasR, totalSize.getX ());
  c2 = totalSize.getY ();
#endif /* PARALLEL_BUFFER_DIMENSION_1D_X */
#ifdef PARALLEL_BUFFER_DIMENSION_1D_Y
  c1 = totalSize.getX ();
  CalculateGridSizeForNode (c2, nodeGridSizeY, hasU, totalSize.getY ());
#endif /* PARALLEL_BUFFER_DIMENSION_1D_Y */

  return GridCoordinate2D (c1, c2);
}
#endif /* PARALLEL_BUFFER_DIMENSION_1D_X || PARALLEL_BUFFER_DIMENSION_1D_Y */

#ifdef PARALLEL_BUFFER_DIMENSION_2D_XY
void
ParallelGrid::NodeGridInit ()
{
  if (totalProcCount < 4)
  {
    ASSERT_MESSAGE ("Unsupported number of nodes for 2D parallel buffers. Use 1D ones.");
  }

  FieldValue overall1 = (FieldValue) totalSize.getX ();
  FieldValue overall2 = (FieldValue) totalSize.getY ();

  int left;
  NodeGridInitInner (overall1, overall2, nodeGridSizeX, nodeGridSizeY, left);

  nodeGridSizeXY = nodeGridSizeX * nodeGridSizeY;

#if PRINT_MESSAGE
  printf ("Nodes' grid process #%d: %dx%d. %d node(s) unused.\n", processId,
    nodeGridSizeX, nodeGridSizeY, left);
#endif /* PRINT_MESSAGE */
}

GridCoordinate2D
ParallelGrid::GridInit ()
{
  grid_coord c1;
  grid_coord c2;

  CalculateGridSizeForNode (c1, nodeGridSizeX, hasR, totalSize.getX (),
                            c2, nodeGridSizeY, hasU, totalSize.getY ());

  return GridCoordinate2D (c1, c2);
}
#endif /* PARALLEL_BUFFER_DIMENSION_2D_XY */

#endif /* PARALLEL_GRID */
#endif /* GRID_2D */