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
short int game_map_in_FP[10][19] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

unsigned int display_lM_in_FP[16][2];
unsigned short end  = 0;
unsigned short score = 0;
unsigned short distance = 0;
unsigned short bar = 4;
unsigned short bird[2][2] = {5, 4, 4, 5};
int speed;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
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
  //Speed up over time
  if (score < 10) {
    speed = 30;
  } else if (score < 30) {
    speed = 25;
  } else if (score < 50) {
    speed = 15;
  } else if (score < 70) {
    speed = 8;
  }

  //Generated bar
  if (bar <= 5) {
    bar = rand() % (bar + 1) + 2;
  } else if (bar >= 5) {
    bar = rand() % (10 - bar) + (bar - 2);
  } else {
    bar = rand() % 5 + (bar - 2);
  }
  for (int i = 0; i < bar - 1; i++) {
    game_map_in_FP[i][16] = 1;
    game_map_in_FP[i][17] = 1;
  }
  for (int i = bar + 2; i < 10; i++) {
    game_map_in_FP[i][16] = 1;
    game_map_in_FP[i][17] = 1;
  }
  
  //Game play
  for (int k = 0; k < 5; k++) {
    if (digitalRead(CH2) == 0) {
      //End cordition
      if (game_map_in_FP[bird[1][0] - 1][bird[1][1]] == 1 || bird[1][0] - 1 == -1) {
        end  = 1;
      } else if (bird[1][0] + 1 == bird[0][0]) {
        bird[0][0]--;
      } 
      bird[1][0]--;
    } else {
      //End cordition
      if (game_map_in_FP[bird[1][0] + 1][bird[1][1]] == 1 || bird[1][0] + 1 == 10) {
        end  = 1;
      } else if (bird[1][0] - 1 == bird[0][0]) {
        bird[0][0]++;
      } 
      bird[1][0]++;
    }
    //End cordition
    if (game_map_in_FP[bird[1][0]][bird[1][1] + 1] == 1) {
      end = 1;
    }

    if (end == 0) {
      //Move map
      for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 10; j++) {
          game_map_in_FP[j][i] = game_map_in_FP[j][i + 1];
        }
      }
      distance++;

      //Display bird in map
      game_map_in_FP[bird[0][0]][bird[0][1]] = 1;
      game_map_in_FP[bird[1][0]][bird[1][1]] = 1;

      //Display
      //Display game
      for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 2; j++) {
          display_lM_in_FP[i][j] = 0;
        }
      }
      for (int i = 0; i < 8; i++) {
        m = 0;
        n = 0;
        for (int j = 0; j <= 3; j++) {
          if (game_map_in_FP[i][j] == 1) {
            m = m + po(2, j - 0);
          }
        }
        for (int j = 4; j <= 7; j++) {
          if (game_map_in_FP[i][j] == 1) {
            n = n + po(2, j - 4);
          }
        }
        display_lM_in_FP[i][0] = hexValue[n][m];
        m = 0;
        n = 0;
        for (int j = 8; j <= 11; j++) {
          if (game_map_in_FP[i][j] == 1) {
            m = m + po(2, j - 8);
          }
        }
        for (int j = 12; j <= 15; j++) {
          if (game_map_in_FP[i][j] == 1) {
            n = n + po(2, j - 12);
          }
        }
        display_lM_in_FP[i][1] = hexValue[n][m];
      }
      for (int i = 8; i < 10; i++) {
        m = 0;
        n = 0;
        for (int j = 3; j >= 0; j--) {
          if (game_map_in_FP[i][j] == 1) {
            m = m + po(2, 3 - j);
          }
        }
        for (int j = 7; j >= 4; j--) {
          if (game_map_in_FP[i][j] == 1) {
            n = n + po(2, 7 - j);
          }
        }
        display_lM_in_FP[i][0] = hexValue[m][n];
        m = 0;
        n = 0;
        for (int j = 11; j >= 8; j--) {
          if (game_map_in_FP[i][j] == 1) {
            m = m + po(2, 11 - j);
          }
        }
        for (int j = 15; j >= 12; j--) {
          if (game_map_in_FP[i][j] == 1) {
            n = n + po(2, 15 - j);
          }
        }
        display_lM_in_FP[i][1] = hexValue[m][n];
      }
      display_lM_in_FP[10][0] = 0xFF;
      display_lM_in_FP[10][1] = 0xFF;

      //Score
      for (int i = 0; i < 5; i++) {
        if (distance < 9) {
          score = 0;
        } else {
          score = (distance - 9) / 5;
        }
        int j = score / 10;
        display_lM_in_FP[i + 11][0] = number[0][j][i];
        int k = score % 10;
        display_lM_in_FP[i + 11][1] = number[1][k][i];
      }
      Serial.print(number[0][0][4]);
      //Display
      for (int i = 0; i < 8; i++) {
        mx.setRow(0, 0, i, display_lM_in_FP[i + 8][1]);
        mx.setRow(1, 1, i, display_lM_in_FP[i + 8][0]);
        mx.setRow(3, 3, 7 - i, display_lM_in_FP[i][1]);
        mx.setRow(2, 2, 7 - i, display_lM_in_FP[i][0]);
      }
      delay(speed*5);
    }

    //Clear bird in map
    game_map_in_FP[bird[0][0]][bird[0][1]] = 0;
    game_map_in_FP[bird[1][0]][bird[1][1]] = 0;
  }


  //Restart game
  if (end == 1) {
    for (int i = 0; i < 16; i++) {
      for (int j = 0; j < 2; j++) {
        display_lM_in_FP[i][j] = 0;
      }
    }
    //chu end
    display_lM_in_FP[5][0] = 0x5C;
    display_lM_in_FP[5][1] = 0x1A;
    display_lM_in_FP[4][0] = 0xC4;
    display_lM_in_FP[4][1] = 0x2A;
    display_lM_in_FP[3][0] = 0x5C;
    display_lM_in_FP[3][1] = 0x2B;
    display_lM_in_FP[2][0] = 0x44;
    display_lM_in_FP[2][1] = 0x2A;
    display_lM_in_FP[1][0] = 0x5C;
    display_lM_in_FP[1][1] = 0x1A;

    for (int i = 0; i < 5; i++) {
      int j = score / 10;
      display_lM_in_FP[i + 9][0] = number[0][j][i];
      int k = score % 10;
      display_lM_in_FP[i + 9][1] = number[1][k][i];
    }

    for (int i = 0; i < 8; i++) {
      mx.setRow(0, 0, i, display_lM_in_FP[i + 8][1]);
      mx.setRow(1, 1, i, display_lM_in_FP[i + 8][0]);
      mx.setRow(3, 3, i, display_lM_in_FP[i][1]);
      mx.setRow(2, 2, i, display_lM_in_FP[i][0]);
    }
    while (end == 1) {
      if (digitalRead(CH5) == 0) {
        end = 0;
        score = 0;
        distance = 0;
        bar = 4;
        bird[0][0] = 5;
        bird[0][1] = 4;
        bird[1][0] = 4;
        bird[1][1] = 5;
        for (int i = 0; i < 16; i++) {
          for (int j = 0; j < 16; j++) {
            game_map_in_FP[i][j] = 0;
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