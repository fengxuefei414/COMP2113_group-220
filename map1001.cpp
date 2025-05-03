#include "map1001.h"
#include "./map_utils.h"

void generateMap1001(vector<vector<char> >& map) {
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
		for(x=10;x<22;x++){
			setfloor(map,x,y);
		}
		for(x=32;x<41;x++){
			setfloor(map,x,y);
		}
		for(x=58;x<65;x++){
			setfloor(map,x,y);
		}	
	}
	
	for(y=8;y<=8;y++){
		for(x=5;x<10;x++){
			setfloor(map,x,y);
		}
		for(x=26;x<31;x++){
			setfloor(map,x,y);
		}	
	}
	
	for(y=10;y<=10;y++){
		for(x=10;x<15;x++){
			setfloor(map,x,y);
		}
		for(x=22;x<27;x++){
			setfloor(map,x,y);
	    }
		for(x=90;x<95;x++){
			setfloor(map,x,y);
		}
		
	}
	
	for(y=12;y<=12;y++){
		for(x=5;x<10;x++){
			setfloor(map,x,y);
		}
		for(x=15;x<25;x++){
			setfloor(map,x,y);
		}
		for(x=41;x<46;x++){
			setfloor(map,x,y);
		}
		for(x=69;x<74;x++){
			setfloor(map,x,y);
	    }
	    for(x=83;x<89;x++){
			setfloor(map,x,y);
	    }
		for(x=98;x<105;x++){
			setfloor(map,x,y);
		}
	}
	
	for(y=14;y<=14;y++){
		for(x=5;x<15;x++){
			setfloor(map,x,y);
		}
		for(x=56;x<60;x++){
			setfloor(map,x,y);
		}
		for(x=63;x<67;x++){
			setfloor(map,x,y);
		}
		for(x=75;x<82;x++){
			setfloor(map,x,y);
		}
		for(x=108;x<=119;x++){
			setfloor(map,x,y);
		}
	}
	
	for(y=16;y<=16;y++){
		for(x=35;x<42;x++){
			setfloor(map,x,y);
		}
		for(x=46;x<54;x++){
			setfloor(map,x,y);
		}
		
	}
	
	for(x=15;x<=15;x++){
		for(y=8;y<17;y++){
			setv(map,x,y);
		}
	}
	
	for(x=40;x<=40;x++){
		for(y=7;y<11;y++){
			setv(map,x,y);
		}
	}
	
	for(x=47;x<=47;x++){
		for(y=7;y<14;y++){
			setv(map,x,y);
		}
	}
	
	A(map,71,7);
	A(map,72,6);
	A(map,73,5);
	A(map,70,8);
	A(map,69,9);
	B(map,74,5);
	B(map,75,6);
	B(map,76,7);
	B(map,77,8);
	B(map,78,9);
	setfloor(map,72,8);
	setfloor(map,73,8);
	setfloor(map,74,8);
	setfloor(map,75,8);
	setfloor(map,82,5);
	setfloor(map,83,5);
	setfloor(map,84,5);
	setfloor(map,85,5);
	setfloor(map,86,5);
	setfloor(map,82,9);
	setfloor(map,83,9);
	setfloor(map,84,9);
	setfloor(map,85,9);
	setfloor(map,86,9);
	setwall(map,84,6);
	setwall(map,84,7);
	setwall(map,84,8);
	C(map,112,13);
	D(map,114,13);
	E(map,61,11);
	E(map,61,9);
	E(map,17,11);
	E(map,92,9);
	E(map,43,11);
	
}
