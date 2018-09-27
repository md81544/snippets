#NoEnv
#Warn
#InstallMouseHook

SendMode Input
SetCapsLockState, AlwaysOff
SetNumLockState,  AlwaysOn

stop = 1
x = 0
y = 0
Menu, Tray, Icon, F:\ahk\green.ico

Pause(times)
{
    global stop
    Loop, %times%
    {
        Sleep, 1000
        if stop = 1
        {
            return
        }
    }
    return
}

Loop
{
    If stop = 0
    {
        Pause(9)
        Random, x, -30, 30
        Random, y, -30, 30
        if ( A_TimeIdlePhysical > 10000 )
        {
            MouseMove, x, y, 100, R
        }
        Pause(1)
        if ( A_TimeIdlePhysical > 10000 )
        {
            MouseMove -x, -y, 100, R
        }
    }
    Else
    {
        Sleep, 300
    }
}

CapsLock & v::
    clp = %clipboard%
    StringReplace, clp, clp, `r,,A
    SendRaw %clp%
    Return

CapsLock & j::
    If stop = 1
        stop = 0
    Else
        stop = 1
    return
