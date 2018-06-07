# QT Platform

## Entry Point

* Framework Side : 

~~~cpp
// Boss2D/Boss2D/platform/boss_platform_qt5.cpp
// 132 LINE
#if BOSS_NEED_MAIN
    extern void PlatformInit();
    extern void PlatformQuit();

    int main(int argc, char* argv[])
    {
        int result = 0;
        {
            QApplication app(argc, argv);
            MainWindow mainWindow;
            g_window = &mainWindow;

            Platform::Option::SetFlag("AssertPopup", !BOSS_IPHONE);
            PlatformInit();
            #if BOSS_NEED_FULLSCREEN
                mainWindow.showFullScreen();
            #else
                mainWindow.show();
            #endif
            result = app.exec();
            PlatformQuit();
            Platform::Option::SetFlag("AssertPopup", false);

            g_window = nullptr;
        }
        Storage::ClearAll(CL_SystemAndUser);
        return result;
    }
#endif
~~~

* Project Side : 

~~~cpp
// Boss2D/helloworld/source/main.cpp

void PlatformInit() { ... }
void PlatformQuit() { ... }
~~~

## Event Phase
 
* Framework Side : 

~~~cpp
// Boss2D/Boss2D/service/boss_zay.hpp
// LINE 119 ~ 142 : 이벤트 함수 선언.
#define ZAY_VIEW_API static void
#define ZAY_DECLARE_VIEW(NAME) ZAY_DECLARE_VIEW_CLASS(NAME, ZayObject)
#define ZAY_DECLARE_VIEW_CLASS(NAME, CLASS) \
    ZAY_VIEW_API OnCommand(CommandType, chars, id_share, id_cloned_share*); \
    ZAY_VIEW_API OnNotify(chars, chars, id_share, id_cloned_share*); \
    ZAY_VIEW_API OnGesture(GestureType, sint32, sint32); \
    ZAY_VIEW_API OnRender(ZayPanel&); \
    ...

// Boss2D/Boss2D/service/boss_zay.cpp
// LINE 5 ~ 9 : 이벤트 함수 정의.
ZAY_VIEW_API OnCommand(CommandType, chars, id_share, id_cloned_share*) {}
ZAY_VIEW_API OnNotify(chars, chars, id_share, id_cloned_share*) {}
ZAY_VIEW_API OnGesture(GestureType, sint32, sint32) {}
ZAY_VIEW_API OnRender(ZayPanel& panel)
{ZAY_RGB(panel, 0x80, 0x80, 0x80) panel.fill();}
~~~

* Project Side : 

~~~cpp
// Boss2D/helloworld/source/helloworld.cpp

ZAY_VIEW_API OnCommand(...)
ZAY_VIEW_API OnNotify(...)
ZAY_VIEW_API OnGesture(...)
ZAY_VIEW_API OnRender(...)
~~~

* Dependency : 

~~~
[service/boss_zay.hpp] <-- [helloworld.hpp] <-- [helloworld.cpp]
                    ^
                    ㄴ---- [boss_zay.cpp]
~~~                    

프로젝트 측에서는 boss_zay.cpp 구현을 사용 안함.
