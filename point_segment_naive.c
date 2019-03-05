#include "points_segments.h"

int * naive(int s, int p, int ** segments, int *points){
  int num = 0;
  int *overlaps = malloc(sizeof(int)*p);
  for(int i = 0; i<p; i++){
    for(int j = 0; j<s; j++){
      if(points[i]<= segments[j][1] && points[i]>=segments[j][0]){
        num++;
      }
    }
    overlaps[i] = num;
    num = 0;
  }
  return overlaps;
}
