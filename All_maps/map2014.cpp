#include "map2014.h"
#include "./map_utils.h"

void generateMap2014(vector<vector<char> >& map) {
    initializeMap(map);
    
    int start_x = 5;
    int start_y = 2;
    int end_x = 114;
    int end_y = 16;

    // Generate top platform
    for (int x = 0; x < 120; x++){    
        setfloor(map,x,2);
    }

    // Generate bottom ground
    for (int x = 0; x < 120; x++){
        setv(map,x,16);
    }

    // Generate main ground level
    for (int k = start_x; k <= end_x; k++){ 
        setv(map,k,end_y); 
    }

    // Generate series of small platforms at height 8
    for (int x = 65+5; x <= 67+5; x++){
        setfloor(map,x,8);
    }   

    for (int x = 71+5; x <= 73+5; x++){
        setfloor(map,x,8);
    }

    for (int x = 77+5; x <= 79+5; x++){
        setfloor(map,x,8);
    }

    for (int x = 83+5; x <= 85+5; x++){
        setfloor(map,x,8);
    }

    for (int x = 89+5; x <= 91+5; x++){
        setfloor(map,x,8);
    }

    for (int x = 95+5; x <= 97+5; x++){
        setfloor(map,x,8);
    }

    
    // Generate ground thorns and ceiling thorns
    for (int x = start_x; x <= end_x; x++){ // Set floor and ceiling
        if (map[start_y][x] == ' '){
            setfloor(map,x,start_y);
        }
    }

    for (int y = 5; y <= 5; y++){
        for (int x = 0+5; x <= 5+5; x++){
            setfloor(map,x,y);
        }

        for (int x = 23+5; x <= 26+5; x++){
            setfloor(map,x,y);
        }

        for (int x = 50+5; x <= 52+5; x++){
            setfloor(map,x,y);
        }
    }

    for (int y = 6; y <= 6; y++){
        for (int x = 19+5; x <=22+5; x++){
            setfloor(map,x,y);
        }
        for (int x = 61+5; x <= 64+5; x++){
            setfloor(map,x,y);
        }

        for (int x = 74+5; x <= 76+5; x++){
            setfloor(map,x,y);
        }

        for (int x = 86+5; x <= 88+5; x++){
            setfloor(map,x,y);
        }

        for (int x = 98+5; x <= 109+5; x++){
            setfloor(map,x,y);
        }
    }

    for (int y = 8; y <= 8; y++){
        setfloor(map,14+5,y);
        setfloors(map,15+5,y);
        setfloor(map,29+5,y);
        setfloors(map,30+5,y);
        setfloor(map,36+5,y);
        setfloors(map,37+5,y);
        setfloors(map,44+5,y);
        setfloors(map,47+5,y);
        setfloors(map,68+5,y);
        setfloors(map,80+5,y);  
        setfloors(map,92+5,y);  
    }
    setfloor(map,19+5,10);
    setfloors(map,20+5,10);
    setfloors(map,14+5,12);
    setfloor(map,17+5,12);
    for (int x = 24+5; x <= 54+5; x += 3){
        setfloors(map,x,12);
    }

    for (int x = 57+5; x <= 60+5; x ++){
        setfloor(map,x,12);
    }

    for (int x = 6+5; x <= 20+5; x += 3){
        setfloors(map,x,14);
    }

    // Generate walls
    for (int x = 5+5; x <= 5+5; x++){
        for (int y = 6; y <= 14; y++){
            setwall(map,x,y);
        }
    }

    for (int x = 13+5; x <= 13+5; x++){
        for (int y = 4; y <= 12; y++){
            setwall(map,x,y);
        }
    }

    for (int x = 23+5; x <= 23+5; x++){
        for (int y = 6; y <= 14; y++){
            setwall(map,x,y);
        }
    }

    for (int x = 50+5; x <= 50+5; x++){
        for (int y = 6; y <= 8; y++){
            setwall(map,x,y);
        }
    }

    for (int x = 61+5; x <= 61+5; x++){
        for (int y = 7; y <= 12; y++){
            setwall(map,x,y);
        }
    }

    for (int y = 9; y <= 9; y++){
        for (int x = 71+5; x <= 74+5; x++){
            side(map,x,y);
        }
        for (int x = 76+5; x <= 79+5; x++){
            side(map,x,y);
        }
        for (int x = 81+5; x <= 82+5; x++){
            side(map,x,y);
        }
        for (int x = 86+5; x <= 89+5; x += 3){
            side(map,x,y);
        }
    }
    for (int y = 10; y <= 10; y++){
        for (int x = 74+5; x <= 74+5; x++){
            side(map,x,y);
        }
        for (int x = 76+5; x <= 79+5; x += 3){
            side(map,x,y);
        }
        for (int x = 82+5; x <= 82+5; x++){
            side(map,x,y);
        }
        for (int x = 86+5; x <= 89+5; x += 3){
            side(map,x,y);
        }
    }
    for (int y = 11; y <= 11; y++){
        for (int x = 73+5; x <= 73+5; x++){
            side(map,x,y);
        }
        for (int x = 76+5; x <= 79+5; x += 3){
            side(map,x,y);
        }
        for (int x = 82+5; x <= 82+5; x++){
            side(map,x,y);
        }
        for (int x = 86+5; x <= 89+5; x++){
            side(map,x,y);
        }
    }
    for (int y = 12; y <= 12; y++){
        for (int x = 71+5; x <= 71+5; x++){
            side(map,x,y);
        }
        for (int x = 76+5; x <= 79+5; x += 3){
            side(map,x,y);
        }
        for (int x = 82+5; x <= 82+5; x++){
            side(map,x,y);
        }
        for (int x = 89+5; x <= 89+5; x++){
            side(map,x,y);
        }
    }
    for (int y = 13; y <= 13; y++){
        for (int x = 71+5; x <= 74+5; x++){
            side(map,x,y);
        }
        for (int x = 76+5; x <= 79+5; x++){
            side(map,x,y);
        }
        for (int x = 81+5; x <= 84+5; x++){
            side(map,x,y);
        }
        for (int x = 89+5; x <= 89+5; x++){
            side(map,x,y);
        }
    }
    // Generate vertical obstacles
    setv(map,39,12);
    setv(map,40,12);
    setv(map,41,12);
    setv(map,45,12);
    setv(map,46,12);
    setv(map,47,12);
    setv(map,52,12);
    setv(map,53,12);
    setv(map,54,12);

    // Place special elements
    E(map,47,9);
    E(map,80,5);
    E(map,26,9);
    C(map,105,5);
    D(map,107,5);
}
