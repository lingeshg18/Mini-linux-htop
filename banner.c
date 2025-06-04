#include <ncurses.h>

void draw_banner() {
    
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);    
    init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(3, COLOR_CYAN, COLOR_BLACK);
    init_pair(4, COLOR_WHITE,COLOR_BLACK);
    
    bkgd(COLOR_PAIR(4));
    clear();


    attron(COLOR_PAIR(1));
    mvprintw(1, 5,  " __  __  ");
    mvprintw(2, 5,  "|  \\/  |");
    mvprintw(3, 5,  "| |\\/| |");
    mvprintw(4, 5,  "|_|  |_| ");
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(1));
    mvprintw(1, 14, " ___ ");
    mvprintw(2, 14, "|_ _|");
    mvprintw(3, 14, " _|_ ");
    mvprintw(4, 14, "|___|");
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(1));
    mvprintw(1, 20, " _   _ ");
    mvprintw(2, 20, "| \\ | |");
    mvprintw(3, 20, "|  \\| |");
    mvprintw(4, 20, "|_|\\__|");
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(1));
    mvprintw(1, 28, " ___ ");
    mvprintw(2, 28, "|_ _|");
    mvprintw(3, 28, " _|_ ");
    mvprintw(4, 28, "|___|");
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(2)); 
    mvprintw(1, 36, " _     ");
    mvprintw(2, 36, "| |    ");
    mvprintw(3, 36, "| |___ ");
    mvprintw(4, 36, "|_|___| ");
    attroff(COLOR_PAIR(2));

    attron(COLOR_PAIR(2)); 
    mvprintw(1, 43, " ___ ");
    mvprintw(2, 43, "|_ _|");
    mvprintw(3, 43, " _|_ ");
    mvprintw(4, 43, "|___|");
    attroff(COLOR_PAIR(2));

    attron(COLOR_PAIR(2));
    mvprintw(1, 49, " _   _ ");
    mvprintw(2, 49, "| \\ | |");
    mvprintw(3, 49, "|  \\| |");
    mvprintw(4, 49, "|_|\\__|");
    attroff(COLOR_PAIR(2));

    attron(COLOR_PAIR(2)); 
    mvprintw(1, 57, " _   _ ");
    mvprintw(2, 57, "| | | |");
    mvprintw(3, 57, "| |_| |");
    mvprintw(4, 57, "|_|_|_|");
    attroff(COLOR_PAIR(2));

    attron(COLOR_PAIR(2)); 
    mvprintw(1, 65, "__  __  ");
    mvprintw(2, 65, "\\ \\/ /");
    mvprintw(3, 65, " >  <   ");
    mvprintw(4, 65, "/_/\\_\\");
    attroff(COLOR_PAIR(2));

    attron(COLOR_PAIR(3)); 
    mvprintw(1, 74, " _   _ ");
    mvprintw(2, 74, "| |_| |");
    mvprintw(3, 74, "| |_| |");
    mvprintw(4, 74, "|_| |_|");
    attroff(COLOR_PAIR(3));

    attron(COLOR_PAIR(3)); 
    mvprintw(1, 81, " _____ ");
    mvprintw(2, 81, "|_   _|");
    mvprintw(3, 81, "  | |  ");
    mvprintw(4, 81, "  |_|  ");
    attroff(COLOR_PAIR(3));

    attron(COLOR_PAIR(3)); 
    mvprintw(1, 88, "  ___  ");
    mvprintw(2, 88, " / _ \\ ");
    mvprintw(3, 88, "| |_| |");
    mvprintw(4, 88, " \\___/ ");
    attroff(COLOR_PAIR(3));

    attron(COLOR_PAIR(3)); 
    mvprintw(1, 95, " _____  ");
    mvprintw(2, 95, "|  _  \\ ");
    mvprintw(3, 95, "| |_|_| ");
    mvprintw(4, 95, "|_|     ");
    attroff(COLOR_PAIR(3));


    attron(COLOR_PAIR(4) | A_BOLD);
    mvprintw(6, 5, "MINI LINUX HTOP: A compact, colorful system monitor built in C using ncurses.");
    attroff(COLOR_PAIR(4) | A_BOLD);


    refresh();
}

int main() {
    initscr();            
    noecho();             
    curs_set(FALSE);      

    draw_banner();        

    getch();              
    endwin();             
    return 0;
}
