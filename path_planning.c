/*
* AstroTinker Bot (AB): Task 1B Path Planner
*
* This program computes the valid path from the start point to the end point.
* Make sure you don't change anything outside the "Add your code here" section.
*/

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#ifdef _linux_ // for host pc

    #include <stdio.h>

    void _put_byte(char c) { putchar(c); }

    void _put_str(char *str) {
        while (*str) {
            _put_byte(*str++);
        }
    }

    void print_output(uint8_t num) {
        if (num == 0) {
            putchar('0'); // if the number is 0, directly print '0'
            _put_byte('\n');
            return;
        }

        if (num < 0) {
            putchar('-'); // print the negative sign for negative numbers
            num = -num;   // make the number positive for easier processing
        }

        // convert the integer to a string
        char buffer[20]; // assuming a 32-bit integer, the maximum number of digits is 10 (plus sign and null terminator)
        uint8_t index = 0;

        while (num > 0) {
            buffer[index++] = '0' + num % 10; // convert the last digit to its character representation
            num /= 10;                        // move to the next digit
        }

        // print the characters in reverse order (from right to left)
        while (index > 0) { putchar(buffer[--index]); }
        _put_byte('\n');
    }

    void _put_value(uint8_t val) { print_output(val); }

#else  // for the test device

    void _put_value(uint8_t val) { }
    void _put_str(char *str) { }

#endif


// main function
int main(int argc, char const *argv[]) {

    #ifdef _linux_

        const uint8_t START_POINT   = atoi(argv[1]);
        const uint8_t END_POINT     = atoi(argv[2]);
        uint8_t CPU_DONE            = 0;

    #else

        #define START_POINT         (* (volatile uint8_t * ) 0x20000000)
        #define END_POINT           (* (volatile uint8_t * ) 0x20000001)
        #define CPU_DONE            (* (volatile uint8_t * ) 0x20000003)

    #endif

    // array to store the planned path
    uint8_t path_planned[32];

    // index to keep track of the path_planned array
    uint8_t idx = 0;

    // instead of using printf() function for debugging,
    // use the below function calls to print a number, string or a newline

    // for newline: _put_byte('\n');
    // for string:  _put_str("your string here");
    // for number:  _put_value(your_number_here);

    // Examples:
    // _put_value(START_POINT);
    // _put_value(END_POINT);
    // _put_str("Hello World!");
    // _put_byte('\n');

    // ############# Add your code here #############
    int start,end;
    int size=0;
	int graph[30][30]={0};
    start=START_POINT;
    end=END_POINT;

    graph[0][1]=1;graph[1][0]=1;
    graph[1][2]=1;graph[2][1]=1;
    graph[2][3]=1;graph[3][2]=1;
    graph[3][4]=2;graph[4][3]=2;
    graph[3][28]=3;graph[28][3]=3;
    graph[4][5]=1;graph[5][4]=1;
    graph[4][6]=3;graph[6][4]=3;
    graph[6][7]=2;graph[7][6]=2;
    graph[7][8]=1;graph[8][7]=1;
    graph[8][2]=1;graph[2][8]=1;
    graph[8][9]=1;graph[9][8]=1;
    graph[9][10]=1;graph[10][9]=1;
    graph[9][11]=1;graph[11][9]=1;
    graph[8][12]=1;graph[12][8]=1;
    graph[12][13]=4;graph[13][12]=4;
    graph[13][14]=4;graph[14][13]=4;
    graph[14][15]=1;graph[15][14]=1;
    graph[14][16]=2;graph[16][14]=2;
    graph[16][17]=1;graph[17][16]=1;
    graph[16][18]=4;graph[18][16]=4;
    graph[18][19]=4;graph[19][18]=4;
    graph[19][20]=1;graph[20][19]=1;
    graph[19][12]=1;graph[12][19]=1;
    graph[20][21]=1;graph[21][20]=1;
    graph[20][29]=1;graph[29][20]=1;
    graph[20][24]=1;graph[24][20]=1;
    graph[21][22]=1;graph[22][21]=1;
    graph[21][23]=1;graph[23][21]=1;
    graph[24][25]=2;graph[25][24]=2;
    graph[25][26]=3;graph[26][25]=3;
    graph[26][27]=1;graph[27][26]=1;
    graph[26][28]=2;graph[28][26]=2;
    graph[28][29]=1;graph[29][28]=1;
    graph[29][1]=1;graph[1][29]=1;	
    
    if(start==end){
    	path_planned[0]=start;
    	idx=1;
	}
    else{
        const int NUM_NODES = 30;
        int distance[NUM_NODES];
        int visited[30] = {0};
        for (int i=0;i<NUM_NODES;i++) {
            distance[i]=99999999;
            visited[i]=0;
        }
        distance[start]=0;
        int parent[30]={0};
        parent[start]=-1;
        for (int i=1;i<NUM_NODES;i++) {
            int neighbour=-1;
            int mindist=99999999;
            for (int j=0;j<NUM_NODES;j++) {
                if(!visited[j] && distance[j] < mindist) {
                    neighbour=j;
                    mindist=distance[j];
                }
            }
            visited[neighbour] = 1;
            for (int c=0;c<NUM_NODES;c++) {
                int edgeDistance=graph[neighbour][c];
                if (edgeDistance>0 && ((mindist+edgeDistance)<distance[c])) {
                    parent[c]=neighbour;
                    distance[c]=mindist+edgeDistance;
                }
            }
        }
        int temp;
        int index=end;
        if(index !=start){
            while(index!=-1){
                path_planned[size]=index;
                size++;
                temp=size;
                index=parent[index];
            }
        }
        idx=temp;
        for(int i=0; i<temp/2;i++){
            temp=path_planned[i];
            path_planned[i]=path_planned[temp-i-1];
            path_planned[temp-i-1] = temp;
        }
    }

    // ##############################################

    #ifdef _linux_    // for host pc

        _put_str("######### Planned Path #########\n");
        for (int i = 0; i < idx; ++i) {
            _put_value(path_planned[i]);
        }
        _put_str("################################\n");
    

    #endif 
	
	
	/*else{
		_put_str("Invalid points");
	}*/
    return 0;
}