#include "map1000.h"
#include "./map_utils.h"

void generateMap1000(vector<vector<char> >& map) {
    initializeMap(map);
    int x;
    int y;
	
	for(int k=5; k <= 119; k++){
		setv(map,k,14);
	}
	
	for (int x = 5; x <= 119; x++){ 
		if (map[2][x] == ' '){
			setfloor(map,x,2);
		}
		if (map[14][x] == ' '){
			setfloor(map,x,14);
		}
	}
	
	for (y = 6; y <= 6 ; y++){
		for(x=25;x<35;x++){
			setfloor(map,x,y);
		}
		for(x=38;x<44;x++){
			setfloor(map,x,y);
		}
		for(x=47;x<57;x++){
			setfloor(map,x,y);
		}
		for(x=87;x<92;x++){
			setfloor(map,x,y);
		}
			
	}
	for (y = 8; y <= 8 ; y++){
		for(x=11;x<15;x++){
			setfloor(map,x,y);
		}
		for(x=20;x<24;x++){
			setfloor(map,x,y);
		}
		for(x=57;x<61;x++){
			setfloor(map,x,y);
		}
		for(x=82;x<86;x++){
			setfloor(map,x,y);
		}
		for(x=93;x<97;x++){
			setfloor(map,x,y);
		}
		
		
	}
	for (y = 10; y <= 10 ; y++){
		for(x=15;x<19;x++){
			setfloor(map,x,y);
		}
		for(x=24;x<31;x++){
			setfloor(map,x,y);
		}
		for(x=34;x<40;x++){
			setfloor(map,x,y);
		}
		for(x=43;x<48;x++){
			setfloor(map,x,y);
		}
		for(x=61;x<65;x++){
			setfloor(map,x,y);
		}
		for(x=77;x<81;x++){
			setfloor(map,x,y);
		}
		for(x=98;x<102;x++){
			setfloor(map,x,y);
		}
	}
		
	for (y = 12; y <= 12 ; y++){
		for(x=11;x<15; x++){
			setfloor(map,x,y);
		}
		for(x=65;x<77;x++){
			setfloor(map,x,y);
		}
		for(x=104;x<=119;x++){
			setfloor(map,x,y);
		}	
	}

	for (y = 14; y <= 14 ; y++){
		for(x=5;x<15;x++){
			setfloor(map,x,y);
		}
		
	}
	
	for (x=19;x<=19;x++){
		for(y=8;y<=10;y++){
			setwall(map,x,y);
		}
	}
	
	for (x=15;x<=15;x++){
		for(y=12;y<=14;y++){
			setwall(map,x,y);
		}
	}
	
	for(x=48;x<=48;x++){
		for(y=7;y<=10;y++){
			setwall(map,x,y);
		}
	}
	
	setv(map,70,12);
	setv(map,71,12);
	C(map,112,11);
	D(map,114,11);
	E(map,40,5);
	E(map,89,5);
	E(map,26,9);
	E(map,68,11);
}
