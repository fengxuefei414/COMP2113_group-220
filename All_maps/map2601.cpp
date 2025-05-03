#include "map2601.h"
#include "./map_utils.h"

void generateMap2601(vector<vector<char> >& map) {
    initializeMap(map);
    
    int start_x = 5;
    int start_y = 2;
    int end_x = 114;
    int end_y = 16;

    // Generate top boundary
    for (int x = 0; x < 120; x++){   
        setfloor(map,x,0);
    }

    // Generate bottom boundary
    for (int x = 0; x < 120; x++){
        setfloor(map,x,19);
    }

    for (int k = 13 + start_x; k <= end_x; k++){ 
        setv(map,k,end_y); 
    }


    for (int x = start_x; x <= end_x; x++){
        if (map[start_y][x] == ' '){
            setfloor(map,x,start_y);
        }
        if (map[end_y][x] == ' '){
            setfloor(map,x,end_y);
        }
    }

    for (int y = 6; y <= 6; y++){
        for (int x = 22+5; x <= 27+5; x++){
            setfloor(map,x,y);
        }

        for (int x = 33+5; x <= 38+5; x++){
            setfloor(map,x,y);
        }

        for (int x = 58+5; x <= 60+5; x++){
            setfloor(map,x,y);
        }

        for (int x = 65+5; x <= 69+5; x++){
            setfloor(map,x,y);
        }

        for (int x = 73+5; x <= 79+5; x++){
            setfloor(map,x,y);
        }

        for (int x = 83+5; x <= 119; x++){
            setfloor(map,x,y);
        }
    }

    for (int y = 8; y <= 8; y++){
        for (int x = 22+5; x <= 30+5; x++){
            setfloor(map,x,y);
        }
        for (int x = 41+5; x <= 43+5; x++){
            setfloor(map,x,y);
        }
        for (int x = 63+5; x <= 65+5; x++){
            setfloor(map,x,y);
        }
    }

    for (int y = 10; y <= 10; y++){
        for (int x = 4+5; x <= 6+5; x++){
            setfloor(map,x,y);
        }
        for (int x = 11+5; x <= 16+5; x++){
            setfloor(map,x,y);
        }
        for (int x = 32+5; x <= 39+5; x++){
            setfloor(map,x,y);
        }
        for (int x = 58+5; x <= 60+5; x++){
            setfloor(map,x,y);
        }
    }

    for (int y = 12; y <= 12; y++){
        for (int x = 9+5; x <= 11+5; x++){
            setfloor(map,x,y);
        }
        for (int x = 17+5; x <= 20+5; x++){
            setfloor(map,x,y);
        }
        for (int x = 23+5; x <= 26+5; x++){
            setfloor(map,x,y);
        }
        for (int x = 29+5; x <= 31+5; x++){
            setfloor(map,x,y);
        }
        for (int x = 40+5; x <= 48+5; x++){
            setfloor(map,x,y);
        }
        for (int x = 53+5; x <= 56+5; x++){
            setfloor(map,x,y);
        }
    }
    
    for (int y = 14; y <= 14; y++){
        for (int x = 4+5; x <= 6+5; x++){
            setfloor(map,x,y);
        }
    }
    
    // Generate walls
    for (int x = 3+5; x <= 3+5; x++){
        for (int y = 10; y <= 14; y++){
            setwall(map,x,y);
        }
    }

    for (int x = 12+5; x <= 12+5; x++){
        for (int y = 12; y <= 16; y++){
            setwall(map,x,y);
        }
    }

    setwall(map,22+5,7);
    setwall(map,27+5,7);

    for (int x = 32+5; x <= 32+5; x++){
        for (int y = 11; y <= 12; y++){
            setwall(map,x,y);
        }
    }

    for (int x = 36+5; x <= 36+5; x++){
        for (int y = 11; y <= 12; y++){
            setwall(map,x,y);
        }
        for (int y = 7; y <= 9; y++){
            setwall(map,x,y);
        }
    }

    for (int x = 44+5; x <= 44+5; x++){
        for (int y = 5; y <= 9; y++){
            setv(map,x,y);
        }
    }

    for (int x = 59+5; x <= 59+5; x++){
        for (int y = 7; y <= 8; y++){
            setv(map,x,y);
        }
    }

    for (int x = 64+5; x <= 64+5; x++){
        for (int y = 9; y <= 10; y++){
            setv(map,x,y);
        }
    }

    // Generate vertical spikes
    setv(map,50+5,11);
    setv(map,51+5,11);

    setv(map,49+5,12);
    setv(map,50+5,12);
    setv(map,51+5,12);
    setv(map,52+5,12);
    setv(map,92,6);
    setv(map,93,6);
    setv(map,94,6);
    setv(map,100,6);
    setv(map,101,6);
    setv(map,102,6);
    
    // Place special elements
    E(map, 24+5, 11);
    E(map, 34+5, 5);
    E(map, 45+5, 11);

    // Place decorations
    
    for (int y = 8; y <= 8; y++){
        for (int x = 71+5; x <= 74+5; x++){
            side(map,x,y);
        }
        for (int x = 76+5; x <= 79+5; x++){
            side(map,x,y);
        }
        for (int x = 81+5; x <= 84+5; x++){
            side(map,x,y);
        }
        for (int x = 87+5; x <= 88+5; x++){
            side(map,x,y);
        }
    }
    for (int y = 9; y <= 9; y++){
        for (int x = 74+5; x <= 74+5; x++){
            side(map,x,y);
        }
        for (int x = 76+5; x <= 76+5; x++){
            side(map,x,y);
        }
        for (int x = 81+5; x <= 84+5; x += 3){
            side(map,x,y);
        }
        for (int x = 88+5; x <= 88+5; x++){
            side(map,x,y);
        }
    }
    for (int y = 10; y <= 10; y++){
        for (int x = 73+5; x <= 73+5; x++){
            side(map,x,y);
        }
        for (int x = 76+5; x <= 79+5; x++){
            side(map,x,y);
        }
        for (int x = 81+5; x <= 84+5; x += 3){
            side(map,x,y);
        }
        for (int x = 88+5; x <= 88+5; x++){
            side(map,x,y);
        }
    }
    for (int y = 11; y <= 11; y++){
        for (int x = 71+5; x <= 71+5; x++){
            side(map,x,y);
        }
        for (int x = 76+5; x <= 79+5; x += 3){
            side(map,x,y);
        }
        for (int x = 81+5; x <= 84+5; x += 3){
            side(map,x,y);
        }
        for (int x = 88+5; x <= 88+5; x++){
            side(map,x,y);
        }
    }
    for (int y = 12; y <= 12; y++){
        for (int x = 71+5; x <= 74+5; x++){
            side(map,x,y);
        }
        for (int x = 76+5; x <= 79+5; x++){
            side(map,x,y);
        }
        for (int x = 81+5; x <= 84+5; x++){
            side(map,x,y);
        }
        for (int x = 86+5; x <= 89+5; x++){
            side(map,x,y);
        }
    }
    // Place level entrance and exit
    C(map,105,5);
    D(map,107,5);
}
