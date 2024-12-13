#include<MD_MAX72xx.h>
#include<SPI.h>

//Led_matrix setup
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CS_PIN    8

MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

//Button
const int CH1 = 5;
const int CH2 = 6;
const int CH3 = 4;
const int CH4 = 3;
const int CH5 = 2;

int m, n;
const unsigned int number[4][10][5] = {0x1E, 0x12, 0x12, 0x12, 0x1E, 
                                   0x02, 0x02, 0x02, 0x02, 0x02,
                                   0x1E, 0x02, 0x04, 0x08, 0x1E,
                                   0x0E, 0x02, 0x0E, 0x02, 0x0E,
                                   0x02, 0x04, 0x0A, 0x0E, 0x02,
                                   0x1E, 0x10, 0x1E, 0x02, 0x1E,
                                   0x1E, 0x10, 0x1E, 0x12, 0x1E,
                                   0x1E, 0x02, 0x04, 0x08, 0x10,
                                   0x1E, 0x12, 0x1E, 0x12, 0x1E,
                                   0x1E, 0x12, 0x1E, 0x02, 0x1E,
                                   0x78, 0x48, 0x48, 0x48, 0x78, 
                                   0x08, 0x08, 0x08, 0x08, 0x08,
                                   0x78, 0x08, 0x10, 0x20, 0x78,
                                   0x38, 0x08, 0x38, 0x08, 0x38,
                                   0x08, 0x10, 0x28, 0x38, 0x08,
                                   0x78, 0x40, 0x78, 0x08, 0x78,
                                   0x78, 0x40, 0x78, 0x48, 0x78,
                                   0x78, 0x08, 0x10, 0x20, 0x40,
                                   0x78, 0x48, 0x78, 0x48, 0x78,
                                   0x78, 0x48, 0x78, 0x08, 0x78,
                                   0x79, 0x49, 0x49, 0x49, 0x79, 
                                   0x09, 0x09, 0x09, 0x09, 0x09,
                                   0x79, 0x09, 0x11, 0x21, 0x79,
                                   0x39, 0x09, 0x39, 0x09, 0x39,
                                   0x09, 0x11, 0x29, 0x39, 0x09,
                                   0x79, 0x41, 0x79, 0x09, 0x79,
                                   0x79, 0x41, 0x79, 0x49, 0x79,
                                   0x79, 0x09, 0x11, 0x21, 0x41,
                                   0x79, 0x49, 0x79, 0x49, 0x79,
                                   0x79, 0x49, 0x79, 0x09, 0x79, 
                                   0x9E, 0x92, 0x92, 0x92, 0x9E, 
                                   0x90, 0x90, 0x90, 0x90, 0x90,
                                   0x9E, 0x90, 0x88, 0x84, 0x9E,
                                   0x9C, 0x90, 0x9C, 0x90, 0x9C,
                                   0x90, 0x88, 0x94, 0x9C, 0x90,
                                   0x9E, 0x82, 0x9E, 0x90, 0x9E,
                                   0x9E, 0x82, 0x9E, 0x92, 0x9E,
                                   0x9E, 0x90, 0x88, 0x84, 0x82,
                                   0x9E, 0x92, 0x9E, 0x92, 0x9E,
                                   0x9E, 0x92, 0x9E, 0x90, 0x9E};
const unsigned int hexValue[16][16] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 
                                 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 
                                 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 
                                 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 
                                 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 
                                 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, 
                                 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 
                                 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F, 
                                 0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 
                                 0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F, 
                                 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 
                                 0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF, 
                                 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 
                                 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF, 
                                 0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED, 0xEE, 0xEF, 
                                 0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8, 0xF9, 0xFA, 0xFB, 0xFC, 0xFD, 0xFE, 0xFF};
short int game_map_in_TT[16][16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,};
unsigned int display_lM_in_TT[16][2];
short int score = 0;
short int highest = 15;
short int end = 0;

void setup() {
  mx.begin();
  mx.control(MD_MAX72XX::INTENSITY, 0);
  mx.clear();
  pinMode(CH1, INPUT_PULLUP);
  pinMode(CH2, INPUT_PULLUP);
  pinMode(CH3, INPUT_PULLUP);
  pinMode(CH4, INPUT_PULLUP);
  pinMode(CH5, INPUT_PULLUP);
}

void loop() {
  //block generate
  short int block[4][2]; //block coordinate
  short int block_type = rand() % 7 + 1; //block type
  short int rotate = 1;
  short int cordition[3] = {0, 0, 0};
  short int fps = 40;

  //block element
  if (block_type == 1) {
    block[0][0] = 0;
    block[0][1] = 11;
    block[1][0] = 1;
    block[1][1] = 11;
    block[2][0] = 2;
    block[2][1] = 11;
    block[3][0] = 3;
    block[3][1] = 11;
  } else if (block_type == 2) {
    block[0][0] = 0;
    block[0][1] = 11;
    block[1][0] = 0;
    block[1][1] = 12;
    block[2][0] = 1;
    block[2][1] = 11;
    block[3][0] = 2;
    block[3][1] = 11;
  } else if (block_type == 3) {
    block[0][0] = 0;
    block[0][1] = 11;
    block[1][0] = 0;
    block[1][1] = 12;
    block[2][0] = 1;
    block[2][1] = 11;
    block[3][0] = 1;
    block[3][1] = 12;
  } else if (block_type == 4) {
    block[0][0] = 0;
    block[0][1] = 10;
    block[1][0] = 0;
    block[1][1] = 11;
    block[2][0] = 1;
    block[2][1] = 11;
    block[3][0] = 1;
    block[3][1] = 12;
  } else if (block_type == 5) {
    block[0][0] = 1;
    block[0][1] = 10;
    block[1][0] = 1;
    block[1][1] = 11;
    block[2][0] = 1;
    block[2][1] = 12;
    block[3][0] = 2;
    block[3][1] = 11;
  } else if (block_type == 7) {
    block[0][0] = 0;
    block[0][1] = 11;
    block[1][0] = 0;
    block[1][1] = 12;
    block[2][0] = 1;
    block[2][1] = 12;
    block[3][0] = 2;
    block[3][1] = 12;
  } else {
    block[0][0] = 0;
    block[0][1] = 11;
    block[1][0] = 0;
    block[1][1] = 12;
    block[2][0] = 1;
    block[2][1] = 10;
    block[3][0] = 1;
    block[3][1] = 11;
  }

  //block move
  int move = 0;
  while (move != 1) {
    //cordition move
    fps = 40;
    for (int i = 0; i < 4; i++) {
      if (game_map_in_TT[block[i][0]][block[i][1] - 1] == 1 || block[i][1] == 8) {
        cordition[0] = 1;
      }
      if (game_map_in_TT[block[i][0]][block[i][1] + 1] == 1 || block[i][1] == 15) {
        cordition[1] = 1;
      }
    }

    if (digitalRead(CH1) == 0 && cordition[0] == 0) {
      for (int i = 0; i < 4; i++) {
        block[i][1]--;
      }
    } else if (digitalRead(CH3) == 0 && cordition[1] == 0) {
      for (int i = 0; i < 4; i++) {
        block[i][1]++;
      }
    } else if (digitalRead(CH4) == 0) {
      fps = 12;
    } else if (digitalRead(CH5) == 0) {
      if (block_type == 1) { 
        if (rotate == 1 && block[1][0] < highest && block[1][1] > 8 && block[1][1] < 14) {
          block[0][0]++;
          block[0][1]--;
          block[2][0]--;
          block[2][1]++;
          block[3][0] = block[3][0] - 2;
          block[3][1] = block[3][1] + 2;
          rotate++;
        } else if (rotate == 2 && block[1][0] + 2 < highest) {
          block[0][0] = block[0][0] - 2;
          block[0][1]++;
          block[1][0]--;
          block[2][1]--;
          block[3][0]++;
          block[3][1] = block[3][1] - 2;
          rotate++;
        } else if (rotate == 3 && block[2][0] < highest && block[2][1] > 9 && block[2][1] < 15) {
          block[0][0] = block[0][0] + 2;
          block[0][1] = block[0][1] - 2;
          block[1][0]++;
          block[1][1]--;
          block[3][0]--;
          block[3][1]++;
          rotate++;
        } else if (rotate == 4 && block[2][0] + 1 < highest) {
          block[0][0]--;
          block[0][1] = block[0][1] + 2;
          block[1][1]++;
          block[2][0]++;
          block[3][0] = block[3][0] + 2;
          block[3][1]--;
          rotate = 1;
        }
      } else if (block_type == 2) {
        if (rotate == 1 && block[2][0] + 1 < highest && block[2][1] > 8 && block[2][1] < 15) {
          block[0][1]--;
          block[1][0]++;
          block[1][1] = block[1][1] - 2;
          block[3][0]--;
          block[3][1]++;
          rotate++;
        } else if (rotate == 2 && block[2][0] + 1 < highest && block[2][1] > 8 && block[2][1] < 15) {
          block[0][1]++;
          block[1][1]++;
          block[2][0]++;
          block[3][0]++;
          block[3][1] = block[3][1] - 2;
          rotate++;
        } else if (rotate == 3 && block[1][0] + 1 < highest && block[1][1] > 8 && block[1][1] < 15) {
          block[0][0]++;
          block[0][1]--;
          block[2][0]--;
          block[2][1]++;
          block[3][1] = block[3][1] + 2;
          rotate++;
        } else if (rotate == 4 && block[1][0] + 1 < highest && block[1][1] > 8 && block[1][1] < 15) {
          block[0][0]--;
          block[0][1]++;
          block[1][0]--;
          block[1][1]++;
          block[2][1]--;
          block[3][1]--;
          rotate = 1;
        }
      } else if (block_type == 4) {
        if (rotate == 1 && block[1][0] + 1 < highest && block[1][1] > 8 && block[1][1] < 15) {
          block[0][0]--;
          block[0][1]++;
          block[2][0]--;
          block[2][1]--;
          block[3][1] = block[3][1] - 2;
          rotate++;
        } else if (rotate == 2 && block[1][0] + 1 < highest && block[1][1] > 8 && block[1][1] < 15) {
          block[0][1]--;
          block[1][0]--;
          block[2][1]++;
          block[3][0]--;
          block[3][1] = block[3][1] + 2;
          rotate++;
        } else if (rotate == 3 && block[2][0] + 1 < highest && block[2][1] > 8 && block[2][1] < 15) {
          block[0][1] = block[0][1] + 2;
          block[1][0]++;
          block[2][1]++;
          block[3][0]++;
          block[3][1]--;
          rotate++;
        } else if (rotate == 4 && block[1][0] + 1 < highest && block[1][1] > 8 && block[1][1] < 15) {
          block[0][0]++;
          block[0][1] = block[0][1] - 2;
          block[2][0]++;
          block[2][1]--;
          block[3][1]++;
          rotate = 1;
        }
      } else if (block_type == 5) {
        if (rotate == 1 && block[1][0] + 1 < highest && block[1][1] > 8 && block[1][1] < 15) {
          block[0][0]--;
          block[0][1]++;
          block[1][1]--;
          block[2][1]--;
          rotate++;
        } else if (rotate == 2 && block[2][0] + 1 < highest && block[2][1] > 8 && block[2][1] < 15) {
          block[3][0]--;
          block[3][1]++;
          rotate++;
        } else if (rotate == 3 && block[2][0] + 1 < highest && block[2][1] > 8 && block[2][1] < 15) {
          block[1][1]++;
          block[2][1]++;
          block[3][0]++;
          block[3][1]--;
          rotate++;
        } else if (rotate == 4 && block[1][0] + 1 < highest && block[1][1] > 8 && block[1][1] < 15) {
          block[0][0]++;
          block[0][1]--;
          rotate = 1;
        }
      } else if (block_type == 6) {
        if (rotate == 1 && block[0][0] + 1 < highest && block[0][1] > 8 && block[0][1] < 15) {
          block[0][0]--;
          block[0][1]--;
          block[1][1] = block[1][1] - 2;
          block[2][0]--;
          block[2][1]++;
          rotate++;
        } else if (rotate == 2 && block[2][0] + 1 < highest && block[2][1] > 8 && block[2][1] < 15) {
          block[0][1]++;
          block[1][0]--;
          block[1][1] = block[1][1] + 2;
          block[2][1]--;
          block[3][0]--;
          rotate++;
        } else if (rotate == 3 && block[3][0] + 1 < highest && block[3][1] > 8 && block[3][1] < 15) {
          block[1][0]++;
          block[1][1]--;
          block[2][1] = block[2][1] + 2;
          block[3][0]++;
          block[3][1]++;
          rotate++;
        } else if (rotate == 4 && block[1][0] + 1 < highest && block[1][1] > 8 && block[1][1] < 15) {
          block[0][0]++;
          block[1][1]++;
          block[2][0]++;
          block[2][1] = block[2][1] - 2;
          block[3][1]--;
          rotate = 1;
        }
      } else if (block_type == 7) {
        if (rotate == 1 && block[2][0] + 1 < highest && block[2][1] > 8 && block[2][1] < 15) {
          block[0][1] = block[0][1] +2;
          block[1][0]++;
          block[1][1]--;
          block[3][0]--;
          block[3][1]++;
          rotate++;
        } else if (rotate == 2 && block[2][0] + 1 < highest && block[2][1] > 8 && block[2][1] < 15) {
          block[0][1]--;
          block[1][1]++;
          block[2][0]++;
          block[3][0]++;
          rotate++;
        } else if (rotate == 3 && block[1][0] + 1 < highest && block[1][1] > 8 && block[1][1] < 15) {
          block[0][0]++;
          block[0][1]--;
          block[2][0]--;
          block[2][1]++;
          block[3][1] = block[3][1] - 2;
          rotate++;
        } else if (rotate == 4 && block[1][0] + 1 < highest && block[1][1] > 8 && block[1][1] < 15) {
          block[0][0]--;
          block[1][0]--;
          block[2][1]--;
          block[3][1]++;
          rotate = 1;
        }
      }
    }
    
    for (int i = 0; i < 4; i++) {
      if (game_map_in_TT[block[i][0] + 1][block[i][1]] == 1 || block[i][0] == 15) {
        cordition[2] = 1;
      }
    }

    if (cordition[2] == 0) {
      //move down
      for (int i = 0; i < 4; i++) {
        block[i][0]++;
      }
      for (int i = 0; i <= 4; i++) {
        game_map_in_TT[block[i][0]][block[i][1]] = 1;
      }

      //display
      for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 2; j++) {
          display_lM_in_TT[i][j] = 0;
        }
      }
      for (int i = 0; i < 8; i++) {
        display_lM_in_TT[i][0] = 0x80; 
        m = 0;
        n = 0;
        for (int j = 8; j <= 11; j++) {
          if (game_map_in_TT[i][j] == 1) {
            m = m + po(2, j - 8);
          }
        }
        for (int j = 12; j <= 15; j++) {
          if (game_map_in_TT[i][j] == 1) {
            n = n + po(2, j - 12);
          }
        }
        display_lM_in_TT[i][1] = hexValue[n][m];
      }
      for (int i = 8; i < 16; i++) {
        display_lM_in_TT[i][0] = 0x01; 
        m = 0;
        n = 0;
        for (int j = 11; j >= 8; j--) {
          if (game_map_in_TT[i][j] == 1) {
            m = m + po(2, 11 - j);
          }
        }
        for (int j = 15; j >= 12; j--) {
          if (game_map_in_TT[i][j] == 1) {
            n = n + po(2, 15 - j);
          }
        }
        display_lM_in_TT[i][1] = hexValue[m][n];
      }
      for (int i = 0; i < 5; i++) {
        int j = score / 10;
        display_lM_in_TT[i + 2][0] = number[3][j][i];
        int k = score % 10;
        display_lM_in_TT[i + 9][0] = number[2][k][i];
      }
      for (int i = 0; i < 8; i++) {
        mx.setRow(0, 0, i, display_lM_in_TT[i + 8][1]);
        mx.setRow(1, 1, i, display_lM_in_TT[i + 8][0]);
        mx.setRow(3, 3, 7 - i, display_lM_in_TT[i][1]);
        mx.setRow(2, 2, 7 - i, display_lM_in_TT[i][0]);
      }
      delay(fps*4);

      for (int i = 0; i <= 4; i++) {
        game_map_in_TT[block[i][0]][block[i][1]] = 0;
      }
    } else {
      //can't down
      for (int i = 0; i <= 4; i++) {
        game_map_in_TT[block[i][0]][block[i][1]] = 1;
      }
      
      //set highest block
      if (highest > block[0][0]) {
        highest = block[0][0];
      }

      //Check full row
      for (int i = block[0][0]; i <= block[3][0] ; i++) {
        int Emty_point = 0;
        //Check light point
        for (int j = 8; j <= 15; j++) {
          if (game_map_in_TT[i][j] == 0) {
            Emty_point++;
            j = 15;
          }
        }

        //Disappear row
        if (Emty_point == 0) {
          for (int j = i; j >= highest; j--) {
            for (int k = 8; k < 16; k++) {
              game_map_in_TT[j][k] = game_map_in_TT[j - 1][k];
            }
          }
          highest++;
          score++;
        }
      }

      if (highest <= 4) {
        end = 1;
      }
      move = 1;
    }
  }

  if (end == 1) {
    for (int i = 0; i < 16; i++) {
      for (int j = 0; j < 2; j++) {
        display_lM_in_TT[i][j] = 0;
      }
    }
    //chu end
    display_lM_in_TT[5][0] = 0x5C;
    display_lM_in_TT[5][1] = 0x1A;
    display_lM_in_TT[4][0] = 0xC4;
    display_lM_in_TT[4][1] = 0x2A;
    display_lM_in_TT[3][0] = 0x5C;
    display_lM_in_TT[3][1] = 0x2B;
    display_lM_in_TT[2][0] = 0x44;
    display_lM_in_TT[2][1] = 0x2A;
    display_lM_in_TT[1][0] = 0x5C;
    display_lM_in_TT[1][1] = 0x1A;

    for (int i = 0; i < 5; i++) {
      int j = score / 10;
      display_lM_in_TT[i + 9][0] = number[0][j][i];
      int k = score % 10;
      display_lM_in_TT[i + 9][1] = number[1][k][i];
    }

    for (int i = 0; i < 8; i++) {
      mx.setRow(0, 0, i, display_lM_in_TT[i + 8][1]);
      mx.setRow(1, 1, i, display_lM_in_TT[i + 8][0]);
      mx.setRow(3, 3, i, display_lM_in_TT[i][1]);
      mx.setRow(2, 2, i, display_lM_in_TT[i][0]);
    }
    while (end == 1) {
      if (digitalRead(CH5) == 0) {
        for (int i = 0; i < 16; i++) {
          for (int j = 0; j < 16; j++) {
            game_map_in_TT[i][j] = 0;
          }
        }
        end = 0;
        highest = 15;
        score = 0;
        for (int i = 0; i < 16; i++) {
          for (int j = 0; j < 16; j++) {
            game_map_in_TT[i][j] = 0;
          }
        }
      }
    }
  }
}


int po(short int a, short int b) {
  short int c = 1;
  for (int i = 0; i < b; i++) {
    c = c * a;
  }
  return c;
}