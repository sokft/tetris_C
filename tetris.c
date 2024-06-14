#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

//(new) 특수문자 오류 해결 위해 도입
#include <wchar.h>
#include <locale.h>

//(new) 사운드
#include <mmsystem.h>
#include <io.h>
#pragma comment(lib, "winmm.lib")

// 별 모양 정의
#define STAR_EMPTY L'☆'
#define STAR_FULL L'★'

#define LEFT 75 //좌로 이동    //키보드값들 
#define RIGHT 77 //우로 이동 
#define UP 72 //회전 
#define DOWN 80 //soft drop
#define SPACE 32 //hard drop
#define p 112 //일시정지 
#define P 80 //일시정지
#define ESC 27 //게임종료 
#define TAB 9 //(new) 아이템/블럭 변경 
#define ENTER 13 //(new) 치트키, 아이템을 하나 생성
#define SHIFT 16 // 기능은 없음, 일단 추가

#define ACTIVE_BLOCK -2 // 게임판배열에 저장될 블록의 상태들 
#define CEILLING -1     // 블록이 이동할 수 있는 공간은 0 또는 음의 정수료 표현 
#define EMPTY 00         // 블록이 이동할 수 없는 공간은 양수로 표현 
#define WALL 01
#define INACTIVE_BLOCK 02 // 굳은 블럭 대신 색상을 저장

#define BOMB 10 //(new)폭탄
#define THORN 11 //(new)가시
#define DRILL 12 //(new)드릴

#define MAIN_X 11 //게임판 가로크기 
#define MAIN_Y 23 //게임판 세로크기 
#define MAIN_X_ADJ 3 //게임판 위치조정 
#define MAIN_Y_ADJ 1 //게임판 위치조정 

#define STATUS_X_ADJ MAIN_X_ADJ+MAIN_X+1 //게임정보표시 위치조정 

#define INVENTORY_SIZE 3 //(new)인벤토리 최대 크기


int STATUS_Y_GOAL; //GOAL 정보표시위치Y 좌표 저장 
int STATUS_Y_LEVEL; //LEVEL 정보표시위치Y 좌표 저장
int STATUS_Y_SCORE; //SCORE 정보표시위치Y 좌표 저장

int blocks[7][4][4][4] = {
    {
        { // 정사각형
            0,0,0,0,
            0,1,1,0,
            0,1,1,0,
            0,0,0,0
        },{
            0,0,0,0,
            0,1,1,0,
            0,1,1,0,
            0,0,0,0
        },{
            0,0,0,0,
            0,1,1,0,
            0,1,1,0,
            0,0,0,0
        },{
            0,0,0,0,
            0,1,1,0,
            0,1,1,0,
            0,0,0,0
        }
    },{
        { // 일자
            0,0,0,0,
            0,0,0,0,
            1,1,1,1,
            0,0,0,0
        },{
            0,1,0,0,
            0,1,0,0,
            0,1,0,0,
            0,1,0,0
        },{
            0,0,0,0,
            0,0,0,0,
            1,1,1,1,
            0,0,0,0
        },{
            0,1,0,0,
            0,1,0,0,
            0,1,0,0,
            0,1,0,0
        }
    },{
        { // 번개1
            0,0,0,0,
            1,1,0,0,
            0,1,1,0,
            0,0,0,0
        },{
            0,0,0,0,
            0,0,1,0,
            0,1,1,0,
            0,1,0,0
        },{
            0,0,0,0,
            1,1,0,0,
            0,1,1,0,
            0,0,0,0
        },{
            0,0,0,0,
            0,0,1,0,
            0,1,1,0,
            0,1,0,0
        }
    },{
        { // 번개2
            0,0,0,0,
            0,1,1,0,
            1,1,0,0,
            0,0,0,0
        },{
            0,0,0,0,
            1,0,0,0,
            1,1,0,0,
            0,1,0,0
        },{
            0,0,0,0,
            0,1,1,0,
            1,1,0,0,
            0,0,0,0
        },{
            0,0,0,0,
            1,0,0,0,
            1,1,0,0,
            0,1,0,0
        }
    }, {
        { // L자1
            0,0,0,0,
            0,0,1,0,
            1,1,1,0,
            0,0,0,0
        },{
            0,0,0,0,
            1,1,0,0,
            0,1,0,0,
            0,1,0,0
        },{
            0,0,0,0,
            0,0,0,0,
            1,1,1,0,
            1,0,0,0
        },{
            0,0,0,0,
            0,1,0,0,
            0,1,0,0,
            0,1,1,0
        }
    }, {
        { // L자2
            0,0,0,0,
            1,0,0,0,
            1,1,1,0,
            0,0,0,0
        },{
            0,0,0,0,
            0,1,0,0,
            0,1,0,0,
            1,1,0,0
        },{
            0,0,0,0,
            0,0,0,0,
            1,1,1,0,
            0,0,1,0
        },{
            0,0,0,0,
            0,1,1,0,
            0,1,0,0,
            0,1,0,0
        }
    }, {
        { // 못
            0,0,0,0,
            0,1,0,0,
            1,1,1,0,
            0,0,0,0
        },{
            0,0,0,0,
            0,1,0,0,
            0,1,1,0,
            0,1,0,0
        },{
            0,0,0,0,
            0,0,0,0,
            1,1,1,0,
            0,1,0,0
        },{
            0,0,0,0,
            0,1,0,0,
            1,1,0,0,
            0,1,0,0
        }
    }
}; //블록모양 저장 4*4공간에 블록을 표현 blcoks[b_type][b_rotation][i][j]로 사용 

int b_type; //블록 종류를 저장 
int b_rotation; //블록 회전값 저장 
int b_type_next; //다음 블록값 저장 

int main_org[MAIN_Y][MAIN_X]; //게임판의 정보를 저장하는 배열 모니터에 표시후에 main_cpy로 복사됨 
int main_cpy[MAIN_Y][MAIN_X]; //즉 maincpy는 게임판이 모니터에 표시되기 전의 정보를 가지고 있음 
//main의 전체를 계속 모니터에 표시하지 않고(이렇게 하면 모니터가 깜빡거림) 
//main_cpy와 배열을 비교해서 값이 달라진 곳만 모니터에 고침 
int bx, by; //이동중인 블록의 게임판상의 x,y좌표를 저장 

int key; //키보드로 입력받은 키값을 저장 


int goal = 10; // 레벨업 목표 (기본 10)
int hard_mode_block_count = 0; // Hard mode에서 블록 제거를 카운트




int speed; //게임진행속도 
int level; //현재 level 
int level_goal; //다음레벨로 넘어가기 위한 목표점수 
int cnt; //현재 레벨에서 제거한 줄 수를 저장 
int score; //현재 점수 
int last_score = 0; //마지막게임점수 
int best_score = 0; //최고게임점수 
int last_game_score = 0; // 게임 오버 시 점수를 저장할 변수
int frame = 0; //(new) 인게임 아이템 애니메이션을 위한 프레임

int new_block_on = 0; //새로운 블럭이 필요함을 알리는 flag 
int new_item_on = 0; //(new) 새로운 아이템이 필요함을 알리는 flag 
int crush_on = 0; //현재 이동중인 블록이 충돌상태인지 알려주는 flag 
int level_up_on = 0; //다음레벨로 진행(현재 레벨목표가 완료되었음을) 알리는 flag 
int space_key_on = 0; //hard drop상태임을 알려주는 flag 


//(new) 아이템 구조체
typedef struct Item {
    int type; // BOMB | THORN | DRILL
    int x, y;
    int shape[4][4][4]; //모양을 저장, 4가지 회전 형태가 있을 수 있음
}Item;

Item current_item; //(new) 현재 움직이는 아이템을 저장
Item Inventory[INVENTORY_SIZE]; //(new) 아이템 슬롯, 최대 3개의 아이템이 누적
Item next_item = { 0 }; //(new) 다음 아이템, 초기화 추가

bool is_item_moving = false; //(new) 현재 블록이 아닌 아이템을 움직이고 있는가?
bool item_selected = false; //(new) 아이템 선택 여부
int selectedItemIndex = -1; //(new) 선택된 아이템 인덱스

wchar_t drill_char[4] = { L'▽', L'◁', L'△',  L'▷' }; //DRILL을 위한 특수문자 배열 정의
wchar_t bomb_char[3] = { L'○', L'●', L'◎' }; // BOMB을 위한 특수문자 배열 -> 프레임마다 바뀜

const char path_bgm[][30] = {
    "src/BGM_1.mp3",
    "src/BGM_2.mp3",
    "src/BGM_3.mp3",
    "src/BGM_4.mp3",
    "src/BGM_5.mp3"
};


const char textline_bgm[][20] = {
    "Bradinsky     ",
    "Nintendo music",
    "Troika        ",
    "Loginska      ",
    "Kalinka       "
};

int current_bgm = 0; // index 0~4

const char* path_sound_hard_drop = "./src/crush.wav";
const char* path_sound_bomb = "./src/bomb.wav";
const char* path_sound_drill = "./src/drill.wav";
const char* path_sound_thorn = "./src/thorn.mp3";
const char* path_sound_block_crush = "./src/drop.mp3";
const char* path_sound_item = "./src/item.wav";

int bgm_volume = 50;
int sound_volume = 50;


//(new) 무작위 아이템을 만드는 함수
Item createRandomItem();
//(new) 지정된 아이템 만드는 함수
Item createItem(int type);
//(new) 인벤토리에 아이템 추가하는 함수
void addItemToInventory(Item item);
//(new) 인벤토리를 그리는 함수
void draw_inventory(void);

void title(void); //게임시작화면 
void reset(void); //게임판 초기화 
void reset_main(void); //메인 게임판(main_org[][]를 초기화)
void reset_main_cpy(void); //copy 게임판(main_cpy[][]를 초기화)
void draw_map(void); //게임 전체 인터페이스를 표시 
void draw_main(void); //게임판을 그림 
void new_block(void); //새로운 블록을 하나 만듦 
void check_key(void); //키보드로 키를 입력받음 
void drop_block(void); //블록을 아래로 떨어트림 
int check_crush(int bx, int by, int rotation); //bx, by위치에 rotation회전값을 같는 경우 충돌 판단 
void move_block(int dir); //dir방향으로 블록을 움직임 
void check_line(void); //줄이 가득찼는지를 판단하고 지움 
void check_level_up(void); //레벨목표가 달성되었는지를 판단하고 levelup시킴 
void check_game_over(void); //게임오버인지 판단하고 게임오버를 진행 
void pause(void);//게임을 일시정지시킴 

void playBGM(const char* bgmFile);
void setBGMVolume(int vol);
void stopBGM();
void playEffect(const char* soundFile);
void setEffectVolume(int vol);

void displayMenuTabs(int x, int y);

// (new) 현재 아이템과 블록을 교환하는 함수
void exchange_block_item(void);
// (new) 폭탄 : 특정 범위의 블록을 모두 EMPTY로 변경(파괴)
void activateBomb(int x, int y);
// (new) 가시 : 수평 라인 제거
void activateThorn(void);
// (new) 드릴 : 수직 라인 제거
void activateDrill(int x, int y);
// (new) 원래 new_block에 있던 next의 블록을 생성하는 기능을 옮겨옴
void update_next();
void playSound(const char* soundFile); //(new) 사운드 재생 함수

void gotoxy(int x, int y) { //gotoxy함수 
    COORD pos = { 2 * x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}



//블럭 색상 입히기
#define COLOR_OFFSET 100 // 색상을 저장할 때 사용할 오프셋 값

#define GREEN 2
#define YELLOW 6
#define BLUE 1
#define PURPLE 5
#define CYAN 3
#define RED 4
#define WHITE 7
#define WALL_COLOR_NORMAL WHITE
#define WALL_COLOR_HARD RED

int getColorByBlockType(int blockType) {
    switch (blockType) {
    case 0: return GREEN; // 정사각형
    case 1: return YELLOW; // 일자
    case 2: return BLUE; // 번개1
    case 3: return PURPLE; // 번개2
    case 4: return CYAN; // L자1
    case 5: return RED; // L자2
    case 6: return WHITE; // 못
    default: return WHITE; // 기본 색상
    }
}

// 블록 색상 설정을 위한 배열
int blockColors[7] = { GREEN, YELLOW, BLUE, PURPLE, CYAN, RED, WHITE };

// 게임판의 색상을 저장하는 배열
int main_color[MAIN_Y][MAIN_X];
int main_color_cpy[MAIN_Y][MAIN_X];


void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void printBlock(int x, int y, int color) {
    setColor(color);
    gotoxy(x, y);
    printf("■");
    setColor(WHITE); // 기본 색상으로 되돌림
}

void clearBlock(int x, int y) {
    gotoxy(x, y);
    printf("  ");
}


typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE; //커서숨기는 함수에 사용되는 열거형 
void setcursortype(CURSOR_TYPE c) { //커서숨기는 함수 
    CONSOLE_CURSOR_INFO CurInfo;

    switch (c) {
    case NOCURSOR:
        CurInfo.dwSize = 1;
        CurInfo.bVisible = FALSE;
        break;
    case SOLIDCURSOR:
        CurInfo.dwSize = 100;
        CurInfo.bVisible = TRUE;
        break;
    case NORMALCURSOR:
        CurInfo.dwSize = 20;
        CurInfo.bVisible = TRUE;
        break;
    }
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}




//main함수
int main() {
    setlocale(LC_CTYPE, "");
    int i;

    srand((unsigned)time(NULL)); //난수표생성 
    setcursortype(NOCURSOR); //커서 없앰 
    title(); //메인타이틀 호출 
    reset();//게임판 리셋 

    while (1) {
        for (i = 0; i < 5; i++) { //블록이 한칸떨어지는동안 5번 키입력받을 수 있음 
            check_key(); //키입력확인 
            draw_main(); //화면을 그림 
            Sleep(speed); //게임속도조절 
            if (crush_on && check_crush(bx, by + 1, b_rotation) == false) Sleep(100);
            //블록이 충돌중인경우 추가로 이동및 회전할 시간을 갖음 
            if (space_key_on == 1) { //스페이스바를 누른경우(hard drop) 추가로 이동및 회전할수 없음 break; 
                space_key_on = 0;
                break;
            }
        }
        drop_block(); // 블록을 한칸 내림 
        check_level_up(); // 레벨업을 체크 
        check_game_over(); //게임오버를 체크 
        if (new_block_on == 1) new_block(); // 뉴 블럭 flag가 있는 경우 새로운 블럭 생성 
    }
}

#define WHITE 7
#define YELLOW 6
#define RED 4
#define GREEN 2
#define BLUE 1


bool hard_mode = false;
char textline_normal_mode_checked[] = { "노말 모드  ■  |  하드 모드  □" };
char textline_hard_mode_checked[] = { "노말 모드  □  |  하드 모드  ■" };
char textline_starting_level[] = { "  시작 레벨      | " };
char textline_sound_warning[] = { "음량에 주의하세요" };

int select_position; // 메인화면 커서의 위치
int start_level = 1;

void showGameSetting(int x, int y); // (new) 메인 화면 우측에 게임 설정 및 시작 창 보여줌
void showKeyBindings(int x, int y); // (new) 메인 화면 우측에 단축키 보여줌
void showAchievement(int x, int y); // (new) 메인 화면 우측에 업적 창 보여줌
void clearMenuArea(int x, int y, int width, int height);

bool shouldGenerateItem() {
    int chance = hard_mode ? 4 : 2;  // hard mode는 1/4, easy mode는 1/2 확률
    return (rand() % chance == 0);
}

void printChar(char str[]);
void printCharColor(char str[], int color_change_start, int color_change_end, int color);
void setTextColor(WORD color);
void displayMode(int x, int y);

#define MODE_MENU 0
#define BINDINGS_MENU 1
#define ACHIEVEMENTS_MENU 2

int currentMenu = MODE_MENU;

void title(void) {
    int x = 5; //타이틀화면이 표시되는 x좌표 
    int y = 4; //타이틀화면이 표시되는 y좌표 
    int cnt; //타이틀 프레임을 세는 변수  

    gotoxy(x, y + 0); printf("■□□□■■■□□■■□□■■"); Sleep(100);
    gotoxy(x, y + 1); printf("■                          ■"); Sleep(100);
    gotoxy(x, y + 2); printf("□                          □"); Sleep(100);
    gotoxy(x, y + 3); printf("■                          □"); Sleep(100);
    gotoxy(x, y + 4); printf("■■  ■□□□■■■□■■□□"); Sleep(100);
    gotoxy(x, y + 5); printf("                              "); Sleep(100);
    gotoxy(x + 5, y + 2); printf("테 트 리 스"); Sleep(100);

    gotoxy(x, y + 8); printf("□□         시작         □□");

    gotoxy(x, y + 11); printf("□□        조작법        □□");

    gotoxy(x, y + 14); printf("□□         업적         □□");

    gotoxy(x, y + 18); printf("|| 기초컴퓨터프로그래밍 4조 ||");
    gotoxy(x, y + 20); printf("강이원, 나세연, 이재윤, 한지강");

    current_bgm = rand() % 5;
    playBGM(path_bgm[current_bgm]);
    setEffectVolume(sound_volume);


    for (cnt = 0;; cnt++) { // cnt를 1씩 증가시키면서 계속 반복  
        //gotoxy(x, y + 13); printf("select_position : %d", select_position);
        //gotoxy(x, y + 14); printf("start_level : %d", start_level);
        if (_kbhit()) {
            //clearMenuArea(x + 23, y + 4, 50, 21);
            key = _getch();
            if (key == 224) { // 방향키인경우 
                key = _getch();
                switch (key) {
                case LEFT: // 왼쪽 방향키 (LEFT)
                    if (select_position % 4 == 0) hard_mode = false;
                    if (select_position % 4 == 1) {
                        current_bgm = (current_bgm > 0) ? current_bgm - 1 : 4;
                        stopBGM;
                        playBGM(path_bgm[current_bgm]);
                    }
                    if (select_position % 4 == 2) {
                        bgm_volume = (bgm_volume > 0) ? bgm_volume - 5 : 0;
                        setBGMVolume(bgm_volume);
                    }
                    if (select_position % 4 == 3) start_level = (start_level > 1) ? start_level - 1 : 10;
                    break;
                case RIGHT: // 오른쪽 방향키 (RIGHT)
                    if (select_position % 4 == 0) hard_mode = true;
                    if (select_position % 4 == 1) {
                        current_bgm = (current_bgm < 4) ? current_bgm + 1 : 0;
                        stopBGM;
                        playBGM(path_bgm[current_bgm]);
                    }
                    if (select_position % 4 == 2) {
                        bgm_volume = (bgm_volume < 100) ? bgm_volume + 5 : 100;
                        setBGMVolume(bgm_volume);
                    }
                    if (select_position % 4 == 3) start_level = (start_level < 10) ? start_level + 1 : 1;
                    break;
                case UP: // 위쪽 방향키 (UP)
                    select_position = (select_position > 1) ? select_position - 1 : 4;
                    break;
                case DOWN: // 오른쪽 방향키 (DOWN)
                    select_position = (select_position < 4) ? select_position + 1 : 1;
                    break;
                }
            }

            if (key == ' ') break; // Space가 입력되면 루프 탈출
            if (key == TAB) {
                currentMenu = (currentMenu + 1) % 3;
                clearMenuArea(x + 23, y + 4, 50, 21);
            }
        }
        displayMenuTabs(x, y); // (new) 현재 선택된 메뉴 탭 강조 표시
        if (currentMenu == MODE_MENU) {
            showGameSetting(x + 25, y);
        }
        else if (currentMenu == BINDINGS_MENU) {
            showKeyBindings(x + 25, y);
        }
        else if (currentMenu == ACHIEVEMENTS_MENU) {
            showAchievement(x + 25, y);
        }
        Sleep(100);
    }
    goal = hard_mode ? 5 : 10;
    while (_kbhit()) _getch(); //버퍼에 기록된 키값을 버림 
}




void printChar(char str[]) {
    for (int i = 0; str[i] != '\0'; i++) {
        printf("%c", str[i]);
    }
}

// 특정 구간의 텍스트 색상을 바꿈
void printCharColor(char str[], int color_change_start, int color_change_end, int color) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (i == color_change_start) { setTextColor(color); }
        if (i == color_change_end) { setTextColor(WHITE); }
        printf("%c", str[i]);
    }
    setTextColor(WHITE);//기본 콘솔 텍스트 색상이 7
}

// 주요 색상 - 파란색(1), 초록색(2), 청록색(3), 빨간색(4), 노란색(6), 흰색(7)
void setTextColor(WORD color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// 게임 세팅 설정하는 창
void showGameSetting(int x, int y) {
    gotoxy(x, y + 4); printf("=====      게임 모드      =====");

    gotoxy(x, y + 7); printf("||           난이도          ||");
    gotoxy(x - 2, y + 9); if (select_position % 4 == 0) printf("> "); else printf("  ");

    gotoxy(x, y + 9);
    if (hard_mode) printCharColor(textline_hard_mode_checked, 17, 28, select_position % 3 == 0 ? YELLOW : WHITE);
    else printCharColor(textline_normal_mode_checked, 0, 11, select_position % 3 == 0 ? YELLOW : WHITE);

    gotoxy(x, y + 12); printf("||         사전 설정         ||");
    /*
    gotoxy(x - 2, y + 14); if (select_position % 3 == 1) printf("> "); else printf("  ");

    gotoxy(x, y + 14);
    if (duo_mode) printCharColor(textline_duo_mode_checked, 17, 27, select_position % 3 == 1 ? YELLOW : WHITE);
    else printCharColor(textline_solo_mode_checked, 0, 11, select_position % 3 == 1 ? YELLOW : WHITE);
    */

    gotoxy(x - 2, y + 15); if (select_position % 4 == 1) printf("> "); else printf("  ");
    printf("  BGM  유형      |  %s ", textline_bgm[current_bgm]);
    gotoxy(x - 2, y + 16); if (select_position % 4 == 2) printf("> "); else printf("  ");
    printf("  BGM  볼륨      |  %d ", bgm_volume);
    gotoxy(x, y + 17);
    if (bgm_volume >= 70) printCharColor(textline_sound_warning, 0, 17, RED);
    else printf("                    ");

    gotoxy(x - 2, y + 18); if (select_position % 4 == 3) printf("> "); else printf("  ");
    printf("  시작 레벨      |  %d ", start_level);

    gotoxy(x, y + 20); printf("===============================");
}

void displayMenuTabs(int x, int y) {
    gotoxy(x, y + 8);
    if (currentMenu == MODE_MENU) {
        setTextColor(YELLOW);
    }
    printf("□□         시작         □□");
    setTextColor(WHITE);

    gotoxy(x, y + 11);
    if (currentMenu == BINDINGS_MENU) {
        setTextColor(YELLOW);
    }
    printf("□□        조작법        □□");
    setTextColor(WHITE);

    gotoxy(x, y + 14);
    if (currentMenu == ACHIEVEMENTS_MENU) {
        setTextColor(YELLOW);
    }
    printf("□□         업적         □□");
    setTextColor(WHITE);
}

void showKeyBindings(int x, int y) {
    gotoxy(x, y + 4); printf("======      단 축 키      ======");
    gotoxy(x, y + 7); printf("  △   : 회전");
    gotoxy(x, y + 8); printf("◁  ▷ : 왼쪽 / 오른쪽 이동");
    gotoxy(x, y + 9); printf("  ▽   : 아래쪽 이동");
    gotoxy(x, y + 10); printf(" SPACE : 하드 드롭 / 게임시작");
    gotoxy(x, y + 11); printf("   P   : 일시정지");
    gotoxy(x, y + 12); printf("  ESC  : 종료");
    gotoxy(x, y + 13); printf("  TAP  : 아이템 활성화");
    gotoxy(x, y + 20); printf("===============================");
}

void showAchievement(int x, int y) {
    gotoxy(x, y + 4);  printf("=======       업적       =======");

    gotoxy(x, y + 7);  printf(" -        테트리스 전공       - ");
    gotoxy(x, y + 8);  printf("           레벨 7 도달          ");

    gotoxy(x, y + 10); printf(" -    대충 살자.  가시처럼    - ");
    gotoxy(x, y + 11); printf("      가시로 블럭 제거 실패     ");

    gotoxy(x, y + 13); printf(" -      폭발은  예술이다      - ");
    gotoxy(x, y + 14); printf("폭탄 하나로 12개 이상의 블럭 제거");

    gotoxy(x, y + 16); printf(" -         월급  루팡         - ");
    gotoxy(x, y + 17); printf("   드릴로 딱 한 개의 블럭 제거  ");

    gotoxy(x, y + 20); printf("===============================");
}

void clearMenuArea(int x, int y, int width, int height) {
    for (int i = 0; i < height; i++) {
        gotoxy(x, y + i);
        for (int j = 0; j < width; j++) {
            printf(" ");
        }
    }
}





void reset(void) {
    FILE* file = fopen("score.dat", "rt"); // score.dat파일을 연결 
    if (file == 0) { best_score = 0; } //파일이 없으면 걍 최고점수에 0을 넣음 
    else {
        fscanf(file, "%d", &best_score); // 파일이 열리면 최고점수를 불러옴 
        fclose(file); //파일 닫음 
    }

    level = 1; //각종변수 초기화 
    score = 0;
    cnt = 0;
    goal = hard_mode ? 5 : 10; // Hard mode에서는 목표를 5로 설정
    key = 0;
    crush_on = 0;
    hard_mode_block_count = 0;
    speed = hard_mode ? 25 : 100; // Hard mode에서는 기본 속도를 더 빠르게 설정

    system("cls"); //화면지움 
    reset_main(); // main_org를 초기화 
    draw_map(); // 게임화면을 그림
    draw_main(); // 게임판을 그림 

    b_type_next = rand() % 7; //다음번에 나올 블록 종류를 랜덤하게 생성 
    new_block(); //새로운 블록을 하나 만듦  

    gotoxy(STATUS_X_ADJ, STATUS_Y_GOAL); // GOAL 값을 다시 출력
    printf(" GOAL  : %5d", goal - cnt);
}



//게임판을 초기화 
void reset_main(void) {
    int i, j;

    for (i = 0; i < MAIN_Y; i++) { // 게임판을 0으로 초기화  
        for (j = 0; j < MAIN_X; j++) {
            main_org[i][j] = 0;
            main_cpy[i][j] = 100;
            main_color[i][j] = WHITE; // 기본 색상으로 초기화
            main_color_cpy[i][j] = WHITE; // 기본 색상으로 초기화
        }
    }
    for (j = 1; j < MAIN_X; j++) { //y값이 3인 위치에 천장을 만듦 
        main_org[3][j] = CEILLING;
    }
    for (i = 1; i < MAIN_Y - 1; i++) { //좌우 벽을 만듦  
        main_org[i][0] = WALL;
        main_color[i][0] = hard_mode ? RED : WHITE; // 벽 색상 설정
        main_org[i][MAIN_X - 1] = WALL;
        main_color[i][MAIN_X - 1] = hard_mode ? RED : WHITE; // 벽 색상 설정
    }
    for (j = 0; j < MAIN_X; j++) { //바닥벽을 만듦 
        main_org[MAIN_Y - 1][j] = WALL;
        main_color[MAIN_Y - 1][j] = hard_mode ? RED : WHITE; // 바닥 색상 설정
    }
}



//main_cpy를 초기화 
void reset_main_cpy(void) {
    int i, j;

    for (i = 0; i < MAIN_Y; i++) {         //게임판에 게임에 사용되지 않는 숫자를 넣음 
        for (j = 0; j < MAIN_X; j++) {  //이는 main_org와 같은 숫자가 없게 하기 위함 
            main_cpy[i][j] = 100;
        }
    }
}


//next와 inventory그리는 것
void draw_map(void) { //게임 상태 표시를 나타내는 함수  
    int y = 3;             // level, goal, score만 게임중에 값이 바뀔수 도 있음 그 y값을 따로 저장해둠 
    // 그래서 혹시 게임 상태 표시 위치가 바뀌어도 그 함수에서 안바꿔도 되게.. 
    gotoxy(STATUS_X_ADJ, STATUS_Y_LEVEL = y); printf(" LEVEL : %5d", level);
    gotoxy(STATUS_X_ADJ, STATUS_Y_GOAL = y + 1); printf(" GOAL  : %5d", 10 - cnt);
    gotoxy(STATUS_X_ADJ, y + 2); printf("+-  N E X T  -+       +- INVENTORY -+");
    gotoxy(STATUS_X_ADJ, y + 3); printf("|             |       |             |");
    gotoxy(STATUS_X_ADJ, y + 4); printf("|             |       |             |");
    gotoxy(STATUS_X_ADJ, y + 5); printf("|             |       |             |");
    gotoxy(STATUS_X_ADJ, y + 6); printf("|             |       |             |");
    gotoxy(STATUS_X_ADJ, y + 7); printf("+-- -  -  - --+       +-- -  -  - --+");
    gotoxy(STATUS_X_ADJ, y + 8); printf(" YOUR SCORE :");
    gotoxy(STATUS_X_ADJ, STATUS_Y_SCORE = y + 9); printf("        %6d", score);
    gotoxy(STATUS_X_ADJ, y + 10); printf(" LAST SCORE :");
    gotoxy(STATUS_X_ADJ, y + 11); printf("        %6d", last_score);
    gotoxy(STATUS_X_ADJ, y + 12); printf(" BEST SCORE :");
    gotoxy(STATUS_X_ADJ, y + 13); printf("        %6d", best_score);
    gotoxy(STATUS_X_ADJ, y + 15); printf("  △   : Shift        SPACE : Hard Drop");
    gotoxy(STATUS_X_ADJ, y + 16); printf("◁  ▷ : Left / Right   P   : Pause");
    gotoxy(STATUS_X_ADJ, y + 17); printf("  ▽   : Soft Drop     ESC  : Quit");
    //gotoxy(STATUS_X_ADJ, y + 20); printf("blog.naver.com/azure0777");
}


void draw_main(void) {
    int i, j;

    for (j = 1; j < MAIN_X - 1; j++) {
        if (main_org[3][j] == EMPTY) main_org[3][j] = CEILLING;
    }
    for (i = 0; i < MAIN_Y; i++) {
        for (j = 0; j < MAIN_X; j++) {
            if (main_cpy[i][j] != main_org[i][j] || main_color_cpy[i][j] != main_color[i][j]) {
                gotoxy(MAIN_X_ADJ + j, MAIN_Y_ADJ + i);
                switch (main_org[i][j]) {
                case EMPTY:
                    printf("  ");
                    break;
                case CEILLING:
                    printf(". ");
                    break;
                case WALL:
                    if (hard_mode) setTextColor(RED);
                    else setTextColor(WHITE);
                    printf("▩");
                    setTextColor(WHITE); // 기본 색상으로 되돌림
                    break;
                case INACTIVE_BLOCK:
                case ACTIVE_BLOCK:
                    setTextColor(main_color[i][j]);
                    printf("■");
                    setTextColor(WHITE); // 기본 색상으로 되돌림
                    break;
                case BOMB:
                    setTextColor(RED);
                    wprintf(L"%lc", STAR_EMPTY);
                    setTextColor(WHITE);
                    break;
                case THORN:
                    setTextColor(WHITE);
                    wprintf(L"%lc", drill_char[2]);
                    setTextColor(WHITE);
                    break;
                case DRILL:
                    setTextColor(YELLOW);
                    printf("▽");
                    setTextColor(WHITE);
                    break;
                default:
                    setTextColor(main_color[i][j]);
                    printf("■");
                    setTextColor(WHITE); // 기본 색상으로 되돌림
                    break;
                }
            }
        }
    }
    for (i = 0; i < MAIN_Y; i++) {
        for (j = 0; j < MAIN_X; j++) {
            main_cpy[i][j] = main_org[i][j];
            main_color_cpy[i][j] = main_color[i][j];
        }
    }
}

void addItemToInventory(Item item) {
    for (int i = 0; i < INVENTORY_SIZE; i++) {
        if (Inventory[i].type == 0) {
            Inventory[i] = item;
            break;
        }
    }
    draw_inventory();
}







//화면에 호출
void drawNextBlock(int blockType, int rotation, int x, int y) {
    int color = getColorByBlockType(blockType);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (blocks[blockType][rotation][i][j] == 1) {
                printBlock(x + j, y + i, color);
            }
            else {
                gotoxy(x + j, y + i);
                printf("  ");
            }
        }
    }
}



//next block만들기
void update_next() {
    b_type_next = rand() % 7; //다음 블럭을 만듦 
    for (int i = 1; i < 3; i++) { //게임상태표시에 다음에 나올블럭을 그림 
        for (int j = 0; j < 4; j++) {
            if (blocks[b_type_next][0][i][j] == 1) {
                gotoxy(STATUS_X_ADJ + 2 + j, i + 6);
                printf("■");
            }
            else {
                gotoxy(STATUS_X_ADJ + 2 + j, i + 6);
                printf("  ");
            }
        }
    }
}
void check_key(void) {
    key = 0;

    if (_kbhit()) {
        key = _getch();
        if (key == 224) {
            key = _getch();
            switch (key) {
            case LEFT:
                if (check_crush(bx - 1, by, b_rotation)) move_block(LEFT);
                break;
            case RIGHT:
                if (check_crush(bx + 1, by, b_rotation)) move_block(RIGHT);
                break;
            case DOWN:
                if (check_crush(bx, by + 1, b_rotation)) move_block(DOWN);
                break;
            case UP:
                if (check_crush(bx, by, (b_rotation + 1) % 4)) move_block(UP);
                else if (crush_on && check_crush(bx, by - 1, (b_rotation + 1) % 4)) move_block(100);
            }
        }
        else {
            switch (key) {
            case SPACE:
                space_key_on = 1;
                while (!crush_on) {
                    drop_block();
                    score += level;
                    gotoxy(STATUS_X_ADJ, STATUS_Y_SCORE); printf("        %6d", score);
                }
                playEffect(path_sound_hard_drop);
                break;
            case P:
            case p:
                pause();
                break;
            case ESC:
                system("cls");
                exit(0);
            case TAB:
                if (item_selected && Inventory[selectedItemIndex].type == THORN) {
                    activateThorn();
                    Inventory[selectedItemIndex].type = 0;
                    item_selected = false;
                    selectedItemIndex = -1;
                    draw_inventory();
                }
                else {
                    exchange_block_item();
                }
                break;
            case ENTER:
                addItemToInventory(createItem(THORN));
                break;
            }
        }
    }
    while (_kbhit()) _getch();
}





//아래로 이동 & 충돌하여 더이상 내려갈 수 없는 경우 inactive상태로 변경
//색상도저장, new blcok on flag켜서 새로운 블록 생성준비
void drop_block(void) {
    int i, j;

    if (crush_on && check_crush(bx, by + 1, b_rotation)) crush_on = 0;
    if (crush_on && !check_crush(bx, by + 1, b_rotation)) {
        for (i = 0; i < MAIN_Y; i++) {
            for (j = 0; j < MAIN_X; j++) {
                if (main_org[i][j] == ACTIVE_BLOCK) {
                    main_org[i][j] = INACTIVE_BLOCK;
                    main_color[i][j] = getColorByBlockType(b_type);
                }
                else if (main_org[i][j] >= BOMB && main_org[i][j] <= DRILL) {
                    int item_type = main_org[i][j];
                    switch (item_type) {
                    case BOMB:
                        activateBomb(i, j);
                        break;
                    case THORN:
                        activateThorn();
                        break;
                    case DRILL:
                        activateDrill(i, j);
                        break;
                    }
                    main_org[i][j] = EMPTY;
                }
            }
        }
        crush_on = 0;
        check_line();
        new_block_on = 1;
        playEffect(path_sound_block_crush);
        return;
    }
    if (check_crush(bx, by + 1, b_rotation)) move_block(DOWN);
    else crush_on++;
}


// Bomb 아이템을 활성화하는 함수 수정
void activateBomb(int x, int y) {
    int range = 1; // 폭탄의 폭발 범위
    int i, j;

    // 폭탄이 터질 범위 내의 블록들을 별로 바꾸고 깜빡이게 함
    for (i = x - range; i <= x + range; i++) {
        for (j = y - range; j <= y + range; j++) {
            // 배열 범위를 벗어나지 않는지 확인
            if (i >= 0 && i < MAIN_Y && j >= 0 && j < MAIN_X && main_org[i][j] != WALL) {
                main_org[i][j] = THORN; // 별 모양으로 임시 변경
                main_color[i][j] = WHITE; // 별의 색상 설정
            }
        }
    }
    draw_main(); // 화면에 별 모양을 그림
    Sleep(500);

    // 별을 깜빡이게 함
    for (int k = 0; k < 2; k++) {
        for (i = x - range; i <= x + range; i++) {
            for (j = y - range; j <= y + range; j++) {
                if (i >= 0 && i < MAIN_Y && j >= 0 && j < MAIN_X && main_org[i][j] == THORN) {
                    gotoxy(MAIN_X_ADJ + j, MAIN_Y_ADJ + i);
                    wprintf(L"%lc", STAR_FULL);
                }
            }
        }
        Sleep(200);
        for (i = x - range; i <= x + range; i++) {
            for (j = y - range; j <= y + range; j++) {
                if (i >= 0 && i < MAIN_Y && j >= 0 && j < MAIN_X && main_org[i][j] == THORN) {
                    gotoxy(MAIN_X_ADJ + j, MAIN_Y_ADJ + i);
                    wprintf(L"%lc", STAR_EMPTY);
                }
            }
        }
        Sleep(200);
    }

    playEffect(path_sound_bomb);

    // 별 모양을 지우고 실제 블록들을 제거함
    for (i = x - range; i <= x + range; i++) {
        for (j = y - range; j <= y + range; j++) {
            if (i >= 0 && i < MAIN_Y && j >= 0 && j < MAIN_X && main_org[i][j] == THORN) {
                main_org[i][j] = EMPTY;
            }
        }
    }
    draw_main(); // 화면을 다시 그림
}


void activateDrill(int x, int y) {
    // 드릴이 제거할 블록들을 별로 바꾸고 깜빡이게 함
    for (int i = x; i < MAIN_Y - 1; i++) { // 바닥(WALL) 바로 위까지만 제거
        if (main_org[i][y] != WALL) {
            main_org[i][y] = THORN; // 별 모양으로 임시 변경
            main_color[i][y] = WHITE; // 별의 색상 설정
        }
        else {
            break;
        }
    }
    draw_main(); // 화면에 별 모양을 그림
    Sleep(500);

    // 별을 깜빡이게 함
    for (int k = 0; k < 2; k++) {
        for (int i = x; i < MAIN_Y - 1; i++) {
            if (main_org[i][y] == THORN) {
                gotoxy(MAIN_X_ADJ + y, MAIN_Y_ADJ + i);
                wprintf(L"%lc", STAR_FULL);
            }
        }
        Sleep(200);
        for (int i = x; i < MAIN_Y - 1; i++) {
            if (main_org[i][y] == THORN) {
                gotoxy(MAIN_X_ADJ + y, MAIN_Y_ADJ + i);
                wprintf(L"%lc", STAR_EMPTY);
            }
        }
        Sleep(200);
    }

    playEffect(path_sound_drill);

    // 별 모양을 지우고 실제 블록들을 제거함
    for (int i = x; i < MAIN_Y - 1; i++) {
        if (main_org[i][y] == THORN) {
            main_org[i][y] = EMPTY;
        }
    }
    draw_main(); // 화면을 다시 그림
}

void activateThorn() {
    int i, j;
    bool star_present = false;

    // 별이 있는지 확인하고 있다면 star_present를 true로 설정
    for (i = 0; i < MAIN_Y; i++) {
        for (j = 0; j < MAIN_X; j++) {
            if (main_org[i][j] == THORN) {
                star_present = true;
                main_org[i][j] = EMPTY;
            }
        }
    }

    if (star_present) {
        // 맨 아래 줄을 별로 바꾸고 반짝이게 함
        for (j = 1; j < MAIN_X - 1; j++) {
            main_org[MAIN_Y - 2][j] = THORN;
            main_color[MAIN_Y - 2][j] = WHITE; // 별의 색상 설정
        }
        draw_main();
        Sleep(500);

        for (int k = 0; k < 2; k++) {
            for (j = 1; j < MAIN_X - 1; j++) {
                gotoxy(MAIN_X_ADJ + j, MAIN_Y_ADJ + MAIN_Y - 2);
                wprintf(L"%lc", STAR_FULL);
            }
            Sleep(200);
            for (j = 1; j < MAIN_X - 1; j++) {
                gotoxy(MAIN_X_ADJ + j, MAIN_Y_ADJ + MAIN_Y - 2);
                wprintf(L"%lc", STAR_EMPTY);
            }
            Sleep(200);
        }

        playEffect(path_sound_thorn);

        // 맨 아래 줄 삭제
        for (j = 1; j < MAIN_X - 1; j++) {
            main_org[MAIN_Y - 2][j] = EMPTY;
        }

        // 위에 있는 블록들을 한 줄씩 내림
        for (i = MAIN_Y - 3; i > 3; i--) {
            for (j = 1; j < MAIN_X - 1; j++) {
                main_org[i + 1][j] = main_org[i][j];
                main_color[i + 1][j] = main_color[i][j];
            }
        }

        // 천장 바로 아래 줄을 빈칸으로 설정 (기존 블록이 한 줄씩 내려온 후)
        for (j = 1; j < MAIN_X - 1; j++) {
            main_org[4][j] = EMPTY;
            main_color[4][j] = WHITE; // 천장 아래 줄 색상 초기화
        }

        draw_main();
    }
}





int check_crush(int bx, int by, int b_rotation) {
    int i, j;

    if (is_item_moving) {
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (current_item.shape[b_rotation][i][j] == 1 && main_org[by + i][bx + j] > 0) return false;
            }
        }
    }
    else {
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1 && main_org[by + i][bx + j] > 0) return false;
            }
        }
    }
    return true;
}

void new_block(void) {
    int i, j;
    if (is_item_moving) is_item_moving = false;

    bx = (MAIN_X / 2) - 1;
    by = 0;
    b_type = b_type_next;
    b_rotation = 0;
    new_block_on = 0;

    if (item_selected) {
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (next_item.shape[b_rotation][i][j] == 1) {
                    main_org[by + i][bx + j] = next_item.type;
                    main_color[by + i][bx + j] = blockColors[next_item.type - 10]; // 아이템 색상 설정
                }
            }
        }
        is_item_moving = true;
        current_item = next_item;
        Inventory[selectedItemIndex] = (Item){ 0 };  // 선택한 아이템을 인벤토리에서 제거
        selectedItemIndex = -1;
        item_selected = false;
    }
    else {
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) {
                    main_org[by + i][bx + j] = ACTIVE_BLOCK;
                    main_color[by + i][bx + j] = blockColors[b_type]; // 블록 색상 설정
                }
            }
        }
    }

    update_next();
}

void move_block(int dir) {
    int i, j;

    switch (dir) {
    case LEFT:
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (is_item_moving && current_item.shape[b_rotation][i][j] == 1) {
                    main_org[by + i][bx + j] = EMPTY;
                    main_color[by + i][bx + j] = WHITE;
                }
                else if (!is_item_moving && blocks[b_type][b_rotation][i][j] == 1) {
                    main_org[by + i][bx + j] = EMPTY;
                    main_color[by + i][bx + j] = WHITE;
                }
            }
        }
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (is_item_moving && current_item.shape[b_rotation][i][j] == 1) {
                    main_org[by + i][bx + j - 1] = current_item.type;
                    main_color[by + i][bx + j - 1] = YELLOW;  // 아이템의 색상 설정
                }
                else if (!is_item_moving && blocks[b_type][b_rotation][i][j] == 1) {
                    main_org[by + i][bx + j - 1] = ACTIVE_BLOCK;
                    main_color[by + i][bx + j - 1] = getColorByBlockType(b_type);  // 블록의 색상 설정
                }
            }
        }
        bx--;
        break;

    case RIGHT:
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (is_item_moving && current_item.shape[b_rotation][i][j] == 1) {
                    main_org[by + i][bx + j] = EMPTY;
                    main_color[by + i][bx + j] = WHITE;
                }
                else if (!is_item_moving && blocks[b_type][b_rotation][i][j] == 1) {
                    main_org[by + i][bx + j] = EMPTY;
                    main_color[by + i][bx + j] = WHITE;
                }
            }
        }
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (is_item_moving && current_item.shape[b_rotation][i][j] == 1) {
                    main_org[by + i][bx + j + 1] = current_item.type;
                    main_color[by + i][bx + j + 1] = YELLOW;  // 아이템의 색상 설정
                }
                else if (!is_item_moving && blocks[b_type][b_rotation][i][j] == 1) {
                    main_org[by + i][bx + j + 1] = ACTIVE_BLOCK;
                    main_color[by + i][bx + j + 1] = getColorByBlockType(b_type);  // 블록의 색상 설정
                }
            }
        }
        bx++;
        break;

    case DOWN:
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (is_item_moving && current_item.shape[b_rotation][i][j] == 1) {
                    main_org[by + i][bx + j] = EMPTY;
                    main_color[by + i][bx + j] = WHITE;
                }
                else if (!is_item_moving && blocks[b_type][b_rotation][i][j] == 1) {
                    main_org[by + i][bx + j] = EMPTY;
                    main_color[by + i][bx + j] = WHITE;
                }
            }
        }
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (is_item_moving && current_item.shape[b_rotation][i][j] == 1) {
                    main_org[by + i + 1][bx + j] = current_item.type;
                    main_color[by + i + 1][bx + j] = YELLOW;  // 아이템의 색상 설정
                }
                else if (!is_item_moving && blocks[b_type][b_rotation][i][j] == 1) {
                    main_org[by + i + 1][bx + j] = ACTIVE_BLOCK;
                    main_color[by + i + 1][bx + j] = getColorByBlockType(b_type);  // 블록의 색상 설정
                }
            }
        }
        by++;
        break;

    case UP:
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (is_item_moving && current_item.shape[b_rotation][i][j] == 1) {
                    main_org[by + i][bx + j] = EMPTY;
                    main_color[by + i][bx + j] = WHITE;
                }
                else if (!is_item_moving && blocks[b_type][b_rotation][i][j] == 1) {
                    main_org[by + i][bx + j] = EMPTY;
                    main_color[by + i][bx + j] = WHITE;
                }
            }
        }
        b_rotation = (b_rotation + 1) % 4;
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (is_item_moving && current_item.shape[b_rotation][i][j] == 1) {
                    main_org[by + i][bx + j] = current_item.type;
                    main_color[by + i][bx + j] = YELLOW;  // 아이템의 색상 설정
                }
                else if (!is_item_moving && blocks[b_type][b_rotation][i][j] == 1) {
                    main_org[by + i][bx + j] = ACTIVE_BLOCK;
                    main_color[by + i][bx + j] = getColorByBlockType(b_type);  // 블록의 색상 설정
                }
            }
        }
        break;

    case 100:
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (is_item_moving && current_item.shape[b_rotation][i][j] == 1) {
                    main_org[by + i][bx + j] = EMPTY;
                    main_color[by + i][bx + j] = WHITE;
                }
                else if (!is_item_moving && blocks[b_type][b_rotation][i][j] == 1) {
                    main_org[by + i][bx + j] = EMPTY;
                    main_color[by + i][bx + j] = WHITE;
                }
            }
        }
        b_rotation = (b_rotation + 1) % 4;
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (is_item_moving && current_item.shape[b_rotation][i][j] == 1) {
                    main_org[by + i - 1][bx + j] = current_item.type;
                    main_color[by + i - 1][bx + j] = YELLOW;  // 아이템의 색상 설정
                }
                else if (!is_item_moving && blocks[b_type][b_rotation][i][j] == 1) {
                    main_org[by + i - 1][bx + j] = ACTIVE_BLOCK;
                    main_color[by + i - 1][bx + j] = getColorByBlockType(b_type);  // 블록의 색상 설정
                }
            }
        }
        by--;
        break;
    }
    draw_main();
}




// 별을 반짝이게 하는 함수
void blink_star(int x, int y) {
    gotoxy(x, y);
    setTextColor(YELLOW);
    printf("★");
    Sleep(200);
    gotoxy(x, y);
    setTextColor(WHITE);
    printf("☆");
    Sleep(200);
}


void exchange_block_item(void) {
    // 인벤토리 정렬
    for (int i = 0; i < INVENTORY_SIZE - 1; i++) {
        if (Inventory[i].type == 0) {
            for (int j = i + 1; j < INVENTORY_SIZE; j++) {
                if (Inventory[j].type != 0) {
                    Inventory[i] = Inventory[j];
                    Inventory[j] = (Item){ 0 }; // 비워진 슬롯을 EMPTY로 설정
                    break;
                }
            }
        }
    }

    if (item_selected) {
        // 이미 선택된 아이템을 해제하고 인벤토리를 다시 그립니다.
        selectedItemIndex = -1;
        item_selected = false;
        draw_inventory();
        return;
    }

    // 첫 번째 사용 가능한 아이템 선택
    for (int i = 0; i < INVENTORY_SIZE; i++) {
        if (Inventory[i].type != 0) {
            selectedItemIndex = i;
            next_item = Inventory[selectedItemIndex];
            item_selected = true;
            break;
        }
    }

    if (selectedItemIndex == -1) { // 유효한 아이템이 없는 경우
        item_selected = false;
    }

    playEffect(path_sound_hard_drop);

    draw_inventory();
}




// 무작위 아이템 생성(3종)
Item createRandomItem() {
    int itemType = rand() % 3 + 10; // BOMB(10), THORN(11), DRILL(12) 중 하나
    return createItem(itemType);
}


Item createItem(int type) {
    Item newItem;
    newItem.type = type;

    // 아이템 모양 설정
    memset(newItem.shape, 0, sizeof(newItem.shape));
    switch (type) {
    case BOMB:
        for (int r = 0; r < 4; r++) {
            newItem.shape[r][1][1] = 1;
        }
        break;
    case THORN:
        for (int r = 0; r < 4; r++) {
            newItem.shape[r][1][0] = 1;
            newItem.shape[r][1][1] = 1;
            newItem.shape[r][1][2] = 1;
        }
        break;
    case DRILL:
        for (int r = 0; r < 4; r++) {
            newItem.shape[r][1][1] = 1;
        }
        break;
    }
    return newItem;
}





void draw_inventory() { // 인벤토리를 다시 그림(업데이트)
    for (int i = 0; i < INVENTORY_SIZE; i++) {
        gotoxy(STATUS_X_ADJ + 15, 6 + i);
        if (i == selectedItemIndex) {
            setTextColor(YELLOW);
        }
        switch (Inventory[i].type) {
        case BOMB:
            printf("BOMB  ");
            break;
        case THORN:
            printf("THORN ");
            break;
        case DRILL:
            printf("DRILL ");
            break;
        default:
            printf("EMPTY ");
            break;
        }
        setTextColor(WHITE); //기본 콘솔 텍스트 색상으로 되돌림
    }
}

void check_line(void) {
    int i, j, k, l;
    int block_amount; //한줄의 블록갯수를 저장하는 변수
    int combo = 0; //콤보갯수 저장하는 변수 지정및 초기화
    bool lineCompleted = false;

    for (i = MAIN_Y - 2; i > 3;) { //i=MAIN_Y-2 : 밑쪽벽의 윗칸부터,  i>3 : 천장(3)아래까지 검사
        block_amount = 0; //블록갯수 저장 변수 초기화
        for (j = 1; j < MAIN_X - 1; j++) { //벽과 벽사이의 블록갯루를 셈
            if (main_org[i][j] > 0) block_amount++;
        }
        if (block_amount == MAIN_X - 2) { //블록이 가득 찬 경우
            lineCompleted = true;
            if (level_up_on == 0) { //레벨업상태가 아닌 경우에(레벨업이 되면 자동 줄삭제가 있음)
                score += 100 * level; //점수추가
                cnt++; //지운 줄 갯수 카운트 증가
                if (hard_mode) hard_mode_block_count++; // Hard mode에서 블록 제거 카운트 증가
                combo++; //콤보수 증가
            }
            for (k = i; k > 1; k--) { //윗줄을 한칸씩 모두 내림(윗줄이 천장이 아닌 경우에만)
                for (l = 1; l < MAIN_X - 1; l++) {
                    if (main_org[k - 1][l] != CEILLING) {
                        main_org[k][l] = main_org[k - 1][l];
                        main_color[k][l] = main_color[k - 1][l]; // 색상도 함께 이동
                    }
                    if (main_org[k - 1][l] == CEILLING) {
                        main_org[k][l] = EMPTY;
                        main_color[k][l] = WHITE; // 색상을 기본값으로 설정
                    }
                    //윗줄이 천장인 경우에는 천장을 한칸 내리면 안되니까 빈칸을 넣음
                }
            }
        }
        else i--;
    }

    if (lineCompleted && shouldGenerateItem()) {
        Item newItem = createRandomItem();
        addItemToInventory(newItem);
        // 인벤토리에 추가된 아이템을 화면에 표시
        draw_inventory();
    }

    if (combo) { //줄 삭제가 있는 경우 점수와 레벨 목표를 새로 표시함
        if (combo > 1) { //2콤보이상인 경우 경우 보너스및 메세지를 게임판에 띄웠다가 지움
            gotoxy(MAIN_X_ADJ + (MAIN_X / 2) - 1, MAIN_Y_ADJ + by - 2); printf("%d COMBO!", combo);
            Sleep(500);
            score += (combo * level * 100);
            reset_main_cpy(); //텍스트를 지우기 위해 main_cpy을 초기화.
            //(main_cpy와 main_org가 전부 다르므로 다음번 draw()호출시 게임판 전체를 새로 그리게 됨)
        }
        gotoxy(STATUS_X_ADJ, STATUS_Y_GOAL); printf(" GOAL  : %5d", (cnt <= goal) ? goal - cnt : 0);
        gotoxy(STATUS_X_ADJ, STATUS_Y_SCORE); printf("        %6d", score);
    }

    // Hard mode에서 5줄을 없앴을 때 속도를 올리고 INACTIVE 블록 한 줄 추가
    if (hard_mode && hard_mode_block_count >= 5) {
        hard_mode_block_count = 0; // 카운트 초기화
        level++; // 레벨 증가
        speed = (speed > 1) ? speed - 1 : speed; // 속도를 증가시킴
        gotoxy(STATUS_X_ADJ, STATUS_Y_LEVEL); printf(" LEVEL : %5d", level); //레벨표시 

        for (i = 0; i < 4; i++) {
            gotoxy(MAIN_X_ADJ + (MAIN_X / 2) - 3, MAIN_Y_ADJ + 4);
            printf("             ");
            gotoxy(MAIN_X_ADJ + (MAIN_X / 2) - 2, MAIN_Y_ADJ + 6);
            printf("             ");
            Sleep(200);

            gotoxy(MAIN_X_ADJ + (MAIN_X / 2) - 3, MAIN_Y_ADJ + 4);
            printf("☆LEVEL UP!☆");
            gotoxy(MAIN_X_ADJ + (MAIN_X / 2) - 2, MAIN_Y_ADJ + 6);
            printf("☆SPEED UP!☆");
            Sleep(200);
        }
        reset_main_cpy(); //텍스트를 지우기 위해 main_cpy을 초기화.

        // 모든 블록을 한 행씩 위로 올림
        for (i = 4; i < MAIN_Y - 2; i++) {
            for (j = 1; j < MAIN_X - 1; j++) {
                main_org[i - 1][j] = main_org[i][j];
                main_color[i - 1][j] = main_color[i][j]; // 색상도 함께 이동
            }
        }

        // 맨 아래에 INACTIVE 블록 한 줄 추가
        for (j = 1; j < MAIN_X - 1; j++) {
            main_org[MAIN_Y - 2][j] = INACTIVE_BLOCK;
            main_color[MAIN_Y - 2][j] = main_color[MAIN_Y - 3][j]; // 이전 줄의 색상으로 설정
        }

        // 맨 위의 행을 빈 칸으로 만듦
        for (j = 1; j < MAIN_X - 1; j++) {
            main_org[3][j] = EMPTY;
            main_color[3][j] = WHITE; // 기본 색상으로 설정
        }

        draw_main(); // 화면을 다시 그림
    }

    // 레벨업을 한 후 goal을 초기화
    if (cnt >= goal) {
        cnt = 0;
        gotoxy(STATUS_X_ADJ, STATUS_Y_GOAL); printf(" GOAL  : %5d", goal);
    }
}





void check_level_up(void) {
    int i, j;

    if (cnt >= 10) { //레벨별로 10줄씩 없애야함. 10줄이상 없앤 경우 
        draw_main();
        level_up_on = 1; //레벨업 flag를 띄움 
        level += 1; //레벨을 1 올림 
        cnt = 0; //지운 줄수 초기화   

        for (i = 0; i < 4; i++) {
            gotoxy(MAIN_X_ADJ + (MAIN_X / 2) - 3, MAIN_Y_ADJ + 4);
            printf("             ");
            gotoxy(MAIN_X_ADJ + (MAIN_X / 2) - 2, MAIN_Y_ADJ + 6);
            printf("             ");
            Sleep(200);

            gotoxy(MAIN_X_ADJ + (MAIN_X / 2) - 3, MAIN_Y_ADJ + 4);
            printf("☆LEVEL UP!☆");
            gotoxy(MAIN_X_ADJ + (MAIN_X / 2) - 2, MAIN_Y_ADJ + 6);
            printf("☆SPEED UP!☆");
            Sleep(200);
        }
        reset_main_cpy(); //텍스트를 지우기 위해 main_cpy을 초기화.
        //(main_cpy와 main_org가 전부 다르므로 다음번 draw()호출시 게임판 전체를 새로 그리게 됨) 

        if (hard_mode) {
            // 맨 아래에 INACTIVE 블록 한 줄 추가
            for (j = 1; j < MAIN_X - 1; j++) {
                main_org[MAIN_Y - 2][j] = INACTIVE_BLOCK;
            }

            // 모든 블록을 한 행씩 위로 올림
            for (i = 4; i < MAIN_Y - 2; i++) {
                for (j = 1; j < MAIN_X - 1; j++) {
                    main_org[i - 1][j] = main_org[i][j];
                }
            }

            // 맨 위의 행을 빈 칸으로 만듦
            for (j = 1; j < MAIN_X - 1; j++) {
                main_org[3][j] = EMPTY;
            }

            draw_main(); // 화면을 다시 그림
        }
        else {
            // Easy mode에서는 아래 줄을 제거함
            for (i = MAIN_Y - 2; i > MAIN_Y - 2 - (level - 1); i--) {
                for (j = 1; j < MAIN_X - 1; j++) {
                    main_org[i][j] = EMPTY;
                    gotoxy(MAIN_X_ADJ + j, MAIN_Y_ADJ + i);
                    printf("  ");
                    Sleep(20);
                }
            }
        }
        Sleep(100); //별찍은거 보여주기 위해 delay 
        check_line(); //블록으로 모두 채운것 지우기
        //.check_line()함수 내부에서 level up flag가 켜져있는 경우 점수는 없음.         
        switch (level) { //레벨별로 속도를 조절해줌. 
        case 2:
            speed = hard_mode ? 25 : 50;
            break;
        case 3:
            speed = hard_mode ? 20 : 40;
            break;
        case 4:
            speed = hard_mode ? 15 : 30;
            break;
        case 5:
            speed = hard_mode ? 10 : 20;
            break;
        case 6:
            speed = hard_mode ? 5 : 10;
            break;
        default:
            speed = hard_mode ? 5 : 5;
            break;
        }
        level_up_on = 0; //레벨업 flag를 초기화
    }
}


// 퀴즈 데이터 구조체 정의
typedef struct {
    char question[512];
    char choices[4][128];
    char answer;
    int coord_y;
} Quiz;

Quiz quizzes[] = {
    {"다음과 같은 언어의 정의를 고르시오.\nLOAD A 1\nLOAD B 2\nADD A,B\n",
     {"A. High level language", "B. Assembly language", "C. Machine language", "D. None of the above"}, 'B', 3},

    {"다음 중 바르게 연결되지 않은 것을 고르시오\n",
     {"A. Integer-%d", "B. String-%s", "C. Octal-%o", "D. Hexadecimal-%h"}, 'D', 3},

    {"unsigned char가 담을 수 있는 허용 범위로 적절한 것을 고르시오\n",
     {"A. 0 to 255", "B. 0 to 65535", "C. -128 to 128", "D. -128 to 127"}, 'A', 3},

    {"다음 중 long과 같은 사이즈(bytes)를 갖는 데이터 타입을 작성하시오\n",
     {"A. char", "B. short", "C. int", "D. double"}, 'C', 3},

    {"다음의 결과를 고르시오\n#include <stdio.h>\nint main(void)\n{\n short s=32767; // Max value 32767\n s+=1;\n printf(\"%d\", s);\n return 0;\n}\n",
     {"A. 32767", "B. 32768", "C. 0", "D. error"}, 'C', 11},

    {"'s+=1' 부분에서 발생하는 현상의 정의를 영어로 쓰시오\n#include <stdio.h>\nint main(void)\n{\n short s=32767; // Max value 32767\n s+=1;\n printf(\"%d\", s);\n return 0;\n}\n",
     {"A. underflow", "B. overflow", "C. segmentation fault", "D. invalid operation"}, 'B', 11},

    {"다음의 결과를 고르시오\n#include <stdio.h>\nint main(void)\n{\nint a,b,c;\na=5;\nb=++a;\nc=a--;\nprintf(\"%d,%d,%d\",a,b,c);\nreturn 0;\n}\n",
     {"A. 5, 6, 5", "B. 5, 6, 4", "C. 6, 6, 6", "D. 5, 6, 6"}, 'D', 13},

    {"입력받은 숫자의 구구단 한 단을 출력하기 위해 다음의 빈칸에 들어갈 for문을 작성하시오\n#include <stdio.h>\nint main()\n{\n int i, n;\n scanf(\"%d\", &n);\n ( ??? )\n {\n printf(\"%d x %d = %d\\n\", n, i, n*i);\n }\n return 0;\n}\n",
     {"A. for(i=1;i<9;i++)", "B. for(i=0;i<10;i++)", "C. for(i=1;i<10;i++)", "D. for(i=1;i<=10;i++)"}, 'C', 14},

    {"!(1 && (0 || 1))\n",
     {"A. True", "B. False", "C. Unevaluatable", "D. None of the above"}, 'B', 3},

    {"다음의 결과를 고르시오.\nint x=0;\nSwitch(x)\n{\ncase 1:\n print(\"One\");\ncase 0:\n print(\"Zero\");\ncase 2:\n print(\"Two\");\n}\n",
     {"A. One", "B. Zero", "C. ZeroTwo", "D. OneZeroTwo"}, 'C', 13},

    {"다음의 printf 함수를 사용하기 위해 필요한 코드를 고르시오.\nint main(void)\n{ printf(\"hello\\n\");\n}\n",
     {"A. #Printf", "B. #Define printf", "C. define printf", "D. #include <stdio.h>"}, 'D', 6},

    {"포인터 변수 a 주소 값에 있는 데이터를 의미하는 것을 고르시오\n",
     {"A. a;", "B. val(a);", "C. *a;", "D. &a;"}, 'C', 3},

    {"다음 빈칸에 들어가야할 코드 한 줄을 작성하시오.\n#include <stdio.h>\n( ??? )\nint main()\n{\n test(5);\n}\nvoid test(int a)\n{\n for(int i=0; i<a; i++){\n printf(\"hello\\n\");\n }\n}\n",
     {"A. void test(void);", "B. void test(int);", "C. int test(void);", "D. int test(int);"}, 'B', 15},

    {"다음의 마지막 출력값이 99가 되기위한 빈칸을 채우시오.(띄어쓰기 없이)\n#include <stdio.h>\nint main()\n{\n int i = 0;\n do {\n printf(\"%d\\n\", i);\n i++;\n } ( ??? );\n return 0;\n}\n",
     {"A. while(i<100)", "B. while(i<=99)", "C. while(i>100)", "D. while(i>=99)"}, 'A', 12},

    {"x의 값을 작성하시오\nint *ptr;\nint x=1;\nptr = &x;\n*ptr = 0;\n",
     {"A. 0", "B. 1", "C. -1", "D. Undefined"}, 'A', 7},

    {"다음 출력값과 같은 것을 고르시오\n#include <stdio.h>\nint main()\n{\n int arr[3] = {1,2,3};\n printf(\"%p\\n\", arr);\n return 0;\n",
     {"A. arr[]", "B. &arr[0]", "C. &arr[1]", "D. &arr[2]"}, 'B', 8},

    {"다음 p의 최종값과 같은 것을 고르시오\nint x[3]={1,2,3};\nint *p;\np=x;\np++;\n",
     {"A. x[1]", "B. &x[0]", "C. &x[1]", "D. &x[2]"}, 'C', 7},

    {"다음 y의 값을 작성하시오\nint x[3]={2,3,5};\nint y;\nint *p=&x[2];\ny=6+*(--p);\n",
     {"A. 7", "B. 8", "C. 9", "D. 10"}, 'C', 7},

    {"다음 y의 값을 작성하시오\nint x[3]={2,3,5};\nint y;\nint *p=x;\n++(*p)\ny=3+*(++p);\n",
     {"A. 5", "B. 6", "C. 7", "D. 8"}, 'B', 8},

    {"다음 y의 값을 작성하시오\nint x[3]={1,3,5};\nint y;\nint *p=x;\n++p\ny=6+ --(*p);\n",
     {"A. 6", "B. 7", "C. 8", "D. 9"}, 'C', 8}
};

void print_options(Quiz quiz, int selected_option) {
    COORD coord;
    for (int i = 0; i < 4; i++) {
        coord.X = 0;
        coord.Y = quiz.coord_y + i; // 질문 출력 후 줄바꿈 한 위치로 설정
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        if (i == selected_option) {
            setTextColor(YELLOW); // 노란색
            printf("■ %s\n", quiz.choices[i]);
            setTextColor(WHITE); // 흰색
        }
        else {
            printf("□ %s\n", quiz.choices[i]);
        }
    }
}

void ask_quiz() {
    int quiz_index = rand() % (sizeof(quizzes) / sizeof(quizzes[0]));
    system("cls");
    printf("%s\n", quizzes[quiz_index].question);
    int selected_option = 0;
    int key;
    COORD coord;

    print_options(quizzes[quiz_index], selected_option); // 초기 선택 항목 출력

    while (1) {
        // 키 입력 처리
        if (_kbhit()) {
            key = _getch();
            if (key == 224) { // 방향키의 경우 첫 번째로 224가 입력됨
                key = _getch(); // 실제 키 값 입력
                switch (key) {
                case 72: // 위쪽 방향키
                    selected_option = (selected_option == 0) ? 3 : selected_option - 1;
                    break;
                case 80: // 아래쪽 방향키
                    selected_option = (selected_option == 3) ? 0 : selected_option + 1;
                    break;
                }
                print_options(quizzes[quiz_index], selected_option); // 변경된 선택 항목을 다시 출력
            }
            else if (key == 32) { // 스페이스 키
                break;
            }
        }
    }

    // 정답 확인
    if (quizzes[quiz_index].choices[selected_option][0] == quizzes[quiz_index].answer) {
        printf("정답입니다! 게임을 이어서 진행할 수 있습니다.\n");
        score = last_game_score; // 저장된 점수를 복원
        Sleep(2000);
        system("cls");
        reset_main_cpy();
        reset_main();
        draw_map();
        draw_main();
    }
    else {
        printf("틀렸습니다. Game Over.\n");
        printf("최종 점수: %d\n", score);
        score = 0; // 점수를 초기화
        Sleep(2000);
        system("cls");
        reset();
    }
}

void check_game_over(void) {
    int i;

    for (i = 1; i < MAIN_X - 2; i++) {
        if (main_org[3][i] == INACTIVE_BLOCK && !is_item_moving) {
            int x = 5;
            int y = 5;

            gotoxy(x, y + 0); printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤");
            gotoxy(x, y + 1); printf("▤                              ▤");
            gotoxy(x, y + 2); printf("▤  +-----------------------+   ▤");
            gotoxy(x, y + 3); printf("▤  |  G A M E  O V E R..   |   ▤");
            gotoxy(x, y + 4); printf("▤  +-----------------------+   ▤");
            gotoxy(x, y + 5); printf("▤   YOUR SCORE: %6d         ▤", score);
            gotoxy(x, y + 6); printf("▤                              ▤");
            gotoxy(x, y + 7); printf("▤  Press any key to continue..  ▤");
            gotoxy(x, y + 8); printf("▤                              ▤");
            gotoxy(x, y + 9); printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤");
            last_score = score;

            // 현재 점수를 last_game_score에 저장
            last_game_score = score;

            if (score > best_score) {
                FILE* file = fopen("score.dat", "wt");

                gotoxy(x, y + 6); printf("▤  ★★★ BEST SCORE! ★★★   ▤  ");

                if (file == 0) {
                    gotoxy(0, 0);
                    printf("FILE ERROR: SYSTEM CANNOT WRITE BEST SCORE ON \"SCORE.DAT\"");
                }
                else {
                    fprintf(file, "%d", score);
                    fclose(file);
                }
            }
            Sleep(1000);
            while (_kbhit()) _getch();
            key = _getch();

            // 퀴즈를 출제하여 맞추면 점수를 유지하고 새 게임을 시작합니다.
            ask_quiz();
        }
    }
}


void pause(void) { //게임 일시정지 함수 
    int i, j;

    int x = 5;
    int y = 5;

    for (i = 1; i < MAIN_X - 2; i++) { //게임 일시정지 메세지 
        gotoxy(x, y + 0); printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤");
        gotoxy(x, y + 1); printf("▤                              ▤");
        gotoxy(x, y + 2); printf("▤  +-----------------------+   ▤");
        gotoxy(x, y + 3); printf("▤  |       P A U S E       |   ▤");
        gotoxy(x, y + 4); printf("▤  +-----------------------+   ▤");
        gotoxy(x, y + 5); printf("▤  Press any key to resume..   ▤");
        gotoxy(x, y + 6); printf("▤                              ▤");
        gotoxy(x, y + 7); printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤");
    }
    _getch(); //키입력시까지 대기 

    system("cls"); //화면 지우고 새로 그림 
    reset_main_cpy();
    draw_main();
    draw_map();

    for (i = 1; i < 3; i++) { // 다음블록 그림 
        for (j = 0; j < 4; j++) {
            if (blocks[b_type_next][0][i][j] == 1) {
                gotoxy(MAIN_X + MAIN_X_ADJ + 3 + j, i + 6);
                printf("■");
            }
            else {
                gotoxy(MAIN_X + MAIN_X_ADJ + 3 + j, i + 6);
                printf("  ");
            }
        }
    }
}

void playBGM(const char* bgmFile) {
    mciSendStringA("stop bgm", NULL, 0, NULL);
    mciSendStringA("close bgm", NULL, 0, NULL);
    char command[256];

    // Open the BGM file
    snprintf(command, sizeof(command), "open \"%s\" type mpegvideo alias bgm", bgmFile);
    mciSendStringA(command, NULL, 0, NULL);

    // Play the BGM
    mciSendStringA("play bgm repeat", NULL, 0, NULL);

    // Set BGM volume
    snprintf(command, sizeof(command), "setaudio bgm volume to %d", bgm_volume * 10);
    mciSendStringA(command, NULL, 0, NULL);
}

void setBGMVolume(int vol) {
    bgm_volume = (vol < 0) ? 0 : (vol > 100) ? 100 : vol;
    char command[64];
    snprintf(command, sizeof(command), "setaudio bgm volume to %d", bgm_volume * 10);
    mciSendStringA(command, NULL, 0, NULL);
}

void stopBGM() {
    mciSendStringA("stop bgm", NULL, 0, NULL);
    mciSendStringA("close bgm", NULL, 0, NULL);
}

void playEffect(const char* soundFile) {
    static int aliasCounter = 0;  // 효과음 별칭을 위한 카운터
    char alias[32];
    snprintf(alias, sizeof(alias), "effect%d", aliasCounter++);

    const char* ext = strrchr(soundFile, '.');
    if (ext != NULL) {
        if (strcmp(ext, ".wav") == 0) {
            if (_access(soundFile, 0) != -1) {
                // .wav 파일 재생
                PlaySoundA(soundFile, NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
                // 볼륨 설정
                DWORD dwVolume = (sound_volume * 0xFFFF / 100) | ((sound_volume * 0xFFFF / 100) << 16);
                waveOutSetVolume(0, dwVolume);
            }
            else {
                gotoxy(30, 50);
                printf("file not found: %s", soundFile);
            }
        }
        else if (strcmp(ext, ".mp3") == 0) {
            char command[256];
            snprintf(command, sizeof(command), "open \"%s\" type mpegvideo alias %s", soundFile, alias);
            mciSendStringA(command, NULL, 0, NULL);
            snprintf(command, sizeof(command), "play %s", alias);
            mciSendStringA(command, NULL, 0, NULL);
            // 볼륨 설정
            snprintf(command, sizeof(command), "setaudio %s volume to %d", alias, sound_volume * 10);
            mciSendStringA(command, NULL, 0, NULL);

            // 효과음이 끝난 후 닫기
            snprintf(command, sizeof(command), "close %s", alias);
            mciSendStringA(command, NULL, 0, NULL);
        }
        else {
            gotoxy(30, 50);
            printf("unsupported file format: %s", soundFile);
        }
    }
    else {
        gotoxy(30, 50);
        printf("no file extension found: %s", soundFile);
    }
}

void setEffectVolume(int vol) {
    sound_volume = (vol < 0) ? 0 : (vol > 100) ? 100 : vol;
    DWORD dwVolume = (sound_volume * 0xFFFF / 100) | ((sound_volume * 0xFFFF / 100) << 16);
    waveOutSetVolume(0, dwVolume);
}