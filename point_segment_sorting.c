#include "points_segments.h"

struct Point{
  char type[10]; //Whether it's the start of a segment, the end or just a point
  int pos;    //coordinates of point
  int index;  //It's index in the orriginal arrays of points(doesn't matter for segments)
};
//I have the index so that I can compare with my naive algorithm, by keeping the same order of the results

/*For my compare function, I am including points that are exactly where a segment starts
or end so when two elemtents have the same position, I check their type
I want point to come after start but before end and it doesn't matter for start and end of a
segment they can just be equivalent*/
int cmpfunc(const void* e1, const void* e2){
  struct Point point1 = *(const struct Point *)e1;
  struct Point point2 = *(const struct Point *)e2;
  if(point1.pos<point2.pos){
    return -1;
  }
  if(point1.pos>point2.pos){
    return 1;
  }//after these two statements positions mmust be equal
  if(!strcmp(point1.type,"Start")){
    return -1;
  }
  if(!strcmp(point1.type,"End")){
    return 1;
  }//after these statements point1 must be of type Point
  if(!strcmp(point2.type,"Start")){
    return 1;
  }
  if(!strcmp(point2.type,"End")){
    return -1;
  }
  return 0;
}
int * withsort(int s, int p, int ** segments, int *points){
  /*First I make the array that will contain all points, segment starts and
  segment ends. I loop through the points and segments to initialize it. I know
  it's length is p+2*s, the number of points plus 2 times the number of segments
  (Because start and end of segment)*/
  int length = p+2*s;
  struct Point array[length];

  for(int i = 0; i<p; i++){
    strcpy(array[i].type, "Point");
    array[i].pos = points[i];
    array[i].index = i;
  }

  for(int i = 0; i<s; i++){
    strcpy(array[i+p].type, "Start");
    array[i+p].pos = segments[i][0];
  }

  for(int i = 0; i<s; i++){
    strcpy(array[i+p+s].type, "End");
    array[i+p+s].pos = segments[i][1];
  }
  int * overlaps = malloc(sizeof(int)*p); //The array with the overlaps of the points at that index in the starting array of points
  //Next I sort the array
  qsort(array, length, sizeof(struct Point), cmpfunc);

  //I loop through the array add one to the count for every start subtract for every end.
  //When I reach a point the current count is the number of overlaps;
  int current_count = 0;
  for(int i = 0; i<length; i++){
    if(!strcmp(array[i].type,"Start")){
      current_count++;
    }
    if(!strcmp(array[i].type,"End")){
      current_count--;
    }
    if(!strcmp(array[i].type,"Point")){
      int index = array[i].index;
      overlaps[index] = current_count;
    }
  }
  return overlaps;
}
