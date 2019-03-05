#include "points_segments.h"
#include <string.h>

static int points[1000];
static int overlaps[1000];

int naive(FILE *fp){
  char line[20];
  fgets(line, 20, fp);
  char delim[] = " \n";
  char *seg = strtok(line, delim);
  char *pts = strtok(NULL, delim);
  int numSeg = atoi(seg);
  int numPts = atoi(pts);
  //printf("%d segments %d points\n",numSeg, numPts);
  int length = numSeg + numPts;
  int starts[numSeg];
  int ends[numSeg];


  for(int i = 0; i<numSeg; i++){
    char lineSeg[100];
    fgets(lineSeg, 100, fp);
    char *r = strtok(lineSeg, delim);
    char *f = strtok(NULL, delim);
    int segStart = atoi(r);
    int segEnd = atoi(f);
    starts[i] = segStart;
    ends[i] = segEnd;
    //printf("%d start %d ends\n",segStart, segEnd);
    }

  /*static int points[1000];
  static int overlaps[1000];*/
  char allPts[1000];
  fgets(allPts, 1000, fp);
  char *pt;
  for(int i = 0; i<numPts; i++){
    if(i == 0){
      pt = strtok(allPts, delim);
    }
    else{
      pt = strtok(NULL, delim);
    }
    points[i] = atoi(pt);
    overlaps[i] = 0;
    for(int j = 0; j<numSeg; j++){
      if(starts[j] <= points[i] && ends[j] >= points[i]){
        overlaps[i]++;
      }
    }
  }
  return numPts;
}

int main(){
  FILE* fp;
  fp = fopen("input3.txt", "r");
  if(fp == NULL){
      printf("Error file not found");
      return -1;
  }
  int numPoints = naive(fp);
  for(int i =0; i<numPoints; i++){
    printf("point: %d, overlaps: %d\n",points[i], overlaps[i]);
  }
}
