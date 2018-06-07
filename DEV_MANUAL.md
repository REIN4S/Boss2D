# QT Platform

* Entry Point : 

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

* Event Phase : 

~~~cpp
// Boss2D/helloworld/source/helloworld.cpp

ZAY_VIEW_API OnCommand(...)
ZAY_VIEW_API OnNotify(...)
ZAY_VIEW_API OnGesture(...)
ZAY_VIEW_API OnRender(...)
~~~

