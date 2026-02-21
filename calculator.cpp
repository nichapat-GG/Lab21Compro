#include <windows.h>
#include <stdio.h>

HWND hEdit1, hEdit2;

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
    switch(Message) {
        case WM_CREATE: {
            CreateWindow("Static", "Number 1:", WS_VISIBLE | WS_CHILD, 20, 5, 100, 20, hwnd, NULL, NULL, NULL);
            hEdit1 = CreateWindow("Edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 20, 25, 200, 25, hwnd, NULL, NULL, NULL);
            
            CreateWindow("Static", "Number 2:", WS_VISIBLE | WS_CHILD, 20, 55, 100, 20, hwnd, NULL, NULL, NULL);
            hEdit2 = CreateWindow("Edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 20, 75, 200, 25, hwnd, NULL, NULL, NULL);
            
            CreateWindow("Button", "+", WS_VISIBLE | WS_CHILD, 20, 110, 45, 40, hwnd, (HMENU)1, NULL, NULL);
            CreateWindow("Button", "-", WS_VISIBLE | WS_CHILD, 75, 110, 45, 40, hwnd, (HMENU)2, NULL, NULL);
            CreateWindow("Button", "*", WS_VISIBLE | WS_CHILD, 130, 110, 45, 40, hwnd, (HMENU)3, NULL, NULL);
            CreateWindow("Button", "/", WS_VISIBLE | WS_CHILD, 185, 110, 45, 40, hwnd, (HMENU)4, NULL, NULL);
            break;
        }

        case WM_COMMAND: {
            if(LOWORD(wParam) >= 1 && LOWORD(wParam) <= 4) {
                char t1[100], t2[100], resStr[100];
                GetWindowText(hEdit1, t1, 100);
                GetWindowText(hEdit2, t2, 100);
                
                double n1 = atof(t1);
                double n2 = atof(t2);
                double res = 0;

                if(LOWORD(wParam) == 1) res = n1 + n2;
                if(LOWORD(wParam) == 2) res = n1 - n2;
                if(LOWORD(wParam) == 3) res = n1 * n2;
                if(LOWORD(wParam) == 4) {
                    if(n2 != 0) res = n1 / n2;
                    else { MessageBox(hwnd, "Divide by Zero!", "Error", MB_OK); return 0; }
                }

                sprintf(resStr, "%f", res);
                MessageBox(hwnd, resStr, "Result", MB_OK);
            }
            break;
        }

        case WM_DESTROY: {
            PostQuitMessage(0);
            break;
        }
        default:
            return DefWindowProc(hwnd, Message, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEX wc;
    HWND hwnd;
    MSG msg;

    memset(&wc,0,sizeof(wc));
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = CreateSolidBrush(RGB(50, 205, 50)); 
    wc.lpszClassName = "WindowClass";
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc)) return 0;

    hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, "WindowClass", "My Calculator", 
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, 250, 200, NULL, NULL, hInstance, NULL);

    while(GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}