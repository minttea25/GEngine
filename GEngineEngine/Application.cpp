#include "pch.h"
#include "Application.h"

#include "GTime.h"
#include "Input.h"
#include "SceneManager.h"

NAMESPACE_OPEN(GEngine);

Application::Application()
    : _hwnd(nullptr), _hdc(nullptr),
    _backBuffer(nullptr), _backHdc(nullptr),
    _width(0), _height(0)
{
}

Application::~Application()
{
}

void Application::Init(HWND hwnd, unsigned int width, unsigned int height)
{
    _hwnd = hwnd;
    _hdc = GetDC(hwnd);

    _height = height;
    _width = width;

#pragma warning(push)
#pragma warning(disable: 4838)
    RECT rect = { 0, 0, _width, _height };
#pragma warning(pop)
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
    SetWindowPos(_hwnd, NULL,   
        0, 0,
        rect.right - rect.left, rect.bottom - rect.top,
        0);
    ShowWindow(_hwnd, true);


    // create back-image
    _backBuffer = CreateCompatibleBitmap(_hdc, _width, _height);
    _backHdc = CreateCompatibleDC(_hdc);

    // Exchange old to new
    HBITMAP oldBitmap = (HBITMAP)SelectObject(_backHdc, _backBuffer);
    DeleteObject(oldBitmap);

    Time::Init();
    Input::Init();
    SceneManager::Init();
}

void Application::Run()
{
    Update();
    LateUpdate();
    Render();
}

void Application::Update()
{
    // Time
    Time::Update();

    // Input
    Input::Update();

    // Scene
    SceneManager::Update();
}

void Application::FixedUpdate()
{
    // TODO
}

void Application::LateUpdate()
{
    SceneManager::LateUpdate();
}

void Application::Render()
{
    clearRenterTarget();

    SceneManager::Render(_backHdc);

    ShowFps();

    // Draw hdcSrc at hdc (COPY)
    copyRenderTarget(_backHdc, _hdc);
}

void Application::ShowFps()
{
    float fps = 1.0f / Time::deltaTime();
    wchar_t str[50] = L"";
    swprintf_s(str, 50, L"FPS: %d", (int)fps);

    auto len = wcsnlen_s(str, 50);
#pragma warning(push)
#pragma warning(disable: 4267)
    TextOut(_backHdc, 0, 0, str, len);
#pragma warning(pop)
}

void Application::clearRenterTarget()
{
    // Clear back hdc
    Rectangle(_backHdc, -1, -1, 1601, 901);
}

void Application::copyRenderTarget(HDC sourceHdc, HDC dest)
{
    BitBlt(dest, 0, 0, _width, _height, sourceHdc, 0, 0, SRCCOPY);
}


NAMESPACE_CLOSE;
