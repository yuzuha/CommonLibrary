#pragma once
#define DIRECTINPUT_VERSION 0x0800
#define WIN32_LEAN_AND_MEAN
#define DIRECTX11_SDK
#define DEBUG_MODE

#include <stdio.h>
#include <winsock2.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <MMSystem.h>
#include <dinput.h>
#include <Dsound.h>
#include <crtdbg.h>
#include <conio.h>
#include <process.h>
#include <vector>
#include <list>
#include <string>
#include <direct.h>

#ifdef DIRECTX11_SDK
#include <d3dx9.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dCompiler.h>
#pragma comment( lib, "dxgi.lib" )
#pragma comment( lib, "d3dx9.lib" )
#pragma comment( lib, "d3d11.lib" )
#pragma comment( lib, "d3dx11.lib")
#pragma comment( lib, "d3dCompiler.lib" )
#endif

#pragma comment( lib, "dsound.lib" )
#pragma comment( lib, "winmm.lib" )
#pragma comment( lib, "dinput8.lib" )
#pragma comment( lib, "dxguid.lib" )
#pragma comment( lib, "ws2_32.lib" )
#pragma comment( lib, "imm32.lib" )

#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }

#define new ::new(_NORMAL_BLOCK,__FILE__,__LINE__)
