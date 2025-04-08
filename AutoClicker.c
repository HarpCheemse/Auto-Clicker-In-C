#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <pthread.h>

#define PRINT_RED "\x1b[31m" 
#define PRINT_GREEN "\x1b[32m"
#define PRINT_AQUA "\x1b[36m"
#define PRINT_GOLD "\033[1;33m"
#define PRINT_LIGHT_AQUA "\033[1;33m""\x1b[36m"
#define PRINT_COLOR_RESET "\x1b[0m" 

int AUTO_CLICKER_RUNNING = 0;
int CLICK_PER_SECOND = 1;
int TOGGLE_KEY = 0;

void getKeybind();
void printMenu();
void changeCPS();

void clearBuffer()
{
    int ch;
    while(ch = getchar() != '\n') {}
}
void refreshMenu()
{
    system("cls");
    printMenu();
}
void printMenu()
{
    char line[50] = "=======================================";
    printf(PRINT_AQUA"%s\n"PRINT_COLOR_RESET, line);
    printf(PRINT_GOLD"          Auto Clicker        \n");
    printf("1. Set Click Speed. Currently"PRINT_GREEN" %d"PRINT_COLOR_RESET PRINT_GOLD" CPS\n", CLICK_PER_SECOND);
    printf("2. Set Key Bind. Currently ` \n");
    printf("3. Exit The Program\n"PRINT_COLOR_RESET);
    printf(PRINT_AQUA"%s\n"PRINT_COLOR_RESET, line);
}
void printUserPrompt()
{
    printf(PRINT_LIGHT_AQUA"\nEnter Your Choice: "PRINT_COLOR_RESET);
}
void leftClick()
{
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}
void menuHandler()
{
    refreshMenu();
    printUserPrompt();
    while(1)
    {
        int user_selection;
        scanf("%d", &user_selection);
        switch (user_selection)
        {
        case 1:
            refreshMenu();
            printUserPrompt();
            changeCPS();
            refreshMenu();
            printUserPrompt();
            break;
        case 2:
            refreshMenu();
            printf("This Feature Will Be Implemented Soon :3\n");
            printf(PRINT_AQUA"Press Enter to continue..."PRINT_COLOR_RESET);
            while (getchar() != '\n');
            getchar();
            printUserPrompt();
            break;
        case 3:
            refreshMenu();
            printf(PRINT_GREEN"Exit Program Succesfully"PRINT_COLOR_RESET);
            break;
        default:
            clearBuffer();
            refreshMenu();
            printf(PRINT_RED"Invalid Input!"PRINT_COLOR_RESET);
            printUserPrompt();
            break;
        }
    }
}
void changeCPS()
{
    refreshMenu();
    printf(PRINT_LIGHT_AQUA"\nChange CPS: "PRINT_COLOR_RESET);
    scanf("%d", &CLICK_PER_SECOND);
    return;
}
void* clickEvent(void* arg)
{
    DWORD last_click_time = 0;
    while(1)
    {
        if (GetAsyncKeyState(VK_OEM_3) & 0x8000)
        {
            AUTO_CLICKER_RUNNING = !AUTO_CLICKER_RUNNING;
            Sleep(150); //debound delay
        }
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
        {
            exit(0);
        }
        if(AUTO_CLICKER_RUNNING)
        {
            DWORD current_click_time =  GetTickCount();
            if(current_click_time-last_click_time >= (1000/CLICK_PER_SECOND))
            {
                leftClick();
                last_click_time = current_click_time;
            }
        }
        else if(!AUTO_CLICKER_RUNNING)
        {
            Sleep(1);
        }
    }
    return NULL;
}
void getKeybind()
{
    refreshMenu();
    printf(PRINT_LIGHT_AQUA"\nPress Any Key For Toogle Button: "PRINT_COLOR_RESET);
    TOGGLE_KEY = getch();
}
int main() 
{
    pthread_t background_button_press_check;
    pthread_create(&background_button_press_check, NULL, clickEvent, NULL);
    pthread_detach(background_button_press_check);
    menuHandler();
    return 0;
}
