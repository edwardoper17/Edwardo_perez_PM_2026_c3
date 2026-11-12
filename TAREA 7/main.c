/*TAREA 7 - Calculadora del costo de un viaje (version grafica simple)*/

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 14
#define ID_CALCULAR 100

static const char *etiquetas[N] = {
    "Consumo ciudad (km/L)",
    "Consumo carretera (km/L)",
    "Seguro anual (RD$)",
    "Impuestos anuales (RD$)",
    "Limpieza anual (RD$)",
    "Neumaticos (RD$/km)",
    "Mantenimiento (RD$/km)",
    "Valor inicial (RD$)",
    "Valor final (RD$)",
    "Tiempo de uso (anios)",
    "Kilometros anuales",
    "Precio combustible (RD$/L)",
    "Distancia del viaje (km)",
    "Porcentaje en carretera (0-100)"
};

static const char *defectos[N] = {
    "12", "16", "25000", "8000", "6000", "1.5", "2",
    "1200000", "600000", "5", "15000", "75", "100", "50"
};

static HWND campos[N];
static HWND resultado;


static int leerCampo(int i, double *out)
{
    char buf[64];
    char *p, *fin = NULL;

    GetWindowText(campos[i], buf, sizeof buf);
    for (p = buf; *p; p++) {
        if (*p == ',') *p = '.';
    }
    if (buf[0] == '\0') return 0;
    *out = strtod(buf, &fin);
    return (fin != buf && *fin == '\0');
}

static void calcular(HWND hwnd)
{
    double v[N];
    int i;
    char msg[128];
    char txt[512];
    double dep, fijos_anual, costo_fijo_km;
    double km_carr, km_ciu, combustible, variables, fijos, total;

    for (i = 0; i < N; i++) {
        if (!leerCampo(i, &v[i])) {
            snprintf(msg, sizeof msg, "Valor invalido en: %s", etiquetas[i]);
            MessageBox(hwnd, msg, "Error", MB_OK | MB_ICONWARNING);
            return;
        }
    }


    if (v[0] <= 0 || v[1] <= 0 || v[9] <= 0 || v[10] <= 0 ||
        v[11] <= 0 || v[12] <= 0 || v[7] <= 0) {
        MessageBox(hwnd,
                   "Consumos, valor inicial, tiempo, km anuales, precio y distancia deben ser mayores que 0.",
                   "Error", MB_OK | MB_ICONWARNING);
        return;
    }
    if (v[2] < 0 || v[3] < 0 || v[4] < 0 || v[5] < 0 || v[6] < 0 || v[8] < 0) {
        MessageBox(hwnd, "Los costos no pueden ser negativos.",
                   "Error", MB_OK | MB_ICONWARNING);
        return;
    }
    if (v[8] > v[7]) {
        MessageBox(hwnd, "El valor final no puede superar el valor inicial.",
                   "Error", MB_OK | MB_ICONWARNING);
        return;
    }
    if (v[13] < 0 || v[13] > 100) {
        MessageBox(hwnd, "El porcentaje en carretera debe estar entre 0 y 100.",
                   "Error", MB_OK | MB_ICONWARNING);
        return;
    }

    dep = (v[7] - v[8]) / v[9];
    fijos_anual = v[2] + v[3] + v[4] + dep;
    costo_fijo_km = fijos_anual / v[10];

    km_carr = v[12] * v[13] / 100.0;
    km_ciu = v[12] - km_carr;
    combustible = (km_ciu / v[0] + km_carr / v[1]) * v[11];
    variables = v[12] * (v[5] + v[6]);
    fijos = v[12] * costo_fijo_km;
    total = combustible + variables + fijos;

    snprintf(txt, sizeof txt,
             "Combustible:      RD$ %.2f\r\n"
             "Costos variables: RD$ %.2f\r\n"
             "Costos fijos:     RD$ %.2f\r\n"
             "\r\n"
             "COSTO TOTAL:      RD$ %.2f\r\n"
             "Costo por km:     RD$ %.2f",
             combustible, variables, fijos, total, total / v[12]);
    SetWindowText(resultado, txt);
}

static LRESULT CALLBACK ventana(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    int i;
    HFONT fuente;
    HWND h;

    switch (msg) {
    case WM_CREATE:
        fuente = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
        for (i = 0; i < N; i++) {
            h = CreateWindow("STATIC", etiquetas[i], WS_CHILD | WS_VISIBLE,
                             10, 12 + i * 28, 220, 20, hwnd, NULL, NULL, NULL);
            SendMessage(h, WM_SETFONT, (WPARAM)fuente, TRUE);
            campos[i] = CreateWindow("EDIT", defectos[i],
                                     WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
                                     240, 10 + i * 28, 140, 22, hwnd, NULL, NULL, NULL);
            SendMessage(campos[i], WM_SETFONT, (WPARAM)fuente, TRUE);
        }
        h = CreateWindow("BUTTON", "Calcular", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
                         10, 10 + N * 28 + 8, 370, 30, hwnd,
                         (HMENU)ID_CALCULAR, NULL, NULL);
        SendMessage(h, WM_SETFONT, (WPARAM)fuente, TRUE);
        resultado = CreateWindow("EDIT", "",
                                 WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | ES_READONLY,
                                 10, 10 + N * 28 + 48, 370, 110, hwnd, NULL, NULL, NULL);
        SendMessage(resultado, WM_SETFONT,
                    (WPARAM)GetStockObject(ANSI_FIXED_FONT), TRUE);
        return 0;
    case WM_COMMAND:
        if (LOWORD(wp) == ID_CALCULAR) {
            calcular(hwnd);
        }
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, msg, wp, lp);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR cmd, int show)
{
    WNDCLASS wc;
    HWND hwnd;
    MSG m;
    RECT r = {0, 0, 392, 10 + N * 28 + 48 + 120};
    DWORD estilo = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;

    memset(&wc, 0, sizeof wc);
    wc.lpfnWndProc = ventana;
    wc.hInstance = hInst;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
    wc.lpszClassName = "CostoViaje";
    RegisterClass(&wc);

    AdjustWindowRect(&r, estilo, FALSE);
    hwnd = CreateWindow("CostoViaje", "Costo de viaje", estilo,
                        CW_USEDEFAULT, CW_USEDEFAULT,
                        r.right - r.left, r.bottom - r.top,
                        NULL, NULL, hInst, NULL);
    ShowWindow(hwnd, show);

    while (GetMessage(&m, NULL, 0, 0)) {
        TranslateMessage(&m);
        DispatchMessage(&m);
    }
    return 0;
}
