#pragma once

#include <iostream>
#include <stdio.h>
/*
    clear_screen=\E[H\E[J
    cursor_address=\E[%i%p1%d;%p2%dH
    set_a_background=\E[4%p1%dm
    set_a_foreground=\E[3%p1%dm
    cursor_invisible=\E[?25l\E[?1c
    cursor_visible=\E[?25h\E[?8c
*/
enum colors {
    BLACK = 0,
    RED,
    GREEN,
    BROWN,
    BLUE,
    PURPLE,
    CYAN,
    LIGHT_GRAY,
};

void escape_commands()
{
    //std::cout << "\E[H\E[J";
    std::cout << "\E[05;10H";//address
    std::cout << "\E[40m\E[31mВлад\E[00m";
    std::cout << "\E[06;8H";//address
    std::cout << "\E[47m\E[32mИП-912";
    std::cout << "\E[010;1H";//address
    std::cout << "\E[00m\n";
    std::cout << "Clear? Y/N\n";
    char c;
    std::cin >> c;
    if(c == 'Y') std::cout << "\E[H\E[J";
}

int mt_clrscr()
{
    if(printf("\E[H\E[J") < 0) {
        return -1;
    }
    return 0;
}

// int mt_gotoXY(int x, int y)
// {
    
// }

int mt_setfgcolor(enum colors fg)
{
    if(printf("\E[3%dm", fg) < 0) {
        return -1;
    }
    return 0;
}

int mt_setbgcolor(enum colors bg)
{
    if(printf("\E[4%dm", bg) < 0) {
        return -1;
    }
    return 0;
}