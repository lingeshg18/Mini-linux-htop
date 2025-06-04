#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>
#include <pwd.h>
#include <ncurses.h>
#include <unistd.h>

#define MAX_PROCESSES 1024

void project_banner() {
    
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

typedef struct{
    int pid;
    char user[64];
    float cpu_percent;
    float mem_percent;
    char command[256];
}processinfo;

processinfo processes[MAX_PROCESSES];
int num_processes=0;

unsigned long long prev_total_cpu_time=0;
unsigned long long prev_proc_time[MAX_PROCESSES]={0};

unsigned long long get_total_cpu_time(){
    FILE *fp=fopen("/proc/stat","r");
    if(fp==NULL) return 0;
    unsigned long long user,nice,system,idle,iowait,irq,softirq,steal;
    fscanf(fp,"cpu %llu %llu %llu %llu %llu %llu %llu %llu", &user, &nice, &system, &idle, &iowait, &irq, &softirq, &steal);
    return user + nice + system + idle + iowait + irq + softirq + steal;
}

int get_process_times(int pid,unsigned long long *total_proc_time){
    char path[64],line[256];
    snprintf(path,sizeof(path),"/proc/%d/stat",pid);
    FILE *fp=fopen(path,"r");
    if(fp==NULL) return -1;
    if(!fgets(line,sizeof(line),fp)){
        fclose(fp);
        return -1;
    }

unsigned long utime,stime,cutime,cstime;
char state;
sscanf(line,"%*d %*s %c %*d %*d %*d %*d %*d %*u %*u %*u %*u %*u %lu %lu %lu %lu", &state, &utime, &stime, &cutime, &cstime);
*total_proc_time= (unsigned long long) (utime + stime + cutime + cstime);
return 0;
}

// Get total memory
long total_memory_kb;
void get_total_memory(){
    FILE *fp=fopen("/proc/meminfo","r");
    char line[256];
    while(fgets(line,sizeof(line),fp)){
        if(strncmp(line,"MemTotal:",9)==0){
            sscanf(line,"MemTotal: %ld kB", &total_memory_kb);
            break;
        }
    }
    fclose(fp);
}

void get_process_info(){
    DIR *dir=opendir("/proc");
    struct dirent *entry;
    num_processes=0;
    
    
    unsigned long long total_cpu_time_now=get_total_cpu_time();

    while((entry=readdir(dir))!=NULL){
        if(!isdigit(entry->d_name[0])) continue;
        if(num_processes>=MAX_PROCESSES) break;
    

    // Get PID
    int pid=atoi(entry->d_name);
    processes[num_processes].pid=pid;

    // Get UID
    FILE *fp;
    char path[64],line[256];
    int uid=-1; //uid cannot be negative thus it keeps it as flag value.
    snprintf(path,sizeof(path),"/proc/%d/status",pid);
    fp=fopen(path,"r");
    if(fp==NULL) continue;
    
    while(fgets(line,sizeof(line),fp)){
        if(strncmp(line,"Uid:",4)==0){
            sscanf(line,"Uid:\t%d", &uid);
            break;
        }
    }
    fclose(fp);
    if(uid<0) continue;

    // Convert uid to username
    struct passwd *pw=getpwuid(uid);
    if(pw==NULL) continue;
    strncpy(processes[num_processes].user,pw->pw_name,sizeof(processes[num_processes].user));

    // Get memory usage
    long rss=0;
    long dummy;
    snprintf(path,sizeof(path),"/proc/%d/statm",pid);
    fp=fopen(path,"r");
    if(fp!=NULL){
        fscanf(fp,"%ld %ld", &dummy, &rss);
        fclose(fp);
    }
    long page_size_kb=sysconf(_SC_PAGESIZE)/1024; //Division is done to convert to kB.
    float mem_usage=((float)rss * page_size_kb) / total_memory_kb*100;
    processes[num_processes].mem_percent=mem_usage;

    //Get command line
    snprintf(path,sizeof(path),"/proc/%d/cmdline",pid);
    fp=fopen(path,"r");
    if(fp) {
        size_t len = fread(processes[num_processes].command,1,sizeof(processes[num_processes].command) - 1 ,fp);
        fclose(fp);
        for(size_t j=0;j<len-1;j++){
            if(processes[num_processes].command[j]='\0'){
                processes[num_processes].command[j]=' ';
            }
        }
    }
    // Fallback to comm if cmdline is empty
    if(strlen(processes[num_processes].command) < 2){
        snprintf(path,sizeof(path),"/proc/%d/comm",pid);
        fp=fopen(path,"r");
        if(fp){
            fgets(processes[num_processes].command,sizeof(processes[num_processes].command),fp);
            fclose(fp);
            size_t len = strlen(processes[num_processes].command);
            if(len>0 && processes[num_processes].command[len-1] == '\n'){
                processes[num_processes].command[len-1]='\0';
            }
        }
    }
    //Cpu usage calculation
    unsigned long long total_proc_time=0;
    if(get_process_times(pid,&total_proc_time)==0){
        unsigned long long prev_time=prev_proc_time[num_processes];
        unsigned long long total_cpu_diff=total_cpu_time_now-prev_total_cpu_time;
        unsigned long long proc_time_diff=total_proc_time-prev_time;

        if(prev_total_cpu_time!=0 && total_cpu_diff>0){
            int num_cpus = sysconf(_SC_NPROCESSORS_ONLN);
            processes[num_processes].cpu_percent=100.0f * proc_time_diff / (float) (total_cpu_diff * num_cpus);
        }
        else{
            processes[num_processes].cpu_percent=0.0f;
        }
        prev_proc_time[num_processes]=total_proc_time;
    }
    else{
        processes[num_processes].cpu_percent=0.0f;
        prev_proc_time[num_processes]=0;
    }
    num_processes++;
    }
    closedir(dir);
    prev_total_cpu_time=total_cpu_time_now;
}
// Displaying processes

void display_processes(){
    initscr();
    noecho();
    curs_set(FALSE);

    project_banner();
    
    getch();

    while(1){
        clear();
        mvprintw(0,0,"%-6s %-10s %-6s %-6s %-s","PID","USER","CPU%","MEM%","COMMAND");

        for(int i=0;i<num_processes;i++){
           int color_pair = 5; // Gives green
           if (processes[i].cpu_percent >= 0.50)
           color_pair = 7; //Gives red
           else if (processes[i].cpu_percent >= 1.0)
           color_pair = 6; //Gives yellow
           
           attron(COLOR_PAIR(color_pair));
           mvprintw(i + 1, 0, "%-6d %-10s %-6.2f %-6.2f %-0.50s",
            processes[i].pid,
            processes[i].user,
            processes[i].cpu_percent,
            processes[i].mem_percent,
            processes[i].command);
            attroff(COLOR_PAIR(color_pair));
        }
        refresh();
        sleep(1);
        get_process_info();
    }
    endwin();
}
int main(){
    
    get_total_memory();
    get_process_info();
    display_processes();
    return 0;
}



