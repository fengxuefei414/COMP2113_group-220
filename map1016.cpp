#include "map1016.h"
#include "./map_utils.h"

void generateMap1016(vector<vector<char> >& map) {
    initializeMap(map);
    int x;
    int y;
    
    for(int k=5; k <= 119; k++){
		setv(map,k,18);
    }
	for (x = 5; x <= 119; x++){ 
		if (map[2][x] == ' '){
			setfloor(map,x,2);
		}
    }
    
    for(y=6;y<=6;y++){
    	for(x=17;x<21;x++){
			setfloor(map,x,y);
		}
		for(x=41;x<48;x++){
			setfloor(map,x,y);
		}
		for(x=52;x<59;x++){
			setfloor(map,x,y);
		}
		for(x=63;x<70;x++){
			setfloor(map,x,y);
		}
    	
	}
	
	for(y=8;y<=8;y++){
		for(x=12;x<16;x++){
			setfloor(map,x,y);
		}
		for(x=22;x<26;x++){
			setfloor(map,x,y);
		}
		for(x=37;x<41;x++){
			setfloor(map,x,y);
		}
		
	}
	
	for(y=9;y<=9;y++){
		for(x=72;x<76;x++){
			setfloor(map,x,y);
		}
		
	}
	
	for(y=10;y<=10;y++){
		for(x=5;x<11;x++){
			setfloor(map,x,y);
		}
		for(x=27;x<33;x++){
			setfloor(map,x,y);
		}
		for(x=41;x<45;x++){
			setfloor(map,x,y);
		}
		for(x=109;x<=119;x++){
			setfloor(map,x,y);
		}	
	}
	
	for(y=11;y<=11;y++){
		for(x=76;x<81;x++){
			setfloor(map,x,y);
		}
    }    
	
	for(y=12;y<=12;y++){
		for(x=22;x<26;x++){
			setfloor(map,x,y);
		}
		for(x=34;x<39;x++){
			setfloor(map,x,y);
		}
		for(x=103;x<107;x++){
			setfloor(map,x,y);
		}
    	
	}
	
	for(y=13;y<=13;y++){
		for(x=60;x<64;x++){
			setfloor(map,x,y);
		}
		for(x=68;x<74;x++){
			setfloor(map,x,y);
		}
		
	}
	
	for(y=14;y<=14;y++){
		for(x=16;x<21;x++){
			setfloor(map,x,y);
		}
		for(x=82;x<88;x++){
			setfloor(map,x,y);
		}
		for(x=96;x<102;x++){
			setfloor(map,x,y);
		}
			
	}
	
	for(y=16;y<=16;y++){
		for(x=22;x<28;x++){
			setfloor(map,x,y);
		}
		for(x=32;x<37;x++){
			setfloor(map,x,y);
		}
		for(x=41;x<46;x++){
			setfloor(map,x,y);
		}
		for(x=50;x<60;x++){
			setfloor(map,x,y);
		}
		for(x=90;x<95;x++){
			setfloor(map,x,y);
		}
    	
	}
	for(x=16;x<=16;x++){
		for(y=6;y<=15;y++){
			setwall(map,x,y);
		}
	}
	
	for(x=60;x<=60;x++){
		for(y=14;y<=16;y++){
			setwall(map,x,y);
		}
	}
	
	for(x=36;x<=36;x++){
		for(y=7;y<=9;y++){
			setv(map,x,y);
		}
	}
	
	setv(map,49,6);
	setv(map,60,6);
	setv(map,50,6);
	setv(map,61,6);
	C(map,112,9);
	D(map,114,9);
	E(map,92,15);
	E(map,55,15);
	E(map,55,5);
	E(map,43,9);
	E(map,18,13);
	E(map,73,8);
}

