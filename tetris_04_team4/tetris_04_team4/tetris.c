#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

//(new) Ư������ ���� �ذ� ���� ����
#include <wchar.h>
#include <locale.h>

//(new) ����
#include <mmsystem.h>
#include <io.h>
#pragma comment(lib, "winmm.lib")

// �� ��� ����
#define STAR_EMPTY L'��'
#define STAR_FULL L'��'

#define LEFT 75 //�·� �̵�    //Ű���尪�� 
#define RIGHT 77 //��� �̵� 
#define UP 72 //ȸ�� 
#define DOWN 80 //soft drop
#define SPACE 32 //hard drop
#define p 112 //�Ͻ����� 
#define P 80 //�Ͻ�����
#define ESC 27 //�������� 
#define TAB 9 //(new) ������/�� ���� 
#define ENTER 13 //(new) ġƮŰ, �������� �ϳ� ����
#define SHIFT 16 // ����� ����, �ϴ� �߰�

#define ACTIVE_BLOCK -2 // �����ǹ迭�� ����� ����� ���µ� 
#define CEILLING -1     // ����� �̵��� �� �ִ� ������ 0 �Ǵ� ���� ������ ǥ�� 
#define EMPTY 00         // ����� �̵��� �� ���� ������ ����� ǥ�� 
#define WALL 01
#define INACTIVE_BLOCK 02 // ���� �� ��� ������ ����

#define BOMB 10 //(new)��ź
#define THORN 11 //(new)����
#define DRILL 12 //(new)�帱

#define MAIN_X 11 //������ ����ũ�� 
#define MAIN_Y 23 //������ ����ũ�� 
#define MAIN_X_ADJ 3 //������ ��ġ���� 
#define MAIN_Y_ADJ 1 //������ ��ġ���� 

#define STATUS_X_ADJ MAIN_X_ADJ+MAIN_X+1 //��������ǥ�� ��ġ���� 

#define INVENTORY_SIZE 3 //(new)�κ��丮 �ִ� ũ��


int STATUS_Y_GOAL; //GOAL ����ǥ����ġY ��ǥ ���� 
int STATUS_Y_LEVEL; //LEVEL ����ǥ����ġY ��ǥ ����
int STATUS_Y_SCORE; //SCORE ����ǥ����ġY ��ǥ ����

int blocks[7][4][4][4] = {
    {
        { // ���簢��
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
        { // ����
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
        { // ����1
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
        { // ����2
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
        { // L��1
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
        { // L��2
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
        { // ��
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
}; //��ϸ�� ���� 4*4������ ����� ǥ�� blcoks[b_type][b_rotation][i][j]�� ��� 

int b_type; //��� ������ ���� 
int b_rotation; //��� ȸ���� ���� 
int b_type_next; //���� ��ϰ� ���� 

int main_org[MAIN_Y][MAIN_X]; //�������� ������ �����ϴ� �迭 ����Ϳ� ǥ���Ŀ� main_cpy�� ����� 
int main_cpy[MAIN_Y][MAIN_X]; //�� maincpy�� �������� ����Ϳ� ǥ�õǱ� ���� ������ ������ ���� 
//main�� ��ü�� ��� ����Ϳ� ǥ������ �ʰ�(�̷��� �ϸ� ����Ͱ� �����Ÿ�) 
//main_cpy�� �迭�� ���ؼ� ���� �޶��� ���� ����Ϳ� ��ħ 
int bx, by; //�̵����� ����� �����ǻ��� x,y��ǥ�� ���� 

int key; //Ű����� �Է¹��� Ű���� ���� 


int goal = 10; // ������ ��ǥ (�⺻ 10)
int hard_mode_block_count = 0; // Hard mode���� ��� ���Ÿ� ī��Ʈ




int speed; //��������ӵ� 
int level; //���� level 
int level_goal; //���������� �Ѿ�� ���� ��ǥ���� 
int cnt; //���� �������� ������ �� ���� ���� 
int score; //���� ���� 
int last_score = 0; //�������������� 
int best_score = 0; //�ְ�������� 
int last_game_score = 0; // ���� ���� �� ������ ������ ����
int frame = 0; //(new) �ΰ��� ������ �ִϸ��̼��� ���� ������

int new_block_on = 0; //���ο� ���� �ʿ����� �˸��� flag 
int new_item_on = 0; //(new) ���ο� �������� �ʿ����� �˸��� flag 
int crush_on = 0; //���� �̵����� ����� �浹�������� �˷��ִ� flag 
int level_up_on = 0; //���������� ����(���� ������ǥ�� �Ϸ�Ǿ�����) �˸��� flag 
int space_key_on = 0; //hard drop�������� �˷��ִ� flag 


//(new) ������ ����ü
typedef struct Item {
    int type; // BOMB | THORN | DRILL
    int x, y;
    int shape[4][4][4]; //����� ����, 4���� ȸ�� ���°� ���� �� ����
}Item;

Item current_item; //(new) ���� �����̴� �������� ����
Item Inventory[INVENTORY_SIZE]; //(new) ������ ����, �ִ� 3���� �������� ����
Item next_item = { 0 }; //(new) ���� ������, �ʱ�ȭ �߰�

bool is_item_moving = false; //(new) ���� ����� �ƴ� �������� �����̰� �ִ°�?
bool item_selected = false; //(new) ������ ���� ����
int selectedItemIndex = -1; //(new) ���õ� ������ �ε���

wchar_t drill_char[4] = { L'��', L'��', L'��',  L'��' }; //DRILL�� ���� Ư������ �迭 ����
wchar_t bomb_char[3] = { L'��', L'��', L'��' }; // BOMB�� ���� Ư������ �迭 -> �����Ӹ��� �ٲ�

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


//(new) ������ �������� ����� �Լ�
Item createRandomItem();
//(new) ������ ������ ����� �Լ�
Item createItem(int type);
//(new) �κ��丮�� ������ �߰��ϴ� �Լ�
void addItemToInventory(Item item);
//(new) �κ��丮�� �׸��� �Լ�
void draw_inventory(void);

void title(void); //���ӽ���ȭ�� 
void reset(void); //������ �ʱ�ȭ 
void reset_main(void); //���� ������(main_org[][]�� �ʱ�ȭ)
void reset_main_cpy(void); //copy ������(main_cpy[][]�� �ʱ�ȭ)
void draw_map(void); //���� ��ü �������̽��� ǥ�� 
void draw_main(void); //�������� �׸� 
void new_block(void); //���ο� ����� �ϳ� ���� 
void check_key(void); //Ű����� Ű�� �Է¹��� 
void drop_block(void); //����� �Ʒ��� ����Ʈ�� 
int check_crush(int bx, int by, int rotation); //bx, by��ġ�� rotationȸ������ ���� ��� �浹 �Ǵ� 
void move_block(int dir); //dir�������� ����� ������ 
void check_line(void); //���� ����á������ �Ǵ��ϰ� ���� 
void check_level_up(void); //������ǥ�� �޼��Ǿ������� �Ǵ��ϰ� levelup��Ŵ 
void check_game_over(void); //���ӿ������� �Ǵ��ϰ� ���ӿ����� ���� 
void pause(void);//������ �Ͻ�������Ŵ 

void playBGM(const char* bgmFile);
void setBGMVolume(int vol);
void stopBGM();
void playEffect(const char* soundFile);
void setEffectVolume(int vol);

void displayMenuTabs(int x, int y);

// (new) ���� �����۰� ����� ��ȯ�ϴ� �Լ�
void exchange_block_item(void);
// (new) ��ź : Ư�� ������ ����� ��� EMPTY�� ����(�ı�)
void activateBomb(int x, int y);
// (new) ���� : ���� ���� ����
void activateThorn(void);
// (new) �帱 : ���� ���� ����
void activateDrill(int x, int y);
// (new) ���� new_block�� �ִ� next�� ����� �����ϴ� ����� �Űܿ�
void update_next();
void playSound(const char* soundFile); //(new) ���� ��� �Լ�

void gotoxy(int x, int y) { //gotoxy�Լ� 
    COORD pos = { 2 * x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}



//�� ���� ������
#define COLOR_OFFSET 100 // ������ ������ �� ����� ������ ��

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
    case 0: return GREEN; // ���簢��
    case 1: return YELLOW; // ����
    case 2: return BLUE; // ����1
    case 3: return PURPLE; // ����2
    case 4: return CYAN; // L��1
    case 5: return RED; // L��2
    case 6: return WHITE; // ��
    default: return WHITE; // �⺻ ����
    }
}

// ��� ���� ������ ���� �迭
int blockColors[7] = { GREEN, YELLOW, BLUE, PURPLE, CYAN, RED, WHITE };

// �������� ������ �����ϴ� �迭
int main_color[MAIN_Y][MAIN_X];
int main_color_cpy[MAIN_Y][MAIN_X];


void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void printBlock(int x, int y, int color) {
    setColor(color);
    gotoxy(x, y);
    printf("��");
    setColor(WHITE); // �⺻ �������� �ǵ���
}

void clearBlock(int x, int y) {
    gotoxy(x, y);
    printf("  ");
}


typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE; //Ŀ������� �Լ��� ���Ǵ� ������ 
void setcursortype(CURSOR_TYPE c) { //Ŀ������� �Լ� 
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




//main�Լ�
int main() {
    setlocale(LC_CTYPE, "");
    int i;

    srand((unsigned)time(NULL)); //����ǥ���� 
    setcursortype(NOCURSOR); //Ŀ�� ���� 
    title(); //����Ÿ��Ʋ ȣ�� 
    reset();//������ ���� 

    while (1) {
        for (i = 0; i < 5; i++) { //����� ��ĭ�������µ��� 5�� Ű�Է¹��� �� ���� 
            check_key(); //Ű�Է�Ȯ�� 
            draw_main(); //ȭ���� �׸� 
            Sleep(speed); //���Ӽӵ����� 
            if (crush_on && check_crush(bx, by + 1, b_rotation) == false) Sleep(100);
            //����� �浹���ΰ�� �߰��� �̵��� ȸ���� �ð��� ���� 
            if (space_key_on == 1) { //�����̽��ٸ� �������(hard drop) �߰��� �̵��� ȸ���Ҽ� ���� break; 
                space_key_on = 0;
                break;
            }
        }
        drop_block(); // ����� ��ĭ ���� 
        check_level_up(); // �������� üũ 
        check_game_over(); //���ӿ����� üũ 
        if (new_block_on == 1) new_block(); // �� �� flag�� �ִ� ��� ���ο� �� ���� 
    }
}

#define WHITE 7
#define YELLOW 6
#define RED 4
#define GREEN 2
#define BLUE 1


bool hard_mode = false;
char textline_normal_mode_checked[] = { "�븻 ���  ��  |  �ϵ� ���  ��" };
char textline_hard_mode_checked[] = { "�븻 ���  ��  |  �ϵ� ���  ��" };
char textline_starting_level[] = { "  ���� ����      | " };
char textline_sound_warning[] = { "������ �����ϼ���" };

int select_position; // ����ȭ�� Ŀ���� ��ġ
int start_level = 1;

void showGameSetting(int x, int y); // (new) ���� ȭ�� ������ ���� ���� �� ���� â ������
void showKeyBindings(int x, int y); // (new) ���� ȭ�� ������ ����Ű ������
void showAchievement(int x, int y); // (new) ���� ȭ�� ������ ���� â ������
void clearMenuArea(int x, int y, int width, int height);

bool shouldGenerateItem() {
    int chance = hard_mode ? 4 : 2;  // hard mode�� 1/4, easy mode�� 1/2 Ȯ��
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
    int x = 5; //Ÿ��Ʋȭ���� ǥ�õǴ� x��ǥ 
    int y = 4; //Ÿ��Ʋȭ���� ǥ�õǴ� y��ǥ 
    int cnt; //Ÿ��Ʋ �������� ���� ����  

    gotoxy(x, y + 0); printf("����������������"); Sleep(100);
    gotoxy(x, y + 1); printf("��                          ��"); Sleep(100);
    gotoxy(x, y + 2); printf("��                          ��"); Sleep(100);
    gotoxy(x, y + 3); printf("��                          ��"); Sleep(100);
    gotoxy(x, y + 4); printf("���  �������������"); Sleep(100);
    gotoxy(x, y + 5); printf("                              "); Sleep(100);
    gotoxy(x + 5, y + 2); printf("�� Ʈ �� ��"); Sleep(100);

    gotoxy(x, y + 8); printf("���         ����         ���");

    gotoxy(x, y + 11); printf("���        ���۹�        ���");

    gotoxy(x, y + 14); printf("���         ����         ���");

    gotoxy(x, y + 18); printf("|| ������ǻ�����α׷��� 4�� ||");
    gotoxy(x, y + 20); printf("���̿�, ������, ������, ������");

    current_bgm = rand() % 5;
    playBGM(path_bgm[current_bgm]);
    setEffectVolume(sound_volume);


    for (cnt = 0;; cnt++) { // cnt�� 1�� ������Ű�鼭 ��� �ݺ�  
        //gotoxy(x, y + 13); printf("select_position : %d", select_position);
        //gotoxy(x, y + 14); printf("start_level : %d", start_level);
        if (_kbhit()) {
            //clearMenuArea(x + 23, y + 4, 50, 21);
            key = _getch();
            if (key == 224) { // ����Ű�ΰ�� 
                key = _getch();
                switch (key) {
                case LEFT: // ���� ����Ű (LEFT)
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
                case RIGHT: // ������ ����Ű (RIGHT)
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
                case UP: // ���� ����Ű (UP)
                    select_position = (select_position > 1) ? select_position - 1 : 4;
                    break;
                case DOWN: // ������ ����Ű (DOWN)
                    select_position = (select_position < 4) ? select_position + 1 : 1;
                    break;
                }
            }

            if (key == ' ') break; // Space�� �ԷµǸ� ���� Ż��
            if (key == TAB) {
                currentMenu = (currentMenu + 1) % 3;
                clearMenuArea(x + 23, y + 4, 50, 21);
            }
        }
        displayMenuTabs(x, y); // (new) ���� ���õ� �޴� �� ���� ǥ��
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
    while (_kbhit()) _getch(); //���ۿ� ��ϵ� Ű���� ���� 
}




void printChar(char str[]) {
    for (int i = 0; str[i] != '\0'; i++) {
        printf("%c", str[i]);
    }
}

// Ư�� ������ �ؽ�Ʈ ������ �ٲ�
void printCharColor(char str[], int color_change_start, int color_change_end, int color) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (i == color_change_start) { setTextColor(color); }
        if (i == color_change_end) { setTextColor(WHITE); }
        printf("%c", str[i]);
    }
    setTextColor(WHITE);//�⺻ �ܼ� �ؽ�Ʈ ������ 7
}

// �ֿ� ���� - �Ķ���(1), �ʷϻ�(2), û�ϻ�(3), ������(4), �����(6), ���(7)
void setTextColor(WORD color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// ���� ���� �����ϴ� â
void showGameSetting(int x, int y) {
    gotoxy(x, y + 4); printf("=====      ���� ���      =====");

    gotoxy(x, y + 7); printf("||           ���̵�          ||");
    gotoxy(x - 2, y + 9); if (select_position % 4 == 0) printf("> "); else printf("  ");

    gotoxy(x, y + 9);
    if (hard_mode) printCharColor(textline_hard_mode_checked, 17, 28, select_position % 3 == 0 ? YELLOW : WHITE);
    else printCharColor(textline_normal_mode_checked, 0, 11, select_position % 3 == 0 ? YELLOW : WHITE);

    gotoxy(x, y + 12); printf("||         ���� ����         ||");
    /*
    gotoxy(x - 2, y + 14); if (select_position % 3 == 1) printf("> "); else printf("  ");

    gotoxy(x, y + 14);
    if (duo_mode) printCharColor(textline_duo_mode_checked, 17, 27, select_position % 3 == 1 ? YELLOW : WHITE);
    else printCharColor(textline_solo_mode_checked, 0, 11, select_position % 3 == 1 ? YELLOW : WHITE);
    */

    gotoxy(x - 2, y + 15); if (select_position % 4 == 1) printf("> "); else printf("  ");
    printf("  BGM  ����      |  %s ", textline_bgm[current_bgm]);
    gotoxy(x - 2, y + 16); if (select_position % 4 == 2) printf("> "); else printf("  ");
    printf("  BGM  ����      |  %d ", bgm_volume);
    gotoxy(x, y + 17);
    if (bgm_volume >= 70) printCharColor(textline_sound_warning, 0, 17, RED);
    else printf("                    ");

    gotoxy(x - 2, y + 18); if (select_position % 4 == 3) printf("> "); else printf("  ");
    printf("  ���� ����      |  %d ", start_level);

    gotoxy(x, y + 20); printf("===============================");
}

void displayMenuTabs(int x, int y) {
    gotoxy(x, y + 8);
    if (currentMenu == MODE_MENU) {
        setTextColor(YELLOW);
    }
    printf("���         ����         ���");
    setTextColor(WHITE);

    gotoxy(x, y + 11);
    if (currentMenu == BINDINGS_MENU) {
        setTextColor(YELLOW);
    }
    printf("���        ���۹�        ���");
    setTextColor(WHITE);

    gotoxy(x, y + 14);
    if (currentMenu == ACHIEVEMENTS_MENU) {
        setTextColor(YELLOW);
    }
    printf("���         ����         ���");
    setTextColor(WHITE);
}

void showKeyBindings(int x, int y) {
    gotoxy(x, y + 4); printf("======      �� �� Ű      ======");
    gotoxy(x, y + 7); printf("  ��   : ȸ��");
    gotoxy(x, y + 8); printf("��  �� : ���� / ������ �̵�");
    gotoxy(x, y + 9); printf("  ��   : �Ʒ��� �̵�");
    gotoxy(x, y + 10); printf(" SPACE : �ϵ� ��� / ���ӽ���");
    gotoxy(x, y + 11); printf("   P   : �Ͻ�����");
    gotoxy(x, y + 12); printf("  ESC  : ����");
    gotoxy(x, y + 13); printf("  TAP  : ������ Ȱ��ȭ");
    gotoxy(x, y + 20); printf("===============================");
}

void showAchievement(int x, int y) {
    gotoxy(x, y + 4);  printf("=======       ����       =======");

    gotoxy(x, y + 7);  printf(" -        ��Ʈ���� ����       - ");
    gotoxy(x, y + 8);  printf("           ���� 7 ����          ");

    gotoxy(x, y + 10); printf(" -    ���� ����.  ����ó��    - ");
    gotoxy(x, y + 11); printf("      ���÷� �� ���� ����     ");

    gotoxy(x, y + 13); printf(" -      ������  �����̴�      - ");
    gotoxy(x, y + 14); printf("��ź �ϳ��� 12�� �̻��� �� ����");

    gotoxy(x, y + 16); printf(" -         ����  ����         - ");
    gotoxy(x, y + 17); printf("   �帱�� �� �� ���� �� ����  ");

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
    FILE* file = fopen("score.dat", "rt"); // score.dat������ ���� 
    if (file == 0) { best_score = 0; } //������ ������ �� �ְ������� 0�� ���� 
    else {
        fscanf(file, "%d", &best_score); // ������ ������ �ְ������� �ҷ��� 
        fclose(file); //���� ���� 
    }

    level = 1; //�������� �ʱ�ȭ 
    score = 0;
    cnt = 0;
    goal = hard_mode ? 5 : 10; // Hard mode������ ��ǥ�� 5�� ����
    key = 0;
    crush_on = 0;
    hard_mode_block_count = 0;
    speed = hard_mode ? 25 : 100; // Hard mode������ �⺻ �ӵ��� �� ������ ����

    system("cls"); //ȭ������ 
    reset_main(); // main_org�� �ʱ�ȭ 
    draw_map(); // ����ȭ���� �׸�
    draw_main(); // �������� �׸� 

    b_type_next = rand() % 7; //�������� ���� ��� ������ �����ϰ� ���� 
    new_block(); //���ο� ����� �ϳ� ����  

    gotoxy(STATUS_X_ADJ, STATUS_Y_GOAL); // GOAL ���� �ٽ� ���
    printf(" GOAL  : %5d", goal - cnt);
}



//�������� �ʱ�ȭ 
void reset_main(void) {
    int i, j;

    for (i = 0; i < MAIN_Y; i++) { // �������� 0���� �ʱ�ȭ  
        for (j = 0; j < MAIN_X; j++) {
            main_org[i][j] = 0;
            main_cpy[i][j] = 100;
            main_color[i][j] = WHITE; // �⺻ �������� �ʱ�ȭ
            main_color_cpy[i][j] = WHITE; // �⺻ �������� �ʱ�ȭ
        }
    }
    for (j = 1; j < MAIN_X; j++) { //y���� 3�� ��ġ�� õ���� ���� 
        main_org[3][j] = CEILLING;
    }
    for (i = 1; i < MAIN_Y - 1; i++) { //�¿� ���� ����  
        main_org[i][0] = WALL;
        main_color[i][0] = hard_mode ? RED : WHITE; // �� ���� ����
        main_org[i][MAIN_X - 1] = WALL;
        main_color[i][MAIN_X - 1] = hard_mode ? RED : WHITE; // �� ���� ����
    }
    for (j = 0; j < MAIN_X; j++) { //�ٴں��� ���� 
        main_org[MAIN_Y - 1][j] = WALL;
        main_color[MAIN_Y - 1][j] = hard_mode ? RED : WHITE; // �ٴ� ���� ����
    }
}



//main_cpy�� �ʱ�ȭ 
void reset_main_cpy(void) {
    int i, j;

    for (i = 0; i < MAIN_Y; i++) {         //�����ǿ� ���ӿ� ������ �ʴ� ���ڸ� ���� 
        for (j = 0; j < MAIN_X; j++) {  //�̴� main_org�� ���� ���ڰ� ���� �ϱ� ���� 
            main_cpy[i][j] = 100;
        }
    }
}


//next�� inventory�׸��� ��
void draw_map(void) { //���� ���� ǥ�ø� ��Ÿ���� �Լ�  
    int y = 3;             // level, goal, score�� �����߿� ���� �ٲ�� �� ���� �� y���� ���� �����ص� 
    // �׷��� Ȥ�� ���� ���� ǥ�� ��ġ�� �ٲ� �� �Լ����� �ȹٲ㵵 �ǰ�.. 
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
    gotoxy(STATUS_X_ADJ, y + 15); printf("  ��   : Shift        SPACE : Hard Drop");
    gotoxy(STATUS_X_ADJ, y + 16); printf("��  �� : Left / Right   P   : Pause");
    gotoxy(STATUS_X_ADJ, y + 17); printf("  ��   : Soft Drop     ESC  : Quit");
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
                    printf("��");
                    setTextColor(WHITE); // �⺻ �������� �ǵ���
                    break;
                case INACTIVE_BLOCK:
                case ACTIVE_BLOCK:
                    setTextColor(main_color[i][j]);
                    printf("��");
                    setTextColor(WHITE); // �⺻ �������� �ǵ���
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
                    printf("��");
                    setTextColor(WHITE);
                    break;
                default:
                    setTextColor(main_color[i][j]);
                    printf("��");
                    setTextColor(WHITE); // �⺻ �������� �ǵ���
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







//ȭ�鿡 ȣ��
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



//next block�����
void update_next() {
    b_type_next = rand() % 7; //���� ���� ���� 
    for (int i = 1; i < 3; i++) { //���ӻ���ǥ�ÿ� ������ ���ú��� �׸� 
        for (int j = 0; j < 4; j++) {
            if (blocks[b_type_next][0][i][j] == 1) {
                gotoxy(STATUS_X_ADJ + 2 + j, i + 6);
                printf("��");
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





//�Ʒ��� �̵� & �浹�Ͽ� ���̻� ������ �� ���� ��� inactive���·� ����
//��������, new blcok on flag�Ѽ� ���ο� ��� �����غ�
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


// Bomb �������� Ȱ��ȭ�ϴ� �Լ� ����
void activateBomb(int x, int y) {
    int range = 1; // ��ź�� ���� ����
    int i, j;

    // ��ź�� ���� ���� ���� ��ϵ��� ���� �ٲٰ� �����̰� ��
    for (i = x - range; i <= x + range; i++) {
        for (j = y - range; j <= y + range; j++) {
            // �迭 ������ ����� �ʴ��� Ȯ��
            if (i >= 0 && i < MAIN_Y && j >= 0 && j < MAIN_X && main_org[i][j] != WALL) {
                main_org[i][j] = THORN; // �� ������� �ӽ� ����
                main_color[i][j] = WHITE; // ���� ���� ����
            }
        }
    }
    draw_main(); // ȭ�鿡 �� ����� �׸�
    Sleep(500);

    // ���� �����̰� ��
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

    // �� ����� ����� ���� ��ϵ��� ������
    for (i = x - range; i <= x + range; i++) {
        for (j = y - range; j <= y + range; j++) {
            if (i >= 0 && i < MAIN_Y && j >= 0 && j < MAIN_X && main_org[i][j] == THORN) {
                main_org[i][j] = EMPTY;
            }
        }
    }
    draw_main(); // ȭ���� �ٽ� �׸�
}


void activateDrill(int x, int y) {
    // �帱�� ������ ��ϵ��� ���� �ٲٰ� �����̰� ��
    for (int i = x; i < MAIN_Y - 1; i++) { // �ٴ�(WALL) �ٷ� �������� ����
        if (main_org[i][y] != WALL) {
            main_org[i][y] = THORN; // �� ������� �ӽ� ����
            main_color[i][y] = WHITE; // ���� ���� ����
        }
        else {
            break;
        }
    }
    draw_main(); // ȭ�鿡 �� ����� �׸�
    Sleep(500);

    // ���� �����̰� ��
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

    // �� ����� ����� ���� ��ϵ��� ������
    for (int i = x; i < MAIN_Y - 1; i++) {
        if (main_org[i][y] == THORN) {
            main_org[i][y] = EMPTY;
        }
    }
    draw_main(); // ȭ���� �ٽ� �׸�
}

void activateThorn() {
    int i, j;
    bool star_present = false;

    // ���� �ִ��� Ȯ���ϰ� �ִٸ� star_present�� true�� ����
    for (i = 0; i < MAIN_Y; i++) {
        for (j = 0; j < MAIN_X; j++) {
            if (main_org[i][j] == THORN) {
                star_present = true;
                main_org[i][j] = EMPTY;
            }
        }
    }

    if (star_present) {
        // �� �Ʒ� ���� ���� �ٲٰ� ��¦�̰� ��
        for (j = 1; j < MAIN_X - 1; j++) {
            main_org[MAIN_Y - 2][j] = THORN;
            main_color[MAIN_Y - 2][j] = WHITE; // ���� ���� ����
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

        // �� �Ʒ� �� ����
        for (j = 1; j < MAIN_X - 1; j++) {
            main_org[MAIN_Y - 2][j] = EMPTY;
        }

        // ���� �ִ� ��ϵ��� �� �پ� ����
        for (i = MAIN_Y - 3; i > 3; i--) {
            for (j = 1; j < MAIN_X - 1; j++) {
                main_org[i + 1][j] = main_org[i][j];
                main_color[i + 1][j] = main_color[i][j];
            }
        }

        // õ�� �ٷ� �Ʒ� ���� ��ĭ���� ���� (���� ����� �� �پ� ������ ��)
        for (j = 1; j < MAIN_X - 1; j++) {
            main_org[4][j] = EMPTY;
            main_color[4][j] = WHITE; // õ�� �Ʒ� �� ���� �ʱ�ȭ
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
                    main_color[by + i][bx + j] = blockColors[next_item.type - 10]; // ������ ���� ����
                }
            }
        }
        is_item_moving = true;
        current_item = next_item;
        Inventory[selectedItemIndex] = (Item){ 0 };  // ������ �������� �κ��丮���� ����
        selectedItemIndex = -1;
        item_selected = false;
    }
    else {
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) {
                    main_org[by + i][bx + j] = ACTIVE_BLOCK;
                    main_color[by + i][bx + j] = blockColors[b_type]; // ��� ���� ����
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
                    main_color[by + i][bx + j - 1] = YELLOW;  // �������� ���� ����
                }
                else if (!is_item_moving && blocks[b_type][b_rotation][i][j] == 1) {
                    main_org[by + i][bx + j - 1] = ACTIVE_BLOCK;
                    main_color[by + i][bx + j - 1] = getColorByBlockType(b_type);  // ����� ���� ����
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
                    main_color[by + i][bx + j + 1] = YELLOW;  // �������� ���� ����
                }
                else if (!is_item_moving && blocks[b_type][b_rotation][i][j] == 1) {
                    main_org[by + i][bx + j + 1] = ACTIVE_BLOCK;
                    main_color[by + i][bx + j + 1] = getColorByBlockType(b_type);  // ����� ���� ����
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
                    main_color[by + i + 1][bx + j] = YELLOW;  // �������� ���� ����
                }
                else if (!is_item_moving && blocks[b_type][b_rotation][i][j] == 1) {
                    main_org[by + i + 1][bx + j] = ACTIVE_BLOCK;
                    main_color[by + i + 1][bx + j] = getColorByBlockType(b_type);  // ����� ���� ����
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
                    main_color[by + i][bx + j] = YELLOW;  // �������� ���� ����
                }
                else if (!is_item_moving && blocks[b_type][b_rotation][i][j] == 1) {
                    main_org[by + i][bx + j] = ACTIVE_BLOCK;
                    main_color[by + i][bx + j] = getColorByBlockType(b_type);  // ����� ���� ����
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
                    main_color[by + i - 1][bx + j] = YELLOW;  // �������� ���� ����
                }
                else if (!is_item_moving && blocks[b_type][b_rotation][i][j] == 1) {
                    main_org[by + i - 1][bx + j] = ACTIVE_BLOCK;
                    main_color[by + i - 1][bx + j] = getColorByBlockType(b_type);  // ����� ���� ����
                }
            }
        }
        by--;
        break;
    }
    draw_main();
}




// ���� ��¦�̰� �ϴ� �Լ�
void blink_star(int x, int y) {
    gotoxy(x, y);
    setTextColor(YELLOW);
    printf("��");
    Sleep(200);
    gotoxy(x, y);
    setTextColor(WHITE);
    printf("��");
    Sleep(200);
}


void exchange_block_item(void) {
    // �κ��丮 ����
    for (int i = 0; i < INVENTORY_SIZE - 1; i++) {
        if (Inventory[i].type == 0) {
            for (int j = i + 1; j < INVENTORY_SIZE; j++) {
                if (Inventory[j].type != 0) {
                    Inventory[i] = Inventory[j];
                    Inventory[j] = (Item){ 0 }; // ����� ������ EMPTY�� ����
                    break;
                }
            }
        }
    }

    if (item_selected) {
        // �̹� ���õ� �������� �����ϰ� �κ��丮�� �ٽ� �׸��ϴ�.
        selectedItemIndex = -1;
        item_selected = false;
        draw_inventory();
        return;
    }

    // ù ��° ��� ������ ������ ����
    for (int i = 0; i < INVENTORY_SIZE; i++) {
        if (Inventory[i].type != 0) {
            selectedItemIndex = i;
            next_item = Inventory[selectedItemIndex];
            item_selected = true;
            break;
        }
    }

    if (selectedItemIndex == -1) { // ��ȿ�� �������� ���� ���
        item_selected = false;
    }

    playEffect(path_sound_hard_drop);

    draw_inventory();
}




// ������ ������ ����(3��)
Item createRandomItem() {
    int itemType = rand() % 3 + 10; // BOMB(10), THORN(11), DRILL(12) �� �ϳ�
    return createItem(itemType);
}


Item createItem(int type) {
    Item newItem;
    newItem.type = type;

    // ������ ��� ����
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





void draw_inventory() { // �κ��丮�� �ٽ� �׸�(������Ʈ)
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
        setTextColor(WHITE); //�⺻ �ܼ� �ؽ�Ʈ �������� �ǵ���
    }
}

void check_line(void) {
    int i, j, k, l;
    int block_amount; //������ ��ϰ����� �����ϴ� ����
    int combo = 0; //�޺����� �����ϴ� ���� ������ �ʱ�ȭ
    bool lineCompleted = false;

    for (i = MAIN_Y - 2; i > 3;) { //i=MAIN_Y-2 : ���ʺ��� ��ĭ����,  i>3 : õ��(3)�Ʒ����� �˻�
        block_amount = 0; //��ϰ��� ���� ���� �ʱ�ȭ
        for (j = 1; j < MAIN_X - 1; j++) { //���� �������� ��ϰ��縦 ��
            if (main_org[i][j] > 0) block_amount++;
        }
        if (block_amount == MAIN_X - 2) { //����� ���� �� ���
            lineCompleted = true;
            if (level_up_on == 0) { //���������°� �ƴ� ��쿡(�������� �Ǹ� �ڵ� �ٻ����� ����)
                score += 100 * level; //�����߰�
                cnt++; //���� �� ���� ī��Ʈ ����
                if (hard_mode) hard_mode_block_count++; // Hard mode���� ��� ���� ī��Ʈ ����
                combo++; //�޺��� ����
            }
            for (k = i; k > 1; k--) { //������ ��ĭ�� ��� ����(������ õ���� �ƴ� ��쿡��)
                for (l = 1; l < MAIN_X - 1; l++) {
                    if (main_org[k - 1][l] != CEILLING) {
                        main_org[k][l] = main_org[k - 1][l];
                        main_color[k][l] = main_color[k - 1][l]; // ���� �Բ� �̵�
                    }
                    if (main_org[k - 1][l] == CEILLING) {
                        main_org[k][l] = EMPTY;
                        main_color[k][l] = WHITE; // ������ �⺻������ ����
                    }
                    //������ õ���� ��쿡�� õ���� ��ĭ ������ �ȵǴϱ� ��ĭ�� ����
                }
            }
        }
        else i--;
    }

    if (lineCompleted && shouldGenerateItem()) {
        Item newItem = createRandomItem();
        addItemToInventory(newItem);
        // �κ��丮�� �߰��� �������� ȭ�鿡 ǥ��
        draw_inventory();
    }

    if (combo) { //�� ������ �ִ� ��� ������ ���� ��ǥ�� ���� ǥ����
        if (combo > 1) { //2�޺��̻��� ��� ��� ���ʽ��� �޼����� �����ǿ� ����ٰ� ����
            gotoxy(MAIN_X_ADJ + (MAIN_X / 2) - 1, MAIN_Y_ADJ + by - 2); printf("%d COMBO!", combo);
            Sleep(500);
            score += (combo * level * 100);
            reset_main_cpy(); //�ؽ�Ʈ�� ����� ���� main_cpy�� �ʱ�ȭ.
            //(main_cpy�� main_org�� ���� �ٸ��Ƿ� ������ draw()ȣ��� ������ ��ü�� ���� �׸��� ��)
        }
        gotoxy(STATUS_X_ADJ, STATUS_Y_GOAL); printf(" GOAL  : %5d", (cnt <= goal) ? goal - cnt : 0);
        gotoxy(STATUS_X_ADJ, STATUS_Y_SCORE); printf("        %6d", score);
    }

    // Hard mode���� 5���� ������ �� �ӵ��� �ø��� INACTIVE ��� �� �� �߰�
    if (hard_mode && hard_mode_block_count >= 5) {
        hard_mode_block_count = 0; // ī��Ʈ �ʱ�ȭ
        level++; // ���� ����
        speed = (speed > 1) ? speed - 1 : speed; // �ӵ��� ������Ŵ
        gotoxy(STATUS_X_ADJ, STATUS_Y_LEVEL); printf(" LEVEL : %5d", level); //����ǥ�� 

        for (i = 0; i < 4; i++) {
            gotoxy(MAIN_X_ADJ + (MAIN_X / 2) - 3, MAIN_Y_ADJ + 4);
            printf("             ");
            gotoxy(MAIN_X_ADJ + (MAIN_X / 2) - 2, MAIN_Y_ADJ + 6);
            printf("             ");
            Sleep(200);

            gotoxy(MAIN_X_ADJ + (MAIN_X / 2) - 3, MAIN_Y_ADJ + 4);
            printf("��LEVEL UP!��");
            gotoxy(MAIN_X_ADJ + (MAIN_X / 2) - 2, MAIN_Y_ADJ + 6);
            printf("��SPEED UP!��");
            Sleep(200);
        }
        reset_main_cpy(); //�ؽ�Ʈ�� ����� ���� main_cpy�� �ʱ�ȭ.

        // ��� ����� �� �྿ ���� �ø�
        for (i = 4; i < MAIN_Y - 2; i++) {
            for (j = 1; j < MAIN_X - 1; j++) {
                main_org[i - 1][j] = main_org[i][j];
                main_color[i - 1][j] = main_color[i][j]; // ���� �Բ� �̵�
            }
        }

        // �� �Ʒ��� INACTIVE ��� �� �� �߰�
        for (j = 1; j < MAIN_X - 1; j++) {
            main_org[MAIN_Y - 2][j] = INACTIVE_BLOCK;
            main_color[MAIN_Y - 2][j] = main_color[MAIN_Y - 3][j]; // ���� ���� �������� ����
        }

        // �� ���� ���� �� ĭ���� ����
        for (j = 1; j < MAIN_X - 1; j++) {
            main_org[3][j] = EMPTY;
            main_color[3][j] = WHITE; // �⺻ �������� ����
        }

        draw_main(); // ȭ���� �ٽ� �׸�
    }

    // �������� �� �� goal�� �ʱ�ȭ
    if (cnt >= goal) {
        cnt = 0;
        gotoxy(STATUS_X_ADJ, STATUS_Y_GOAL); printf(" GOAL  : %5d", goal);
    }
}





void check_level_up(void) {
    int i, j;

    if (cnt >= 10) { //�������� 10�پ� ���־���. 10���̻� ���� ��� 
        draw_main();
        level_up_on = 1; //������ flag�� ��� 
        level += 1; //������ 1 �ø� 
        cnt = 0; //���� �ټ� �ʱ�ȭ   

        for (i = 0; i < 4; i++) {
            gotoxy(MAIN_X_ADJ + (MAIN_X / 2) - 3, MAIN_Y_ADJ + 4);
            printf("             ");
            gotoxy(MAIN_X_ADJ + (MAIN_X / 2) - 2, MAIN_Y_ADJ + 6);
            printf("             ");
            Sleep(200);

            gotoxy(MAIN_X_ADJ + (MAIN_X / 2) - 3, MAIN_Y_ADJ + 4);
            printf("��LEVEL UP!��");
            gotoxy(MAIN_X_ADJ + (MAIN_X / 2) - 2, MAIN_Y_ADJ + 6);
            printf("��SPEED UP!��");
            Sleep(200);
        }
        reset_main_cpy(); //�ؽ�Ʈ�� ����� ���� main_cpy�� �ʱ�ȭ.
        //(main_cpy�� main_org�� ���� �ٸ��Ƿ� ������ draw()ȣ��� ������ ��ü�� ���� �׸��� ��) 

        if (hard_mode) {
            // �� �Ʒ��� INACTIVE ��� �� �� �߰�
            for (j = 1; j < MAIN_X - 1; j++) {
                main_org[MAIN_Y - 2][j] = INACTIVE_BLOCK;
            }

            // ��� ����� �� �྿ ���� �ø�
            for (i = 4; i < MAIN_Y - 2; i++) {
                for (j = 1; j < MAIN_X - 1; j++) {
                    main_org[i - 1][j] = main_org[i][j];
                }
            }

            // �� ���� ���� �� ĭ���� ����
            for (j = 1; j < MAIN_X - 1; j++) {
                main_org[3][j] = EMPTY;
            }

            draw_main(); // ȭ���� �ٽ� �׸�
        }
        else {
            // Easy mode������ �Ʒ� ���� ������
            for (i = MAIN_Y - 2; i > MAIN_Y - 2 - (level - 1); i--) {
                for (j = 1; j < MAIN_X - 1; j++) {
                    main_org[i][j] = EMPTY;
                    gotoxy(MAIN_X_ADJ + j, MAIN_Y_ADJ + i);
                    printf("  ");
                    Sleep(20);
                }
            }
        }
        Sleep(100); //�������� �����ֱ� ���� delay 
        check_line(); //������� ��� ä��� �����
        //.check_line()�Լ� ���ο��� level up flag�� �����ִ� ��� ������ ����.         
        switch (level) { //�������� �ӵ��� ��������. 
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
        level_up_on = 0; //������ flag�� �ʱ�ȭ
    }
}


// ���� ������ ����ü ����
typedef struct {
    char question[512];
    char choices[4][128];
    char answer;
    int coord_y;
} Quiz;

Quiz quizzes[] = {
    {"������ ���� ����� ���Ǹ� ���ÿ�.\nLOAD A 1\nLOAD B 2\nADD A,B\n",
     {"A. High level language", "B. Assembly language", "C. Machine language", "D. None of the above"}, 'B', 3},

    {"���� �� �ٸ��� ������� ���� ���� ���ÿ�\n",
     {"A. Integer-%d", "B. String-%s", "C. Octal-%o", "D. Hexadecimal-%h"}, 'D', 3},

    {"unsigned char�� ���� �� �ִ� ��� ������ ������ ���� ���ÿ�\n",
     {"A. 0 to 255", "B. 0 to 65535", "C. -128 to 128", "D. -128 to 127"}, 'A', 3},

    {"���� �� long�� ���� ������(bytes)�� ���� ������ Ÿ���� �ۼ��Ͻÿ�\n",
     {"A. char", "B. short", "C. int", "D. double"}, 'C', 3},

    {"������ ����� ���ÿ�\n#include <stdio.h>\nint main(void)\n{\n short s=32767; // Max value 32767\n s+=1;\n printf(\"%d\", s);\n return 0;\n}\n",
     {"A. 32767", "B. 32768", "C. 0", "D. error"}, 'C', 11},

    {"'s+=1' �κп��� �߻��ϴ� ������ ���Ǹ� ����� ���ÿ�\n#include <stdio.h>\nint main(void)\n{\n short s=32767; // Max value 32767\n s+=1;\n printf(\"%d\", s);\n return 0;\n}\n",
     {"A. underflow", "B. overflow", "C. segmentation fault", "D. invalid operation"}, 'B', 11},

    {"������ ����� ���ÿ�\n#include <stdio.h>\nint main(void)\n{\nint a,b,c;\na=5;\nb=++a;\nc=a--;\nprintf(\"%d,%d,%d\",a,b,c);\nreturn 0;\n}\n",
     {"A. 5, 6, 5", "B. 5, 6, 4", "C. 6, 6, 6", "D. 5, 6, 6"}, 'D', 13},

    {"�Է¹��� ������ ������ �� ���� ����ϱ� ���� ������ ��ĭ�� �� for���� �ۼ��Ͻÿ�\n#include <stdio.h>\nint main()\n{\n int i, n;\n scanf(\"%d\", &n);\n ( ??? )\n {\n printf(\"%d x %d = %d\\n\", n, i, n*i);\n }\n return 0;\n}\n",
     {"A. for(i=1;i<9;i++)", "B. for(i=0;i<10;i++)", "C. for(i=1;i<10;i++)", "D. for(i=1;i<=10;i++)"}, 'C', 14},

    {"!(1 && (0 || 1))\n",
     {"A. True", "B. False", "C. Unevaluatable", "D. None of the above"}, 'B', 3},

    {"������ ����� ���ÿ�.\nint x=0;\nSwitch(x)\n{\ncase 1:\n print(\"One\");\ncase 0:\n print(\"Zero\");\ncase 2:\n print(\"Two\");\n}\n",
     {"A. One", "B. Zero", "C. ZeroTwo", "D. OneZeroTwo"}, 'C', 13},

    {"������ printf �Լ��� ����ϱ� ���� �ʿ��� �ڵ带 ���ÿ�.\nint main(void)\n{ printf(\"hello\\n\");\n}\n",
     {"A. #Printf", "B. #Define printf", "C. define printf", "D. #include <stdio.h>"}, 'D', 6},

    {"������ ���� a �ּ� ���� �ִ� �����͸� �ǹ��ϴ� ���� ���ÿ�\n",
     {"A. a;", "B. val(a);", "C. *a;", "D. &a;"}, 'C', 3},

    {"���� ��ĭ�� ������ �ڵ� �� ���� �ۼ��Ͻÿ�.\n#include <stdio.h>\n( ??? )\nint main()\n{\n test(5);\n}\nvoid test(int a)\n{\n for(int i=0; i<a; i++){\n printf(\"hello\\n\");\n }\n}\n",
     {"A. void test(void);", "B. void test(int);", "C. int test(void);", "D. int test(int);"}, 'B', 15},

    {"������ ������ ��°��� 99�� �Ǳ����� ��ĭ�� ä��ÿ�.(���� ����)\n#include <stdio.h>\nint main()\n{\n int i = 0;\n do {\n printf(\"%d\\n\", i);\n i++;\n } ( ??? );\n return 0;\n}\n",
     {"A. while(i<100)", "B. while(i<=99)", "C. while(i>100)", "D. while(i>=99)"}, 'A', 12},

    {"x�� ���� �ۼ��Ͻÿ�\nint *ptr;\nint x=1;\nptr = &x;\n*ptr = 0;\n",
     {"A. 0", "B. 1", "C. -1", "D. Undefined"}, 'A', 7},

    {"���� ��°��� ���� ���� ���ÿ�\n#include <stdio.h>\nint main()\n{\n int arr[3] = {1,2,3};\n printf(\"%p\\n\", arr);\n return 0;\n",
     {"A. arr[]", "B. &arr[0]", "C. &arr[1]", "D. &arr[2]"}, 'B', 8},

    {"���� p�� �������� ���� ���� ���ÿ�\nint x[3]={1,2,3};\nint *p;\np=x;\np++;\n",
     {"A. x[1]", "B. &x[0]", "C. &x[1]", "D. &x[2]"}, 'C', 7},

    {"���� y�� ���� �ۼ��Ͻÿ�\nint x[3]={2,3,5};\nint y;\nint *p=&x[2];\ny=6+*(--p);\n",
     {"A. 7", "B. 8", "C. 9", "D. 10"}, 'C', 7},

    {"���� y�� ���� �ۼ��Ͻÿ�\nint x[3]={2,3,5};\nint y;\nint *p=x;\n++(*p)\ny=3+*(++p);\n",
     {"A. 5", "B. 6", "C. 7", "D. 8"}, 'B', 8},

    {"���� y�� ���� �ۼ��Ͻÿ�\nint x[3]={1,3,5};\nint y;\nint *p=x;\n++p\ny=6+ --(*p);\n",
     {"A. 6", "B. 7", "C. 8", "D. 9"}, 'C', 8}
};

void print_options(Quiz quiz, int selected_option) {
    COORD coord;
    for (int i = 0; i < 4; i++) {
        coord.X = 0;
        coord.Y = quiz.coord_y + i; // ���� ��� �� �ٹٲ� �� ��ġ�� ����
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        if (i == selected_option) {
            setTextColor(YELLOW); // �����
            printf("�� %s\n", quiz.choices[i]);
            setTextColor(WHITE); // ���
        }
        else {
            printf("�� %s\n", quiz.choices[i]);
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

    print_options(quizzes[quiz_index], selected_option); // �ʱ� ���� �׸� ���

    while (1) {
        // Ű �Է� ó��
        if (_kbhit()) {
            key = _getch();
            if (key == 224) { // ����Ű�� ��� ù ��°�� 224�� �Էµ�
                key = _getch(); // ���� Ű �� �Է�
                switch (key) {
                case 72: // ���� ����Ű
                    selected_option = (selected_option == 0) ? 3 : selected_option - 1;
                    break;
                case 80: // �Ʒ��� ����Ű
                    selected_option = (selected_option == 3) ? 0 : selected_option + 1;
                    break;
                }
                print_options(quizzes[quiz_index], selected_option); // ����� ���� �׸��� �ٽ� ���
            }
            else if (key == 32) { // �����̽� Ű
                break;
            }
        }
    }

    // ���� Ȯ��
    if (quizzes[quiz_index].choices[selected_option][0] == quizzes[quiz_index].answer) {
        printf("�����Դϴ�! ������ �̾ ������ �� �ֽ��ϴ�.\n");
        score = last_game_score; // ����� ������ ����
        Sleep(2000);
        system("cls");
        reset_main_cpy();
        reset_main();
        draw_map();
        draw_main();
    }
    else {
        printf("Ʋ�Ƚ��ϴ�. Game Over.\n");
        printf("���� ����: %d\n", score);
        score = 0; // ������ �ʱ�ȭ
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

            gotoxy(x, y + 0); printf("�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�");
            gotoxy(x, y + 1); printf("��                              ��");
            gotoxy(x, y + 2); printf("��  +-----------------------+   ��");
            gotoxy(x, y + 3); printf("��  |  G A M E  O V E R..   |   ��");
            gotoxy(x, y + 4); printf("��  +-----------------------+   ��");
            gotoxy(x, y + 5); printf("��   YOUR SCORE: %6d         ��", score);
            gotoxy(x, y + 6); printf("��                              ��");
            gotoxy(x, y + 7); printf("��  Press any key to continue..  ��");
            gotoxy(x, y + 8); printf("��                              ��");
            gotoxy(x, y + 9); printf("�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�");
            last_score = score;

            // ���� ������ last_game_score�� ����
            last_game_score = score;

            if (score > best_score) {
                FILE* file = fopen("score.dat", "wt");

                gotoxy(x, y + 6); printf("��  �ڡڡ� BEST SCORE! �ڡڡ�   ��  ");

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

            // ��� �����Ͽ� ���߸� ������ �����ϰ� �� ������ �����մϴ�.
            ask_quiz();
        }
    }
}


void pause(void) { //���� �Ͻ����� �Լ� 
    int i, j;

    int x = 5;
    int y = 5;

    for (i = 1; i < MAIN_X - 2; i++) { //���� �Ͻ����� �޼��� 
        gotoxy(x, y + 0); printf("�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�");
        gotoxy(x, y + 1); printf("��                              ��");
        gotoxy(x, y + 2); printf("��  +-----------------------+   ��");
        gotoxy(x, y + 3); printf("��  |       P A U S E       |   ��");
        gotoxy(x, y + 4); printf("��  +-----------------------+   ��");
        gotoxy(x, y + 5); printf("��  Press any key to resume..   ��");
        gotoxy(x, y + 6); printf("��                              ��");
        gotoxy(x, y + 7); printf("�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�");
    }
    _getch(); //Ű�Է½ñ��� ��� 

    system("cls"); //ȭ�� ����� ���� �׸� 
    reset_main_cpy();
    draw_main();
    draw_map();

    for (i = 1; i < 3; i++) { // ������� �׸� 
        for (j = 0; j < 4; j++) {
            if (blocks[b_type_next][0][i][j] == 1) {
                gotoxy(MAIN_X + MAIN_X_ADJ + 3 + j, i + 6);
                printf("��");
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
    static int aliasCounter = 0;  // ȿ���� ��Ī�� ���� ī����
    char alias[32];
    snprintf(alias, sizeof(alias), "effect%d", aliasCounter++);

    const char* ext = strrchr(soundFile, '.');
    if (ext != NULL) {
        if (strcmp(ext, ".wav") == 0) {
            if (_access(soundFile, 0) != -1) {
                // .wav ���� ���
                PlaySoundA(soundFile, NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
                // ���� ����
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
            // ���� ����
            snprintf(command, sizeof(command), "setaudio %s volume to %d", alias, sound_volume * 10);
            mciSendStringA(command, NULL, 0, NULL);

            // ȿ������ ���� �� �ݱ�
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