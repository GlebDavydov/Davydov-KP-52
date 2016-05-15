#include <stdio.h>
#include <windows.h>
#include <CommCtrl.h>
#include <stdlib.h>

#include "teachers.h"

const char g_szClassName[] = "Windows";

#define ID_LABEL 131
#define ID_LB    132

enum {DIALOG_BOX_ID = 1, BUTTON_ID, CHECK_BOX_ID, FNAME_EDIT_ID, LNAME_EDIT_ID, EXP_EDIT_ID, SAL_EDIT_ID};


HINSTANCE hInst;
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(
                   HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow
                  )
{
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_szClassName,
        "Teachers",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 380, 260,
        NULL, NULL, hInstance, NULL);

    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static HWND hButton, hCheckBox, hEditFirstName, hEditLastName, hEditExp, hEditSal, hLabelFirstName, hLabelLastName,
    hLabelExp, hLabelSal;
	HINSTANCE hInstance = GetModuleHandle(NULL);
	teacher_t *teacher = teacher_new_defaults();
    switch(msg)
    {
		case WM_CREATE:
        {
            hButton = CreateWindowEx(0,
                                    WC_BUTTON,
                                    "Show",
                                    WS_CHILD | WS_VISIBLE  | WS_TABSTOP | BS_DEFPUSHBUTTON,
                                    240, 20, 80, 60,
                                    hwnd, (HMENU)BUTTON_ID, hInst, NULL);
            hEditFirstName = CreateWindowEx(0,
                                    WC_EDIT,
                                    teacher_get_fname(teacher),
                                    WS_CHILD | WS_VISIBLE | WS_BORDER,
                                    110, 20, 120, 25,
                                    hwnd, (HMENU)FNAME_EDIT_ID, hInst, NULL);
            hLabelFirstName = CreateWindowEx(0,
                                    "STATIC",
                                    "First name:",
                                     WS_CHILD | WS_VISIBLE,
                                    20, 20, 80, 25,
                                    hwnd, (HMENU)ID_LABEL, hInstance, NULL);
            hEditLastName = CreateWindowEx(0,
                                    WC_EDIT,
                                    teacher_get_lname(teacher),
                                    WS_CHILD | WS_VISIBLE | WS_BORDER,
                                    110, 50, 120, 25,
                                    hwnd, (HMENU)LNAME_EDIT_ID, hInst, NULL);
            hLabelLastName = CreateWindowEx(0,
                                    "STATIC",
                                    "Last name:",
                                     WS_CHILD | WS_VISIBLE,
                                    20, 50, 80, 25,
                                    hwnd, (HMENU)ID_LABEL, hInstance, NULL);
            hEditExp = CreateWindowEx(0,
                                    WC_EDIT,
                                    "0",
                                    WS_CHILD | WS_VISIBLE | WS_BORDER,
                                    110, 80, 120, 50,
                                    hwnd, (HMENU)EXP_EDIT_ID, hInst, NULL);
            hLabelExp = CreateWindowEx(0,
                                    "STATIC",
                                    "Work experience:",
                                     WS_CHILD | WS_VISIBLE,
                                    20, 80, 80, 50,
                                    hwnd, (HMENU)ID_LABEL, hInstance, NULL);
            hEditSal = CreateWindowEx(0,
                                    WC_EDIT,
                                    "1366",
                                    WS_CHILD | WS_VISIBLE | WS_BORDER,
                                    110, 135, 120, 25,
                                    hwnd, (HMENU)EXP_EDIT_ID, hInst, NULL);
            hLabelSal = CreateWindowEx(0,
                                    "STATIC",
                                    "Salary:",
                                     WS_CHILD | WS_VISIBLE,
                                    20, 135, 80, 25,
                                    hwnd, (HMENU)ID_LABEL, hInstance,  NULL);
            hCheckBox = CreateWindowEx(0,
                                     "button",
                                     "Edit info",
                                     BS_CHECKBOX | BS_AUTOCHECKBOX | WS_CHILD | WS_VISIBLE,
                                     240, 95, 80, 25,
                                     hwnd, (HMENU)CHECK_BOX_ID, hInst, NULL);
        }
		break;
		case WM_COMMAND:
		{
		    switch(LOWORD(wParam))
		    {
                case BUTTON_ID:
                {
                    char buff[256];
                    if(IsDlgButtonChecked(hwnd, CHECK_BOX_ID)) {
                        char buff2[30];
                        GetWindowText(hEditFirstName, buff2, sizeof(buff2));
                        teacher_set_fname(teacher, buff2);
                        GetWindowText(hEditLastName, buff2, sizeof(buff2));
                        teacher_set_lname(teacher, buff2);
                        GetWindowText(hEditExp, buff2, sizeof(buff2));
                        teacher_set_experience(teacher, atoi(buff2));
                        GetWindowText(hEditSal, buff2, sizeof(buff2));
                        teacher_set_salary(teacher, atoi(buff2));
                    }
                    sprintf(buff, "First name:\t%10s\nLast name:\t%10s\nExperience:\t%10d\nSalary:\t\t%10d\n", teacher_get_fname(teacher), teacher_get_lname(teacher), teacher_get_experience(teacher), teacher_get_salary(teacher));
                    MessageBox(NULL, (LPCTSTR)buff, L"INFO", MB_OK | MB_ICONINFORMATION);
                    break;
                }
            }
		}
		break;
        case WM_CLOSE:
            free(teacher);
            DestroyWindow(hwnd);
        break;
        case WM_DESTROY:
            free(teacher);
            PostQuitMessage(0);
        break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}
